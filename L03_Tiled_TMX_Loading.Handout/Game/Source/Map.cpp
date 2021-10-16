
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>
#include "SDL_image/include/SDL_image.h"

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

void Map::Draw()
{
    if(mapLoaded == false)
        return;

    // L03: TODO 6: Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)
    ListItem<TileSet*>* item;
    item = mapData.tilesets.start;
    while (item != NULL)
    {
        app->render->DrawTexture(item->data->texture, 0, 0);

        item = item->next;
    }
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: TODO 2: Make sure you clean up any memory allocated from tilesets/map

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_document mapFile;
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if(ret == true)
    {
        ret = LoadMap(mapFile);
    }

    if (ret == true)
    {
        ret = LoadTileSet(mapFile);
    }

    if(ret == true)
    {
        //L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
        LOG("Succesfully parsed map XML file: %s", mapFile.name());
        LOG("Width: %i Heigth: %i", mapData.width, mapData.height);
        LOG("Tile Width: %i Tile Height: %i", mapData.tileWidth, mapData.tileheight);


        ListItem<TileSet*>* item;
        item = mapData.tilesets.start;
        LOG("----------------------------");
        LOG("Tileset");
        while (item != NULL)
        {
            LOG("Name: %i", item->data->name);
            LOG("Firstgid: %i", item->data->firstID);
            LOG("Tile width: %i Tile height: %i", item->data->tileWidth, item->data->tileHeight);
            LOG("Spacing: %i Margin: %i", item->data->spacing, item->data->margin);

            item = item->next;
        }
    }

    if(mapFile) mapFile.reset();

    mapLoaded = ret;

    return ret;
}

// L03: TODO 3: Implement LoadMap to load the map properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
    bool ret = true;
    mapData.mapVersion = mapFile.child("map").attribute("version").as_string();
    mapData.tiledVersion = mapFile.child("map").attribute("tileversion").as_string();
    mapData.orientation = mapFile.child("map").attribute("orientation").as_string();
    mapData.renderOrder = mapFile.child("map").attribute("renderorder").as_string();
    mapData.width = mapFile.child("map").attribute("width").as_int();
    mapData.height = mapFile.child("map").attribute("height").as_int();
    mapData.tileWidth = mapFile.child("map").attribute("tilewidth").as_int();
    mapData.tileheight = mapFile.child("map").attribute("tileheight").as_int();
    mapData.infinite = mapFile.child("map").attribute("infinite").as_int();
    mapData.nextLayerid = mapFile.child("map").attribute("nextlayerid").as_int();
    mapData.nextObjesctid = mapFile.child("map").attribute("nextobjectid").as_int();
    
    return ret;
}

// L03: TODO 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSet(pugi::xml_node mapFile){

    bool ret = true; 
    for (pugi::xml_node tileset = mapFile.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {
        TileSet* tmp = new TileSet();
        tmp->firstID = tileset.attribute("firstid").as_int();
        tmp->name = tileset.attribute("name").as_string();
        tmp->tileWidth = tileset.attribute("tilewidth").as_int();
        tmp->tileHeight = tileset.attribute("tileheight").as_int();
        tmp->spacing = tileset.attribute("spacing").as_int();
        tmp->margin = tileset.attribute("margin").as_int();
        tmp->tileCount = tileset.attribute("tilecount").as_int();
        tmp->columns = tileset.attribute("columns").as_int();
        tmp->imgSrc = tileset.child("image").attribute("source").as_string();
        tmp->imageWidth = tileset.child("image").attribute("height").as_int();
        tmp->imageHeight = tileset.child("image").attribute("width").as_int();
        SString tmpS("%s%s", folder.GetString(), tmp->imgSrc.GetString());
        tmp->texture = app->tex->Load(tmpS.GetString());
        mapData.tilesets.add(tmp);
    }

    return ret;
}


