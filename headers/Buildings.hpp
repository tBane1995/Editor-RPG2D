#ifndef BuildingsManager_hpp
#define BuildingsManager_hpp

class Building : public GameObject {
public:
    sf::Vector2i size;

    short id = -1;

    std::vector < ItemOnMap* > _items;      // from item Manager
    std::vector < Furniture* > _furnitures; // from furniture Manager
    std::vector < Wall* > _walls;           // from wall Manager

    SingleTexture* texture_top_walls = nullptr;
    SingleTexture* texture_center_walls = nullptr;
    SingleTexture* texture_bottom_walls = nullptr;
    SingleTexture* texture_windows = nullptr;
    Door* _door = nullptr;
    Floors* floors = nullptr;


    short x1, x2, y1, y2; // corners of building

    Building(std::wstring location) : GameObject(GameObjectType::Building, -1, 0, 0) {
        this->id = -1;

        size = sf::Vector2i(16, 16);
        colliders.push_back(new Collider(size.x * 16, size.y * 16, position, 0, -size.y / 2 * 16, ColliderType::Rectangle));
        colliders[0]->setPosition(position);

        floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);
        _door = new Door(getPrefab(L"doors\\wooden_door"));
        _door->setPosition(position);
        texture_top_walls = getSingleTexture(L"walls\\wooden_wall");
        texture_center_walls = getSingleTexture(L"walls\\stone_wall");
        texture_bottom_walls = getSingleTexture(L"walls\\stone_wall");
        texture_windows = nullptr;

