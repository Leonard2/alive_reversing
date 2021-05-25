#include "../AliveLibCommon/stdafx_common.h"
#include "TypesCollectionBase.hpp"
#include "TlvObjectBase.hpp"
#include "../AliveLibAO/PathData.hpp"
#include "../AliveLibAO/Map.hpp"
#include "../AliveLibAE/Path.hpp"
#include "../AliveLibCommon/SwitchStates_common.hpp"


TypesCollectionBase::TypesCollectionBase()
{
#define ADD_BASIC_TYPE(name, type) AddBasicType<type>(name, std::numeric_limits<type>::min(), std::numeric_limits<type>::max());

    ADD_BASIC_TYPE("Byte", u8);
    ADD_BASIC_TYPE("UInt16", u16);
    ADD_BASIC_TYPE("SInt16", s16);
    ADD_BASIC_TYPE("Uint32", u32);
    ADD_BASIC_TYPE("SInt32", s32);

#undef ADD_BASIC_TYPE

    // Common types.
    // Should we put these elsewhere?
    AddBasicType<SwitchId>("SwitchID", std::numeric_limits<u8>::min(), std::numeric_limits<u8>::max());
    AddEnum<SwitchOp>("Enum_SwitchOp",
    {
        {SwitchOp::eSetTrue_0, "SetTrue"},
        {SwitchOp::eSetFalse_1, "SetFalse"},
        {SwitchOp::eToggle_2, "Toggle"},
        {SwitchOp::eIncrement_3, "Increment"},
        {SwitchOp::eDecrement_4, "Decrement"},
    });
}

TypesCollectionBase::~TypesCollectionBase() = default;

[[nodiscard]] jsonxx::Array TypesCollectionBase::EnumsToJson() const
{
    jsonxx::Array ret;

    for (const auto& basicType : mTypes)
    {
        if (!basicType->IsBasicType())
        {
            basicType->ToJson(ret);
        }
    }

    return ret;
}

[[nodiscard]] jsonxx::Array TypesCollectionBase::BasicTypesToJson() const
{
    jsonxx::Array ret;

    for (const auto& basicType : mTypes)
    {
        if (basicType->IsBasicType())
        {
            basicType->ToJson(ret);
        }
    }

    return ret;
}

[[nodiscard]] const std::string& TypesCollectionBase::TypeName(const std::type_index& typeIndex) const
{
    const ITypeBase* ptr = FindByTypeIndex(typeIndex);
    return ptr != nullptr ? ptr->Name() : mEmptyStr;
}

[[nodiscard]] ITypeBase* TypesCollectionBase::RegisterType(ITypeBase* typeBase)
{
    std::unique_ptr<ITypeBase>& emplaced = mTypes.emplace_back(typeBase);
    mTypesByName[typeBase->Name()] = mTypesByTypeIndex[typeBase->TypeIndex()] = emplaced.get();
    return emplaced.get();
}

[[nodiscard]] const ITypeBase* TypesCollectionBase::FindByTypeName(const std::string& typeName) const
{
    const auto it = mTypesByName.find(typeName);
    return it != mTypesByName.end() ? it->second : nullptr;
}

[[nodiscard]] const ITypeBase* TypesCollectionBase::FindByTypeIndex(const std::type_index& typeIndex) const
{
    const auto it = mTypesByTypeIndex.find(typeIndex);
    return it != mTypesByTypeIndex.end() ? it->second : nullptr;
}
