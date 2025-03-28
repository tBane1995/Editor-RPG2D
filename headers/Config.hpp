#ifndef Config_hpp
#define Config_hpp

class Config {
public:

    MenuBar* _menu_bar;
    Palette* _palette;
    Clipboard* _clipboard;
    //Mapa* _mapa;
    Painter* _painter;
    Camera* _cam;

    std::vector < GameObject* > _gameObjects;
    std::vector < Nature* > _natures;
    std::vector < Object*> _objects;
    std::vector < Monster* > _monsters;
    std::vector < Character* > _characters;
    std::vector < ItemOnMap* > _itemsOnMap;
    std::vector < InventoryOnMap* > _inventoriesOnMap;
    std::vector < FlatObject* > _flatObjects;
    std::vector < SmallObject* > _smallObjects;
    std::vector < Door* > _doors;
    std::vector < Furniture* > _furnitures;
    std::vector < Wall* > _walls;
    std::vector < Building* > _buildings;

    Config() {

    }

    ~Config() {

    }

    void save() {
        _menu_bar = menu_bar;
        _palette = palette;
        _painter = painter;
        _clipboard = clipboard;
        //_mapa = mapa;
        _cam = cam;
        

        _gameObjects = gameObjects;
        _natures = natures;
        _objects = objects;
        _monsters = monsters;
        _characters = characters;
        _itemsOnMap = itemsOnMap;
        _inventoriesOnMap = inventoriesOnMap;
        _flatObjects = flatObjects;
        _smallObjects = smallObjects;
        _doors = doors;
        _furnitures = furnitures;
        _walls = walls;
        _buildings = buildings;
    }

    void load() {

        delete menu_bar;
        delete palette;
        delete painter;
        delete clipboard;
        //delete mapa;

        menu_bar = _menu_bar;
        palette = _palette;
        painter = _painter;
        clipboard = _clipboard;
        //mapa = _mapa;
        cam = _cam;

        // TO-DO - must prev a delete
        gameObjects = _gameObjects;
        natures = _natures;
        objects = _objects;
        monsters = _monsters;
        characters = _characters;
        itemsOnMap = _itemsOnMap;
        inventoriesOnMap = _inventoriesOnMap;
        flatObjects = _flatObjects;
        smallObjects = _smallObjects;
        doors = _doors;
        furnitures = _furnitures;
        walls = _walls;
        buildings = _buildings;
    }
};

Config* config = nullptr;

#endif