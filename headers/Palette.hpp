#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp
/*
sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;


short paletteScroll;
short paletteCols;
short paletteRows;
*/


sf::Texture tileset;



enum class PaletteType { MapEditor, BuildingEditor };
enum class PaletteStates { Open, Opening, Closeing, Close };

class GameObjectAndTextureInfo {
public:
    GameObject* object;
    sf::Texture texture;
    sf::IntRect rect;
    sf::Vector2f scale;
    sf::Vector2f origin;

    GameObjectAndTextureInfo(GameObject* object) {
        this->object = object;

        if (object != nullptr) {
            if (this->object->type == GameObjectType::Water) {
                texture = *dynamic_cast<WaterPrefab*>(this->object)->terrain->texture->texture;
                rect = sf::IntRect(0, 0, 16, 16);
                scale = sf::Vector2f(3, 3);
                origin = sf::Vector2f(8, 8);
            }
            else if (this->object->type == GameObjectType::Terrain || this->object->type == GameObjectType::Water) {
                texture = *this->object->texture->texture;
                rect = sf::IntRect(0, 0, 16, 16);
                scale = sf::Vector2f(3, 3);
                origin = sf::Vector2f(8, 8);
            }
            else if (this->object->type == GameObjectType::Building) {
                texture = *(dynamic_cast<Building*>(this->object)->sprite.getTexture());

                rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);

                if (texture.getSize().x > texture.getSize().y) {
                    scale.x = 64.0f / float(texture.getSize().x) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().x) * 0.75f;
                }
                else if (texture.getSize().x < texture.getSize().y) {
                    scale.x = 64.0f / float(texture.getSize().y) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().y) * 0.75f;
                }
                else {
                    scale.x = 64.0f / float(texture.getSize().x) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().x) * 0.75f;
                }

                origin = sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2);
            }
            else if (this->object->type == GameObjectType::Character) {
                texture = dynamic_cast<Character*>(this->object)->renderTexture->getTexture();
                rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);
                origin = sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2);
            }
            else if (this->object->type != GameObjectType::ItemOnMap) {
                if (this->object != nullptr && this->object->texture != nullptr)
                    texture = *this->object->texture->texture;
                else if(this->object != nullptr && !this->object->textures.empty())
                    texture = *this->object->textures[0]->texture;

                rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);

                if (texture.getSize().x > texture.getSize().y) {
                    scale.x = 64.0f / float(texture.getSize().x) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().x) * 0.75f;
                }
                else if (texture.getSize().x < texture.getSize().y) {
                    scale.x = 64.0f / float(texture.getSize().y) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().y) * 0.75f;
                }
                else {
                    scale.x = 64.0f / float(texture.getSize().x) * 0.75f;
                    scale.y = 64.0f / float(texture.getSize().x) * 0.75f;
                }

                origin = sf::Vector2f(texture.getSize().x/2, texture.getSize().y/2);
            }
            else {
                // Items
                texture = *this->object->textures[0]->texture;
                rect = sf::IntRect(8, 8, 48, 48);
                scale = sf::Vector2f(1, 1);
                origin = sf::Vector2f(texture.getSize().x/2 - 8, texture.getSize().y/2 - 8);
            }
        }
    }

    GameObjectAndTextureInfo(GameObject* object, sf::Vector2f scale, sf::IntRect rect) {
        this->object = object;

        if (object->type == GameObjectType::Building) {
            this->texture = *(dynamic_cast<Building*>(object)->sprite.getTexture());
        }
        else if (object->type == GameObjectType::Character) {
            this->texture = dynamic_cast<Character*>(object)->renderTexture->getTexture();
        }
        else 
            this->texture = *this->object->texture->texture;

        this->rect = rect;
        this->scale = scale;
        origin = sf::Vector2f(this->rect.width/2,this->rect.height/2);
        
    }

    GameObjectAndTextureInfo(GameObject* object, sf::Texture* texture, sf::Vector2f origin, sf::Vector2f scale, sf::IntRect rect) {
        this->object = object;

        this->texture = *texture;

        this->origin = origin;
        this->rect = rect;
        this->scale = scale;

        
    }

    GameObjectAndTextureInfo(GameObject* object, const sf::Texture* texture, sf::Vector2f origin, sf::Vector2f scale, sf::IntRect rect) {
        // FOR CHARACTER
        this->object = object;

        this->texture = *texture;

        this->origin = origin;
        this->rect = rect;
        this->scale = scale;
    }

    ~GameObjectAndTextureInfo() {

    }
};

class PaletteButton : public ButtonWithImage {
public:

    GameObjectAndTextureInfo* object_and_texture_info;
    sf::Sprite sprite;

    PaletteButton(sf::Vector2f position) : ButtonWithImage(getSingleTexture(L"GUI\\slot2"), position) {
        object_and_texture_info = nullptr;
    }