        if(name != L"") {
            this->name = getShortName(location);
            size_t pos = name.find_last_of('.');
            if (pos != std::string::npos)
                name = name.substr(0, pos);

            type = GameObjectType::Building;

            load(location);
            loadTexture();
        }
    }

    Building(GameObject* object) : GameObject(GameObjectType::Building, -1, 0, 0) {
        
        this->id = -1;
        type = GameObjectType::Building;

        size = sf::Vector2i(16, 16);
        colliders.push_back(new Collider(size.x * 16, size.y * 16, position, 0, -size.y / 2 * 16, ColliderType::Rectangle));
        colliders[0]->setPosition(position);

        floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);
        _door = new Door(getPrefab(L"doors\\wooden_door"));
        _door->setPosition(position);
        texture_top_walls = getSingleTexture(L"walls\\wooden_wall");
        texture_center_walls = getSingleTexture(L"walls\\stone_wall");
        texture_bottom_walls = getSingleTexture(L"walls\\stone_wall");
        texture_windows = nullptr;

        Building* ob = dynamic_cast<Building*>(object);

        if (ob != nullptr) {
            name = ob->name;
            position = ob->position;

            size = ob->size;
            colliders.push_back(new Collider(size.x * 16, size.y * 16, position, 0, -size.y / 2 * 16, ColliderType::Rectangle));
            colliders[0]->setPosition(position);

            floors = new Floors(ob->floors);
            _door = new Door(ob->_door);
            _door->setPosition(position);
            texture_top_walls = ob->texture_top_walls;
            texture_center_walls = ob->texture_center_walls;
            texture_bottom_walls = ob->texture_bottom_walls;
            texture_windows = ob->texture_windows;
            
            for (auto& item : ob->_items) {
                _items.push_back(new ItemOnMap(item->item));
                _items.back()->setPosition(item->position);
            }
                

            for (auto& fur : ob->_furnitures) {
                _furnitures.push_back(new Furniture(fur));
                _furnitures.back()->setPosition(fur->position);
            }
                

            for (auto& wall : ob->_walls) {
                _walls.push_back(new Wall(wall));
                _walls.back()->setPosition(wall->position);
            }
                

            loadTexture();
        }
    }

    Building(short id) : GameObject(GameObjectType::Building, id, 0, 0 )
    {
        this->id = id;
        type = GameObjectType::Building;

        std::string location = getLocation();
        
        size = sf::Vector2i(16, 16);
        colliders.push_back(new Collider(size.x * 16, size.y * 16, position, 0, -size.y / 2 * 16, ColliderType::Rectangle));
        colliders[0]->setPosition(position);

        floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);
        _door = new Door(getPrefab(L"doors\\wooden_door"));
        _door->setPosition(position);
        texture_top_walls = getSingleTexture(L"walls\\wooden_wall");
        texture_center_walls = getSingleTexture(L"walls\\stone_wall");
        texture_bottom_walls = getSingleTexture(L"walls\\stone_wall");
        texture_windows = nullptr;

        loadTexture();
    }

    

    virtual ~Building() {

        if(_door!=nullptr)
            delete _door;

        if(floors!=nullptr)
            delete floors;

        for (auto& item : _items)
            delete item;

        for (auto& furniture : _furnitures)
            delete furniture;

        for (auto& wall : _walls)
            delete wall;
    }

    void calculateCorners()
    {
        x1 = position.x - size.x / 2 * 16;
        x2 = position.x + size.x / 2 * 16;
        y1 = position.y - size.y * 16;
        y2 = position.y;
    }
    virtual void mouseHovering() {
        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 && worldMousePosition.y > y1 && worldMousePosition.y < y2)
            mouseIsHover = true;
        else
            mouseIsHover = false;
    }

    void setPosition(sf::Vector2f position) {

        for (auto& col : colliders) {
            sf::Vector2f pos = position;
            col->setPosition(pos);
        }

        sf::Vector2f floor_position;
        floor_position.x = position.x/16*16 - size.x/2*16;
        floor_position.y = position.y/16*16 - size.y*16;
        floors->setPosition(floor_position);

        sf::Vector2f offset;

        offset = _door->position - this->position;
        _door->setPosition(position + offset);
           
        for (auto& wall : _walls) {
            offset = wall->position - this->position;
            wall->setPosition(position + offset);
        }

        for (auto& item : _items) {
            offset = item->position - this->position;
            item->setPosition(position + offset);
        }

        for (auto& furniture : _furnitures) {
            offset = furniture->position - this->position;
            furniture->setPosition(position + offset);
        }

        textname.setPosition(position.x, position.y - height - 35);
        sprite.setPosition(position.x, position.y);
        this->position = position;
    }

    void addGameObject(GameObject* object) {

        if (object == nullptr)
            return;

        if (object->type == GameObjectType::Wall) {
            _walls.push_back(dynamic_cast<Wall*>(object));
        }

        if (object->type == GameObjectType::Furniture) {
            _furnitures.push_back(dynamic_cast<Furniture*>(object));
        }

        if (object->type == GameObjectType::ItemOnMap) {
            _items.push_back(dynamic_cast<ItemOnMap*>(object));
        }
    }

    void deleteGameObject(GameObject* object) {
        
        if (object == nullptr)
            return;

        if (object->type == GameObjectType::Door) {
            _door = nullptr;
        }

        if (object->type == GameObjectType::Wall) {
            auto it = std::find(_walls.begin(), _walls.end(), object);
            if (it != _walls.end())
                _walls.erase(it);
        }

        if (object->type == GameObjectType::ItemOnMap) {
            auto it = std::find(_items.begin(), _items.end(), object);
            if (it != _items.end())
                _items.erase(it);
        }

        if (object->type == GameObjectType::Furniture) {
            auto it = std::find(_furnitures.begin(), _furnitures.end(), object);
            if (it != _furnitures.end())
                _furnitures.erase(it);
        }

    }

    void addGameObjectsToMainLists() {
        doors.push_back(_door);
        gameObjects.push_back(_door);

        for (auto& item : _items) {
            itemsOnMap.push_back(item);
            gameObjects.push_back(item);
        }

        for (auto& furniture : _furnitures) {
            furnitures.push_back(furniture);
            gameObjects.push_back(furniture);
        }

        for (auto& wall : _walls) {
            walls.push_back(wall);
            gameObjects.push_back(wall);
        }
    }

    std::vector < GameObject* > getAllGameObjects() {
        std::vector < GameObject* > all_gameobjects;

        for (auto& wall : _walls)
            all_gameobjects.push_back(wall);

        for (auto& fur : _furnitures)
            all_gameobjects.push_back(fur);

        for (auto& item : _items)
            all_gameobjects.push_back(item);

        return all_gameobjects;
    }

    std::string getLocation() {
        std::string location = "assets\\buildings\\building_";
        if (id < 10) location += "00";
        else if (id < 100) location += "0";
        location += to_string(this->id) + ".bld";

        return location;
    }

    bool playerInside() {

        short x3, y3, rx3, ry3;
        x3 = player->position.x;
        y3 = player->position.y;
        rx3 = (player->colliders[0]->width / 2.0f);
        ry3 = (player->colliders[0]->length) / 2.0f;

        if (intersectionRectangleWithElipse((x1 + x2) / 2, (y1 + y2) / 2, x2 - x1, y2 - y1, x3, y3, rx3, ry3))
            return true;
        else
            return false;
    }

    bool isPart(GameObject* object) {
        if (object == nullptr)
            return false;

        for (auto& item : _items)
            if (object == item)
                return true;

        for (auto& furniture : _furnitures)
            if (object == furniture)
                return true;

        for (auto& wall : _walls)
            if (object == wall)
                return true;

        if (object == _door)
            return true;

        return false;
    }

    void loadTexture() {

        // check the size
        //cout << size.x << " " << size.y << "\n";

        short walls_height = 3;

        // variables for generate roof
        float tiles_rows = size.y / 2;
        float tiles_columns = size.x / 2;
        float tile_width = float(size.x) / 4.0f * 32.0f / tiles_columns;
        float tile_height = float(size.y / 2.0f - walls_height + 1) * 32.0f / tiles_rows;
        float tile_border = 1;

        // TO-DO
        //delete RoofTexture;
        //RoofTexture = nullptr;

        sf::Image main_image;
        main_image.create(size.x*16+64, (walls_height+size.x/8+size.y/2 - 2)*32, sf::Color::Transparent);
        
        // BOTTOM WALLS
        sf::Image bottom_walls_image;
        bottom_walls_image.create(32, 32, sf::Color::Transparent);
        bottom_walls_image = texture_bottom_walls->texture->copyToImage();

        for (short x = 0; x < size.x/2; x++)
            main_image.copy(bottom_walls_image, x*32+32, main_image.getSize().y-32);

        // CENTER WALLS
        sf::Image center_walls_image;
        center_walls_image = texture_center_walls->texture->copyToImage();
        for (short y = 1; y < walls_height; y++) {
            for (short x = 0; x < size.x / 2; x++)
                main_image.copy(center_walls_image, x * 32 + 32, main_image.getSize().y - 32 - y * 32);
        }

        // TOP WALLS
        sf::Image top_walls_image;
        top_walls_image = texture_top_walls->texture->copyToImage();
        for (short y = 0; y <= size.x/4; y++) {
            for (short x = y * 2; x < size.x/2 - y*2; x++) {

                short dest_y = main_image.getSize().y - 32 * walls_height - (y+1)*32;
                main_image.copy(top_walls_image, x * 32 + 32, dest_y);
            }
        }

        // LOAD TEXTURES OF ROOF
        sf::Texture tile_left_texture = *getSingleTexture(L"buildings\\parts\\tile_left")->texture;
        sf::Texture tile_left_top_texture = *getSingleTexture(L"buildings\\parts\\tile_left_top")->texture;
        sf::Texture tile_left_bottom_texture = *getSingleTexture(L"buildings\\parts\\tile_left_bottom")->texture;

        sf::Texture tile_right_texture = *getSingleTexture(L"buildings\\parts\\tile_right")->texture;
        sf::Texture tile_right_top_texture = *getSingleTexture(L"buildings\\parts\\tile_right_top")->texture;
        sf::Texture tile_right_bottom_texture = *getSingleTexture(L"buildings\\parts\\tile_right_bottom")->texture;

        sf::Texture tile_center_texture = *getSingleTexture(L"buildings\\parts\\tile_center")->texture;
        sf::Texture tile_center_top_texture = *getSingleTexture(L"buildings\\parts\\tile_center_top")->texture;
        sf::Texture tile_center_bottom_texture = *getSingleTexture(L"buildings\\parts\\tile_center_bottom")->texture;

        sf::Texture bar_of_roof_texture = *getSingleTexture(L"buildings\\parts\\bar")->texture;

        // TILE DEFINITION
        sf::Vector2f tile_size(16, 16);
        sf::Image tile_image;
        sf::Image tile_top_image;
        sf::Image tile_bottom_image;

        // CREATE LEFT PART ROOF
        sf::Image left_part_roof_image;
        left_part_roof_image.create(size.x/2*16,(size.y-2)*16, sf::Color::Red);
        
        tile_image = tile_left_texture.copyToImage();
        tile_top_image = tile_left_top_texture.copyToImage();
        tile_bottom_image = tile_left_bottom_texture.copyToImage();

        for (short x = 0; x < size.x/2/(tile_size.x/16); x += 1)
        {
            if (x % 2 == 1) {
                for (short y = 0; y < (size.y - 2)/(tile_size.y/16); y += 1)
                {
                    float dest_x = x * tile_size.x;
                    float dest_y = y * tile_size.y;
                    left_part_roof_image.copy(tile_image, dest_x, dest_y);
                }
            }
            else {
                left_part_roof_image.copy(tile_top_image, x*tile_size.x, 0);

                for (short y = 0; y < (size.y-2-(tile_size.y/16))/(tile_size.y/16); y += 1)
                {
                    float dest_x = x * tile_size.x;
                    float dest_y = y * tile_size.y+tile_size.y/2;
                    left_part_roof_image.copy(tile_image, dest_x, dest_y);
                }

                left_part_roof_image.copy(tile_bottom_image, x*tile_size.x, (size.y-2)/(tile_size.y/16)*tile_size.y-tile_size.y/2);
            }
        }

        // CREATE RIGHT PART ROOF
        sf::Image right_part_roof_image;
        right_part_roof_image.create(size.x * 16/2, (size.y - 2) * 16, sf::Color::Transparent);

        tile_image = tile_right_texture.copyToImage();
        tile_top_image = tile_right_top_texture.copyToImage();
        tile_bottom_image = tile_right_bottom_texture.copyToImage();

        for (short x = 0; x < size.x / 2 / (tile_size.x / 16); x += 1)
        {
            if (x % 2 == 0) {
                for (short y = 0; y < (size.y - 2) / (tile_size.y / 16); y += 1)
                {
                    float dest_x = x * tile_size.x;
                    float dest_y = y * tile_size.y;
                    right_part_roof_image.copy(tile_image, dest_x, dest_y);
                }
            }
            else {
                right_part_roof_image.copy(tile_top_image, x * tile_size.x, 0);

                for (short y = 0; y < (size.y - 2 - (tile_size.y / 16)) / (tile_size.y / 16); y += 1)
                {
                    float dest_x = x * tile_size.x;
                    float dest_y = y * tile_size.y + tile_size.y / 2;
                    right_part_roof_image.copy(tile_image, dest_x, dest_y);
                }

                right_part_roof_image.copy(tile_bottom_image, x * tile_size.x, (size.y - 2) / (tile_size.y / 16) * tile_size.y - tile_size.y / 2);
            }
        }

        // CREATE CENTER PART ROOF
        sf::Image center_part_roof_image;
        center_part_roof_image.create(tile_size.x, (size.y - 2) * 16, sf::Color::Transparent);

        tile_image = tile_center_texture.copyToImage();
        tile_top_image = tile_center_top_texture.copyToImage();
        tile_bottom_image = tile_center_bottom_texture.copyToImage();

        center_part_roof_image.copy(tile_top_image, 0, 0);

        for (short y = 0; y < (size.y - 2 - (tile_size.y / 16)) / (tile_size.y / 16); y += 1)
        {
            float dest_y = y * tile_size.y + tile_size.y / 2;
            center_part_roof_image.copy(tile_image, 0, dest_y);
        }

        center_part_roof_image.copy(tile_bottom_image, 0, (size.y - 2) / (tile_size.y / 16) * tile_size.y - tile_size.y / 2);

        // TEXTURES 
        sf::Texture left_part_roof_texture;
        left_part_roof_texture.loadFromImage(left_part_roof_image);
        
        sf::Texture right_part_roof_texture;
        right_part_roof_texture.loadFromImage(right_part_roof_image);

        sf::Texture center_part_roof_texture;
        center_part_roof_texture.loadFromImage(center_part_roof_image);

        // VERTEXES ARRAYS
        sf::VertexArray left_part_vertex(sf::Quads, 4);
        left_part_vertex[0].position = sf::Vector2f(32/2+size.x/2*16, 0);
        left_part_vertex[1].position = sf::Vector2f(32/2, (size.x/4)*16);
        left_part_vertex[2].position = sf::Vector2f(32/2, (size.y-4+size.x/4)*16);
        left_part_vertex[3].position = sf::Vector2f(32/2+size.x/2*16, (size.y-4)*16);

        left_part_vertex[0].texCoords = sf::Vector2f(left_part_roof_image.getSize().x, 0);
        left_part_vertex[1].texCoords = sf::Vector2f(0, 0);
        left_part_vertex[2].texCoords = sf::Vector2f(0, left_part_roof_image.getSize().y);
        left_part_vertex[3].texCoords = sf::Vector2f(left_part_roof_image.getSize().x, left_part_roof_image.getSize().y);

        sf::VertexArray right_part_vertex(sf::Quads, 4);
        right_part_vertex[0].position = sf::Vector2f(32+size.x/2*16, 0);
        right_part_vertex[1].position = sf::Vector2f(32+size.x*16, size.x/4 * 16);
        right_part_vertex[2].position = sf::Vector2f(32+size.x*16, (size.y-4 + size.x / 4) * 16);
        right_part_vertex[3].position = sf::Vector2f(32+size.x/2*16, (size.y-4)*16);

        right_part_vertex[0].texCoords = sf::Vector2f(0, 0);
        right_part_vertex[1].texCoords = sf::Vector2f(right_part_roof_image.getSize().x, 0);
        right_part_vertex[2].texCoords = sf::Vector2f(right_part_roof_image.getSize().x, right_part_roof_image.getSize().y);
        right_part_vertex[3].texCoords = sf::Vector2f(0, right_part_roof_image.getSize().y);

        sf::VertexArray center_part_vertex(sf::Quads, 4);
        center_part_vertex[0].position = sf::Vector2f(32/2+size.x/2*16, 0);
        center_part_vertex[1].position = sf::Vector2f(32/2+size.x/2*16 + tile_width, 0);
        center_part_vertex[2].position = sf::Vector2f(32/2+size.x/2*16 + tile_width, (size.y-4)*16);
        center_part_vertex[3].position = sf::Vector2f(32/2+size.x/2*16, (size.y-4)*16);

        center_part_vertex[0].texCoords = sf::Vector2f(0, 0);
        center_part_vertex[1].texCoords = sf::Vector2f(center_part_roof_image.getSize().x, 0);
        center_part_vertex[2].texCoords = sf::Vector2f(center_part_roof_image.getSize().x, center_part_roof_image.getSize().y);
        center_part_vertex[3].texCoords = sf::Vector2f(0, center_part_roof_image.getSize().y);

        float width_of_roof = 4;

        sf::VertexArray left_bar_vertex(sf::Quads, 4);
        left_bar_vertex[0].position = sf::Vector2f(32/2,(size.y-4+size.x/4)*16+width_of_roof);
        left_bar_vertex[1].position = sf::Vector2f(32/2+size.x/2*16, (size.y-4)*16+width_of_roof);
        left_bar_vertex[2].position = sf::Vector2f(32/2+size.x/2*16, (size.y-4)*16);
        left_bar_vertex[3].position = sf::Vector2f(32/2, (size.y-4+size.x/4)*16);

        left_bar_vertex[0].texCoords = left_bar_vertex[0].position;
        left_bar_vertex[1].texCoords = left_bar_vertex[1].position;
        left_bar_vertex[2].texCoords = left_bar_vertex[2].position;
        left_bar_vertex[3].texCoords = left_bar_vertex[3].position;

        sf::VertexArray center_bar_vertex(sf::Quads, 4);
        center_bar_vertex[0].position = sf::Vector2f(32/2+size.x/2*16,(size.y-4)*16+width_of_roof);
        center_bar_vertex[1].position = sf::Vector2f(32/2+size.x/2*16+tile_size.x, (size.y-4)*16+width_of_roof);
        center_bar_vertex[2].position = sf::Vector2f(32/2+size.x/2*16+tile_size.x, (size.y-4)*16);
        center_bar_vertex[3].position = sf::Vector2f(32/2+size.x/2*16, (size.y-4)*16);

        center_bar_vertex[0].texCoords = center_bar_vertex[0].position;
        center_bar_vertex[1].texCoords = center_bar_vertex[1].position;
        center_bar_vertex[2].texCoords = center_bar_vertex[2].position;
        center_bar_vertex[3].texCoords = center_bar_vertex[3].position;

        sf::VertexArray right_bar_vertex(sf::Quads, 4);
        right_bar_vertex[0].position = sf::Vector2f(32/2+size.x/2*16+tile_size.x, (size.y-4)*16+width_of_roof);
        right_bar_vertex[1].position = sf::Vector2f(32/2+size.x*16+tile_size.x, (size.y-4+size.x/4)*16+width_of_roof);
        right_bar_vertex[2].position = sf::Vector2f(32/2+size.x*16+tile_size.x, (size.y-4+size.x/4)*16);
        right_bar_vertex[3].position = sf::Vector2f(32/2+size.x/2*16+tile_size.x, (size.y-4)*16);

        right_bar_vertex[0].texCoords = right_bar_vertex[0].position;
        right_bar_vertex[1].texCoords = right_bar_vertex[1].position;
        right_bar_vertex[2].texCoords = right_bar_vertex[2].position;
        right_bar_vertex[3].texCoords = right_bar_vertex[3].position;

        // CREATE RENDER TEXTURE OF ROOF
        sf::RenderTexture rtex;
        rtex.create(size.x * 16 + 64, (size.y + size.x/4 -4) * 16 + width_of_roof);
        rtex.clear(sf::Color::Transparent);

        sf::RenderStates states;
        states.texture = &left_part_roof_texture;
        rtex.draw(left_part_vertex, states);

        states.texture = &right_part_roof_texture;
        rtex.draw(right_part_vertex, states);

        states.texture = &center_part_roof_texture;
        rtex.draw(center_part_vertex, states);

        states.texture = &bar_of_roof_texture;
        rtex.draw(left_bar_vertex, states);

        states.texture = &bar_of_roof_texture;
        rtex.draw(center_bar_vertex, states);

        states.texture = &bar_of_roof_texture;
        rtex.draw(right_bar_vertex, states);

        rtex.display();

        // CREATE IMAGE
        sf::Image roof_image;
        roof_image = rtex.getTexture().copyToImage();
        main_image.copy(roof_image, tile_width/2, 32-tile_height/2,sf::IntRect(0,0,0,0),true);
        
        // CREATE WINDOWS
        if ((size.x / 2 - 1) > 2 && (size.x / 4 - 1) % 2 == 1) {
            if (texture_windows != nullptr) {
                sf::Texture win_tex = *texture_windows->texture;
                sf::Image window_image = win_tex.copyToImage();

                short left_window_pos;
                short right_window_pos;
                short pos_y = main_image.getSize().y - 64;

                for (short i = 1; i < size.x / 4 - 1; i += 2) {

                    left_window_pos = tile_size.x + i * 32 + 32/2;
                    right_window_pos = tile_size.x + (size.x / 4 + i + 1) * 32 + 32/2;

                    main_image.copy(window_image, left_window_pos, pos_y, sf::IntRect(0, 0, 0, 0));
                    main_image.copy(window_image, right_window_pos, pos_y, sf::IntRect(0, 0, 0, 0));
                }
            }
        }

        // CREATE EMPTY PLACE FOR THE DOOR
        if (_door != nullptr) {
            sf::RectangleShape door(sf::Vector2f(_door->textures[_door->frame]->texture->getSize()));

            for (short y = 0; y < door.getSize().y - 1; y++)
                for (short x = 0; x < door.getSize().x; x++) {
                    sf::Vector2i pos;
                    pos.x = float(size.x) / 2.0f * 16.0f - door.getSize().x / 2.0f + tile_size.x + x + 32/2;
                    pos.y = main_image.getSize().y - 1 - y;
                    main_image.setPixel(pos.x, pos.y, sf::Color(0, 0, 0, 0));
                }
        }
        
        texture = new SingleTexture(main_image);
        
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x/2, texture->texture->getSize().y);
        sprite.setPosition(position);

    }

    sf::Texture* getTextureWithDoors() {

        sf::Texture doors_texture = *_door->textures[0]->texture;
        
        sf::Image doors_image;
        doors_image.create(doors_texture.getSize().x, doors_texture.getSize().y, sf::Color::Transparent);
        doors_image = doors_texture.copyToImage();

        //////////////////////////////

        sf::Texture house_texture;
        house_texture = *sprite.getTexture();

        sf::Image house_image;
        house_image.create(house_texture.getSize().x, house_texture.getSize().y, sf::Color::Transparent);
        house_image = house_texture.copyToImage();
        house_image.copy(doors_image, size.x / 2 * 16, house_image.getSize().y - 64, sf::IntRect(0,0,0,0), true);
        ////////////////////////////

        sf::Texture* house_with_door_texture = new sf::Texture();
        house_with_door_texture->loadFromImage(house_image);
        
        return house_with_door_texture;
    }

    void load(std::wstring location) {

        // DELETE OLD GAMEOBJECTS

        if (_door != nullptr) {
            delete _door;
            _door = nullptr;
        }

        if (floors != nullptr) {
            delete floors;
            floors = nullptr;
        }

        if (!colliders.empty()) {
            for (auto& col : colliders)
                delete col;
            colliders.clear();
        }

        for (auto& item : _items)
            delete item;

        _items.clear();

        for (auto& furniture : _furnitures)
            delete furniture;

        _furnitures.clear();

        for (auto& wall : _walls)
            delete wall;

        _walls.clear();

        // LOAD THE BUILDING
        std::ifstream file(location);

        if (!file.is_open()) {
            std::wcout << L"cant open building script: " << location << L"\n";
            return;
        }

        std::string line;
        std::string objectType;
        std::string objectName;

        //std::cout << "load building: \n";

        

        while (std::getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            std::istringstream lineStream(line);
            lineStream >> objectType;

            //std::cout << "objectType: " << objectType << "\n";

            if (objectType == "name") {
                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "name \"" << objectName << "\"\n";

            }

            if (objectType == "size") {
                lineStream >> size.x >> size.y;
                //std::cout << "size " << size.x << " " << size.y << "\n";

                if (!colliders.empty()) {
                    delete colliders[0];
                    colliders.clear();
                }

                colliders.push_back(new Collider(size.x * 16, size.y * 16, position, 0, -size.y / 2 * 16, ColliderType::Rectangle));
                colliders[0]->setPosition(position);
            }

            if (objectType == "door") {
                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "door \"" << objectName << "\"\n";

                GameObject* prefab = getPrefab(ConvertUtf8ToWide(objectName));
                if (prefab != nullptr) {
                    _door = new Door(prefab);
                    _door->setPosition(position);

                }

            }

            if (objectType == "top_walls") {

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "top_walls \"" << objectName << "\"\n";

                SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(objectName));
                if (tex != nullptr)
                    texture_top_walls = tex;
            }

            if (objectType == "center_walls") {

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "walls \"" << objectName << "\"\n";

                SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(objectName));
                if (tex != nullptr)
                    texture_center_walls = tex;
            }

            if (objectType == "bottom_walls") {

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "bottom_walls \"" << objectName << "\"\n";

                SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(objectName));
                if (tex != nullptr)
                    texture_bottom_walls = tex;
            }

            if (objectType == "windows") {
                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                //std::cout << "windows \"" << objectName << "\"\n";

                SingleTexture* tex = getSingleTexture(ConvertUtf8ToWide(objectName));
                if (tex != nullptr)
                    texture_windows = tex;

            }

            if (line.find("// FLOORS") != std::string::npos && line.find("// FLOORS" == 0)) {  // TO-DO
                //std::cout << "load the floors\n";

                if (floors != nullptr)
                    delete floors;


                floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);

                short value;
                for (short y = 0; y < size.y; y++) {
                    for (short x = 0; x < size.x; x++) {
                        file >> value;
                        //std::cout << value << " ";
                        floors->edit(x, y, value);
                    }

                    //std::cout << "\n";
                }
            }

            if (objectType == "Item") {

                short x, y;
                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16) + position.y;

                Item* item = getItem(ConvertUtf8ToWide(objectName));
                if (item != nullptr) {
                    ItemOnMap* itemOnMap = new ItemOnMap(item);
                    itemOnMap->setPosition(sf::Vector2f(x, y));
                    _items.push_back(itemOnMap);
                }

            }

            if (objectType == "Furniture") {
                std::string name;
                short x, y, id;

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;
                lineStream >> id;

                x += (position.x - size.x / 2 * 16);
                y += (position.y - size.y * 16);

                GameObject* prefab = getPrefab(ConvertUtf8ToWide(objectName));
                if (prefab != nullptr) {
                    Furniture* furniture = new Furniture(prefab);
                    
                    furniture->inventory = getInventory(id);
                    furniture->setPosition(sf::Vector2f(x, y));
                    _furnitures.push_back(furniture);
                }

            }

            if (objectType == "Wall") {
                std::string name;
                short x, y;

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;

                x = x + position.x - size.x / 2 * 16;
                y = y + position.y - size.y * 16;
                
                GameObject* prefab = getPrefab(ConvertUtf8ToWide(objectName));
                if (prefab != nullptr) {
                    Wall* wall = new Wall(prefab);
                    wall->setPosition(sf::Vector2f(x, y));
                    _walls.push_back(wall);
                }

            }

        }

        file.close();
    }

    void save(std::string filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cout << "cant open file to save building: " << filename << "\n";
            return;
        }

        file << "name \"testBuilding\"\n";
        file << "size " << std::to_string(floors->width) << " " << std::to_string(floors->height) << "\n";
        file << "door \"" << ConvertWideToUtf8(_door->name) << "\"\n";
        file << "top_walls \"" << ConvertWideToUtf8(texture_top_walls->name) << "\"\n";
        file << "center_walls \"" << ConvertWideToUtf8(texture_center_walls->name) << "\"\n";
        file << "bottom_walls \"" << ConvertWideToUtf8(texture_bottom_walls->name) << "\"\n";
        file << "windows \"" << ConvertWideToUtf8(texture_windows->name) << "\"\n";

        file << "\n";

        // SAVE FLOORS
        file << "// FLOORS\n";
        for (short y = 0; y < floors->height; y++) {
            for (short x = 0; x < floors->width; x++) {
                file << floors->floors[y * floors->width + x];
                if (x != floors->width - 1)
                    file << " ";
            }
            file << "\n";
        }
        file << "\n";

        // SAVE ITEMS
        if (_items.size() > 0)
            file << "// ITEMS\n";
        for (auto& item : _items) {
            sf::Vector2i position;
            position.x = int(item->position.x) - int(this->position.x) + size.x/2*16;
            position.y = int(item->position.y) - int(this->position.y) + size.y * 16;
            file << "Item " << char(34) << ConvertWideToUtf8(item->name) << char(34) << " " << position.x << " " << position.y << "\n";
        }

        if (_items.size() > 0)
            file << "\n";


        if (_furnitures.size() > 0)
            file << "// FURNITURES\n";
        for (auto& furniture : _furnitures) {
            sf::Vector2i position;
            position.x = int(furniture->position.x) - int(this->position.x) + size.x/2*16;
            position.y = int(furniture->position.y) - int(this->position.y) + size.y * 16;
            file << "Furniture " << char(34) << ConvertWideToUtf8(furniture->name) << char(34) << " " << position.x << " " << position.y << "\n";

        }

        if (_furnitures.size() > 0)
            file << "\n";


        if (_walls.size() > 0)
            file << "// WALLS\n";
        for (auto& wall : _walls) {
            sf::Vector2i position;
            position.x = int(wall->position.x) - int(this->position.x) + size.x/2*16;
            position.y = int(wall->position.y) - int(this->position.y) + size.y*16;
            file << "Wall " << char(34) << ConvertWideToUtf8(wall->name) << char(34) << " " << position.x << " " << position.y << "\n";
            std::cout << "save - position of wall: " << position.x << " " << position.y << "\n";
        }

        if (_walls.size() > 0)
            file << "\n";


        file.close();
    }
    
    void save() {
        save(getLocation());
    }

    virtual void update() {
        calculateCorners();
        mouseHovering();
    } 

    virtual void drawColliders() {
        if (isSelected == true) {
            renderer->getTheCurrentFrame()->draw(*colliders[0]->shape);
        }
    }

    virtual void draw() {
        

        if (renderer->renderBuildingsOutside) {

            bool show_outside_sprite = true;

            if (editor_state == EditorStates::BuildingEditor || editor_state == EditorStates::MapEditorInit) {
                show_outside_sprite = false;
            }
            else {

                for (auto& object : gameObjects) {
                    
                    if (object!=this && intersection(object, this) && object->isSelected) {
                        show_outside_sprite = false;
                        break;
                    }
                        
                }

                if (show_outside_sprite == false) {
                    std::cout << "selected object is selected and is inside of building\n";
                }
                else if (player == nullptr && isSelected) {
                    //cout << "is selected\n";
                    show_outside_sprite = false;
                }
                else if (player == nullptr && GUIwasOpen == false && GUIwasClicked == false && GUIwasHover == false && mouseIsHover) {
                    //cout << "mouse is over\n";
                    show_outside_sprite = false;
                }
                else if (player != nullptr && playerInside()) {
                    //cout << "player inside\n";
                    show_outside_sprite = false;
                }

            }

            if (show_outside_sprite) {
                //std::cout << "show\n";
                renderer->getTheCurrentFrame()->draw(sprite);
            }
        }
    }

};

std::vector < Building* > buildings;
Building* building_to_edit = nullptr;
sf::Vector2f building_to_edit_position;

#endif 