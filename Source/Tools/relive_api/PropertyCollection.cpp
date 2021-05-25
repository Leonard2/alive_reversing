#include "PropertyCollection.hpp"

#include "relive_api.hpp"
#include "BaseProperty.hpp"
#include "TypedProperty.hpp"

#include "../AliveLibCommon/stdafx_common.h"

#include <jsonxx/jsonxx.h>

void PropertyCollection::ThrowOnAddPropertyError(const std::string& name, const std::string& typeName, void* key)
{
    if (name.empty())
    {
        throw ReliveAPI::EmptyPropertyNameException();
    }

    if (typeName.empty())
    {
        throw ReliveAPI::EmptyTypeNameException();
    }

    if (mProperties.find(key) != mProperties.end())
    {
        throw ReliveAPI::DuplicatePropertyKeyException();
    }

    if (mRegisteredPropertyNames.find(name) != mRegisteredPropertyNames.end())
    {
        throw ReliveAPI::DuplicatePropertyNameException(name.c_str());
    }
}

PropertyCollection::~PropertyCollection() = default;

[[nodiscard]] const std::string& PropertyCollection::PropType(const void* key) const
{
    const auto it = mProperties.find(key);

    if (it == mProperties.end())
    {
        throw ReliveAPI::PropertyNotFoundException();
    }

    return it->second->TypeName();
}

[[nodiscard]] const std::string& PropertyCollection::PropName(const void* key) const
{
    const auto it = mProperties.find(key);

    if (it == mProperties.end())
    {
        throw ReliveAPI::PropertyNotFoundException();
    }

    return it->second->Name();
}

[[nodiscard]] jsonxx::Array PropertyCollection::PropertiesToJson() const
{
    jsonxx::Array ret;

    for (const auto& [key, value] : mProperties)
    {
        jsonxx::Object property;
        property << "Type" << value->TypeName();
        property << "Visible" << value->IsVisibleToEditor();
        property << "name" << value->Name();

        ret << property;
    }

    return ret;
}

void PropertyCollection::PropertiesFromJson(const TypesCollectionBase& types, const jsonxx::Object& properties)
{
    for (auto& [Key, value] : mProperties)
    {
        value->Read(*this, types, properties);
    }
}

void PropertyCollection::PropertiesToJson(const TypesCollectionBase& types, jsonxx::Object& properties)
{
    for (auto& [Key, value] : mProperties)
    {
        value->Write(*this, types, properties);
    }
}


// Special handling for special types.
#include "../AliveLibCommon/SwitchStates_common.hpp"

template<>
void PropertyCollection::ReadBasicType<SwitchId>(SwitchId& field, const jsonxx::Object& properties) const
{
    field.mId = static_cast<u8>(properties.get<jsonxx::Number>(PropName(&field)));
}

template <>
void PropertyCollection::WriteBasicType<SwitchId>(const SwitchId& field, jsonxx::Object& properties) const
{
    properties << PropName(&field) << static_cast<s32>(field.mId);
}