    void setGameObjectAndTextureInfo(GameObjectAndTextureInfo* object_and_texture_info) {

        this->hover_func = []() {};
        this->onclick_func = []() {};

        this->object_and_texture_info = object_and_texture_info;

        sprite = sf::Sprite();

        if (this->object_and_texture_info != nullptr && this->object_and_texture_info->object!=nullptr) {

            hover_func = [this]() {
                if (tip == nullptr || (tip != nullptr && tip->btn != this)) {
                    sf::Vector2f pos;
                    pos.x = this->position.x - sprite.getTexture()->getSize().x / 4.0f;
                    pos.y = this->position.y + sprite.getTexture()->getSize().y / 4.0f;
                    if (tip != nullptr)
                        delete tip;
                    tip = new Tip(getShortName(this->object_and_texture_info->object->name), pos, this);       // TO-DO delete convert and use std::wstring
                }

                };

            onclick_func = [this]() {
                painter->tool = toolType::AddGameObject;
                painter->setPrefabToPaint(this->object_and_texture_info->object);
                };

            sprite.setTexture(object_and_texture_info->texture);
            sprite.setTextureRect(object_and_texture_info->rect);
            sprite.setScale(object_and_texture_info->scale);
            sprite.setOrigin(object_and_texture_info->origin);
        }

        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    }

    void setTexture(sf::Texture& texture, sf::Vector2f scale, sf::IntRect rect) {
        
        rect = rect;
        
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setOrigin(rect.width/2, rect.height/2);
        sprite.setScale(scale);
        
    }

    

    void update(bool hover_action = true) {
        ButtonWithImage::update(hover_action);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    }

    void draw() {
        ButtonWithImage::draw();

        if (object_and_texture_info != nullptr) {
            if (object_and_texture_info->object->type == GameObjectType::Water) {
                window->draw(sprite, dynamic_cast<WaterPrefab*>(object_and_texture_info->object)->shader->shader);
            }
            else
                window->draw(sprite);
        }



    }
};

class Palette : public ElementGUI {
public:

    PaletteType type;
    sf::Vector2i size;
    sf::RectangleShape rect;
    PaletteStates state;

    std::vector < ButtonWithImage* > groupButtons;
    std::vector < ButtonWithImage* > toolsButtons;
    std::vector < PaletteButton* > paletteButtons;

    ButtonWithImage* selectedGroupButton;
    ButtonWithImage* selectedToolButton;
    PaletteButton* selectedPaletteButton;

    short group_scroll = 0;
    short palette_scroll = 0;

    Scrollbar* scrollbar;

    ButtonWithImage* btnNavLeft;
    ButtonWithImage* btnNavRight;
    sf::Vector2i visible_group_count = sf::Vector2i(4, 2);
    std::vector < ButtonWithImage* > visibleGroups;

    ButtonWithImage* btnGroupEmpty;
    ButtonWithImage* btnGroupTerrain;
    ButtonWithImage* btnGroupHighlands;
    ButtonWithImage* btnGroupFloors;
    ButtonWithImage* btnGroupWater;
    ButtonWithImage* btnGroupFurnitures;
    ButtonWithImage* btnGroupWalls;
    ButtonWithImage* btnGroupMonsters;
    ButtonWithImage* btnGroupFlatObjects;
    ButtonWithImage* btnGroupItems;
    ButtonWithImage* btnGroupNatures;
    ButtonWithImage* btnGroupSmallObjects;
    ButtonWithImage* btnGroupObjects;
    ButtonWithImage* btnGroupBuildings;
    ButtonWithImage* btnGroupCharacters;
    ButtonWithImage* btnGroupDirections;

    ButtonWithImage* btnToolsEmpty;
    ButtonWithImage* btnToolsCursor;
    ButtonWithImage* btnToolsBrush;
    ButtonWithImage* btnToolsRectBrush;
    ButtonWithImage* btnToolsIncrease;
    ButtonWithImage* btnToolsDecrease;
    ButtonWithImage* btnToolsRectangle;
    ButtonWithImage* btnToolsElipse;
    ButtonWithImage* btnToolsFill;
    ButtonWithImage* btnToolsEraser;

    std::vector < GameObjectAndTextureInfo* > gameObjectsAndTexturesInfo;

    Palette(PaletteType type) : ElementGUI() {
        this->type = type;
        state = PaletteStates::Open;

        rect = sf::RectangleShape(sf::Vector2f(340, 690));
        rect.setFillColor(panelColor_verydark);
		rect.setOrigin(rect.getSize().x/2, rect.getSize().y/2);
		rect.setPosition(cam->position.x + screenWidth / 2.0f - rect.getSize().x/2, cam->position.y + screenHeight / 2.0f - rect.getSize().y/2);

        createPaletteButtons(5, 8);
        createToolsButtons();
        createGroupButtons();
        setTheVisibleGroupsButtons();

        if (type == PaletteType::MapEditor)        selectedGroupButton = btnGroupTerrain;
        if (type == PaletteType::BuildingEditor)   selectedGroupButton = btnGroupFloors;

        selectedToolButton = btnToolsCursor;
        selectedPaletteButton = nullptr;

        if (type == PaletteType::MapEditor)       setTerrainObjectsToPalette();
        if (type == PaletteType::BuildingEditor)  setFloorsObjectsToPalette();

        loadPalette();
        create_scrollbar();

        
        
    }

