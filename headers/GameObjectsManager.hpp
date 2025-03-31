#ifndef GameObjectsManager_hpp
#define GameObjectsManager_hpp

std::vector < MouseMovedGameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object) {

    if (object == nullptr)
        return nullptr;

    for (auto& building : buildings)
        if (building->isPart(object)) {
            //cout << "is a part of building\n";
            return building;
        }

    //cout << "is not a part of building\n";
    return nullptr;
}

bool unselectGameObjects() {

    //std::cout << "unselect gameobjects\n";

    if (!selectedGameObjects.empty()) {
        for (auto& sgo : selectedGameObjects) {
            sgo->_object->isSelected = false;
            delete sgo;
        }


        selectedGameObjects.clear();
        return true;
    }
    else
        return false;

}

void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h) {

    short count_selected_gameobjects = 0;    // count of selected gameobjects

    if (!selectedGameObjects.empty())
        unselectGameObjects();

    for (auto& go : gameObjects) {

        if (go->type == GameObjectType::Building) {

            float x = go->colliders[0]->position.x + go->colliders[0]->dx;
            float y = go->colliders[0]->position.y + go->colliders[0]->dy - dynamic_cast<Building*>(go)->size.y * 16 / 2;
            float w = go->colliders[0]->width;
            float h = go->colliders[0]->length;

            if (intersectionTwoRectangles(rect_x, rect_y, rect_w, rect_h, x, y, w, h)) {
                go->isSelected = true;
                MouseMovedGameObject* moved_object = new MouseMovedGameObject(go);
                selectedGameObjects.push_back(moved_object);
                count_selected_gameobjects += 1;
            }

        }
        else if (!isPartOfBuilding(go) || editor_state == EditorStates::BuildingEditor) {

            for (auto& collider : go->colliders) {
                if (collider->type == ColliderType::Rectangle) {
                    if (intersectionTwoRectangles(rect_x, rect_y, rect_w, rect_h, collider->position.x+collider->dx, collider->position.y+collider->dy, collider->width, collider->length)) {
                        go->isSelected = true;
                    }
                }
                else if (collider->type == ColliderType::Elipse) {
                    if (intersectionRectangleWithElipse(rect_x, rect_y, rect_w, rect_h, go->position.x+collider->dx, go->position.y+collider->dy, collider->width / 2, collider->length / 2)) {
                        go->isSelected = true;
                    }
                }

                if (go->isSelected) {
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(go);
                    selectedGameObjects.push_back(moved_object);
                    count_selected_gameobjects += 1;
                }
            }
        }

    }

    //std::cout << "selected gameobjects: " << count_selected_gameobjects << "\n";
}

void selectGameObjects() {
    float x = selectArea.getPosition().x;
    float y = selectArea.getPosition().y;
    float w = selectArea.getSize().x;
    float h = selectArea.getSize().y;

    if (w < 16) w = 16;
    if (h < 16) h = 16;

    selectGameObjects(x, y, w, h);
}



