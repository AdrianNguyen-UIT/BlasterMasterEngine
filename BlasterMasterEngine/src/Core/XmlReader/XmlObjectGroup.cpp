#include "d3dpch.h"
#include "XmlObjectGroup.h"

int XmlObjectGroup::nextParseOrder = 0;

XmlObjectGroup::XmlObjectGroup()
{
    name = std::string();
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    opacity = 1.0f;
    visible = true;
    zOrder = nextParseOrder;
    parseOrder = nextParseOrder;
    ++nextParseOrder;
}

XmlObjectGroup::~XmlObjectGroup()
{
}

void XmlObjectGroup::Parse(const tinyxml2::XMLNode* objectGroupNode)
{
    const tinyxml2::XMLElement* objectGroupElem = objectGroupNode->ToElement();

    name = objectGroupElem->Attribute("name");

    if (objectGroupElem->Attribute("color"))
    {
        color = objectGroupElem->Attribute("color");
    }

    objectGroupElem->QueryFloatAttribute("opacity", &opacity);
    objectGroupElem->QueryBoolAttribute("visible", &visible);

    const tinyxml2::XMLNode* propertiesNode = objectGroupNode->FirstChildElement("properties");
    if (propertiesNode)
    {
        property.Parse(propertiesNode);
    }

    const tinyxml2::XMLNode* objectNode = objectGroupNode->FirstChildElement("object");
    while (objectNode)
    {
        XmlObject object;
        object.Parse(objectNode);

        objects.emplace_back(object);

        objectNode = objectNode->NextSiblingElement("object");
    }
}