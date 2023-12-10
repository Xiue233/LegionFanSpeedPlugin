// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

static int LoadFanSpeed(int fanID) {
    return LegionInfoDLL::Fan::GetFanSpeed(fanID);
}

static void LoadData(LegionPlugin& plugin) {
    plugin.cpuFanItem->itemValueText.assign(std::to_wstring(LoadFanSpeed(CPU_FAN_SPEED)).append(L" RPM"));
    plugin.gpuFanItem->itemValueText.assign(std::to_wstring(LoadFanSpeed(GPU_FAN_SPEED)).append(L" RPM"));
}

LegionPlugin::LegionPlugin()
{
    cpuFanItem = new InfoItem();
    cpuFanItem->itemId = L"LegionInfo_CPUFan";
    cpuFanItem->itemLableText = L"CPU Fan: ";
    cpuFanItem->itemName = L"CPU风扇风速";
    cpuFanItem->itemValueSampleText = L"2100 RPM";
    cpuFanItem->itemValueText = L"Loading";
    gpuFanItem = new InfoItem();
    gpuFanItem->itemId = L"LegionInfo_GPUFan";
    gpuFanItem->itemLableText = L"GPU Fan: ";
    gpuFanItem->itemName = L"GPU风扇风速";
    gpuFanItem->itemValueSampleText = L"2100 RPM";
    gpuFanItem->itemValueText = L"Loading";
}

LegionPlugin LegionPlugin::m_instance;

LegionPlugin& LegionPlugin::Instance()
{
    return m_instance;
}

ITMPlugin* TMPluginGetInstance()
{
    return &LegionPlugin::Instance();
}

IPluginItem* LegionPlugin::GetItem(int index)
{
    switch (index)
    {
    case ITEM_CPU_FAN_SPEED:
        return cpuFanItem;
    case ITEM_GPU_FAN_SPEED:
        return gpuFanItem;
    default:
        break;
    }
    return nullptr;
}

const wchar_t* LegionPlugin::GetTooltipInfo()
{
    return L"";
}

void LegionPlugin::DataRequired()
{
    LoadData(*this);
}

ITMPlugin::OptionReturn LegionPlugin::ShowOptionsDialog(void* hParent)
{
    return OptionReturn();
}

const wchar_t* LegionPlugin::GetInfo(PluginInfoIndex index)
{
    return nullptr;
}

void LegionPlugin::OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data)
{
}

void* LegionPlugin::GetPluginIcon()
{
    return nullptr;
}

