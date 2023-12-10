// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include "PluginInterface.h"
#include "InfoItem.h"

#endif //PCH_H

#using "LegionInfoDLL.dll"

#pragma managed

using namespace LegionInfoDLL;

class LegionPlugin : public ITMPlugin
{
public:
    static LegionPlugin& Instance();

    virtual IPluginItem* GetItem(int index) override;
    virtual const wchar_t* GetTooltipInfo() override;
    virtual void DataRequired() override;
    virtual OptionReturn ShowOptionsDialog(void* hParent) override;
    virtual const wchar_t* GetInfo(PluginInfoIndex index) override;
    virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data) override;
    virtual void* GetPluginIcon() override;

private:
    LegionPlugin();

private:
    static LegionPlugin m_instance;
    //CBatteryItem m_item;
    std::wstring m_tooltop_info;
public:
    InfoItem* cpuFanItem;
    InfoItem* gpuFanItem;
};

#ifdef __cplusplus
extern "C" {
#endif
#include <string>
    __declspec(dllexport) ITMPlugin* TMPluginGetInstance();
#ifdef __cplusplus
}
#endif

constexpr auto CPU_FAN_SPEED = 0;
constexpr auto GPU_FAN_SPEED = 1;

constexpr auto ITEM_CPU_FAN_SPEED = 0;
constexpr auto ITEM_GPU_FAN_SPEED = 1;
