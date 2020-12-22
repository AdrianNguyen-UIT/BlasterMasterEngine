#pragma once
#include "XmlObjectGroup.h"

class XmlMap
{
    enum MapError
    {
        // A file could not be opened. (usually due to permission problems)
        XML_COULDNT_OPEN = 0x01,

        // There was an error in parsing the TMX file.
        // This is being caused by TinyXML parsing problems.
        XML_PARSING_ERROR = 0x02,

        // The size of the file is invalid.
        XML_INVALID_FILE_SIZE = 0x04
    };

    //-------------------------------------------------------------------------
    // The way the map is viewed.
    //-------------------------------------------------------------------------
    enum MapOrientation
    {
        // This map is an orthogonal map.
        XML_MO_ORTHOGONAL = 0x01,

        // This map is an isometric map.
        XML_MO_ISOMETRIC = 0x02,

        // This map is an isometric staggered map.
        XML_MO_STAGGERED = 0x03,

        // This map is an hexagonal staggered map.
        XML_MO_HEXAGONAL = 0x04
    };

    //-------------------------------------------------------------------------
    // The order in which tiles on tile layers are rendered.
    //-------------------------------------------------------------------------
    enum MapRenderOrder
    {
        // The default is TMX_RIGHT_DOWN.
        XML_RIGHT_DOWN = 0x01,
        XML_RIGHT_UP = 0x02,
        XML_LEFT_DOWN = 0x03,
        XML_LEFT_UP = 0x03
    };

    //-------------------------------------------------------------------------
    // The stagger axis for the map. (only applies to hexagonal maps)
    //-------------------------------------------------------------------------
    enum MapStaggerAxis
    {
        XML_SA_NONE = 0x00,  // if the map is not hexagonal
        XML_SA_X = 0x01,
        XML_SA_Y = 0x02
    };

    //-------------------------------------------------------------------------
    // The stagger index for the map. (applies to hexagonal AND isometric staggered maps)
    //-------------------------------------------------------------------------
    enum MapStaggerIndex
    {
        XML_SI_NONE = 0x00,  // if the map is not hexagonal
        XML_SI_EVEN = 0x01,
        XML_SI_ODD = 0x02
    };

private:
    // Prevent copy constructor.
    XmlMap(const XmlMap& _map);

public:
    XmlMap();
    ~XmlMap();

    // Read a file and parse it.
    // Note: use '/' instead of '\\' as it is using '/' to find the path.
    void ParseFile(const std::string& fileName);

    void ParseText(const std::string& text);

    const std::string& GetFilename() { return file_name; }

    const std::string& GetFilepath() const { return file_path; }

    const std::string& GetBackgroundColor() const { return background_color; }

    double GetVersion() const { return version; }

    MapOrientation GetOrientation() const { return orientation; }

    MapRenderOrder GetRenderOrder() const { return render_order; }

    MapStaggerAxis GetStaggerAxis() const { return stagger_axis; }

    MapStaggerIndex GetStaggerIndex() const { return stagger_index; }

    int GetWidth() const { return width; }

    int GetHeight() const { return height; }

    int GetTileWidth() const { return tile_width; }

    int GetTileHeight() const { return tile_height; }

    int GetNextObjectId() const { return next_object_id; }

    int GetHexsideLength() const { return hexside_length; }

    const XmlObjectGroup &GetObjectGroup(int index) const { return object_groups.at(index); }

    int GetNumObjectGroups() const { return (int)object_groups.size(); }

    const std::vector<XmlObjectGroup> &GetObjectGroups() const { return object_groups; }

    bool HasError() const { return has_error; }

    const std::string& GetErrorText() const { return error_text; }

    unsigned char GetErrorCode() const { return error_code; }
private:
    std::string file_name;
    std::string file_path;

    std::string background_color;

    double version;
    MapOrientation orientation;
    MapRenderOrder render_order;
    MapStaggerAxis stagger_axis;
    MapStaggerIndex stagger_index;

    int width;
    int height;
    int tile_width;
    int tile_height;
    int next_object_id;
    int hexside_length;

    std::vector<XmlObjectGroup> object_groups;

    bool has_error;
    unsigned char error_code;
    std::string error_text;

    // Parse a 'map' node.
    void Parse(tinyxml2::XMLNode* mapNode);
};