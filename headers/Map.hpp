#ifndef  Map_hpp
#define  Map_hpp

class Chunk {
public:
    sf::Vector2i coords;
    Terrain* terrain;
    Water* water;
    Water* swamp;
    Borders* borders;

    sf::RectangleShape frame;
    sf::Text coordsText;

    std::vector < Nature* > _natures;
    std::vector < Object* > _objects;
    std::vector < ItemOnMap* > _items;
    std::vector < InventoryOnMap* > _inventories;
    std::vector < FlatObject* > _flatObjects;
    std::vector < Monster* > _monsters;
    std::vector < SmallObject* > _smallObjects;
    std::vector < Door* > _doors;
    std::vector < Character* > _characters;
    std::vector < Building* > _buildings;


    bool visible;

    Chunk(short x, short y)
    {
        coords.x = x;
        coords.y = y;

        terrain = new Terrain(x * 16, y * 16, 16, 16);
        water = new Water(WaterType::Lake, x * 16, y * 16, 16, 16);
        swamp = new Water(WaterType::Swamp, x * 16, y * 16, 16, 16);
        borders = new Borders();

        short frameWidth = 2;
        frame = sf::RectangleShape(sf::Vector2f(256 - 2 * frameWidth, 256 - 2 * frameWidth));
        frame.setPosition(x * 256, y * 256);
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineColor(sf::Color(128, 48, 48, 128));
        frame.setOutlineThickness(frameWidth);

        coordsText = sf::Text();
        coordsText.setFont(basicFont);
        coordsText.setCharacterSize(17);
        coordsText.setString(std::to_string(coords.x) + " x " + std::to_string(coords.y));
        coordsText.setFillColor(dialoguesColor);
        coordsText.setPosition(coords.x * 256, coords.y * 256);

        visible = false;
    }

    ~Chunk() {
        // Usuń i zwolnij pamięć dla wszystkich elementów w wektorach
        for (auto& nature : _natures)
            delete nature;
        _natures.clear();

        for (auto& object : _objects)
            delete object;
        _objects.clear();

        for (auto& item : _items)
            delete item;
        _items.clear();

        for (auto& inventory : _inventories)
            delete inventory;
        _inventories.clear();

        for (auto& flat : _flatObjects)
            delete flat;
        _flatObjects.clear();

        for (auto& monster : _monsters)
            delete monster;
        _monsters.clear();

        for (auto& smallObject : _smallObjects)
            delete smallObject;
        _smallObjects.clear();

        for (auto& door : _doors)
            delete door;
        _doors.clear();

        for (auto& character : _characters)
            delete character;
        _characters.clear();

        for (auto& building : _buildings)
            delete building;
        _buildings.clear();



        delete terrain;
        delete water;
        delete swamp;
    }

    void addGameObjectsToMainLists() {
        // Add all GameObjects of Chunk to Main Lists

        for (auto& nature : _natures) {
            nature->isInTheMainList = true;
            gameObjects.push_back(nature);
            natures.push_back(nature);
        }

        for (auto& object : _objects) {
            object->isInTheMainList = true;
            gameObjects.push_back(object);
            objects.push_back(object);
        }

        for (auto& item : _items) {
            item->isInTheMainList = true;
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
        }

        for (auto& inventory : _inventories) {
            inventory->isInTheMainList = true;
            gameObjects.push_back(inventory);
            inventoriesOnMap.push_back(inventory);
        }

        for (auto& flat : _flatObjects) {
            flat->isInTheMainList = true;
            gameObjects.push_back(flat);
            flatObjects.push_back(flat);
        }

        for (auto& monster : _monsters) {
            monster->isInTheMainList = true;
            gameObjects.push_back(monster);
            monsters.push_back(monster);
        }

        for (auto& smallObject : _smallObjects) {
            smallObject->isInTheMainList = true;
            gameObjects.push_back(smallObject);
            smallObjects.push_back(smallObject);
        }

        for (auto& door : _doors) {
            door->isInTheMainList = true;
            gameObjects.push_back(door);
            doors.push_back(door);
        }

        for (auto& character : _characters) {
            character->isInTheMainList = true;
            gameObjects.push_back(character);
            characters.push_back(character);
        }

        for (auto& building : _buildings) {
            building->isInTheMainList = true;
            gameObjects.push_back(building);
            buildings.push_back(building);

            building->_door->isInTheMainList = true;
            doors.push_back(building->_door);
            gameObjects.push_back(building->_door);

            for (auto& item : building->_items) {
                item->isInTheMainList = true;
                itemsOnMap.push_back(item);
                gameObjects.push_back(item);
            }


            for (auto& furniture : building->_furnitures) {
                furniture->isInTheMainList = true;
                furnitures.push_back(furniture);
                gameObjects.push_back(furniture);
            }


            for (auto& wall : building->_walls) {
                wall->isInTheMainList = true;
                walls.push_back(wall);
                gameObjects.push_back(wall);
            }

        }
    }

    void removeGameObjectsFromMainLists() {

        // delete natures ////////////////////////////////////////////////////////////
        for (auto& nature : _natures)
            nature->isInTheMainList = false;

        std::erase_if(natures, [](const auto& nature) { return !nature->isInTheMainList; });

        // delete objects ////////////////////////////////////////////////////////////
        for (auto& object : _objects)
            object->isInTheMainList = false;

        std::erase_if(objects, [](const auto& object) { return !object->isInTheMainList; });

        // delete items ////////////////////////////////////////////////////////////
        for (auto& item : _items)
            item->isInTheMainList = false;

        std::erase_if(itemsOnMap, [](const auto& item) { return !item->isInTheMainList; });

        // delete inventories ////////////////////////////////////////////////////////////
        for (auto& inventory : _inventories)
            inventory->isInTheMainList = false;

        std::erase_if(inventoriesOnMap, [](const auto& inventory) { return !inventory->isInTheMainList; });

        // delete flatObjects ////////////////////////////////////////////////////////////
        for (auto& flat : _flatObjects)
            flat->isInTheMainList = false;

        std::erase_if(flatObjects, [](const auto& flat) { return !flat->isInTheMainList; });

        // delete monsters ////////////////////////////////////////////////////////////
        for (auto& monster : _monsters)
            monster->isInTheMainList = false;

        std::erase_if(monsters, [](const auto& monster) { return !monster->isInTheMainList; });

        // delete smallObjects ////////////////////////////////////////////////////////////
        for (auto& object : _smallObjects)
            object->isInTheMainList = false;

        std::erase_if(smallObjects, [](const auto& object) { return !object->isInTheMainList; });

        // delete doors ////////////////////////////////////////////////////////////
        for (auto& door : _doors)
            door->isInTheMainList = false;

        std::erase_if(doors, [](const auto& door) { return !door->isInTheMainList; });

        // delete characters ////////////////////////////////////////////////////////////
        for (auto& character : _characters)
            character->isInTheMainList = false;

        std::erase_if(characters, [](const auto& character) { return !character->isInTheMainList; });

        // delete buildings ////////////////////////////////////////////////////////////
        for (auto& building : _buildings) {
            building->isInTheMainList = false;

            // delete building - doors
            building->_door->isInTheMainList = false;
            std::erase_if(doors, [](const auto& door) { return !door->isInTheMainList; });

            // delete building - items
            for (auto& item : building->_items)
                item->isInTheMainList = false;

            std::erase_if(itemsOnMap, [](const auto& item) { return !item->isInTheMainList; });

            // delete building - furnitures
            for (auto& furniture : building->_furnitures)
                furniture->isInTheMainList = false;

            std::erase_if(furnitures, [](const auto& furniture) { return !furniture->isInTheMainList; });

            // delete building - walls
            for (auto& wall : building->_walls)
                wall->isInTheMainList = false;

            std::erase_if(walls, [](const auto& wall) { return !wall->isInTheMainList; });

        }

        std::erase_if(buildings, [](const auto& building) { return !building->isInTheMainList; });


        // delete GameObjects  /////////////////////////////////////////////////////////////////////
        std::erase_if(gameObjects, [](const auto& go) { return !go->isInTheMainList; });
    }

