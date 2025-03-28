#ifndef  Map_hpp
#define  Map_hpp

class Chunk {
public:
    sf::Vector2i coords;
    Terrain* terrain;
    Water* water;
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
        water = new Water(x * 16, y * 16, 16, 16);
        borders = new Borders();

        short frameWidth = 2;
        frame = sf::RectangleShape(sf::Vector2f(256 - 2 * frameWidth, 256 - 2 * frameWidth));
        frame.setPosition(x * 256, y * 256);
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineColor(sf::Color(128, 48, 48, 128));
        frame.setOutlineThickness(frameWidth);

        coordsText = sf::Text();
        coordsText.setFont(basicFont);
        coordsText.setCharacterSize(16);
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
                std::cout << "delete character\n";
                _characters.erase(it);
            }

        }

        if (object->type == GameObjectType::Building) {
            auto it = std::find(_buildings.begin(), _buildings.end(), object);
            if (it != _buildings.end())
                _buildings.erase(it);
        }
    }

    void update()
    {
    }

    void draw() {
        window->draw(*terrain);

        water->update();    // TO-DO
        window->draw(*water);

        if (renderTilesBorders == true)
            window->draw(*borders);
    }

    void drawAllStatistics() {
        if (renderBorders)
            window->draw(frame);

        if (renderCoords)
            window->draw(coordsText);
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

    void save(std::string filename = "world/world.map") {
        std::ofstream file(filename);

        for (auto& chunk : chunks) {
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
                file << "Nature \"" << nature->name << "\" y=" << int(nature->position.y) << " x=" << int(nature->position.x) << "\n";

            for (auto& object : chunk->_objects)
                file << "Object \"" << object->name << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& item : chunk->_items)
                file << "Item \"" << item->name << "\" y=" << int(item->position.y) << " x=" << int(item->position.x) << "\n";

            for (auto& inventory : chunk->_inventories)
                file << "Inventory \"" << inventory->name << "\" y=" << int(inventory->position.y) << " x=" << int(inventory->position.x) << "\n";

            for (auto& flat : chunk->_flatObjects)
                file << "FlatObject \"" << flat->name << "\" y=" << int(flat->position.y) << " x=" << int(flat->position.x) << "\n";

            for (auto& monster : chunk->_monsters)
                file << "Monster \"" << monster->name << "\" y=" << int(monster->base.y) << " x=" << int(monster->base.x) << "\n";

            for (auto& object : chunk->_smallObjects)
                file << "SmallObject \"" << object->name << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& object : chunk->_doors)
                file << "Door \"" << object->name << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

            for (auto& character : chunk->_characters)
                file << "Character \"" << character->name << "\" y=" << int(character->position.y) << " x=" << int(character->position.x) << "\n";

            for (auto& building : chunk->_buildings)
                file << "Building \"" << to_string(building->id) << "\" y=" << int(building->position.y) << " x=" << int(building->position.x) << "\n";

            file << "\n";
        }

        file.close();

        std::cout << "saved map\n";
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

    void load(std::string filename = "world/world.map") {
        // clearing chunks
        for (auto& chunk : chunks) {
            delete chunk;
        }

        chunks.clear();

        clearAllMainListsOfGameObjects();

        // create chunks
        short width = 32;
        short height = 32;

        for (short y = 0; y < height; y++) {
            for (short x = 0; x < width; x++) {
                Chunk* ch = new Chunk(x, y);
                chunks.push_back(ch);
            }
        }

        // open file map
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "cant open map: " << filename << "\n";
            return;
        }

        std::cout << "open map: " << filename << "\n";

        std::string line;
        std::string objectType;
        Chunk* chunk = nullptr;

        // loading
        while (std::getline(file, line)) {

            if (line.empty()) {
                //cout << "empty line\n";
                continue;
            }

            std::istringstream lineStream(line);
            lineStream >> objectType;

            if (objectType == "Chunk") {

                // load Chunk
                std::regex chunk_regex(R"(Chunk y=([0-9]+) x=([0-9]+))");
                std::smatch chunk_match;

                if (std::regex_search(line, chunk_match, chunk_regex)) {
                    int chunk_y = std::stoi(chunk_match[1]);
                    int chunk_x = std::stoi(chunk_match[2]);

                    // get chunk
                    chunk = getChunk(chunk_x, chunk_y);

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

                std::getline(lineStream, temp, '"');         // get string to temp to sign "
                std::getline(lineStream, objectName, '"');   // get string to objectName to sign "
                std::getline(lineStream, temp, '=');         // get string to temp to sign =
                lineStream >> y;                        // string to y
                std::getline(lineStream, temp, '=');         // get string to temp to sign =
                lineStream >> x;                        // string to x
                //cout << objectType << " \"" << objectName << "\" " << x << " " << y << "\n";

                chunk = getChunk(sf::Vector2f(x, y));
                if (chunk == nullptr) {
                    chunk = new Chunk(x / 256, y / 256);
                    chunks.push_back(chunk);
                }

                if (objectType == "Nature") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        Nature* nature = new Nature(prefab, x, y);
                        chunk->_natures.push_back(nature);
                    }
                }

                if (objectType == "Object") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        Object* object = new Object(prefab, x, y);
                        chunk->_objects.push_back(object);
                    }
                }

                if (objectType == "Item") {
                    Item* item = getItem(objectName);
                    if (item != nullptr) {
                        ItemOnMap* itemOnMap = new ItemOnMap(item, x, y);
                        chunk->_items.push_back(itemOnMap);
                    }
                }

                if (objectType == "Inventory") {
                    // TO-DO - get Inventory(id)
                    Inventory* inventory = getInventory(0);
                    if (inventory != nullptr) {
                        InventoryOnMap* inventoryOnMap = new InventoryOnMap(inventory, x, y);
                        chunk->_inventories.push_back(inventoryOnMap);
                    }
                }

                if (objectType == "FlatObject") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        FlatObject* flat = new FlatObject(prefab, x, y);
                        chunk->_flatObjects.push_back(flat);
                    }
                }

                if (objectType == "Monster") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        Monster* monster = new Monster(prefab, x, y);
                        chunk->_monsters.push_back(monster);
                    }
                }

                if (objectType == "SmallObject") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        SmallObject* object = new SmallObject(prefab, x, y);
                        chunk->_smallObjects.push_back(object);
                    }
                }

                if (objectType == "Door") {
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        Door* door = new Door(prefab, x, y);
                        chunk->_doors.push_back(door);
                    }
                }

                if (objectType == "Character") {
                    // To-DO - get Character
                    GameObject* prefab = getPrefab(objectName);
                    if (prefab != nullptr) {
                        Character* character = new Character(prefab, x, y);
                        chunk->_characters.push_back(character);
                    }
                }

                if (objectType == "Building") {
                    // TO-DO
                    Building* building = new Building(stoi(objectName), x, y);
                    chunk->_buildings.push_back(building);
                }

            }


        }

        file.close();

        mapVisiblings();
        generateBorders();
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

            chunk->visible = intersectionTwoRectangles(cam->position.x, cam->position.y, width, height, chunk_position.x, chunk_position.y, 16 * tileSide, 16 * tileSide);

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
            chunk->draw();
        }
    }

    void drawStatistics() {
        for (auto& chunk : chunks) {
            chunk->drawAllStatistics();
        }
    }


};

Mapa* mapa = nullptr;

#endif // ! Map_hpp
