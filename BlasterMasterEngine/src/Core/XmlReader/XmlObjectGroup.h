#pragma once
#include "XmlObject.h"

class XmlObjectGroup
{
public:
    XmlObjectGroup();
    ~XmlObjectGroup();

    void Parse(const tinyxml2::XMLNode* objectGroupNode);

    const XmlObject& GetObject(int index) const { return objects.at(index); }

    int GetNumObjects() const { return (int)objects.size(); }

    const std::string& GetColor() const { return color; }

    const std::vector<XmlObject>& GetObjects() const { return objects; }

    const std::string& GetName() const { return name; }

    int GetX() const { return x; }

    int GetY() const { return y; }

    int GetWidth() const { return width; }

    int GetHeight() const { return height; }

    float GetOpacity() const { return opacity; }

    bool IsVisible() const { return visible; }

    const XmlProperty& GetProperties() const { return property; }

    int GetZOrder() const { return zOrder; }

    void SetZOrder(int z) { zOrder = z; }

    int GetParseOrder() const { return parseOrder; }

private:
    std::string name;

    int x;
    int y;
    int width;
    int height;

    float opacity;
    bool visible;
    int zOrder;
    int parseOrder;

    XmlProperty property;

    static int nextParseOrder;

    std::string color;

    std::vector<XmlObject> objects;
};