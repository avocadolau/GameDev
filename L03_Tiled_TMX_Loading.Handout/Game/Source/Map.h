#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"

// L03: TODO 2: Create a struct to hold information for a TileSet
// Ignore Wangsets and Tile Types for now, but we want the image!
struct TileSet
{
    int firstID;
    SString name;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int tileCount;
    int columns;
    SString imgSrc;
    int imageWidth;
    int imageHeight;
    SDL_Texture* texture;
};

// L03: TODO 1: Create a struct needed to hold the information to Map node
struct MapData
{
    SString mapVersion;
    SString tiledVersion;
    SString orientation;
    SString renderOrder;
    int width;
    int height;
    int tileWidth;
    int tileheight;
    int infinite;
    int nextLayerid;
    int nextObjesctid;
    List<TileSet*> tilesets;
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);


public:
    MapData mapData;

private:

    // L03: TODO 3: Implement LoadMap to load the map properties
	bool LoadMap(pugi::xml_node mapFile);

	// L03: TODO 4: Implement the LoadTileSet function to load the tileset
	bool LoadTileSet(pugi::xml_node mapFile);

	// L03: TODO 1: Declare a variable data of the struct MapData
	

    SString folder;
    bool mapLoaded;
    
};

#endif // __MAP_H__