    void deletePaletteButtons() {
        if (paletteButtons.size() > 0) {
            for (int i = 0; i < paletteButtons.size(); i++) {
                delete paletteButtons[i];
            }

            paletteButtons.clear();
        }
    }

    void deleteToolsButtons() {
        if (toolsButtons.size() > 0) {
            for (int i = 0; i < toolsButtons.size(); i++) {
                delete toolsButtons[i];
            }

            toolsButtons.clear();
        }

        cout << "delete Tools Buttons\n";
    }

    void deleteGroupButtons() {

        delete btnNavLeft;
        btnNavLeft = nullptr;

        delete btnNavRight;
        btnNavRight = nullptr;

        if (groupButtons.size() > 0) {
            for (int i = 0; i < groupButtons.size(); i++) {
                delete groupButtons[i];
            }

            groupButtons.clear();
        }
    }

    void createPaletteButtons(short size_x, short size_y) {

        deletePaletteButtons();

        size.x = size_x;
        size.y = size_y;

        sf::Vector2f start_pos; // left bottom 
        start_pos.x = screenWidth / 2.0f - size.x * 64 + 32 - 20;
        start_pos.y = screenHeight / 2.0f - 32;

        for (short y = 0; y < size.y; y++) {
            for (short x = 0; x < size.x; x++) {

                sf::Vector2f pos;
                pos.x = start_pos.x + x * 64;
                pos.y = start_pos.y - (size.y - 1 - y) * 64;

                PaletteButton* btn = new PaletteButton(pos);
                paletteButtons.push_back(btn);
            }
        }



    }