    void addGameObject(GameObject* object) {
        if (object == nullptr)
            return;

        if (object->type == GameObjectType::Nature) {
            _natures.push_back(dynamic_cast<Nature*>(object));
        }

        if (object->type == GameObjectType::Object) {
            _objects.push_back(dynamic_cast<Object*>(object));
        }

        if (object->type == GameObjectType::Monster) {
            _monsters.push_back(dynamic_cast<Monster*>(object));
        }

        if (object->type == GameObjectType::Character) {
            _characters.push_back(dynamic_cast<Character*>(object));
        }

        if (object->type == GameObjectType::ItemOnMap) {
            _items.push_back(dynamic_cast<ItemOnMap*>(object));
        }

        if (object->type == GameObjectType::InventoryOnMap) {
            _inventories.push_back(dynamic_cast<InventoryOnMap*>(object));
        }

        if (object->type == GameObjectType::FlatObject) {
            _flatObjects.push_back(dynamic_cast<FlatObject*>(object));
        }

        if (object->type == GameObjectType::SmallObject) {
            _smallObjects.push_back(dynamic_cast<SmallObject*>(object));
        }

        if (object->type == GameObjectType::Door) {
            _doors.push_back(dynamic_cast<Door*>(object));
        }

        if (object->type == GameObjectType::Building) {
            _buildings.push_back(dynamic_cast<Building*>(object));
        }


    }

    void deleteGameObject(GameObject* object) {

        if (object == nullptr)
            return;

        if (object->type == GameObjectType::Nature) {
            auto it = std::find(_natures.begin(), _natures.end(), object);
            if (it != _natures.end())
                _natures.erase(it);
        }

        if (object->type == GameObjectType::Object) {
            auto it = std::find(_objects.begin(), _objects.end(), object);
            if (it != _objects.end())
                _objects.erase(it);
        }

        if (object->type == GameObjectType::ItemOnMap) {
            auto it = std::find(_items.begin(), _items.end(), object);
            if (it != _items.end())
                _items.erase(it);
        }

        if (object->type == GameObjectType::InventoryOnMap) {
            auto it = std::find(_inventories.begin(), _inventories.end(), object);
            if (it != _inventories.end())
                _inventories.erase(it);
        }

        if (object->type == GameObjectType::FlatObject) {
            auto it = std::find(_flatObjects.begin(), _flatObjects.end(), object);
            if (it != _flatObjects.end())
                _flatObjects.erase(it);
        }

        if (object->type == GameObjectType::Monster) {
            auto it = std::find(_monsters.begin(), _monsters.end(), object);
            if (it != _monsters.end())
                _monsters.erase(it);
        }

        if (object->type == GameObjectType::SmallObject) {
            auto it = std::find(_smallObjects.begin(), _smallObjects.end(), object);
            if (it != _smallObjects.end())
                _smallObjects.erase(it);
        }

        if (object->type == GameObjectType::Door) {
            auto it = std::find(_doors.begin(), _doors.end(), object);
            if (it != _doors.end())
                _doors.erase(it);
        }

        if (object->type == GameObjectType::Character) {
            auto it = std::find(_characters.begin(), _characters.end(), object);
            if (it != _characters.end()) {
                _characters.erase(it);
            }

        }

        if (object->type == GameObjectType::Building) {
            auto it = std::find(_buildings.begin(), _buildings.end(), object);
            if (it != _buildings.end())
                _buildings.erase(it);
        }
    }

    std::vector < GameObject* > getAllGameObjects() {
        std::vector < GameObject* > gameobjects;
        gameobjects.clear();

        for (auto& go : _natures) {
            gameobjects.push_back(go);
        }

        for (auto& go : _objects) {
            gameobjects.push_back(go);
        }

        for (auto& go : _items) {
            gameobjects.push_back(go);
        }

        for (auto& go : _inventories) {
            gameobjects.push_back(go);
        }

        for (auto& go : _flatObjects) {
            gameobjects.push_back(go);
        }

        for (auto& go : _monsters) {
            gameobjects.push_back(go);
        }

        for (auto& go : _smallObjects) {
            gameobjects.push_back(go);
        }

        for (auto& go : _doors) {
            gameobjects.push_back(go);
        }

        for (auto& go : _characters) {
            gameobjects.push_back(go);
        }

        for (auto& go : _buildings) {
            gameobjects.push_back(go);
        }

        return gameobjects;
    }

    void update()
    {
    }

    void draw() {
        renderer->getTheCurrentFrame()->draw(*terrain);

        water->update();    // TO-DO
        swamp->update();
        renderer->getTheCurrentFrame()->draw(*water);
        renderer->getTheCurrentFrame()->draw(*swamp);

        if (renderer->WE_renderTilesBorders == true)
            renderer->getTheCurrentFrame()->draw(*borders);
    }

    void drawAllStatistics() {
        if (renderer->WE_renderBorders)
            renderer->getTheCurrentFrame()->draw(frame);

        if (renderer->WE_renderCoords)
            renderer->getTheCurrentFrame()->draw(coordsText);
    }

};

class Mapa {
public:
    std::vector < Chunk* > chunks;
    short width;
    short height;
    
    Mapa() {
        for (auto& chunk : chunks)
            delete chunk;
        chunks.clear();
        clearAllMainListsOfGameObjects();

        width = 32;
        height = 32;

        for (short y = 0; y < height; y++) {
            for (short x = 0; x < width; x++) {
                Chunk* ch = new Chunk(x, y);
                chunks.push_back(ch);
            }
        }
    }

    short generateNewBuildingId() {

        std::vector < short > ids;
        ids.clear();

        for (auto& chunk : chunks) {
            for (auto& building : chunk->_buildings) {
                ids.push_back(building->id);
            }
        }

        if (ids.size() == 0) {
            return 0;
        }
        else {
            std::sort(ids.begin(), ids.end(), [](const auto& a, const auto& b) { return a < b; });
            
            for (auto& i : ids) {
                std::cout << i << " ";
            }

            std::cout << endl;

            short i;
            for (i = 0; i < ids.size(); i++) {
                if (ids[i] != i) {
                    break;
                }
            }

            return i;
        }
    }

    short generateNewFurnitureInventoryId() {
        std::vector < short > ids;
        ids.clear();

        for (auto& chunk : chunks) {
            for (auto& building : chunk->_buildings) {
                if (building->id != building_to_edit->id) {
                    for (auto& furniture : building->_furnitures) {
                        if (furniture->inventory != nullptr) {
                            ids.push_back(furniture->inventory->id);
                        }
                    }
                }
            }
        }

        for (auto& furniture : building_to_edit->_furnitures) {
            if (furniture->inventory != nullptr) {
                ids.push_back(furniture->inventory->id);
            }
        }

        std::erase_if(ids, [](const auto& id) { return id<0; });

        if (ids.size() == 0) {
            return 0;
        }
        else {
            std::sort(ids.begin(), ids.end(), [](const auto& a, const auto& b) { return a < b; });

            short i;
            for (i = 0; i < ids.size(); i++) {
                if (ids[i] != i) {
                    break;
                }
            }

            return i;
        }
            
    }

    short generateNewCharacterId() {
        std::vector < short > ids;
        ids.clear();

        for (auto& chunk : chunks) {
            for (auto& character : chunk->_characters) {
                ids.push_back(character->id);
            }
        }

        std::erase_if(ids, [](const auto& id) { return id < 0; });

        if (ids.size() == 0) {
            return 0;
        }
        else {
            std::sort(ids.begin(), ids.end(), [](const auto& a, const auto& b) { return a < b; });

            short i;
            for (i = 0; i < ids.size(); i++) {
                if (ids[i] != i) {
                    break;
                }
            }

            return i;
        }

    }

