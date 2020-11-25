#pragma once
#include "XmlProperty.h"
class XmlObject
{
public:
    XmlObject();
    ~XmlObject();

    void Parse(const tinyxml2::XMLNode* objectNode);

    const std::string& GetName() const { return name; }

    const std::string& GetType() const { return type; }

    int GetX() const { return x; }

    int GetY() const { return y; }

    int GetWidth() const { return width; }

    int GetHeight() const { return height; }

    double GetRot() const { return rotation; }

    int GetGid() const { return gid; }

    int GetId() const { return id; }

    bool IsVisible() const { return visible; }

private:
    std::string name;
    std::string type;

    int x;
    int y;
    int width;
    int height;
    int gid;
    int id;

    double rotation;
    bool visible;

    XmlProperty property;
};