    void setTerrainObjectsToPalette() {

        gameObjectsAndTexturesInfo.clear();

        // skip the empty terrainGameObjects[0]


        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[4]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[5]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[7]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[8]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[9]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[10]));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);


        short id = countOfBasicTerrain;
        // SET - SANDS_WATER
        id += 8;    // skip the SET - SANDS_WATER
        id += 8;    // skip the SET - WATER_SANDS

        // SET - SANDS_GRASS
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 0]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 2]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 5]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 7]));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        // SET - GRASS_SANDS
        id += 8;
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 0]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 2]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 5]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 7]));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        // SET - GRASS_GRAVEL
        id += 8;
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 0]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 2]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 5]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 7]));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        // SET - GRAVEL_GRASS
        id += 8;
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 0]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 1]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 2]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 3]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[2]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 4]));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 5]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 6]));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[id + 7]));


    }

    void setFloorsObjectsToPalette() {

        gameObjectsAndTexturesInfo.clear();

        for (auto& floor : floorGameObjects)
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(floor));

    }

    void setWaterObjectsToPalette() {

        gameObjectsAndTexturesInfo.clear();

        for (int i = 1; i < countOfBasicWater; i++) {

            // TERRAIN_WATER
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 8]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 9]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 9]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 9]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 10]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 11]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 12]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 11]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 12]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 11]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[i]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 12]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 13]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 14]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 14]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 14]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 15]));

            gameObjectsAndTexturesInfo.push_back(nullptr);
            gameObjectsAndTexturesInfo.push_back(nullptr);
            gameObjectsAndTexturesInfo.push_back(nullptr);
            gameObjectsAndTexturesInfo.push_back(nullptr);
            gameObjectsAndTexturesInfo.push_back(nullptr);

            // WATER_TERRAIN
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 0]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 2]));
            
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 3]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 4]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 3]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 4]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 3]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(terrainGameObjects[1]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 4]));

            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 5]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 6]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 6]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 6]));
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(waterGameObjects[countOfBasicWater + (i - 1) * 16 + 7]));

            if (i < countOfBasicWater - 1) {
                gameObjectsAndTexturesInfo.push_back(nullptr);
                gameObjectsAndTexturesInfo.push_back(nullptr);
                gameObjectsAndTexturesInfo.push_back(nullptr);
                gameObjectsAndTexturesInfo.push_back(nullptr);
                gameObjectsAndTexturesInfo.push_back(nullptr);
            }
        }




    }

    void setFurnituresObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& p : prefabs)
            if (p->type == GameObjectType::Furniture)
                gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(p));
    }

    void setWallsObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_0")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mud_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_5")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_6")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_7")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mud_wall_8")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mud_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mud_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mud_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mud_wall_overgrown")));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_0")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\stone_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_5")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_6")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_7")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_stone_wall_8")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\stone_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\stone_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\stone_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\stone_wall_overgrown")));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_0")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\wooden_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_5")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_6")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_7")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_wooden_wall_8")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\wooden_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\wooden_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\wooden_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\wooden_wall_overgrown")));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_0")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\brick_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_5")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_6")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_7")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_brick_wall_8")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\brick_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\brick_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\brick_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\brick_wall_overgrown")));

        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);
        gameObjectsAndTexturesInfo.push_back(nullptr);

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_0")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mulch_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_3")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_5")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_6")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_7")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\set_mulch_wall_8")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mulch_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mulch_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\empty_wall")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mulch_wall_overgrown")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"walls\\mulch_wall_overgrown")));
    }

    void setMonstersObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Monster) {
                gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(p));
            }
        }
    }

    void setFlatObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\path_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\path_2")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\stonepath_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\stonepath_2")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\sandspath_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\sandspath_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\herb_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\herb_2")));

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_rock_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_rock_2")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_rock_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_rock_4")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_sands_rock_1")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_sands_rock_2")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_sands_rock_3")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"flatObjects\\small_sands_rock_4")));

        
    }

    void setItemsObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& i : items) {
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(i->name)));
        }

    }

    void setNaturesObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Nature) {
                gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(p));
            }
        }

    }

    void setObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Object) {
                gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(p));
            }
        }

        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"doors\\wooden_gate")));
        gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(getPrefab(L"doors\\great_stone_gate")));
    }

    void setSmallObjectsToPalette() {
        gameObjectsAndTexturesInfo.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::SmallObject) {
                gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(p));
            }
        }
    }

    void setBuildingsToPalette() {

        gameObjectsAndTexturesInfo.clear();
        float part_size = 64;

        for (auto& building : buildings_prefabs) {
            sf::Texture* texture = building->getTextureWithDoors();
            std::cout << "Texture Size: " << texture->getSize().x << "x" << texture->getSize().y << "\n";


            for (int y = 0; y < texture->getSize().y; y += part_size) {
                for (int x = 0; x < texture->getSize().x; x += part_size) {
                    sf::IntRect rect;
                    rect.left = x + 8;
                    rect.top = y + 8;
                    rect.width = std::min(part_size - 16, float(texture->getSize().x - x - 8));
                    rect.height = std::min(part_size - 16, float(texture->getSize().y - y - 8));

                    gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(building, texture, sf::Vector2f(32-8,32-8), sf::Vector2f(1, 1), rect));

                }
            }
        }
    }

    void setCharactersToPalette() {
        gameObjectsAndTexturesInfo.clear();

        sf::IntRect rect(8, 8, 48, 48);
        int i = 0;
        for (auto& c : characters_prefabs) {
            
            gameObjectsAndTexturesInfo.push_back(new GameObjectAndTextureInfo(c, &c->renderTexture->getTexture(), sf::Vector2f(32, 32 - 8), sf::Vector2f(1, 1), sf::IntRect(0, 0, 48, 48)));
            i++;

            if (i == 4) {
                gameObjectsAndTexturesInfo.push_back(nullptr);
                i = 0;
            }
                
            
        }

    }

    void loadPalette() {
        for (int i = 0; i < paletteButtons.size(); i++) {

            (scrollbar == nullptr) ? palette_scroll = i + 0 * size.x : palette_scroll = i + scrollbar->scroll_value * size.x;

            GameObjectAndTextureInfo* gameobject_and_texture_info;
            (palette_scroll < gameObjectsAndTexturesInfo.size() && gameObjectsAndTexturesInfo[palette_scroll]!=nullptr) ? gameobject_and_texture_info = gameObjectsAndTexturesInfo[palette_scroll] : gameobject_and_texture_info = nullptr;
            
            paletteButtons[i]->setGameObjectAndTextureInfo(gameobject_and_texture_info);

            GameObject* object = (gameobject_and_texture_info != nullptr) ? gameobject_and_texture_info->object : nullptr;

            if (object != nullptr) {
                auto button = paletteButtons[i];

                paletteButtons[i]->hover_func = [this, button]() {
                    if (tip == nullptr || tip->btn != button) {
                        sf::Vector2f pos;
                        pos.x = button->position.x - button->sprite.getGlobalBounds().width / 4.0f;
                        pos.y = button->position.y + button->sprite.getGlobalBounds().height / 4.0f;
                        if (tip != nullptr)
                            delete tip;
                        tip = new Tip(getShortName(button->object_and_texture_info->object->name), pos, button);       // TO-DO delete convert and use std::wstring
                    }
                    };

                paletteButtons[i]->onclick_func = [this, button]() {

                    selectedPaletteButton = button;
                    painter->setPrefabToPaint(button->object_and_texture_info->object);

                    if (button->object_and_texture_info->object->type == GameObjectType::Terrain || button->object_and_texture_info->object->type == GameObjectType::Floor || button->object_and_texture_info->object->type == GameObjectType::Water) {
                        if (painter->tool == toolType::Cursor || painter->tool == toolType::AddGameObject) {
                            painter->tool = toolType::Brush;
                            selectedToolButton = btnToolsBrush;
                        }
                    }
                    else {
                        painter->tool = toolType::AddGameObject;
                        selectedToolButton = btnToolsEmpty;
                    }
                    };
            }
            else {
                paletteButtons[i]->hover_func = []() {};
                paletteButtons[i]->onclick_func = []() {};
            }
        }
    }

    void delete_scrollbar() {
        delete scrollbar;
        scrollbar = nullptr;
    }

    void create_scrollbar() {
        sf::Vector2f scrollbar_size(20, size.y * 64);
        sf::Vector2f scrollbar_position;
        scrollbar_position.x = screenWidth / 2.0f - scrollbar_size.x;
        scrollbar_position.y = screenHeight / 2.0f - size.y * 64;
        short scrollbar_max_value = ceil(float(gameObjectsAndTexturesInfo.size()) / 5.0f);
        scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, scrollbar_max_value, 0, 1, size.y, ScrollbarPartSize::_20);
    
        scrollbar->setScrollAreaSize(sf::Vector2f(rect.getSize().x, scrollbar->size.y));
        scrollbar->setScrollAreaPosition(sf::Vector2f(screenWidth / 2.0f - rect.getSize().x, screenHeight / 2.0f - scrollbar->size.y));

    }

    void createToolsButtons() {
        // delete old Tools Buttons
        deleteToolsButtons();

        btnToolsEmpty = new ButtonWithImage();
        btnToolsEmpty->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton"));

        btnToolsCursor = new ButtonWithImage();
        btnToolsCursor->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-cursor"));
        btnToolsCursor->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsCursor) {
                if (tip != nullptr)
                    delete tip;

                tip = new Tip(L"Cursor", btnToolsCursor);
            }



            };
        btnToolsCursor->onclick_func = [this]() {
            selectedToolButton = btnToolsCursor;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            };


        btnToolsBrush = new ButtonWithImage();
        btnToolsBrush->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-brush"));
        btnToolsBrush->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsBrush) {
                if (tip != nullptr)
                    delete tip;

                tip = new Tip(L"Brush", btnToolsBrush);
            }



            };
        btnToolsBrush->onclick_func = [this]() {
            selectedToolButton = btnToolsBrush;
            painter->tool = toolType::Brush;
            if (painter->prefabToPaint == nullptr) {
                painter->setPrefabToPaint(gameObjectsAndTexturesInfo[1]->object);
                selectedPaletteButton = paletteButtons[1];
            }
            };


        btnToolsRectBrush = new ButtonWithImage();
        btnToolsRectBrush->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-rect_brush"));
        btnToolsRectBrush->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsRectBrush) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Rectangle Brush", btnToolsRectBrush);
            }



            };
        btnToolsRectBrush->onclick_func = [this]() {
            selectedToolButton = btnToolsRectBrush;
            painter->tool = toolType::RectBrush;
            if (painter->prefabToPaint == nullptr) {
                painter->setPrefabToPaint(gameObjectsAndTexturesInfo[1]->object);
                selectedPaletteButton = paletteButtons[1];
            }
            };


        btnToolsIncrease = new ButtonWithImage();
        btnToolsIncrease->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-increase"));
        btnToolsIncrease->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsIncrease) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Increase", btnToolsIncrease);
            }



            };
        btnToolsIncrease->onclick_func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                painter->increaseBrush();

            }
            };


        btnToolsDecrease = new ButtonWithImage();
        btnToolsDecrease->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-decrease"));
        btnToolsDecrease->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsDecrease) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Decrease", btnToolsDecrease);
            }



            };
        btnToolsDecrease->onclick_func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                painter->decreaseBrush();
            }
            };


        btnToolsRectangle = new ButtonWithImage();
        btnToolsRectangle->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-rectangle"));
        btnToolsRectangle->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsRectangle) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Rectangle", btnToolsRectangle);
            }



            };
        btnToolsRectangle->onclick_func = [this]() {
            selectedToolButton = btnToolsRectangle;
            painter->tool = toolType::Rectangle;

            if (painter->prefabToPaint == nullptr) {
                painter->setPrefabToPaint(gameObjectsAndTexturesInfo[1]->object);
                selectedPaletteButton = paletteButtons[1];
            }

            unselectGameObjects();
            };


        btnToolsElipse = new ButtonWithImage();
        btnToolsElipse->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-elipse"));
        btnToolsElipse->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsElipse) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Elipse", btnToolsElipse);
            }



            };
        btnToolsElipse->onclick_func = [this]() {
            selectedToolButton = btnToolsElipse;
            painter->tool = toolType::Elipse;

            if (painter->prefabToPaint == nullptr) {
                painter->setPrefabToPaint(gameObjectsAndTexturesInfo[1]->object);
                selectedPaletteButton = paletteButtons[1];
            }

            unselectGameObjects();

            };


        btnToolsFill = new ButtonWithImage();
        btnToolsFill->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-fill"));
        btnToolsFill->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsElipse) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Fill", btnToolsFill);
            }



            };
        btnToolsFill->onclick_func = [this]() {
            selectedToolButton = btnToolsFill;
            painter->tool = toolType::Fill;
            };


        btnToolsEraser = new ButtonWithImage();
        btnToolsEraser->setTexture(getSingleTexture(L"GUI\\toolButtons\\toolbutton-eraser"));
        btnToolsEraser->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsEraser) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Eraser", btnToolsEraser);
            }



            };
        btnToolsEraser->onclick_func = [this]() {
            // TO-DO - what is this ?!?!
            selectedToolButton = btnToolsEraser;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            painter->tool = toolType::Eraser;
            if (painter->prefabToPaint == nullptr) {
                painter->setPrefabToPaint(gameObjectsAndTexturesInfo[1]->object);
                selectedPaletteButton = paletteButtons[1];
            }
            };

        ////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f button_size(34, 34);

        sf::Vector2f sp;    // start position
        sp.x = screenWidth / 2.0f - 10 * button_size.x + button_size.x / 2;
        sp.y = -screenHeight / 2.0f + 30 + 2 * 52 + button_size.y / 2 + 3;

        btnToolsCursor->setPosition(sf::Vector2f(sp.x, sp.y));
        btnToolsBrush->setPosition(sf::Vector2f(sp.x + 34, sp.y));
        btnToolsRectBrush->setPosition(sf::Vector2f(sp.x + 68, sp.y));
        btnToolsIncrease->setPosition(sf::Vector2f(sp.x + 102, sp.y));
        btnToolsDecrease->setPosition(sf::Vector2f(sp.x + 136, sp.y));
        btnToolsRectangle->setPosition(sf::Vector2f(sp.x + 170, sp.y));
        btnToolsElipse->setPosition(sf::Vector2f(sp.x + 204, sp.y));
        btnToolsFill->setPosition(sf::Vector2f(sp.x + 238, sp.y));

        toolsButtons.push_back(btnToolsCursor);
        toolsButtons.push_back(btnToolsBrush);
        toolsButtons.push_back(btnToolsRectBrush);
        toolsButtons.push_back(btnToolsIncrease);
        toolsButtons.push_back(btnToolsDecrease);
        toolsButtons.push_back(btnToolsRectangle);
        toolsButtons.push_back(btnToolsElipse);
        toolsButtons.push_back(btnToolsFill);
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 272, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 306, sp.y)));

        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 34, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 68, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 102, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 136, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 170, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 204, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 238, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 272, sp.y + 34)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 306, sp.y + 34)));

    }

    void createGroupButtons() {

        deleteGroupButtons();

        btnNavLeft = new ButtonWithImage();
        btnNavLeft->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton_to_left"));
        btnNavLeft->onclick_func = [this]() {
            moveVisibleGroupsToLeft();
            setTheVisibleGroupsButtons();
            };

        btnNavRight = new ButtonWithImage();
        btnNavRight->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton_to_right"));
        btnNavRight->onclick_func = [this]() {
            moveVisibleGroupsToRight();
            setTheVisibleGroupsButtons();
            };

        // create Group Buttons
        btnGroupEmpty = new ButtonWithImage();
        btnGroupEmpty->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton"));

        btnGroupTerrain = new ButtonWithImage();
        btnGroupTerrain->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-terrain"));
        btnGroupTerrain->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupTerrain) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Terrains", btnGroupTerrain);
            }
                


            };
        btnGroupTerrain->onclick_func = [this]() {
            selectedGroupButton = btnGroupTerrain;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 8);
            createToolsButtons();
            setTerrainObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupHighlands = new ButtonWithImage();
        btnGroupHighlands->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-highlands"));
        btnGroupHighlands->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupHighlands) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Highlands", btnGroupHighlands);
            }



            };
        btnGroupHighlands->onclick_func = [this]() {
            selectedGroupButton = btnGroupHighlands;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 8);
            createToolsButtons();
            //setHighlandsObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupFloors = new ButtonWithImage();
        btnGroupFloors->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-floors"));
        btnGroupFloors->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFloors) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Floors", btnGroupFloors);
            }
                
            };
        btnGroupFloors->onclick_func = [this]() {
            selectedGroupButton = btnGroupFloors;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 8);
            createToolsButtons();
            setFloorsObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupWater = new ButtonWithImage();
        btnGroupWater->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-water"));
        btnGroupWater->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupWater) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Waters", btnGroupWater);
            }
                
            };
        btnGroupWater->onclick_func = [this]() {
            selectedGroupButton = btnGroupWater;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 8);
            createToolsButtons();
            setWaterObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupFurnitures = new ButtonWithImage();
        btnGroupFurnitures->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-furnitures"));
        btnGroupFurnitures->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFurnitures) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Furnitures", btnGroupFurnitures);
            }
                
            };
        btnGroupFurnitures->onclick_func = [this]() {
            selectedGroupButton = btnGroupFurnitures;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setFurnituresObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupWalls = new ButtonWithImage();
        btnGroupWalls->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-walls"));
        btnGroupWalls->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupWalls) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Walls", btnGroupWalls);
            }
                
            };
        btnGroupWalls->onclick_func = [this]() {
            selectedGroupButton = btnGroupWalls;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setWallsObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupMonsters = new ButtonWithImage();
        btnGroupMonsters->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-monsters"));
        btnGroupMonsters->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupMonsters) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Monsters", btnGroupMonsters);
            }
                
            };
        btnGroupMonsters->onclick_func = [this]() {
            selectedGroupButton = btnGroupMonsters;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setMonstersObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupFlatObjects = new ButtonWithImage();
        btnGroupFlatObjects->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-flat_objects"));
        btnGroupFlatObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFlatObjects) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Flat Objects", btnGroupFlatObjects);
            }
                
            };
        btnGroupFlatObjects->onclick_func = [this]() {
            selectedGroupButton = btnGroupFlatObjects;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setFlatObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupItems = new ButtonWithImage();
        btnGroupItems->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-items"));
        btnGroupItems->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupItems) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Items", btnGroupItems);
            }
                
            };
        btnGroupItems->onclick_func = [this]() {
            selectedGroupButton = btnGroupItems;
            painter->tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setItemsObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupNatures = new ButtonWithImage();
        btnGroupNatures->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-natures"));
        btnGroupNatures->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupNatures) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Natures Objects", btnGroupNatures);
            }
                
            };
        btnGroupNatures->onclick_func = [this]() {
            painter->tool = toolType::Cursor;
            selectedGroupButton = btnGroupNatures;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setNaturesObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupObjects = new ButtonWithImage();
        btnGroupObjects->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-objects"));
        btnGroupObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupObjects) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Objects", btnGroupObjects);
            }
                
            };
        btnGroupObjects->onclick_func = [this]() {
            painter->tool = toolType::Cursor;
            selectedGroupButton = btnGroupObjects;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupSmallObjects = new ButtonWithImage();
        btnGroupSmallObjects->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-smallObjects"));
        btnGroupSmallObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupSmallObjects) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Small Objects", btnGroupSmallObjects);
            }
                
            };
        btnGroupSmallObjects->onclick_func = [this]() {
            painter->tool = toolType::Cursor;
            selectedGroupButton = btnGroupSmallObjects;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setSmallObjectsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupBuildings = new ButtonWithImage();
        btnGroupBuildings->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-buildings"));
        btnGroupBuildings->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupBuildings) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Buildings", btnGroupBuildings);
            }

            };
        btnGroupBuildings->onclick_func = [this]() {
            painter->tool = toolType::Cursor;
            selectedGroupButton = btnGroupBuildings;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setBuildingsToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupCharacters = new ButtonWithImage();
        btnGroupCharacters->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-characters"));
        btnGroupCharacters->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupCharacters) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Characters", btnGroupCharacters);
            }

            };

        btnGroupCharacters->onclick_func = [this]() {
            painter->tool = toolType::Cursor;
            selectedGroupButton = btnGroupCharacters;
            selectedPaletteButton = nullptr;
            painter->setPrefabToPaint(nullptr);
            createPaletteButtons(5, 9);
            deleteToolsButtons();
            setCharactersToPalette();
            delete_scrollbar();
            loadPalette();
            create_scrollbar();
            };

        btnGroupDirections = new ButtonWithImage();
        btnGroupDirections->setTexture(getSingleTexture(L"GUI\\groupButtons\\groupButton-directions"));
        btnGroupDirections->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupDirections) {
                if (tip != nullptr)
                    delete tip;
                tip = new Tip(L"Directions", btnGroupDirections);
            }

            };
        btnGroupDirections->onclick_func = [this]() {

            };


        // create Group Buttons Menu
        groupButtons.clear();

        if (type == PaletteType::MapEditor) {
            groupButtons.push_back(btnGroupTerrain);
            groupButtons.push_back(btnGroupHighlands);
            groupButtons.push_back(btnGroupWater);
            groupButtons.push_back(btnGroupNatures);
            groupButtons.push_back(btnGroupFlatObjects);
            groupButtons.push_back(btnGroupMonsters);
            groupButtons.push_back(btnGroupItems);
            groupButtons.push_back(btnGroupSmallObjects);
            groupButtons.push_back(btnGroupObjects);
            groupButtons.push_back(btnGroupBuildings);
            groupButtons.push_back(btnGroupCharacters);
            groupButtons.push_back(btnGroupDirections);
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
        }
        else if (type == PaletteType::BuildingEditor) {
            groupButtons.push_back(btnGroupFloors);
            groupButtons.push_back(btnGroupWalls);
            groupButtons.push_back(btnGroupFurnitures);
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
            groupButtons.push_back(new ButtonWithImage(btnGroupEmpty));
        }
    }

    void setTheVisibleGroupsButtons() {
        sf::Vector2f nav_size(34, 104);
        sf::Vector2f button_size(68, 52);

        visibleGroups.clear();
        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 4; x++) {
                int index = (y % 2 * (groupButtons.size())/2) + x + group_scroll;
                if(index >= 0 && index < groupButtons.size())
                    visibleGroups.push_back(groupButtons[index]);
            }
        }



        sf::Vector2f position;
        position.y = -screenHeight / 2.0f + nav_size.y / 2 + 30;
        position.x = screenWidth / 2.0f - visible_group_count.x * button_size.x - nav_size.x * 3 / 2;
        btnNavLeft->setPosition(position);

        position.x = screenWidth / 2.0f - nav_size.x / 2;
        btnNavRight->setPosition(position);

        for (auto i = 0; i < visible_group_count.x * visible_group_count.y; i++) {
            position.x = screenWidth / 2.0f - (visible_group_count.x - 1 - i % visible_group_count.x) * button_size.x - button_size.x / 2 - nav_size.x;
            position.y = -screenHeight / 2.0f + i / visible_group_count.x * button_size.y + button_size.y / 2 + 30;
            visibleGroups[i]->setPosition(position);
        }
    }

    void moveVisibleGroupsToRight() {
        if (group_scroll < (groupButtons.size()-visible_group_count.x*visible_group_count.y + visible_group_count.y)/visible_group_count.y )
            group_scroll += 1;
    }

    void moveVisibleGroupsToLeft() {
        if(group_scroll > 0)
        group_scroll -= 1;
    }

    bool unselectPaletteButton() {
        
        if (selectedPaletteButton != nullptr) {
            selectedPaletteButton = nullptr;
            selectedToolButton = btnToolsCursor;
            painter->tool = toolType::Cursor;
            painter->setPrefabToPaint(nullptr);
            return true;
        }
        else
            return false;
        
    }

    void open() {
        state = PaletteStates::Open;
    }

    void close() {
        state = PaletteStates::Close;
    }

    void cursorHover() {

        if (state == PaletteStates::Open && dialogs.empty()) {

            if (rect.getGlobalBounds().contains(worldMousePosition)) {
                ElementGUI_hovered = this;
            }

            for (auto& tool : toolsButtons)
                tool->cursorHover();

            btnNavLeft->cursorHover();
            btnNavRight->cursorHover();

            for (auto& btn : visibleGroups)
                btn->cursorHover();

            for (auto& btn : paletteButtons)
                btn->cursorHover();

            
        }

        
    }

    void handleEvent(sf::Event& event) {

        if (state == PaletteStates::Open) {

            scrollbar->handleEvent(event);
            

            for (auto& tool : toolsButtons)
                tool->handleEvent(event);

            btnNavLeft->handleEvent(event);
            btnNavRight->handleEvent(event);

            for (auto& btn : visibleGroups)
                btn->handleEvent(event);

            for (auto& btn : paletteButtons)
                btn->handleEvent(event);

            
                

            loadPalette();
        }
    }

    void update() {

        rect.setPosition(cam->position.x + screenWidth / 2.0f - rect.getSize().x/2, cam->position.y + screenHeight / 2.0f - rect.getSize().y);

        bool hover_action;

        (state == PaletteStates::Open) ? hover_action = true : hover_action = false;

        for (auto& tool : toolsButtons)
            tool->update(hover_action);

        btnNavLeft->update(hover_action);
        btnNavRight->update(hover_action);

        for (auto& btn : visibleGroups)
            btn->update(hover_action);

        for (auto& btn : paletteButtons)
            btn->update(hover_action);

        scrollbar->update();
    }

    void draw() {

        if (state == PaletteStates::Open) {
            window->draw(rect);

            for (auto& tool : toolsButtons)
                tool->draw();

            btnNavLeft->draw();
            btnNavRight->draw();
            
            for (auto& btn : visibleGroups)
                btn->draw();

            for (auto& btn : paletteButtons) {
                btn->draw();
            }

            scrollbar->draw();

        }
    }
};

Palette* palette = nullptr;

#endif