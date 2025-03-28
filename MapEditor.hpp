#ifndef MapEditor_hpp
#define MapEditor_hpp

void editTiles();
void editFloor();
void MapEditorEventRightClick(sf::Event& event);
void BuildingEditorEventRightClick(sf::Event& event);

void Editor() {

    window->setTitle("Map Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    editor_state = EditorStates::Start;

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    sf::Text* welcomeText = new sf::Text("Map Editor", basicFont, 32);
    welcomeText->setFillColor(textColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(textColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    bool skip = false;
    while (window->isOpen() && skip == false) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                skip = true;
                break;
            }
        }
        window->setView(cam->view);
        welcomeText->setPosition(cam->position.x, cam->position.y - 50);
        pressText->setPosition(cam->position.x, cam->position.y + 50);

        window->clear(sf::Color::Black);
        window->draw(*welcomeText);
        window->draw(*pressText);
        window->display();

    }

    editor_state = EditorStates::MapEditorInit;

    

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        if (editor_state == EditorStates::Close) {
            return;
        }

        else if (editor_state == EditorStates::MapEditorInit) {

            createTerrainPrefabs();
            createFloorsPrefabs();
            createWaterPrefabs();

            if (config != nullptr) {
                config->load();
            }
            else {
                menu_bar = new MenuBar(MenuBarType::MapEditor);
                palette = new Palette(PaletteType::MapEditor);
                painter = new Painter();
                tip = nullptr;
                context_menu = nullptr;
                clipboard = new Clipboard();

                mapa = new Mapa();

                ///cam->setPosition(sf::Vector2f(1280, 320+32));
                cam->setPosition(sf::Vector2f(0, 0));

                clearAllMainListsOfGameObjects();
                mapa->load();
                mapa->mapVisiblings();
                unselectGameObjects();
            }
            
            if (building_to_edit != nullptr) {
                sf::Vector2f position;
                position.x = building_to_edit_position.x+160;
                position.y = building_to_edit_position.y - building_to_edit->size.y/2*16;
                cam->setPosition(position);
                addGameObjectToMainLists(building_to_edit);
                building_to_edit->setPosition(building_to_edit_position);
                building_to_edit = nullptr;
            }

            
            mouse_state = MouseState::Idle;

            editor_state = EditorStates::MapEditor;

        }
        else if (editor_state == EditorStates::MapEditor) {

            if (dialogs.empty()) {
                float moveSpeed = 300.0f * dt;

                // moving the view
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    cam->move(0.0f, -moveSpeed);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    cam->move(0.0f, moveSpeed);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    cam->move(-moveSpeed, 0.0f);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    cam->move(moveSpeed, 0.0f);
            }

            GUIwasHover = false;
            GUIwasClicked = false;
            GUIwasOpen = false;

            for (auto& dialog : dialogs)
                dialog->update();

            palette->update();
            menu_bar->update();
            clipboard->update();

            if (context_menu != nullptr) {
                context_menu->update();

                if (context_menu->_state == ContextMenuState::Close) {
                    delete context_menu;
                    context_menu = nullptr;
                }
            }



            if (tip != nullptr && tip->btn != nullptr && tip->btn->state != ButtonState::Hover) {
                delete tip;
                tip = nullptr;
            }

            // events
            sf::Event event;
            while (window->pollEvent(event)) {

                //std::cout << "cursor on " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                else if (!dialogs.empty()) {

                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

                        delete dialogs.back();
                        dialogs.pop_back();
                    }
                    else if (dialogs.size() >= 2 && dialogs.back()->type == DialogType::Confirm && dialogs[dialogs.size() - 2]->type == DialogType::SaveFile) {
                        Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs[dialogs.size() - 2]);
                        confirm->handleEvent(event);

                        if (confirm->value != ConfirmValue::Undefinded) {
                            if (confirm->value == ConfirmValue::True) {
                                mapa->save(dial->getPathfile());
                                delete confirm;
                                delete dial;
                                dialogs.pop_back();
                                dialogs.pop_back();
                            }
                            else if (confirm->value == ConfirmValue::False) {
                                dial->state = FileDialogState::Idle;
                                delete confirm;
                                dialogs.pop_back();
                            }
                        }

                    }
                    else if (dialogs.back()->type == DialogType::SaveFile) {
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                        dial->handleEvent(event);

                        if (dial->state == FileDialogState::Canceled) {
                            delete dial;
                            dialogs.pop_back();
                        }
                        else if (dial->state == FileDialogState::FileSelected) {
                            std::wstring filename = getShortName(ConvertUtf8ToWide(dial->getPathfile()));
                            dialogs.push_back(new Confirm(L"Plik " + getShortName(filename) + L" już istnieje. Czy chcesz go zamienić?"));
                            dial->state = FileDialogState::Idle;
                            dial->selectButton->state = ButtonState::Idle;
                            dial->selectButton->changeColor();
                        }

                    }
                    else if (dialogs.back()->type == DialogType::OpenFile) {
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                        dial->handleEvent(event);

                        if (dial->cancelButton->state == ButtonState::Pressed) {
                            delete dial;
                            dialogs.pop_back();
                        }
                        else if (dial->state == FileDialogState::FileSelected) {
                            dial->selectButton->state == ButtonState::Idle;
                            mapa->load(dial->getPathfile());
                            delete dial;
                            dialogs.pop_back();
                        }

                    }
                    else if (dialogs.back()->type == DialogType::ScrollableText) {
                        ScrollableText* scrolltext = dynamic_cast<ScrollableText*>(dialogs.back());
                        scrolltext->handleEvent(event);
                    }
                    else if (dialogs.back()->type == DialogType::Confirm) {
                        Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                        confirm->handleEvent(event);

                        if (confirm->value != ConfirmValue::Undefinded) {
                            delete dialogs.back();
                            dialogs.pop_back();
                        }
                    }
                    else if (dialogs.back()->type == DialogType::Panel) {
                        dialogs.back()->handleEvent(event);
                    }

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                    std::cout << "left mouse is released\n";

                    if (context_menu != nullptr) {
                        context_menu->handleEvent(event);

                    }
                    else {
                        palette->handleEvent(event);
                        menu_bar->handleEvent(event);

                        if (!GUIwasHover && !GUIwasClicked) {
                            if (mouse_state == MouseState::MovingGameObjects) {
                                std::cout << "end of moving\n";
                            }
                            else if (painter->tool == toolType::AddGameObject) {
                                painter->addGameObjectsToMapAndLists(painter->prefabsToPaint, false);
                                std::cout << "add gameobject\n";
                            }
                            else if (mouse_state == MouseState::Selecting) {
                                mouseSelection();
                                selectGameObjects();
                                std::cout << "selecting\n";
                            }
                            

                        }

                    }

                    mouse_state = MouseState::Click;
                    mouse_state = MouseState::Idle;

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                    MapEditorEventRightClick(event);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    palette->handleEvent(event);

                    if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                        if (!GUIwasOpen && !GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork
                            if (mouse_state == MouseState::Idle) {

                                GameObject* clickedObject = nullptr;
                                for (auto& go : gameObjects) {
                                    if (go->mouseIsHover) {

                                        if (isPartOfBuilding(go) != nullptr) {
                                            clickedObject = isPartOfBuilding(go);
                                            break;
                                        }
                                        else {
                                            clickedObject = go;
                                            break;
                                        }
                                    }
                                }

                                if (clickedObject != nullptr && clickedObject->isSelected) {
                                    // MOVING GAMEOBJECTS

                                    sf::Vector2f center(0, 0);
                                    for (auto& obj : selectedGameObjects)
                                        center += obj->_object->position;

                                    center.x /= selectedGameObjects.size();
                                    center.y /= selectedGameObjects.size();

                                    sf::Vector2f offset;
                                    for (auto& obj : selectedGameObjects) {
                                        offset = obj->_object->position - worldMousePosition;
                                        obj->setOffset(offset);
                                    }

                                    mouse_state = MouseState::MovingGameObjects;
                                }
                                else if (clipboard->_state == ClipboardState::Idle) {
                                    // SELECTING
                                    mouse_state = MouseState::Selecting;
                                    mouse_start_time = currentTime;
                                    startMousePosition = mousePosition;
                                    startWorldMousePosition = worldMousePosition;

                                }



                            }

                        }
                    }

                }
                else if (sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    palette->handleEvent(event);
                }
                else if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                        exit(0);
                    }

                    if (event.key.code == sf::Keyboard::F5) {
                        mapa->save();
                    }

                    if (event.key.code == sf::Keyboard::F6) {
                        mapa->load();
                    }

                    if (event.key.code == sf::Keyboard::N) {
                        mapa->saveAsPNG("mapa.png");
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                        // TO-DO - UNDO ACTION
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        // DO NOTHING
                    }

                }
            } // events

            


            // UPDATE ////////////////////////////////////////////////////////////////////////
            /*
            if (!dialogs.empty()) {

                dialogs.back()->update();

                if (dialogs.back()->type == DialogType::SaveFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());

                    if (dial->state == FileDialogState::Canceled) {
                        delete dial;
                        dialogs.pop_back();
                    }
                }
            }
            */

            

            // drawing a terrain
            if (dialogs.empty()) {
                if (!GUIwasHover && !GUIwasClicked) {
                    if (!(menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen)) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if (painter->prefabToPaint != nullptr) {
                                if (painter->tool == toolType::Brush || painter->tool == toolType::RectBrush) {
                                    if (painter->prefabToPaint->type == GameObjectType::Terrain || painter->prefabToPaint->type == GameObjectType::Water)
                                        editTiles();
                                }
                            }
                            else if (mouse_state == MouseState::MovingGameObjects) {
                                for (auto& obj : selectedGameObjects) {
                                    Chunk* chunk;
                                    sf::Vector2f pos;

                                    (obj->_object->type == GameObjectType::Monster) ? pos = dynamic_cast<Monster*>(obj->_object)->base : pos = obj->_object->position;
                                    chunk = mapa->getChunk(pos);

                                    if (chunk != nullptr)
                                        chunk->deleteGameObject(obj->_object);


                                    obj->update();
                                    if (obj->_object->type == GameObjectType::Monster) {
                                        Monster* m = dynamic_cast<Monster*>(obj->_object);
                                        m->base = obj->_object->position;
                                        m->state = unitStates::idle;
                                        m->path.clear();    // TO-DO


                                    }


                                    (obj->_object->type == GameObjectType::Monster) ? pos = dynamic_cast<Monster*>(obj->_object)->base : pos = obj->_object->position;
                                    chunk = mapa->getChunk(pos);

                                    if (chunk != nullptr) {
                                        //std::cout << "new chunk is [" << chunk->coords.x << ", " << chunk->coords.y << "]\n";
                                        chunk->addGameObject(obj->_object);
                                    }
                                    else {
                                        //std::cout << "new chunk is nullptr\n";
                                    }
                                        
                                }

                            }
                        }
                    }
                }
            }

            if (!dialogs.empty())
                dialogs.back()->update();

            updateShaders();

            mapa->mapVisiblings();
            mapa->update();

            cam->update();

            if (context_menu == nullptr && mouse_state == MouseState::Selecting) {
                selectGameObjects();
            }

            updateGameObjects();
            sortGameObjects();

            painter->update();

            if (tip != nullptr)
                tip->update();

            // RENDER ////////////////////////////////////////////////////////////////////////////

            window->clear(backgroundColor);
            window->setView(cam->view);

            mapa->draw();
            mapa->drawStatistics();

            drawGameObjects();
            painter->draw();
            palette->draw();
            menu_bar->draw();

            for (auto& dial : dialogs)
                dial->draw();

            if (context_menu != nullptr)
                context_menu->draw();

            if (tip != nullptr)
                tip->draw();

            

            window->display();
        }

        else if (editor_state == EditorStates::BuildingEditorInit) {

            deleteGameObjectFromMainLists(building_to_edit);

            config = new Config();
            config->save();

            clearAllMainListsOfGameObjects();

            menu_bar = new MenuBar(MenuBarType::BuildingEditor);
            palette = new Palette(PaletteType::BuildingEditor);
            tip = nullptr;
            painter = new Painter();
            context_menu = nullptr;
            clipboard = new Clipboard();

            //mapa = new Mapa();
            cam = new Camera();

            unselectGameObjects();

            buildings.push_back(building_to_edit);
            building_to_edit_position = building_to_edit->position;
            building_to_edit->addGameObjectsToMainLists();
            building_to_edit->setPosition(sf::Vector2f(building_to_edit->size.x*16/2,building_to_edit->size.y*16));

            terrain = new Terrain(0, 0, building_to_edit->size.x, building_to_edit->size.y);
            
            cam->setPosition(building_to_edit->size.x*16/2+160, building_to_edit->size.y*16/2);

            std::cout << "Building Editor run\n";
            std::cout << "edit building nr " << building_to_edit->id << "\n";
            editor_state = EditorStates::BuildingEditor;

        }
        else if (editor_state == EditorStates::BuildingEditor) {

            GUIwasHover = false;
            GUIwasClicked = false;
            GUIwasOpen = false;

            for (auto& dialog : dialogs)
                dialog->update();

            palette->update();
            menu_bar->update();
            clipboard->update();

            if (context_menu != nullptr) {
                context_menu->update();

                if (context_menu->_state == ContextMenuState::Close) {
                    delete context_menu;
                    context_menu = nullptr;
                }
            }

            if (tip != nullptr && tip->btn != nullptr && tip->btn->state != ButtonState::Hover) {
                delete tip;
                tip = nullptr;
            }

            // events
            sf::Event event;
            while (window->pollEvent(event)) {

                //std::cout << "cursor on " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                else if (!dialogs.empty()) {

                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

                        delete dialogs.back();
                        dialogs.pop_back();
                    }
                    else if (dialogs.size() >= 2 && dialogs.back()->type == DialogType::Confirm && dialogs[dialogs.size() - 2]->type == DialogType::SaveFile) {
                        Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs[dialogs.size() - 2]);
                        confirm->handleEvent(event);

                        if (confirm->value != ConfirmValue::Undefinded) {
                            if (confirm->value == ConfirmValue::True) {
                                mapa->save(dial->getPathfile());
                                delete confirm;
                                delete dial;
                                dialogs.pop_back();
                                dialogs.pop_back();
                            }
                            else if (confirm->value == ConfirmValue::False) {
                                dial->state = FileDialogState::Idle;
                                delete confirm;
                                dialogs.pop_back();
                            }
                        }

                    }
                    else if (dialogs.back()->type == DialogType::SaveFile) {
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                        dial->handleEvent(event);

                        if (dial->state == FileDialogState::Canceled) {
                            delete dial;
                            dialogs.pop_back();
                        }
                        else if (dial->state == FileDialogState::FileSelected) {
                            std::wstring filename = getShortName(ConvertUtf8ToWide(dial->getPathfile()));
                            dialogs.push_back(new Confirm(L"Plik " + getShortName(filename) + L" już istnieje. Czy chcesz go zamienić?"));
                            dial->state = FileDialogState::Idle;
                            dial->selectButton->state = ButtonState::Idle;
                            dial->selectButton->changeColor();
                        }

                    }
                    else if (dialogs.back()->type == DialogType::OpenFile) {
                        FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                        dial->handleEvent(event);

                        if (dial->cancelButton->state == ButtonState::Pressed) {
                            delete dial;
                            dialogs.pop_back();
                        }
                        else if (dial->state == FileDialogState::FileSelected) {
                            dial->selectButton->state == ButtonState::Idle;
                            mapa->load(dial->getPathfile());
                            delete dial;
                            dialogs.pop_back();
                        }

                    }
                    else if (dialogs.back()->type == DialogType::ScrollableText) {
                        ScrollableText* scrolltext = dynamic_cast<ScrollableText*>(dialogs.back());
                        scrolltext->handleEvent(event);
                    }
                    else if (dialogs.back()->type == DialogType::Confirm) {
                        Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                        confirm->handleEvent(event);

                        if (confirm->value != ConfirmValue::Undefinded) {
                            delete dialogs.back();
                            dialogs.pop_back();
                        }
                    }
                    else if (dialogs.back()->type == DialogType::Panel) {
                        dialogs.back()->handleEvent(event);
                    }

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                    std::cout << "left mouse is released\n";

                    if (context_menu != nullptr) {
                        context_menu->handleEvent(event);

                    }
                    else {
                        palette->handleEvent(event);
                        menu_bar->handleEvent(event);

                        if (!GUIwasHover && !GUIwasClicked) {
                            if (mouse_state == MouseState::MovingGameObjects) {
                                std::cout << "end of moving gameobjects\n";
                            }
                            else if (painter->tool == toolType::AddGameObject) {
                                painter->addGameObjectsToBuildingAndLists(painter->prefabsToPaint, false);
                            }
                            else if (mouse_state == MouseState::Selecting) {
                                std::cout << "mouse selecting\n";
                                mouseSelection();
                                selectGameObjects();
                            }
                            else {
                                std::cout << "mouse idling\n";
                            }

                        }

                    }

                    mouse_state = MouseState::Click;
                    mouse_state = MouseState::Idle;

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                    BuildingEditorEventRightClick(event);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                        if (!GUIwasOpen && !GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork
                            if (mouse_state == MouseState::Idle) {

                                GameObject* clickedObject = nullptr;
                                for (auto& go : gameObjects) {
                                    if (go->mouseIsHover) {

                                        if (isPartOfBuilding(go) != nullptr) {
                                            clickedObject = isPartOfBuilding(go);
                                            break;
                                        }
                                        else {
                                            clickedObject = go;
                                            break;
                                        }
                                    }
                                }

                                if (clickedObject != nullptr && clickedObject->isSelected) {
                                    // MOVING GAMEOBJECTS

                                    sf::Vector2f center(0, 0);
                                    for (auto& obj : selectedGameObjects)
                                        center += obj->_object->position;

                                    center.x /= selectedGameObjects.size();
                                    center.y /= selectedGameObjects.size();

                                    sf::Vector2f offset;
                                    for (auto& obj : selectedGameObjects) {
                                        offset = obj->_object->position - worldMousePosition;
                                        obj->setOffset(offset);
                                    }

                                    mouse_state = MouseState::MovingGameObjects;
                                }
                                else if (clipboard->_state == ClipboardState::Idle) {
                                    // SELECTING
                                    mouse_state = MouseState::Selecting;
                                    mouse_start_time = currentTime;
                                    startMousePosition = mousePosition;
                                    startWorldMousePosition = worldMousePosition;

                                }



                            }

                        }
                    }

                }
                else if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                        exit(0);
                    }

                    if (event.key.code == sf::Keyboard::F5) {
                        mapa->save();
                    }

                    if (event.key.code == sf::Keyboard::F6) {
                        mapa->load();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                        // TO-DO - UNDO ACTION
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        // DO NOTHING
                    }

                }
            } // events

            // UPDATE ////////////////////////////////////////////////////////////////////////

            if (dialogs.empty()) {
                if (!GUIwasHover && !GUIwasClicked) {
                    if (!(menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen)) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if (painter->prefabToPaint != nullptr) {
                                if (painter->tool == toolType::Brush || painter->tool == toolType::RectBrush) {
                                    if (painter->prefabToPaint->type == GameObjectType::Floor) {
                                        editFloor();
                                    }
                                        
                                }
                            }
                            else if (mouse_state == MouseState::MovingGameObjects) {
                                for (auto& obj : selectedGameObjects) {
                                    sf::Vector2f pos;

                                    obj->update();
                                    if (obj->_object->type == GameObjectType::Monster) {
                                        Monster* m = dynamic_cast<Monster*>(obj->_object);
                                        m->base = obj->_object->position;
                                        m->state = unitStates::idle;
                                        m->path.clear();    // TO-DO
                                    }
                                }

                            }
                        }
                    }
                }
            }

            if (!dialogs.empty())
                dialogs.back()->update();

            updateShaders();

            cam->update();

            if (context_menu == nullptr && mouse_state == MouseState::Selecting) {
                selectGameObjects();
            }

            updateGameObjects();
            sortGameObjects();

            painter->update();

            if (tip != nullptr)
                tip->update();

            // RENDER ////////////////////////////////////////////////////////////////////////////

            window->clear(backgroundColor);
            window->setView(cam->view);
            window->draw(*terrain);
            drawGameObjects();
            painter->draw();
            palette->draw();
            menu_bar->draw();

            for (auto& dial : dialogs)
                dial->draw();

            if (context_menu != nullptr)
                context_menu->draw();

            if (tip != nullptr)
                tip->draw();

            

            window->display();
        }
    }


    // end of program
    delete window;
}

