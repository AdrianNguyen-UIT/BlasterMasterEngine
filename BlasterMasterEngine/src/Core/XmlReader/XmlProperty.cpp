#include "d3dpch.h"
#include "XmlProperty.h"

XmlProperty::XmlProperty() : properties()
{}

XmlProperty::~XmlProperty()
{
    properties.clear();
}

void XmlProperty::Parse(const tinyxml2::XMLNode* propertiesNode)
{
    // Iterate through all of the property nodes.
    const tinyxml2::XMLNode* propertyNode = propertiesNode->FirstChildElement("property");
    std::string propertyName;
    std::string propertyValue;

    while (propertyNode)
    {
        const tinyxml2::XMLElement* propertyElem = propertyNode->ToElement();

        // Read the attributes of the property and add it to the map
        propertyName = std::string(propertyElem->Attribute("name"));
        propertyValue = std::string(propertyElem->Attribute("value"));
        properties[propertyName] = propertyValue;

        //propertyNode = propertiesNode->IterateChildren("property", propertyNode); FIXME MAYBE
        propertyNode = propertyNode->NextSiblingElement("property");
    }
}

std::string XmlProperty::GetStringProperty(const std::string& name) const
{
    std::map< std::string, std::string >::const_iterator iter = properties.find(name);

    if (iter == properties.end())
        return std::string();

    return iter->second;
}

int XmlProperty::GetIntProperty(const std::string& name, int defaultValue) const
{
    std::string str = GetStringProperty(name);
    return (str.size() == 0) ? defaultValue : atoi(GetStringProperty(name).c_str());
}

float XmlProperty::GetFloatProperty(const std::string& name, float defaultValue) const
{
    std::string str = GetStringProperty(name);
    return (str.size() == 0) ? defaultValue : atof(GetStringProperty(name).c_str());
}

bool XmlProperty::HasProperty(const std::string& name) const
{
    if (properties.empty()) return false;
    return (properties.find(name) != properties.end());
}
