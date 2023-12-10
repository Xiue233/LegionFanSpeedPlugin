using System;
using System.Collections.Generic;
using System.Linq;
using System.Management;

namespace LegionInfoDLL
{
    public static class Fan
    {
        public static int GetFanSpeed(int fanID)
        {
            var speed = -1;
            try// Get the client's SMS_Client class.  
            {
                speed = Call("root\\WMI",
                    $"SELECT * FROM LENOVO_FAN_METHOD",
                    "Fan_GetCurrentFanSpeed",
                    new Dictionary<string, object>() { { "FanID", fanID } },
                    pdc => Convert.ToInt32(pdc["CurrentFanSpeed"].Value));
            }
            catch (Exception ignore)
            {
                return -1;
            }
            return speed;
        }

        private static T Call<T>(string scope, FormattableString query, string methodName, Dictionary<string, object> methodParams, Func<PropertyDataCollection, T> converter)
        {
            try
            {
                var queryFormatted = query.ToString(WMIPropertyValueFormatter.Instance);

                var mos = new ManagementObjectSearcher(scope, queryFormatted);
                var managementObject = mos.Get().Cast<ManagementBaseObject>().FirstOrDefault() ?? throw new InvalidOperationException("No results in query");

                var mo = (ManagementObject)managementObject;
                var methodParamsObject = mo.GetMethodParameters(methodName);
                foreach (var pair in methodParams)
                    methodParamsObject[pair.Key] = pair.Value;

                var resultProperties = mo.InvokeMethod(methodName, methodParamsObject, new InvokeMethodOptions());
                var result = converter(resultProperties.Properties);
                return result;
            }
            catch (ManagementException ex)
            {
                throw new ManagementException($"Call failed: {ex.Message}. [scope={scope}, query={query}, methodName={methodName}]", ex);
            }
        }

        private class WMIPropertyValueFormatter : IFormatProvider, ICustomFormatter
        {
            public static readonly WMIPropertyValueFormatter Instance = new WMIPropertyValueFormatter();

            private WMIPropertyValueFormatter() { }

            public object GetFormat(Type formatType)
            {
                if (formatType == typeof(ICustomFormatter))
                    return this;

                throw new InvalidOperationException("Invalid type of formatted");
            }

            public string Format(string format, object arg, IFormatProvider formatProvider)
            {
                var stringArg = arg?.ToString()?.Replace("\\", "\\\\");
                return stringArg ?? string.Empty;
            }
        }
    }
}
