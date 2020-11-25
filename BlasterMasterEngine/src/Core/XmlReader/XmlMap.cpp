#include "d3dpch.h"
#include "XmlMap.h"

XmlMap::XmlMap()
{
    version = 0.0;
    orientation = MapOrientation::XML_MO_ORTHOGONAL;
    render_order = MapRenderOrder::XML_RIGHT_DOWN;
    stagger_axis = MapStaggerAxis::XML_SA_NONE;
    stagger_index = MapStaggerIndex::XML_SI_NONE;
    width = 0;
    height = 0;
    tile_width = 0;
    tile_height = 0;
    next_object_id = 0;
    hexside_length = 0;
    has_error = false;
    error_code = 0;
}

XmlMap::~XmlMap()
{
}

void XmlMap::ParseFile(const std::string& fileName)
{
    file_name = fileName;

    int lastSlash = fileName.find_last_of("/");

    // Get the directory of the file using substring.
    if (lastSlash > 0)
    {
        file_path = fileName.substr(0, lastSlash + 1);
    }
    else
    {
        file_path = "";
    }

    // Create a tiny xml document and use it to parse the text.
    tinyxml2::XMLDocument doc;
    doc.LoadFile(fileName.c_str());

    // Check for parsing errors.
    if (doc.Error())
    {
        has_error = true;
        error_code = MapError::XML_PARSING_ERROR;
        error_text = doc.ErrorStr();
        return;
    }

    tinyxml2::XMLNode* mapNode = doc.FirstChildElement("map");
    Parse(mapNode);
}

void XmlMap::ParseText(const std::string& text)
{
    // Create a tiny xml document and use it to parse the text.
    tinyxml2::XMLDocument doc;
    doc.Parse(text.c_str());

    // Check for parsing errors.
    if (doc.Error())
    {
        has_error = true;
        error_code = MapError::XML_PARSING_ERROR;
        error_text = doc.ErrorStr();
        return;
    }

    tinyxml2::XMLNode* mapNode = doc.FirstChildElement("map");
    Parse(mapNode);
}


void XmlMap::Parse(tinyxml2::XMLNode* mapNode)
{
    tinyxml2::XMLElement* mapElem = mapNode->ToElement();

    // Read the map attributes.
    version = mapElem->IntAttribute("version");
    width = mapElem->IntAttribute("width");
    height = mapElem->IntAttribute("height");
    tile_width = mapElem->IntAttribute("tilewidth");
    tile_height = mapElem->IntAttribute("tileheight");
    next_object_id = mapElem->IntAttribute("nextobjectid");

    if (mapElem->Attribute("backgroundcolor"))
    {
        background_color = mapElem->Attribute("backgroundcolor");
    }

    // Read the orientation
    std::string orientationStr = mapElem->Attribute("orientation");

    if (!orientationStr.compare("orthogonal"))
    {
        orientation = MapOrientation::XML_MO_ORTHOGONAL;
    }
    else if (!orientationStr.compare("isometric"))
    {
        orientation = MapOrientation::XML_MO_ISOMETRIC;
    }
    else if (!orientationStr.compare("staggered"))
    {
        orientation = MapOrientation::XML_MO_STAGGERED;
    }
    else if (!orientationStr.compare("hexagonal"))
    {
        orientation = MapOrientation::XML_MO_HEXAGONAL;
    }

    // Read the render order
    if (mapElem->Attribute("renderorder"))
    {
        std::string renderorderStr = mapElem->Attribute("renderorder");
        if (!renderorderStr.compare("right-down"))
        {
            render_order = MapRenderOrder::XML_RIGHT_DOWN;
        }
        else if (!renderorderStr.compare("right-up"))
        {
            render_order = MapRenderOrder::XML_RIGHT_UP;
        }
        else if (!renderorderStr.compare("left-down"))
        {
            render_order = MapRenderOrder::XML_LEFT_DOWN;
        }
        else if (!renderorderStr.compare("left-down"))
        {
            render_order = MapRenderOrder::XML_LEFT_UP;
        }
    }

    // Read the stagger axis
    if (mapElem->Attribute("staggeraxis"))
    {
        std::string staggerAxisStr = mapElem->Attribute("staggeraxis");
        if (!staggerAxisStr.compare("x"))
        {
            stagger_axis = MapStaggerAxis::XML_SA_X;
        }
        else if (!staggerAxisStr.compare("y"))
        {
            stagger_axis = MapStaggerAxis::XML_SA_Y;
        }
    }

    // Read the stagger index
    if (mapElem->Attribute("staggerindex"))
    {
        std::string staggerIndexStr = mapElem->Attribute("staggerindex");
        if (!staggerIndexStr.compare("even"))
        {
            stagger_index = MapStaggerIndex::XML_SI_EVEN;
        }
        else if (!staggerIndexStr.compare("odd"))
        {
            stagger_index = MapStaggerIndex::XML_SI_ODD;
        }
    }

    // read the hexside length
    if (mapElem->IntAttribute("hexsidelength"))
    {
        hexside_length = mapElem->IntAttribute("hexsidelength");
    }

    // read all other attributes
    const tinyxml2::XMLNode* node = mapElem->FirstChild();
    while (node)
    {
        // Iterate through all of the "objectgroup" (object layer) elements.
        if (strcmp(node->Value(), "objectgroup") == 0)
        {
            // Allocate a new object group and parse it.
            XmlObjectGroup objectGroup;
            objectGroup.Parse(node);

            // Add the object group to the lists.
            object_groups.emplace_back(objectGroup);
        }

        node = node->NextSibling();
    }
}