void editTiles() {

    for (auto& prefab : painter->prefabsToPaint) {

        if (prefab->_object->type == GameObjectType::Terrain) {

            TerrainPrefab* tp = dynamic_cast<TerrainPrefab*>(prefab->_object);
            //std::cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(tp->position);
            if (chunk != nullptr) {

                chunk->terrain->edit(tp->position, tp->id);
                chunk->water->edit(tp->position, -1);

                mapa->generateBorders(chunk);

                //
            }
        }

        if (prefab->_object->type == GameObjectType::Water) {

            WaterPrefab* wp = dynamic_cast<WaterPrefab*>(prefab->_object);
            //std::cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(wp->position);
            if (chunk != nullptr) {
                chunk->terrain->edit(wp->position, wp->terrain->id);
                chunk->water->edit(wp->position, wp->terrain->id);

                mapa->generateBorders(chunk);
            }
        }
    }
}

void editFloor() {
    for (auto& prefab : painter->prefabsToPaint) {
        if (prefab->_object->type == GameObjectType::Floor) {
            FloorPrefab* fp = dynamic_cast<FloorPrefab*>(prefab->_object);

            building_to_edit->floors->edit(fp->position, fp->id);
        }
    }
}

void MapEditorEventRightClick(sf::Event& event) {

    if (menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen) {
        menu_bar->handleEvent(event);
        return;
    }

    GameObject* clickedObject = nullptr;
    for (auto& go : gameObjects) {
        if (go->mouseIsHover) {

            if (isPartOfBuilding(go) != nullptr) {
                clickedObject = isPartOfBuilding(go);
            }
            else {
                clickedObject = go;
            }
        }
    }

    if (!painter->prefabsToPaint.empty()) {
        palette->unselectPaletteButton();
        painter->setPrefabToPaint(nullptr);
        painter->clear();
        painter->tool = toolType::Cursor;

        if (context_menu != nullptr) {
            delete context_menu;
            context_menu = nullptr;
        }
        return;
    }

    if (clickedObject != nullptr) {
        if (clickedObject->isSelected == false) {
            clickedObject->isSelected = true;
            unselectGameObjects();
            selectedGameObjects.push_back(new MouseMovedGameObject(clickedObject));
        }

        if (context_menu != nullptr)
            delete context_menu;

        context_menu = new ContextMenu(clickedObject);
        return;
    }

    if (!selectedGameObjects.empty()) {

        startMousePosition = mousePosition;
        startWorldMousePosition = worldMousePosition;

        mouseSelection();
        selectGameObjects();

        if (context_menu != nullptr)
            delete context_menu;

        context_menu = new ContextMenu(clickedObject);  // wdrożona poprawka 
        return;
    }

    if (context_menu != nullptr)
        delete context_menu;

    context_menu = new ContextMenu(nullptr);

}

