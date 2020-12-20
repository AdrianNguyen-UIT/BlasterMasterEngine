#include "d3dpch.h"
#include "XmlObject.h"

XmlObject::XmlObject()
    : name()
    , type()
    , x(0)
    , y(0)
    , width(0)
    , height(0)
    , gid(0)
    , id(0)
    , rotation(0.0)
    , visible(true)
    , property()
{}

XmlObject::~XmlObject()
{
}

void XmlObject::Parse(const tinyxml2::XMLNode* objectNode)
{
    const tinyxml2::XMLElement* objectElem = objectNode->ToElement();

    // Read the attributes of the object.
    const char* tempName = objectElem->Attribute("name");
    const char* tempType = objectElem->Attribute("type");

    if (tempName) name = tempName;
    if (tempType) type = tempType;

    id = objectElem->IntAttribute("id");
    x = objectElem->IntAttribute("x");
    y = objectElem->IntAttribute("y");
    width = objectElem->IntAttribute("width");
    height = objectElem->IntAttribute("height");
    gid = objectElem->IntAttribute("id");
    rotation = objectElem->IntAttribute("rotation");
    objectElem->QueryBoolAttribute("visible", &visible);

    // Read the properties of the object.
    const tinyxml2::XMLNode* propertiesNode = objectNode->FirstChildElement("properties");
    if (propertiesNode)
    {
        property.Parse(propertiesNode);
    }
}