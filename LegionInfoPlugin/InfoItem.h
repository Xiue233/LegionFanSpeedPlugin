#pragma once
#include "PluginInterface.h"
#include <string>

class InfoItem : public IPluginItem
{
public:
    InfoItem();

    const wchar_t* GetItemName() const override {
        return itemName;
     }
    const wchar_t* GetItemId() const override {
        return itemId;
     }
    const wchar_t* GetItemLableText() const override {
        return itemLableText;
     }
    const wchar_t* GetItemValueText() const override {
        return itemValueText.c_str();
     }
    const wchar_t* GetItemValueSampleText() const override {
        return itemValueSampleText;
     }
    bool IsCustomDraw() const override {
        return false;
    }

    const wchar_t* itemName;
    const wchar_t* itemId;
    const wchar_t* itemLableText;
    std::wstring itemValueText;
    const wchar_t* itemValueSampleText;
};