    Chunk* getChunk(short x, short y) {
        for (auto& chunk : chunks) {
            if (short(chunk->coords.x) == x && short(chunk->coords.y) == y) {
                //cout << chunk->coords.x << " " << chunk->coords.y << "\n";
                return chunk;
            }

        }

        return nullptr;
    }

    Chunk* getChunk(sf::Vector2f position) {
        float left, right, top, bottom;

        for (auto& chunk : chunks) {

            left = chunk->coords.x * 16 * tileSide;
            right = left + chunk->terrain->width * tileSide;
            top = chunk->coords.y * 16 * tileSide;
            bottom = top + chunk->terrain->height * tileSide;

            if (position.x >= left && position.x < right && position.y >= top && position.y < bottom)
            {
                //cout << m->coords.x << ", " << m->coords.y << "\n";
                return chunk;

            }
        }

        return nullptr;
    }

    void save(std::wstring pathfile = L"world\\world.wrd") {
        std::ofstream file(pathfile);

        file << "#MapBegin\n";

        for (auto& chunk : chunks){
            file << "Chunk ";

            file << "y=" << chunk->coords.y << " ";
            file << "x=" << chunk->coords.x << "\n";

            for (short y = 0; y < 16; y++) {
                for (short x = 0; x < 16; x++) {

                    file << chunk->terrain->tiles[y * 16 + x];

                    if (x != 15)
                        file << " ";
                }

                file << "\n";
            }

            for (auto& nature : chunk->_natures)
                file  << "Nature \"" << ConvertWideToUtf8(nature->name) << "\" y=" << int(nature->position.y) << " x=" << int(nature->position.x) << "\n";

            for (auto& object : chunk->_objects)
                file << "Object \"" << ConvertWideToUtf8(object->name) << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& item : chunk->_items)
                file << "Item \"" << ConvertWideToUtf8(item->name) << "\" y=" << int(item->position.y) << " x=" << int(item->position.x) << "\n";

            for (auto& inventory : chunk->_inventories)
                file << "Inventory \"" << ConvertWideToUtf8(inventory->name) << "\" y=" << int(inventory->position.y) << " x=" << int(inventory->position.x) << "\n";

            for (auto& flat : chunk->_flatObjects)
                file << "FlatObject \"" << ConvertWideToUtf8(flat->name) << "\" y=" << int(flat->position.y) << " x=" << int(flat->position.x) << "\n";

            for (auto& monster : chunk->_monsters)
                file << "Monster \"" << ConvertWideToUtf8(monster->name) << "\" y=" << int(monster->base.y) << " x=" << int(monster->base.x) << "\n";

            for (auto& object : chunk->_smallObjects)
                file << "SmallObject \"" << ConvertWideToUtf8(object->name) << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& object : chunk->_doors)
                file << "Door \"" << ConvertWideToUtf8(object->name) << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& character : chunk->_characters)
                file << "Character \"" << to_string(character->id) << "\" y=" << int(character->position.y) << " x=" << int(character->position.x) << "\n";

            for (auto& building : chunk->_buildings)
                file << "Building \"" << to_string(building->id) << "\" y=" << int(building->position.y) << " x=" << int(building->position.x) << "\n";

            file << "\n";
        }

        file << "#MapEnd\n";


        // SAVE BUILDINGS
        for (auto& chunk : chunks) {
            for (auto& building : chunk->_buildings) {

                file << "#BuildingBegin\n";

                file << "id " << std::to_string(building->id) << "\n";
                file << "name \"testBuilding\"\n";
                file << "size " << std::to_string(building->size.x) << " " << std::to_string(building->size.y) << "\n";
                file << "door \"" << ConvertWideToUtf8(building->_door->name) << "\"\n";
                file << "top_walls \"" << ConvertWideToUtf8(building->texture_top_walls->name) << "\"\n";
                file << "center_walls \"" << ConvertWideToUtf8(building->texture_center_walls->name) << "\"\n";
                file << "bottom_walls \"" << ConvertWideToUtf8(building->texture_bottom_walls->name) << "\"\n";
                file << "windows \"" << ConvertWideToUtf8(building->texture_windows->name) << "\"\n";

                file << "\n";

                // SAVE FLOORS
                file << "//FLOORS\n";
                for (short y = 0; y < building->floors->height; y++) {
                    for (short x = 0; x < building->floors->width; x++) {
                        file << building->floors->floors[y * building->floors->width + x];
                        if (x != building->floors->width - 1)
                            file << " ";
                    }
                    file << "\n";
                }
                file << "\n";

                if (building->_walls.size() > 0) {
                    file << "//WALLS\n";
                    for (auto& wall : building->_walls) {
                        sf::Vector2i position;
                        position.x = int(wall->position.x) - int(building->position.x) + building->size.x / 2 * 16;
                        position.y = int(wall->position.y) - int(building->position.y) + building->size.y * 16;
                        file << "Wall " << char(34) << ConvertWideToUtf8(wall->name) << char(34) << " " << position.x << " " << position.y << "\n";
                        std::cout << "save - position of wall: " << position.x << " " << position.y << "\n";
                    }
                }
                    

                if (building->_furnitures.size() > 0) {
                    file << "//FURNITURES\n";
                    for (auto& furniture : building->_furnitures) {
                        sf::Vector2i position;
                        position.x = int(furniture->position.x) - int(building->position.x) + building->size.x / 2 * 16;
                        position.y = int(furniture->position.y) - int(building->position.y) + building->size.y * 16;
                        file << "Furniture " << char(34) << ConvertWideToUtf8(furniture->name) << char(34) << " " << position.x << " " << position.y << "\n";

                    }
                }

                // SAVE ITEMS
                if (building->_items.size() > 0) {
                    file << "//ITEMS\n";
                    for (auto& item : building->_items) {
                        sf::Vector2i position;
                        position.x = int(item->position.x) - int(building->position.x) + building->size.x / 2 * 16;
                        position.y = int(item->position.y) - int(building->position.y) + building->size.y * 16;
                        file << "Item " << char(34) << ConvertWideToUtf8(item->name) << char(34) << " " << position.x << " " << position.y << "\n";
                    }
                }

                file << "#BuildingEnd\n";
            }
        }

        // SAVE CHARACTERS
        for (auto& chunk : chunks) {
            for (auto& character : chunk->_characters) {

                file << "#CharacterBegin\n";

                /////////////////////////////

                file << "ID: " << character->id << "\n";
                file << "Name: " << ConvertWideToUtf8(character->name) << "\n";
                file << "Dialogue: " << (character->dialogue!=nullptr ? to_string(character->dialogue->id) : "-1" ) << "\n";

                file << "Level: " << character->LEVEL << "\n";
                file << "Experience: " << character->EXPERIENCE << "\n";
                file << "SkillPoints: " << character->SKILL_POINTS << "\n";

                file << "CurrentHP: " << character->attributes[Attribute::HP] << "\n";
                file << "MaxHP: " << character->attributes[Attribute::HP_max] << "\n";
                file << "CurrentMP: " << character->attributes[Attribute::MP] << "\n";
                file << "MaxMP: " << character->attributes[Attribute::MP_max] << "\n";

                file << "Strength: " << character->attributes[Attribute::STRENGTH] << "\n";
                file << "Dexterity: " << character->attributes[Attribute::DEXTERITY] << "\n";
                file << "Intelligence: " << character->attributes[Attribute::INTELLIGENCE] << "\n";

                /////////////////////////////

                file << "Body: \"" << ConvertWideToUtf8(character->body) << "\"\n";
                file << "Head: \"" << ConvertWideToUtf8(character->head) << "\"\n";

                /////////////////////////////

                file << "Helmet: \"" << (character->helmet!=nullptr? ConvertWideToUtf8(character->helmet->name) : "none" ) << "\"\n";
                file << "Armor: \"" << (character->armor !=nullptr? ConvertWideToUtf8(character->armor->name) : "none" ) << "\"\n";
                file << "Pants: \"" << (character->pants !=nullptr? ConvertWideToUtf8(character->pants->name) : "none" ) << "\"\n";
                file << "RightHand: \"" << (character->rightHand !=nullptr? ConvertWideToUtf8(character->rightHand->name) : "none" ) << "\"\n";
                file << "LeftHand: \"" << (character->leftHand !=nullptr? ConvertWideToUtf8(character->leftHand->name) : "none" ) << "\"\n";

                /////////////////////////////

                file << "#CharacterEnd\n";
            }
        }

        file.close();

        std::cout << "saved map\n";
    }

    void binary_save(std::wstring pathfile = L"world\\test_world.wrd") {

        class Writer
        {
            std::ostream& os;
        public:
            Writer(std::ostream& os)
                : os(os)
            { }

            void write_string(const std::string& str)
            {
                uint16_t str_len = static_cast <uint16_t>(str.size());
                os.write(reinterpret_cast <const char*>(&str_len), sizeof(str_len));
                os.write(str.data(), str_len);
            }

            void write_uint32(uint32_t val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(uint32_t));
            }

            void write_uint16(uint16_t val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(uint16_t));
            }

            void write_uint8(uint8_t val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(uint8_t));
            }

            void write_float(float val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(float));
            }

            void write_int(int val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(int));
            }

            void write_short(short val) {
                os.write(reinterpret_cast<const char*>(&val), sizeof(short));
            }
            //itd inne warianty write()

            void write_Vector2f(sf::Vector2f val) {
                os.write(reinterpret_cast<const char*>(&val.x), sizeof(float));
                os.write(reinterpret_cast<const char*>(&val.y), sizeof(float));
            }

            void write_Vector2i(sf::Vector2i val) {
                os.write(reinterpret_cast<const char*>(&val.x), sizeof(int));
                os.write(reinterpret_cast<const char*>(&val.y), sizeof(int));
            }
        };

        std::ofstream file(pathfile, std::ios::binary);
        Writer writer(file);

        // najpierw zapisz ścieżki prefabrykatów w celu wyeliminowania powtarzalnych scieżek i zastąpieniu ich przez id
        writer.write_string("#Resources");
        writer.write_uint32(prefabs.size());

        for (auto& prefab : prefabs)
            writer.write_string(ConvertWideToUtf8(prefab->name));

        // save chunks and objects
        writer.write_string("#Map");

        writer.write_uint8(this->width);
        writer.write_uint8(this->height);

        for (auto& chunk : chunks) {

            // save chunk coords
            writer.write_Vector2i(chunk->coords);

            // save tiles
            Terrain* ter = chunk->terrain;
            for (short y = 0; y < 16; y++) {
                for (short x = 0; x < 16; x++) {
                    writer.write_short(ter->tiles[y * 16 + x]);
                }
            }


            // save objects
            writer.write_uint32(chunk->getAllGameObjects().size());

            for (auto& object : chunk->getAllGameObjects()) {

                writer.write_uint16(static_cast<uint16_t>(object->type));
                

                if (object->type == GameObjectType::Building) {
                   
                    writer.write_short(dynamic_cast<Building*>(object)->id);
                    writer.write_Vector2f(object->position);

                }
                else if (object->type == GameObjectType::Monster) {
                    writer.write_uint32(getPrefabID(object->name));
                    sf::Vector2f position = dynamic_cast<Monster*>(object)->base; 
                    writer.write_Vector2f(object->position);

                }
                else if (object->type == GameObjectType::Character) {
                    writer.write_uint32(dynamic_cast<Character*>(object)->id);
                    writer.write_Vector2f(object->position);

                }
                else if (object->type == GameObjectType::InventoryOnMap) {
                    writer.write_short(dynamic_cast<InventoryOnMap*>(object)->inventory->id);
                    writer.write_Vector2f(object->position);

                }
                else {
                    writer.write_uint32(getPrefabID(object->name));
                    writer.write_Vector2f(object->position);
                }
            }

        }

        // save buildings
        for (auto& chunk : chunks) {
            for (auto& building : chunk->_buildings) {
                writer.write_string("#Building");

                writer.write_short(building->id);
                writer.write_string(ConvertWideToUtf8(building->name));
                writer.write_Vector2i(building->size);
                writer.write_string(ConvertWideToUtf8(building->_door->name));
                writer.write_string(ConvertWideToUtf8(building->texture_top_walls->name));
                writer.write_string(ConvertWideToUtf8(building->texture_center_walls->name));
                writer.write_string(ConvertWideToUtf8(building->texture_bottom_walls->name));
                writer.write_string(ConvertWideToUtf8(building->texture_windows->name));


                writer.write_short(building->floors->width);
                writer.write_short(building->floors->height);

                for (short y = 0; y < building->floors->height; y++) {
                    for (short x = 0; x < building->floors->width; x++) {
                        writer.write_short(building->floors->floors[y * building->floors->width + x]);
                    }
                }

                std::vector < GameObject* > building_objects = building->getAllGameObjects();
                writer.write_uint32(building_objects.size());

                for (auto& object : building_objects) {
                    writer.write_uint16(static_cast<uint16_t>(object->type));
                    writer.write_uint32(getPrefabID(object->name));

                    sf::Vector2f position;
                    position.x = int(object->position.x) - int(building->position.x) + building->size.x / 2 * 16;
                    position.y = int(object->position.y) - int(building->position.y) + building->size.y * 16;

                    writer.write_Vector2f(position);
                }
            }
        }


        for (auto& inventory : inventories) {
            writer.write_string("#Inventory");

            writer.write_short(inventory->id);
            writer.write_uint32(inventory->items.size());

            for (short i = 0; i < inventory->items.size(); i++) {
                uint32_t id = getPrefabID(inventory->items[i]->name);
                uint16_t count = inventory->counts[i];

                writer.write_uint32(id);
                writer.write_uint16(count);

            }
        }

        for (auto& chunk : chunks) {
            for (auto& character : chunk->_characters) {
                
                writer.write_string("#Character");

                writer.write_int(character->id);
                writer.write_string(ConvertWideToUtf8(character->name));
                (character->dialogue != nullptr) ? writer.write_int(character->dialogue->id) : writer.write_int(-1);

                writer.write_int(character->LEVEL);
                writer.write_int(character->EXPERIENCE);
                writer.write_int(character->SKILL_POINTS);

                writer.write_int(character->attributes[Attribute::HP]);
                writer.write_int(character->attributes[Attribute::HP_max]);
                writer.write_int(character->attributes[Attribute::MP]);
                writer.write_int(character->attributes[Attribute::MP_max]);

                writer.write_int(character->attributes[Attribute::STRENGTH]);
                writer.write_int(character->attributes[Attribute::DEXTERITY]);
                writer.write_int(character->attributes[Attribute::INTELLIGENCE]);

                /////////////////////////////

                writer.write_string(ConvertWideToUtf8(character->body));
                writer.write_string(ConvertWideToUtf8(character->head));
                
                /////////////////////////////

                (character->helmet != nullptr) ? writer.write_string(ConvertWideToUtf8(character->helmet->name)) : writer.write_string("none");
                (character->armor != nullptr) ? writer.write_string(ConvertWideToUtf8(character->armor->name)) : writer.write_string("none");
                (character->pants != nullptr) ? writer.write_string(ConvertWideToUtf8(character->pants->name)) : writer.write_string("none");
                (character->rightHand != nullptr) ? writer.write_string(ConvertWideToUtf8(character->rightHand->name)) : writer.write_string("none");
                (character->leftHand != nullptr) ? writer.write_string(ConvertWideToUtf8(character->leftHand->name)) : writer.write_string("none");
                
            }
        }

        file.close();

    }

    void saveAsPNG(std::string filename) {

		sf::Vector2f size(width * 16 * tileSide, height * 16 * tileSide);
        
        std::cout << "creating Map Texture\n";

        sf::RenderTexture rtex;
        rtex.create(size.x, size.y);
        rtex.clear(sf::Color(48, 48, 48, 255));
        
        std::cout << "adding Terrains and Waters\n";

        for (auto& chunk : chunks) {
            rtex.draw(*chunk->terrain);
            rtex.draw(*chunk->water);
            rtex.draw(*chunk->swamp);
        
        }

        std::cout << "adding FlatObjects to Map Texture\n";

        std::vector < GameObject* > objects;
        for (auto& chunk : chunks) {
            for (auto& f : chunk->_flatObjects)
                objects.push_back(f);
        }

        std::sort(objects.begin(), objects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });

        for (auto& obj : objects) {
            rtex.draw(dynamic_cast<FlatObject*>(obj)->sprite);
        }

        std::cout << "sorting other GameObjects\n";
		objects.clear();

        for (auto& chunk : chunks) {
			for (auto& n : chunk->_natures)
				objects.push_back(n);

			for (auto& o : chunk->_objects)
				objects.push_back(o);

            for (auto& i : chunk->_items)
                objects.push_back(i);

            for (auto& i : chunk->_inventories)
                objects.push_back(i);

            for (auto& m : chunk->_monsters)
                objects.push_back(m);

            for (auto& s : chunk->_smallObjects)
                objects.push_back(s);

            for (auto& d : chunk->_doors)
                objects.push_back(d);

            for (auto& c : chunk->_characters)
                objects.push_back(c);

            for (auto& b : chunk->_buildings)
                objects.push_back(b);
        }

        std::sort(objects.begin(), objects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });


        std::cout << "adding GameObjects to Map Texture\n";

        for (auto& obj : objects) {

            if (obj->type == GameObjectType::Nature)
                rtex.draw(dynamic_cast<Nature*>(obj)->sprite);

            if (obj->type == GameObjectType::Object)
                rtex.draw(dynamic_cast<Object*>(obj)->sprite);

            if (obj->type == GameObjectType::ItemOnMap)
                rtex.draw(dynamic_cast<ItemOnMap*>(obj)->sprite);

            if (obj->type == GameObjectType::InventoryOnMap)
                rtex.draw(dynamic_cast<InventoryOnMap*>(obj)->sprite);

            if (obj->type == GameObjectType::Monster)
                rtex.draw(dynamic_cast<Monster*>(obj)->sprite);

            if (obj->type == GameObjectType::SmallObject)
                rtex.draw(dynamic_cast<SmallObject*>(obj)->sprite);

            if (obj->type == GameObjectType::Door)
                rtex.draw(dynamic_cast<Door*>(obj)->sprite);

            if (obj->type == GameObjectType::Character) {
                rtex.draw(dynamic_cast<Character*>(obj)->sprite);
            }
                

            if (obj->type == GameObjectType::Building) {
                rtex.draw(dynamic_cast<Building*>(obj)->sprite);
				rtex.draw(dynamic_cast<Building*>(obj)->_door->sprite);
            }
                
        }

        std::cout << "saving Texture\n";

		sf::Image png = rtex.getTexture().copyToImage();
        png.flipVertically();
		png.saveToFile(filename);

		std::cout << "saved map as PNG\n";
    }

    Building* getBuilding(short id) {

        for (auto& chunk : chunks) {
            for (auto& building : chunk->_buildings) {
                if (building->id == id)
                    return building;
            }
        }

        return nullptr;
    }

    Character* getCharacter(short id) {

        for (auto& chunk : chunks) {
            for (auto& character : chunk->_characters) {
                if (character->id == id)
                    return character;
            }
        }

        return nullptr;
    }

    void load(std::wstring filename = L"world\\world.wrd") {
        // clearing chunks
        /*
        for (auto& chunk : chunks) {
            delete chunk;
        }
        */
        chunks.clear();

        clearAllMainListsOfGameObjects();

        for (auto& chunk : chunks) {
            delete chunk;
        }

        // create chunks
        width = 40;
        height = 40;

        for (short y = 0; y < height; y++) {
            for (short x = 0; x < width; x++) {
                Chunk* ch = new Chunk(x, y);
                chunks.push_back(ch);
            }
        }

        // open file map
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::wcout << L"cant open map: " << filename << L"\n";
            return;
        }

        std::wcout << L"open map: " << filename << L"\n";

        std::string line;
        std::string phrase;

        enum class LoadObjectType { None, Map, Building, Character };
        LoadObjectType load_object_type = LoadObjectType::None;

        Building* building = nullptr;
        Character* character = nullptr;

        // loading
        while (std::getline(file, line)) {

            if (line.empty()) {
                //cout << "empty line\n";
                continue;
            }

            std::istringstream lineStream(line);
            lineStream >> phrase;

            if (phrase == "#MapBegin") {
                load_object_type = LoadObjectType::Map;
            }
            else if (phrase == "#MapEnd") {
                load_object_type = LoadObjectType::None;
            }
            else if (phrase == "#BuildingBegin") {
                building = nullptr;
                load_object_type = LoadObjectType::Building;
            }
            else if (phrase == "#BuildingEnd") {
                building->loadTexture();
                load_object_type = LoadObjectType::None;
            }
            else if (phrase == "#CharacterBegin") {
                character = nullptr;
                load_object_type = LoadObjectType::Character;
            }
            else if (phrase == "#CharacterEnd") {
                character->loadSprites();
                
                load_object_type = LoadObjectType::None;
            }
            else if (load_object_type == LoadObjectType::Map) {
                if (phrase == "Chunk") {

                    // load Chunk
                    std::regex chunk_regex(R"(Chunk y=([0-9]+) x=([0-9]+))");
                    std::smatch chunk_match;

                    if (std::regex_search(line, chunk_match, chunk_regex)) {
                        int chunk_y = std::stoi(chunk_match[1]);
                        int chunk_x = std::stoi(chunk_match[2]);

                        // get chunk
                        Chunk* chunk = getChunk(chunk_x, chunk_y);

                        if (chunk == nullptr) {
                            chunk = new Chunk(chunk_x, chunk_y);
                            chunks.push_back(chunk);
                        }

                        // check the correct of datas
                        std::streampos pos = file.tellg(); // Zapisanie pozycji linii
                        bool correct_data = true;
                        std::string _line;
                        int y = 0;
                        int x;

                        while (std::getline(file, _line) && _line[0] >= '0' && _line[0] <= '9') {

                            std::istringstream iss(_line);
                            int val;
                            x = 0;

                            while (iss >> val)
                                x += 1;

                            if (x != 16) {
                                //cout << x << "\n";
                                correct_data = false;
                            }

                            y += 1;
                        };

                        if (y != 16) {
                            //cout << y << "\n";
                            correct_data = false;
                        }

                        // predefine tiles
                        std::vector < short > tiles(256, 0);

                        if (correct_data == true) {
                            file.seekg(pos); // wczytanie pozycji linii

                            // load tiles
                            short y = 0;
                            while (y < 16 && std::getline(file, line)) {

                                std::istringstream tileStream(line);
                                short value;
                                short x = 0;

                                while (tileStream >> value) {
                                    tiles[y * 16 + x] = value;
                                    x += 1;
                                }

                                y += 1;
                            }

                            // set the tiles
                            for (short i = 0; i < tiles.size(); i++) {

                                chunk->terrain->edit(i % 16, i / 16, tiles[i]);

                                // TO-DO
                                if (tiles[i] == 0 || (tiles[i] >= countOfBasicTerrain && tiles[i] < countOfBasicTerrain + 16)) {
                                    chunk->water->edit(i % 16, i / 16, tiles[i]);
                                }
                                else
                                    chunk->water->edit(i % 16, i / 16, -1);

                            }
                        }
                    }
                }
                else {

                    short x, y;
                    std::string temp;
                    std::string objectName;

                    std::getline(lineStream, temp, '"');        // get string to temp to sign "
                    std::getline(lineStream, objectName, '"');  // get string to objectName to sign "
                    std::getline(lineStream, temp, '=');        // get string to temp to sign =
                    lineStream >> y;                            // string to y
                    std::getline(lineStream, temp, '=');        // get string to temp to sign =
                    lineStream >> x;                            // string to x
                    //cout << objectType << " \"" << objectName << "\" " << x << " " << y << "\n";

                    Chunk* chunk = getChunk(sf::Vector2f(x, y));
                    if (chunk == nullptr) {
                        chunk = new Chunk(x / 256, y / 256);
                        chunks.push_back(chunk);
                    }

                    GameObject* new_object = nullptr;

                    if (phrase == "Item") {
                        Item* item = getItem(ConvertUtf8ToWide(objectName));
                        if (item != nullptr) {
                            new_object = new ItemOnMap(item);
                        }
                    }
                    else if (phrase == "Inventory") {
                        // TO-DO - get Inventory(id)
                        Inventory* inventory = getInventory(0);
                        if (inventory != nullptr) {
                            new_object = new InventoryOnMap(inventory);
                        }
                    }else if (phrase == "Building") {
                        new_object = new Building(std::stoi(objectName));
                    }
                    else if (phrase == "Character") {
                        new_object = new Character(std::stoi(objectName));
                    }
                    else{
                        GameObject* prefab = getPrefab(ConvertUtf8ToWide(objectName));
                        if (prefab == nullptr)
                            std::cout << "prefab is nullptr - " << line << "\n";
                        if(prefab != nullptr)
                            new_object = getNewGameObject(prefab);
                    }

                    if (new_object != nullptr) {
                        new_object->setPosition(sf::Vector2f(x, y));
                        chunk->addGameObject(new_object);
                    }

                }
            }
            else if (load_object_type == LoadObjectType::Building) {

       
                if (phrase == "id") {
                    short id;
                    lineStream >> id;
                    building = getBuilding(id);
                    //cout << "load building: " << id << "\n";

                }
                else if (phrase == "name") {
                    std::string name;
                    std::getline(lineStream, name, '"');        // get string to temp to sign "
                    std::getline(lineStream, name, '"');        // get string to objectName to sign "
                    //building->name = name;
                    //cout << name << "\n";
                }
                else if (phrase == "size") {
                    lineStream >> building->size.x >> building->size.y;
                    //cout << "size: " << building->size.x << "x" << building->size.y << "\n";
                    
                    for (auto& col : building->colliders)
                        delete col;

                    building->colliders.clear();

                    building->colliders.push_back(new Collider(building->size.x * 16, building->size.y * 16, building->position, 0, -building->size.y / 2 * 16, ColliderType::Rectangle));
                    building->colliders[0]->setPosition(building->position);
                }
                else if (phrase == "door") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    //std::cout << "door \"" << name << "\"\n";

                    GameObject* prefab = getPrefab(ConvertUtf8ToWide(name));
                    if (prefab != nullptr) {
                        building->_door = new Door(prefab);
                        building->_door->setPosition(building->position);

                    }
                }
                else if (phrase == "top_walls") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    //std::cout << "top_walls \"" << name << "\"\n";

                    SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(name));
                    if (tex != nullptr)
                        building->texture_top_walls = tex;
                }
                else if (phrase == "center_walls") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    //std::cout << "center_walls \"" << name << "\"\n";

                    SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(name));
                    if (tex != nullptr)
                        building->texture_center_walls = tex;
                }
                else if (phrase == "bottom_walls") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    //std::cout << "bottom_walls \"" << name << "\"\n";

                    SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(name));
                    if (tex != nullptr)
                        building->texture_bottom_walls = tex;
                }
                else if (phrase == "windows") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    //std::cout << "windows \"" << name << "\"\n";

                    SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(name));
                    if (tex != nullptr)
                        building->texture_windows = tex;
                }
                else if (phrase == "//FLOORS") {

                    // TO-DO
                    //std::cout << "load floors ... \n";

                    if (building->floors != nullptr)
                        delete building->floors;

                    building->floors = new Floors(building->position.x / 16 - building->size.x / 2, building->position.y / 16 - building->size.y, building->size.x, building->size.y);

                    // check the correct of datas
                    std::streampos pos = file.tellg(); // Zapisanie pozycji linii
                    bool correct_data = true;
                    std::string _line;
                    int y = 0;
                    int x;

                    while (std::getline(file, _line) && _line[0] >= '0' && _line[0] <= '9') {

                        std::istringstream iss(_line);
                        int val;
                        x = 0;

                        while (iss >> val)
                            x += 1;

                        if (x != building->size.x) {
                            //cout << x << "\n";
                            correct_data = false;
                        }

                        y += 1;
                    };

                    if (y != building->size.y) {
                        //cout << y << "\n";
                        correct_data = false;
                    }

                    // predefine tiles
                    std::vector < short > floor_tiles(building->size.x*building->size.y, 0);

                    if (correct_data == true) {
                        file.seekg(pos); // wczytanie pozycji linii

                        // load tiles
                        short y = 0;
                        while (y < building->size.y && std::getline(file, line)) {

                            std::istringstream tileStream(line);
                            short value;
                            short x = 0;

                            while (tileStream >> value) {
                                floor_tiles[y * building->size.x + x] = value;
                                x += 1;
                            }

                            y += 1;
                        }


                        for (short y = 0; y < building->size.y; y++) {
                            for (short x = 0; x < building->size.x; x++) {
                                //std::cout << value << " ";
                                building->floors->edit(x, y, floor_tiles[y * building->size.x + x]);
                            }

                            //std::cout << "\n";
                        }
                    }
                }
                else if (phrase == "Wall" || phrase == "Furniture") {
                    std::string name;

                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');

                    GameObject* prefab = getPrefab(ConvertUtf8ToWide(name));
                    if (prefab != nullptr) {

                        //std::cout << prefab->name << "\n";
                        GameObject* new_object = getNewGameObject(prefab);

                        short x, y;
                        lineStream >> x;
                        lineStream >> y;

                        x = x - (building->size.x * 16 / 2) + building->position.x;
                        y = y - (building->size.y * 16) + building->position.y;

                        new_object->setPosition(sf::Vector2f(x, y));
                        building->addGameObject(new_object);
                    }
                }else if(phrase == "Item"){
                    std::string name;

                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');

                    Item* item = getItem(ConvertUtf8ToWide(name));
                    if (item != nullptr) {
                        GameObject* new_object = new ItemOnMap(item);

                        short x, y;
                        lineStream >> x;
                        lineStream >> y;

                        x = x - (building->size.x * 16 / 2) + building->position.x;
                        y = y - (building->size.y * 16) + building->position.y;

                        new_object->setPosition(sf::Vector2f(x, y));
                        building->addGameObject(new_object);
                    }
                }
            }
            else if (load_object_type == LoadObjectType::Character) {

                if (phrase == "ID:") {
                    short id;
                    lineStream >> id;
                    character = getCharacter(id);
                }
                else if (phrase == "Name:") {
                    std::string name;
                    lineStream >> name;
                    character->name = ConvertUtf8ToWide(name);
                }
                else if (phrase == "Dialogue:") {
                    int id;
                    lineStream >> id;
                    character->dialogue = getDialogue(id);
                }
                else if (phrase == "Level:") {
                    lineStream >> character->LEVEL;
                }
                else if (phrase == "Experience:") {
                    lineStream >> character->EXPERIENCE;
                }
                else if (phrase == "SkillPoints:") {
                    lineStream >> character->SKILL_POINTS;
                }
                else if (phrase == "CurrentHP:") {
                    lineStream >> character->attributes[Attribute::HP];
                }
                else if (phrase == "MaxHP:") {
                    lineStream >> character->attributes[Attribute::HP_max];
                }
                else if (phrase == "CurrentMP:") {
                    lineStream >> character->attributes[Attribute::MP];
                }
                else if (phrase == "MaxMP:") {
                    lineStream >> character->attributes[Attribute::MP_max];
                }
                else if (phrase == "Strength:") {
                    lineStream >> character->attributes[Attribute::STRENGTH];
                }
                else if (phrase == "Dexterity:") {
                    lineStream >> character->attributes[Attribute::DEXTERITY];
                }
                else if (phrase == "Intelligence:") {
                    lineStream >> character->attributes[Attribute::INTELLIGENCE];
                }
                else if (phrase == "Body:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->body = ConvertUtf8ToWide(name);
                    character->loadBody();
                }
                else if (phrase == "Head:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->head = ConvertUtf8ToWide(name);
                    character->loadHead();
                }
                else if (phrase == "Helmet:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->helmet = getItem(ConvertUtf8ToWide(name));
                    character->loadHelmet();
                }
                else if (phrase == "Armor:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->armor = getItem(ConvertUtf8ToWide(name));
                    character->loadArmor();
                }
                else if (phrase == "Pants:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->pants = getItem(ConvertUtf8ToWide(name));
                    character->loadPants();
                }
                else if (phrase == "RightHand:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->rightHand = getItem(ConvertUtf8ToWide(name));
                    character->loadRightHand();
                    character->loadBody();
                    character->loadHead();
                    character->loadArmor();
                }
                else if (phrase == "LeftHand:") {
                    std::string name;
                    std::getline(lineStream, name, '"');
                    std::getline(lineStream, name, '"');
                    character->leftHand = getItem(ConvertUtf8ToWide(name));
                    character->loadLeftHand();
                }

            }


        }

        file.close();

        mapVisiblings();
        generateBorders();

        sf::Vector2f pos1((cam->position.x - 100)/8*8, (cam->position.y + 100)/8*8);
        Spell* fire_spell = new AreaFireballSpell(1, pos1.x, pos1.y);
        gameObjects.push_back(fire_spell);

        sf::Vector2f pos2 = pos1 - sf::Vector2f(256, 0);
        Spell* water_spell = new AreaWaterConesSpell(3, pos2.x, pos2.y);
        gameObjects.push_back(water_spell);

        sf::Vector2f pos3 = pos2 - sf::Vector2f(256, 0);
        Spell* circle_spell = new StaticSpell(L"magic_circle", pos3.x, pos3.y);
        gameObjects.push_back(circle_spell);
    }

    void binary_load(std::wstring pathfile = L"world\\world.wrd") {

        class Reader {
            std::istream& is;

        public:
            Reader(std::istream& is) : is(is) { }

            std::string read_string() {
                uint16_t len;
                is.read(reinterpret_cast<char*>(&len), sizeof(uint16_t));

                std::string str(len, '\0'); // utwórz pusty string o długości len
                is.read(&str[0], len);      // bezpieczne wczytanie danych do stringa
                return str;
            }

            uint32_t read_uint32() {
                uint32_t value;
                is.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
                return value;
            }

            uint16_t read_uint16() {
                uint16_t value;
                is.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
                return value;
            }

            uint8_t read_uint8() {
                uint8_t value;
                is.read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
                return value;
            }

            float read_float() {
                float value;
                is.read(reinterpret_cast<char*>(&value), sizeof(float));
                return value;
            }

            int read_int() {
                int value;
                is.read(reinterpret_cast<char*>(&value), sizeof(int));
                return value;
            }

            short read_short() {
                short value;
                is.read(reinterpret_cast<char*>(&value), sizeof(short));
                return value;
            }

            sf::Vector2f read_Vector2f() {
                sf::Vector2f value;
                is.read(reinterpret_cast<char*>(&value.x), sizeof(float));
                is.read(reinterpret_cast<char*>(&value.y), sizeof(float));
                return value;
            }

            sf::Vector2i read_Vector2i() {
                sf::Vector2i value;
                is.read(reinterpret_cast<char*>(&value.x), sizeof(int));
                is.read(reinterpret_cast<char*>(&value.y), sizeof(int));
                return value;
            }
        };


        std::ifstream file(pathfile, std::ios::binary);
        Reader reader(file);

        std::vector < std::wstring > pathfiles;

        while (file && !file.eof()) {
            std::string phrase;

            try {
                phrase = reader.read_string();
            }
            catch (...) {
                break; // na wypadek błędu odczytu
            }

            if (phrase == "#Resources") {

                uint32_t resources_count = reader.read_uint32();

                for (uint32_t i = 0; i < resources_count; i++) {
                    pathfiles.push_back(ConvertUtf8ToWide(reader.read_string()));
                    //cout << i << " : " << pathfiles.back() << "\n";

                }
            }
            else if (phrase == "#Map") {

                // clearing chunks
                for (auto& chunk : chunks)
                    delete chunk;

                chunks.clear();
                clearAllMainListsOfGameObjects();

                this->width = reader.read_uint8();
                this->height = reader.read_uint8();

                for (short i = 0; i < width*height; i++) {
                    
                    sf::Vector2i coords = reader.read_Vector2i();
                    Chunk* ch = new Chunk(coords.x, coords.y);
                    
                    //std::cout << coords.x << " " << coords.y << "\n";

                    for (short y = 0; y < 16; y++) {
                        for (short x = 0; x < 16; x++) {
                            short t_val = reader.read_short();
                            ch->terrain->edit(x, y, t_val);
                            (t_val == 0 || (t_val >= countOfBasicTerrain && t_val < countOfBasicTerrain + 16)) ? ch->water->edit(x, y, t_val) : ch->water->edit(x, y, -1);

                        }
                    }

                    uint32_t objects_count = reader.read_uint32();
                    for (uint32_t i = 0; i < objects_count; i++) {
                        uint16_t objectType = reader.read_uint16();
                        GameObject* object = nullptr;

                        if (objectType == static_cast<uint16_t>(GameObjectType::Building)) {
                            object = new Building(reader.read_short());                            
                        }
                        else if (objectType == static_cast<uint16_t>(GameObjectType::Character)) {
                            object = new Character(reader.read_uint32());
                        }
                        else if (objectType == static_cast<uint16_t>(GameObjectType::InventoryOnMap)) {
                            Inventory* in = new Inventory(reader.read_short());
                            object = new InventoryOnMap(in);
                        }
                        else {
                            GameObject* prefab = getPrefab(pathfiles[reader.read_uint32()]);
                            //std::cout << "Other\n";
                            object = getNewGameObject(prefab);
                            
                        }

                        if (object != nullptr) {
                            object->setPosition(reader.read_Vector2f());
                            ch->addGameObject(object);
                        }
                    }

                    chunks.push_back(ch);
                }

            }
            else if (phrase == "#Building") {

                Building* building = getBuilding(reader.read_short());
                building->name = ConvertUtf8ToWide(reader.read_string());
                building->size = reader.read_Vector2i();
                
                building->_door = dynamic_cast<Door*>(getNewGameObject(getPrefab(ConvertUtf8ToWide(reader.read_string()))));
                building->_door->setPosition(building->position);

                building->texture_top_walls = getSingleTexture(ConvertUtf8ToWide(reader.read_string()));
                building->texture_center_walls = getSingleTexture(ConvertUtf8ToWide(reader.read_string()));
                building->texture_bottom_walls = getSingleTexture(ConvertUtf8ToWide(reader.read_string()));
                building->texture_windows = getSingleTexture(ConvertUtf8ToWide(reader.read_string()));

                short floor_w = reader.read_short();
                short floor_h = reader.read_short();

                if (building->floors != nullptr)
                    delete building->floors;

                building->floors = new Floors(building->position.x / 16 - building->size.x / 2, building->position.y / 16 - building->size.y, building->size.x, building->size.y);

                for (short y = 0; y < floor_h; y++) {
                    for (short x = 0; x < floor_w; x++) {
                        building->floors->edit(x, y, reader.read_short());
                    }
                }

                uint32_t objects_count = reader.read_uint32();
                for (uint32_t i = 0; i < objects_count; i++) {

                    uint16_t objectType = reader.read_uint16();
                    GameObject* prefab = getPrefab(pathfiles[reader.read_uint32()]);
                    if (prefab != nullptr) {
                        GameObject* object = getNewGameObject(prefab);
                        sf::Vector2f position = reader.read_Vector2f();
                        position.x = position.x - (building->size.x * 16 / 2) + building->position.x;
                        position.y = position.y - (building->size.y * 16) + building->position.y;
                        object->setPosition(position);
                        building->addGameObject(object);
                    }
                }

                building->loadTexture();

            }
            else if(phrase == "#Inventory") {

                clearInventories();
                Inventory* inventory = new Inventory(reader.read_short());
                uint32_t items_count = reader.read_uint32();

                for (uint32_t i = 0; i < items_count; i++) {

                    uint32_t id = reader.read_uint32();
                    Item* item = getItem(pathfiles[id]);
                    uint16_t count = reader.read_uint16();

                    inventory->addItem(item, count);

                }

                std::cout << "#Inventory: " << inventory->id << "\n";
                for (short i = 0; i < inventory->items.size(); i++) {
                    std::wcout << inventory->items[i]->name << L" " << inventory->counts[i] << L"\n";
                }
            }
            else if (phrase == "#Character") {

                Character* character = getCharacter(reader.read_int());
                character->name = ConvertUtf8ToWide(reader.read_string());
                character->dialogue = getDialogue(reader.read_int());

                character->LEVEL = reader.read_int();
                character->EXPERIENCE = reader.read_int();
                character->SKILL_POINTS = reader.read_int();

                character->attributes[Attribute::HP] = reader.read_int();
                character->attributes[Attribute::HP_max] = reader.read_int();
                character->attributes[Attribute::MP] = reader.read_int();
                character->attributes[Attribute::MP_max] = reader.read_int();

                character->attributes[Attribute::STRENGTH] = reader.read_int();
                character->attributes[Attribute::DEXTERITY] = reader.read_int();
                character->attributes[Attribute::INTELLIGENCE] = reader.read_int();

                /////////////////////////////

                character->body = ConvertUtf8ToWide(reader.read_string());
                character->head = ConvertUtf8ToWide(reader.read_string());

                /////////////////////////////

                character->helmet = getItem(ConvertUtf8ToWide(reader.read_string()));
                character->armor = getItem(ConvertUtf8ToWide(reader.read_string()));
                character->pants = getItem(ConvertUtf8ToWide(reader.read_string()));
                character->rightHand = getItem(ConvertUtf8ToWide(reader.read_string()));
                character->leftHand = getItem(ConvertUtf8ToWide(reader.read_string()));

                /////////////////////////////

                character->loadBody();
                character->loadHead();
                character->loadHelmet();
                character->loadArmor();
                character->loadPants();
                character->loadRightHand();
                character->loadLeftHand();
                character->loadSprites();
            }

            
        }

        file.close();

    }

    bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

        if (abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1 - y2) < (height1 + height2) / 2.0f)
            return true;

        return false;

    }

    void mapVisiblings() {
        sf::Vector2f chunk_position;
        float width = screenWidth * 2.0f;
        float height = screenHeight * 2.0f;
        bool prevVisible;

        for (auto& chunk : chunks) {

            chunk_position.x = (chunk->terrain->coords.x * tileSide) + 8 * tileSide;
            chunk_position.y = (chunk->terrain->coords.y * tileSide) + 8 * tileSide;

            prevVisible = chunk->visible;

            std::vector < GameObject* > objects_from_chunk;
            objects_from_chunk = chunk->getAllGameObjects();
            bool object_from_chunk_is_selected = false;

            for (short i = 0; i < objects_from_chunk.size(); i++) {
                if (objects_from_chunk[i]->isSelected) {
                    object_from_chunk_is_selected = true;
                    break;
                }
            }

            if (object_from_chunk_is_selected == false) {
                chunk->visible = intersectionTwoRectangles(cam->position.x, cam->position.y, width, height, chunk_position.x, chunk_position.y, 16 * tileSide, 16 * tileSide);
            }
            else
                chunk->visible = true;

            if (prevVisible == false && chunk->visible == true) {
                chunk->addGameObjectsToMainLists();
            }
            else if (prevVisible == true && chunk->visible == false) {
                chunk->removeGameObjectsFromMainLists();
            }

        }
    }

    void generateBorders(Chunk* chunk) {
        Chunk* centerChunk;
        Chunk* topChunk;
        Chunk* bottomChunk;
        Chunk* leftChunk;
        Chunk* rightChunk;

        Terrain* centerTerrain;
        Terrain* topTerrain;
        Terrain* bottomTerrain;
        Terrain* leftTerrain;
        Terrain* rightTerrain;

        for (short y = -1; y <= 1; y++)
            for (short x = -1; x <= 1; x++) {
                centerChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y);

                if (centerChunk != nullptr) {
                    topChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y - 1);
                    bottomChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y + 1);
                    leftChunk = getChunk(chunk->coords.x + x - 1, chunk->coords.y + y);
                    rightChunk = getChunk(chunk->coords.x + x + 1, chunk->coords.y + y);

                    centerTerrain = centerChunk->terrain;
                    (topChunk != nullptr) ? topTerrain = topChunk->terrain : topTerrain = nullptr;
                    (bottomChunk != nullptr) ? bottomTerrain = bottomChunk->terrain : bottomTerrain = nullptr;
                    (leftChunk != nullptr) ? leftTerrain = leftChunk->terrain : leftTerrain = nullptr;
                    (rightChunk != nullptr) ? rightTerrain = rightChunk->terrain : rightTerrain = nullptr;

                    centerChunk->borders->generate(centerTerrain, topTerrain, bottomTerrain, leftTerrain, rightTerrain);
                }

            }
    }

    void generateBorders() {
        Chunk* chunk;
        Chunk* topChunk;
        Chunk* bottomChunk;
        Chunk* leftChunk;
        Chunk* rightChunk;

        Terrain* terrain;
        Terrain* topTerrain;
        Terrain* bottomTerrain;
        Terrain* leftTerrain;
        Terrain* rightTerrain;

        short y, x;

        for (int i = 0; i < chunks.size(); i++) {

            y = chunks[i]->coords.y;
            x = chunks[i]->coords.x;

            //cout << x << " " << y << "\n";

            chunk = getChunk(x, y);
            topChunk = getChunk(x, y - 1);
            bottomChunk = getChunk(x, y + 1);
            leftChunk = getChunk(x - 1, y);
            rightChunk = getChunk(x + 1, y);

            terrain = chunk->terrain;
            (topChunk != nullptr) ? topTerrain = topChunk->terrain : topTerrain = nullptr;
            (bottomChunk != nullptr) ? bottomTerrain = bottomChunk->terrain : bottomTerrain = nullptr;
            (leftChunk != nullptr) ? leftTerrain = leftChunk->terrain : leftTerrain = nullptr;
            (rightChunk != nullptr) ? rightTerrain = rightChunk->terrain : rightTerrain = nullptr;

            chunks[i]->borders->generate(terrain, topTerrain, bottomTerrain, leftTerrain, rightTerrain);
        }
    }

    void update() {

    }

    void draw() {
        for (auto& chunk : chunks) {
            if (chunk->visible) {
                chunk->draw();
            }
        }
    }

    void drawColliders() {
        for (auto& chunk : chunks) {
            if (chunk->visible) {
                chunk->drawAllStatistics();
            }
            
        }
    }


};

Mapa* mapa = nullptr;

#endif // ! Map_hpp
