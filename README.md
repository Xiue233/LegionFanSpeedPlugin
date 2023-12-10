An easy traffic monitor plugin of showing fan speed in Lenovo Legion Laptop.

Thanks to [LenovoLegionToolkit](https://github.com/BartoszCichecki/LenovoLegionToolkit), which offers the method to get fan speed. And its developer gave me a hand.

Because I had never develop with C++ or C#, the code maybe ugly and silly.

## [Usage]

Put LegionInfoDLL.dll in the same directory with traffic-monitor.exe.

Put LegionInfoPlugin.dll in the plugins directory of traffic monitor.

## [Code]

First, I use C# to develop a dll to offer GetCurrentFanSpeed() api to C++ dll plugin, just because C# invokes wmi method is easy while it is more inconvenient to invkoe wmi methods in C++.

Then just develop taffic monitor plugin. But it is important to add .Net Framework Runtime Support(./clr) for C++ dll plugin without which C# dll can not use .Net to invoke wmi methods.

## [Wmi]


NameSpace: root\WMI

Class: LENOVO_FAN_METHOD

Method: Fan_GetCurrentFanSpeed(System.Byte FanID) => int Speed
