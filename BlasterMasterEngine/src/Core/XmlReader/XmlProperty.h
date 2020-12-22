#pragma once

class XmlProperty
{
public:
    XmlProperty();
    ~XmlProperty();

    // Parse a node containing all the property nodes.
    void Parse(const tinyxml2::XMLNode* propertiesNode);

    // Get a int property.
    int GetIntProperty(const std::string& name, int defaultValue = 0) const;
    // Get a float property.
    float GetFloatProperty(const std::string& name, float defaultValue = 0.0f) const;

    // Get a string property. Returns "" if no value.
    std::string GetStringProperty(const std::string& name) const;

    // Returns the amount of properties.
    int GetSize() const { return (int)properties.size(); }

    bool HasProperty(const std::string& name) const;

    // Returns the STL map of the properties.
    std::map< std::string, std::string > GetList() const
    {
        return properties;
    }

    // Returns whether there are no properties.
    bool Empty() const { return properties.empty(); }

private:
    std::map< std::string, std::string > properties;
};