GameObject* getNewGameObject(GameObject* object) {

    if (object == nullptr)
        return nullptr;

    if (object->type == GameObjectType::Terrain) {
        TerrainPrefab* o = new TerrainPrefab(object->name, dynamic_cast<TerrainPrefab*>(object)->id);
        return o;
    }
    else if (object->type == GameObjectType::Water) {
        WaterPrefab* o = new WaterPrefab(object->name, dynamic_cast<WaterPrefab*>(object)->id, dynamic_cast<WaterPrefab*>(object)->terrain);
        return o;
    }
    else if (object->type == GameObjectType::Floor) {
        FloorPrefab* o = new FloorPrefab(object->name, dynamic_cast<FloorPrefab*>(object)->id);
        return o;
    }
    else if (object->type == GameObjectType::Nature) {
        Nature* o = new Nature(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Object) {
        Object* o = new Object(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Monster) {
        Monster* o = new Monster(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Character) {
        Character* o = new Character(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::ItemOnMap) {
        ItemOnMap* o = new ItemOnMap(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::FlatObject) {
        FlatObject* o = new FlatObject(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::SmallObject) {
        SmallObject* o = new SmallObject(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Door) {
        Door* o = new Door(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Wall) {
        Wall* o = new Wall(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Furniture) {
        Furniture* o = new Furniture(object, 0, 0);
        return o;
    }
    else if (object->type == GameObjectType::Building) {
        Building* o = new Building(object);
        return o;
    }

    return nullptr;
}

void addGameObjectToMainLists(GameObject* object) {
    if (object == nullptr)
        return;

    if (object->type == GameObjectType::Nature) {
        natures.push_back(dynamic_cast<Nature*>(object));
        
    }

    if (object->type == GameObjectType::Object) {
        objects.push_back(dynamic_cast<Object*>(object));
    }

    if (object->type == GameObjectType::Monster) {
        monsters.push_back(dynamic_cast<Monster*>(object));
    }

    if (object->type == GameObjectType::Character) {
        characters.push_back(dynamic_cast<Character*>(object));
    }

    if (object->type == GameObjectType::ItemOnMap) {
        itemsOnMap.push_back(dynamic_cast<ItemOnMap*>(object));
    }

    if (object->type == GameObjectType::InventoryOnMap) {
        inventoriesOnMap.push_back(dynamic_cast<InventoryOnMap*>(object));
    }

    if (object->type == GameObjectType::FlatObject) {
        flatObjects.push_back(dynamic_cast<FlatObject*>(object));
    }

    if (object->type == GameObjectType::SmallObject) {
        smallObjects.push_back(dynamic_cast<SmallObject*>(object));
    }

    if (object->type == GameObjectType::Door) {
        doors.push_back(dynamic_cast<Door*>(object));
    }

    if (object->type == GameObjectType::Furniture) {
        furnitures.push_back(dynamic_cast<Furniture*>(object));
    }

    if (object->type == GameObjectType::Wall) {
        walls.push_back(dynamic_cast<Wall*>(object));
    }

    if (object->type == GameObjectType::Building) {

        
        Building* b = dynamic_cast<Building*>(object);
        buildings.push_back(b);
        b->isInTheMainList = true;

        b->_door->isInTheMainList = true;
        doors.push_back(b->_door);
        gameObjects.push_back(b->_door);
        

        for (auto& o : b->_furnitures) {
            Furniture* f = dynamic_cast<Furniture*>((o));
            f->isInTheMainList = true;
            furnitures.push_back(f);
            gameObjects.push_back(f);
        }
            

        for (auto& o : b->_walls) {
            Wall* w = dynamic_cast<Wall*>((o));
            w->isInTheMainList = true;
            walls.push_back(w);
            gameObjects.push_back(w);
        }
            

        for (auto& o : b->_items) {
            ItemOnMap* i = dynamic_cast<ItemOnMap*>((o));
            i->isInTheMainList = true;
            itemsOnMap.push_back(i);
            gameObjects.push_back(i);
        }
            

    }

    gameObjects.push_back(object);
}

void deleteGameObjectFromMainLists(GameObject* object) {

    if (object->type == GameObjectType::Nature) {
        auto it = std::find(natures.begin(), natures.end(), object);
        if (it != natures.end())
            natures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Object) {
        auto it = std::find(objects.begin(), objects.end(), object);
        if (it != objects.end())
            objects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), object);
        if (it != itemsOnMap.end())
            itemsOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::FlatObject) {
        auto it = std::find(flatObjects.begin(), flatObjects.end(), object);
        if (it != flatObjects.end())
            flatObjects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Furniture) {
        auto it = std::find(furnitures.begin(), furnitures.end(), object);
        if (it != furnitures.end())
            furnitures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Wall) {
        auto it = std::find(walls.begin(), walls.end(), object);
        if (it != walls.end())
            walls.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Door) {
        auto it = std::find(doors.begin(), doors.end(), object);
        if (it != doors.end())
            doors.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Monster) {
        auto it = std::find(monsters.begin(), monsters.end(), object);
        if (it != monsters.end())
            monsters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::SmallObject) {
        auto it = std::find(smallObjects.begin(), smallObjects.end(), object);
        if (it != smallObjects.end())
            smallObjects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Character) {
        auto it = std::find(characters.begin(), characters.end(), object);
        if (it != characters.end())
            characters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::InventoryOnMap) {
        auto it = std::find(inventoriesOnMap.begin(), inventoriesOnMap.end(), object);
        if (it != inventoriesOnMap.end())
            inventoriesOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    // TO-DO BUILDINGS
    if (object->type == GameObjectType::Building) {

        Building* b = dynamic_cast<Building*>(object);

        // delete Doors
        auto d = std::find(doors.begin(), doors.end(), b->_door);
        if (d != doors.end())
            doors.erase(d);

        auto dgo = std::find(gameObjects.begin(), gameObjects.end(), b->_door);
        if (dgo != gameObjects.end())
            gameObjects.erase(dgo);

        // delete items
        for (auto& item : b->_items) {
            auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
            if (it != itemsOnMap.end())
                itemsOnMap.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete furnitures
        for (auto& furniture : b->_furnitures) {
            auto it = std::find(furnitures.begin(), furnitures.end(), furniture);
            if (it != furnitures.end())
                furnitures.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), furniture);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete walls
        for (auto& wall : b->_walls) {
            auto it = std::find(walls.begin(), walls.end(), wall);
            if (it != walls.end())
                walls.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), wall);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        auto it = std::find(buildings.begin(), buildings.end(), object);
        if (it != buildings.end()) {
            buildings.erase(it);
            std::cout << "delete building from buildings\n";
        }
            

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end()) {
            gameObjects.erase(go);
            std::cout << "delete building from gameobjects\n";
        }
           
    }

}

void clearAllMainListsOfGameObjects() {
    // clear all main lists

    gameObjects.clear();

    natures.clear();
    objects.clear();
    itemsOnMap.clear();
    flatObjects.clear();
    furnitures.clear();
    walls.clear();
    doors.clear();
    monsters.clear();
    smallObjects.clear();
    characters.clear();
    inventoriesOnMap.clear();
    buildings.clear();
}

bool visiblings(GameObject* object) {
    // return true if GameObject is visible

    if (object != nullptr) {

        if (object->colliders[0] != nullptr) {
            if (object->colliders[0]->type == ColliderType::Elipse) {
                if (intersectionRectangleWithElipse(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->colliders[0]->width / 2.0f, object->colliders[0]->length / 2.0f)) {
                    return true;
                }
            }

            else if (object->colliders[0]->type == ColliderType::Rectangle) {
                if (intersectionTwoRectangles(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->colliders[0]->width, object->colliders[0]->length))
                    return true;
            }
        }
        else
            return true;
    }

    return true;
}

void updateGameObjects() {

    for (auto& go : gameObjects) {
        if (visiblings(go)) {

            go->isVisible = true;
            go->update();
            go->mouseHovering();
        }
        else
            go->isVisible = false;
    }
}

void sortGameObjects()
{
    std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void drawGameObjects() {

    for (auto& f : flatObjects) {
        if (f->isVisible) {
            f->drawStatistics();
        }
    }

    for (auto& f : flatObjects) {
        if (f->isVisible) {
            f->draw();
        }
    }

    for (auto& building : buildings) {
        window->draw(*building->floors);
        building->draw();
    }

    for (auto& go : gameObjects) {
        if (go->type != GameObjectType::FlatObject)
            if (go->isVisible) {
                go->drawStatistics();
            }
    }

    for (auto& go : gameObjects)
        if (go->type == GameObjectType::Building || go->isVisible == true)
            go->draw();

}


#endif