void BuildingEditorEventRightClick(sf::Event& event) {

    if (menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen) {
        menu_bar->handleEvent(event);
        return;
    }

    GameObject* clickedObject = nullptr;
    for (auto& go : gameObjects) {
        if (go->type != GameObjectType::Building && go->mouseIsHover) {
            clickedObject = go;
        }
    }

    if (!painter->prefabsToPaint.empty()) {
        palette->unselectPaletteButton();
        painter->setPrefabToPaint(nullptr);
        painter->clear();
        painter->tool = toolType::Cursor;

        if (context_menu != nullptr) {
            delete context_menu;
            context_menu = nullptr;
        }
        return;
    }

    if (clickedObject != nullptr) {
        if (clickedObject->isSelected == false) {
            clickedObject->isSelected = true;
            unselectGameObjects();
            selectedGameObjects.push_back(new MouseMovedGameObject(clickedObject));
        }


        if (context_menu != nullptr)
            delete context_menu;

        context_menu = new ContextMenu(clickedObject);
        return;
    }

    if (!selectedGameObjects.empty()) {

        startMousePosition = mousePosition;
        startWorldMousePosition = worldMousePosition;

        mouseSelection();
        selectGameObjects();

        if (context_menu != nullptr)
            delete context_menu;

        context_menu = new ContextMenu(clickedObject);
        return;
    }

    

    if (context_menu != nullptr)
        delete context_menu;

    context_menu = new ContextMenu(nullptr);

}
#endif