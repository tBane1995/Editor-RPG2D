#ifndef MapEditor_hpp
#define MapEditor_hpp

void editTiles();
void editFloor();
void MapEditorEventRightClick(sf::Event& event);
void BuildingEditorEventRightClick(sf::Event& event);

sf::Text fps_counter;
sf::Text coordinates;

ButtonWithImage* reset_camera;

void Editor() {

    window->setTitle("Map Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets\\logo\\MapEditorLogo.png");
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

    // TO-DO - to delete
    fps_counter.setFont(basicFont);
    fps_counter.setFillColor(textColor);

    coordinates.setFont(basicFont);
    coordinates.setFillColor(textColor);
    coordinates.setCharacterSize(20);
    //

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

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
                renderer = new Renderer();
                menu_bar = new MenuBar(MenuBarType::MapEditor);
                palette = new Palette(PaletteType::MapEditor);
                painter = new Painter();
                tip = nullptr;
                context_menu = nullptr;
                clipboard = new Clipboard();

                mapa = new Mapa();

                ///cam->setPosition(sf::Vector2f(1280, 320+32));
                cam->setPosition(sf::Vector2f(1650, 1700));

                clearAllMainListsOfGameObjects();
                mapa->load();


                int map_size = sizeof(*mapa);

                for (auto& chunk : mapa->chunks) {
                    map_size += sizeof(*chunk);

                    // terrain
                    map_size += sizeof(*chunk->terrain);
                    map_size += chunk->terrain->tiles.size() * sizeof(chunk->terrain->tiles.front());
                    map_size += chunk->terrain->vertexes.getVertexCount() * sizeof(sf::Vertex);

                    // water
                    map_size += sizeof(*chunk->water);
                    map_size += chunk->water->tiles.size() * sizeof(chunk->water->tiles.front());
                    map_size += chunk->water->vertexes.getVertexCount() * sizeof(sf::Vertex);

                    // borders
                    map_size += sizeof(*chunk->borders);
                    map_size += chunk->borders->tiles.size() * sizeof(sf::FloatRect);
                    map_size += chunk->borders->outlines.getVertexCount() * sizeof(sf::Vertex);
                }

                std::cout << "map_sie: " << map_size << "\n";

                mapa->mapVisiblings();
                unselectGameObjects();

                ElementGUI_hovered = nullptr;
                ElementGUI_pressed = nullptr;
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
            else if (mesh_to_edit != nullptr) {
                mesh_to_edit->save();

                mesh_to_edit_gameobject = nullptr;
                mesh_to_edit = nullptr;
            }

            
            mouse_state = MouseState::Idle;

            editor_state = EditorStates::MapEditor;

        }
        else if (editor_state == EditorStates::MapEditor) {

            // MOVING THE MAP BY KEYS /////////////////////////////////
            

            if (dialogs.empty()) {
                float moveSpeed = 300.0f * dt;
                bool cam_moved = false;

                // moving the view
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    cam->move(0.0f, -moveSpeed);
                    cam_moved = true;
                }    

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    cam->move(0.0f, moveSpeed);
                    cam_moved = true;
                }
                    
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    cam->move(-moveSpeed, 0.0f);
                    cam_moved = true;
                }
                 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    cam->move(moveSpeed, 0.0f);
                    cam_moved = true;
                }
                
                if (cam_moved) {

                    if (context_menu != nullptr) {
                        delete context_menu;
                        context_menu = nullptr;
                    }


                    if (mouse_state == MouseState::MovingGameObjects) {
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
                                m->state = State::Idle;
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

            /////////////////////////////////////////////////////////

            GUIwasHover = false;
            GUIwasClicked = false;
            GUIwasOpen = false;

            ElementGUI_hovered = nullptr;

            cam->update();
            window->setView(cam->view);

            mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
            worldMousePosition = window->mapPixelToCoords(mousePosition);

            ///////////////////////////////////////////////////
            // cursor hovering

            for (auto& dialog : dialogs)
                dialog->cursorHover();

            palette->cursorHover();
            menu_bar->cursorHover();

            if (context_menu != nullptr) {
                context_menu->cursorHover();
            }

            ///////////////////////////////////////////////////
            // update 
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
                                std::wstring filename = dial->getPathfile();
                                if (filename.find(L".wrd") != filename.length() - 4)
                                    filename = filename + L".wrd";

                                mapa->save(filename);
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
                            
                            dial->state = FileDialogState::Idle;
                            dial->selectButton->state = ButtonState::Idle;
                            dial->selectButton->changeColor();

                            std::wstring pathfile = dial->getPathfile();

                            if (pathfile.find(L".wrd") != pathfile.length() - 4)
                                pathfile = pathfile + L".wrd";

                            std::wstring filename = getShortName(dial->getPathfile());

                            std::wcout << L"filename: " << filename << L"\n";
                            std::wcout << L"link: " << pathfile << L"\n";

                            std::ifstream file(pathfile); 
                            if (file.is_open()) {
                                dialogs.push_back(new Confirm(L"Plik " + filename + L" już istnieje. Czy chcesz go zamienić?"));
                            }
                            else {
                                mapa->save(pathfile);
                                delete dial;
                                dialogs.pop_back();
                            }
                            file.close();

                            
                            
                            
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
                            
                            std::cout << "file selected\n";
                            dial->selectButton->state == ButtonState::Idle;
                            
                            std::wstring pathfile = dial->getPathfile();
                            std::wstring filename = getShortName(pathfile);

                            if (pathfile.find(L".wrd") != pathfile.length() - 4)
                                pathfile = pathfile + L".wrd";

                            std::wcout << "filename: " << filename << L"\n";
                            std::wcout << "link: " << pathfile << L"\n";

                            std::ifstream file(pathfile);
                            if (file.is_open()) {
                                mapa->load(pathfile);
                                delete dial;
                                dialogs.pop_back();
                            }
                            else {
                                // TO-DO - Info Dialog
                                // dialogs.push_back(new Info(L"Plik " + filename + L" nie istnieje."));
                                std::wcout << L"Plik " + filename + L" nie istnieje.\n";
                                delete dial;
                                dialogs.pop_back();
                            }

                            

                            
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

                    if (context_menu != nullptr) {
                        context_menu->handleEvent(event);

                    }
                    else {
                        palette->handleEvent(event);
                        menu_bar->handleEvent(event);

                        if (clicked_gameObject != nullptr) {
                            if (clicked_gameObject->isSelected == false) {
                                unselectGameObjects();

                                MouseMovedGameObject* object = new MouseMovedGameObject(clicked_gameObject);
                                object->_object->isSelected = true;
                                selectedGameObjects.push_back(object);
                            }

                            clicked_gameObject = nullptr;

                        }else if (!GUIwasHover && !GUIwasClicked) {
                            if (mouse_state == MouseState::MovingGameObjects) {
                                //std::cout << "end of moving\n";
                            }
                            else if (painter->tool == toolType::AddGameObject) {
                                painter->addGameObjectsToMapAndLists(painter->prefabsToPaint, false);
                                //std::cout << "add gameobject\n";
                            }
                            else if (mouse_state == MouseState::Selecting) {
                                mouseSelection();
                                selectGameObjects();
                                //std::cout << "selecting\n";
                            }
                        }
                    }

                    ElementGUI_pressed = nullptr;

                    mouse_state = MouseState::Idle;

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                    MapEditorEventRightClick(event);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    startMousePosition = mousePosition;
                    startWorldMousePosition = worldMousePosition;

                    palette->handleEvent(event);
                    menu_bar->handleEvent(event);

                    if (context_menu != nullptr)
                        context_menu->handleEvent(event);

                    if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                        if (!GUIwasOpen && !GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork
                            if (mouse_state == MouseState::Idle) {

                                clicked_gameObject = getGameObject(worldMousePosition);
                                if (isPartOfBuilding(clicked_gameObject) != nullptr)
                                    clicked_gameObject = isPartOfBuilding(clicked_gameObject);

                                if (clicked_gameObject != nullptr && clicked_gameObject->isSelected) {
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
                                else {
                                    unselectGameObjects();
                                }
                            }

                        }
                    }
                }
                else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    
                    if (mouse_state == MouseState::Idle) {
                        if (ElementGUI_hovered == nullptr && ElementGUI_pressed == nullptr) {
                            float distance = sqrt(pow(startWorldMousePosition.x - worldMousePosition.x, 2) + pow(startWorldMousePosition.y - worldMousePosition.y, 2));

                            if (distance > 8) {
                                mouse_state = MouseState::Selecting;
                            }
                        }
                        
                    }

                    if (mouse_state == MouseState::Selecting) {
                        mouseSelection();
                        selectGameObjects();
                        //std::cout << "selecting\n";
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
                                m->state = State::Idle;
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

                    if (event.key.code == sf::Keyboard::M) {
                        mapa->saveAsPNG("mapa.png");
                    }

                    if (event.key.code == sf::Keyboard::N) {
                        for (auto& m : meshes) {
                            m->save();
                        }
                    }

                    if (event.key.code == sf::Keyboard::G) {
                        mapa->binary_save(L"world\\test_world.wrd");
                        std::cout << "saved\n";
                    }

                    if (event.key.code == sf::Keyboard::H) {
                        mapa->binary_load(L"world\\test_world.wrd");
                        std::cout << "loaded\n";
                    }

                    if (event.key.code == sf::Keyboard::B) {
                        menu_bar->WE_show_paletteBtn->click();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                        // TO-DO - UNDO ACTION
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        // DO NOTHING
                    }

                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    palette->handleEvent(event);
                }
            } // events

            // FRAMES PER SECONDS
            fps_counter.setPosition(cam->position.x - screenWidth / 2 + 25, cam->position.y - screenHeight / 2 + 50);
            FPS = 1.0f / FPSClock.restart().asSeconds();
            if (FPSClockUpdate.getElapsedTime().asSeconds() > 0.5f) {

                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << FPS << " FPS";

                window->setTitle("Editor RPG2D - " + ss.str());
                fps_counter.setString(ss.str());
                FPSClockUpdate.restart();
            }

            coordinates.setPosition(cam->position.x - screenWidth / 2 + 25, cam->position.y - screenHeight/2 + 90);
            coordinates.setString(to_string(int(cam->position.x)) + " " + to_string(int(cam->position.y)));

            // UPDATE ////////////////////////////////////////////////////////////////////////
            /*
            if (!dialogs.empty()) {

                dialogs.back()->update();

                if (dialogs.back()->type == DialogType::SaveFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                    `
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
                        }
                    }
                }
            }

            if (!dialogs.empty())
                dialogs.back()->update();

            updateShaders();

            renderer->update();
            mapa->mapVisiblings();
            mapa->update();

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

            mapa->draw();
            mapa->drawColliders();

            drawGameObjectsOnRenderer();

            renderer->draw();

            window->draw(fps_counter);
            window->draw(coordinates);

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

            cam = new Camera();

            unselectGameObjects();

            /////////////////////////////////////////////////////////////////////////////////////////

            buildings.push_back(building_to_edit);
            gameObjects.push_back(building_to_edit);
            building_to_edit_position = building_to_edit->position;
            building_to_edit->addGameObjectsToMainLists();
            building_to_edit->setPosition(sf::Vector2f(building_to_edit->size.x*16/2,building_to_edit->size.y*16));

            terrain = new Terrain(0, 0, building_to_edit->size.x, building_to_edit->size.y);
            
            cam->setPosition(building_to_edit->size.x*16/2+160, building_to_edit->size.y*16/2);

            /////////////////////////////////////////////////////////////////////////////////////////

            ElementGUI_hovered = nullptr;
            ElementGUI_pressed = nullptr;

            std::cout << "Building Editor run\n";
            std::cout << "edit building nr " << building_to_edit->id << "\n";
            editor_state = EditorStates::BuildingEditor;

            // TO-DO
            reset_camera = new ButtonWithImage(getSingleTexture(L"GUI\\building_editor_side_menu\\reset_camera"));
            reset_camera->setPosition(sf::Vector2f(-screenWidth/2.0f + 48, -screenHeight/2.0f + 48 + menu_bar->getSize().y));
            reset_camera->onclick_func = []() {
                if (palette->state == PaletteStates::Open) {
                    cam->setPosition(building_to_edit->size.x * 16 / 2 + 160, building_to_edit->size.y * 16 / 2);
                }else
                    cam->setPosition(building_to_edit->size.x * 16 / 2, building_to_edit->size.y * 16 / 2);
                };
            reset_camera->hover_func = []() {
                if (tip == nullptr || tip->btn != reset_camera) {
                    if (tip != nullptr)
                        delete tip;

                    tip = new Tip(L"reset camera", reset_camera);
                }
                };

        }
        else if (editor_state == EditorStates::BuildingEditor) {

            if (dialogs.empty()) {
                float moveSpeed = 300.0f * dt;
                bool cam_moved = false;

                // moving the view
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    cam->move(0.0f, -moveSpeed);
                    cam_moved = true;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    cam->move(0.0f, moveSpeed);
                    cam_moved = true;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    cam->move(-moveSpeed, 0.0f);
                    cam_moved = true;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    cam->move(moveSpeed, 0.0f);
                    cam_moved = true;
                }

                if (cam_moved) {

                    if (context_menu != nullptr) {
                        delete context_menu;
                        context_menu = nullptr;
                    }
                }
            }

            GUIwasHover = false;
            GUIwasClicked = false;
            GUIwasOpen = false;

            ElementGUI_hovered = nullptr;

            cam->update();
            window->setView(cam->view);

            mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
            worldMousePosition = window->mapPixelToCoords(mousePosition);

            for (auto& dialog : dialogs)
                dialog->update();

            palette->cursorHover();
            menu_bar->cursorHover();
            reset_camera->cursorHover();

            if (context_menu != nullptr) {
                context_menu->cursorHover();
            }

            palette->update();
            menu_bar->update();
            clipboard->update();
            reset_camera->update();

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
                            std::wstring filename = getShortName(dial->getPathfile());
                            dialogs.push_back(new Confirm(L"Plik " + getShortName(filename) + L" już istnieje. Czy chcesz go zamienić?"));
                            dial->state = FileDialogState::Idle;
                            //dial->selectButton->state = ButtonState::Idle;
                            //dial->selectButton->changeColor();
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

                    if (context_menu != nullptr) {
                        context_menu->handleEvent(event);

                    }
                    else {
                        palette->handleEvent(event);
                        menu_bar->handleEvent(event);
                        reset_camera->handleEvent(event);

                        if (clicked_gameObject != nullptr && clicked_gameObject->type != GameObjectType::Building) {
                            if (clicked_gameObject->isSelected == false) {
                                unselectGameObjects();

                                MouseMovedGameObject* object = new MouseMovedGameObject(clicked_gameObject);
                                object->_object->isSelected = true;
                                selectedGameObjects.push_back(object);
                            }

                            clicked_gameObject = nullptr;

                        }
                        else if (!GUIwasHover && !GUIwasClicked) {
                            if (mouse_state == MouseState::MovingGameObjects) {
                                //std::cout << "end of moving\n";
                            }
                            else if (painter->tool == toolType::AddGameObject) {
                                painter->addGameObjectsToBuildingAndLists(painter->prefabsToPaint, false);
                                //std::cout << "add gameobject\n";
                            }
                            else if (mouse_state == MouseState::Selecting) {
                                mouseSelection();
                                selectGameObjects();
                                //std::cout << "selecting\n";
                            }
                        }
                    }

                    ElementGUI_pressed = nullptr;

                    mouse_state = MouseState::Click;
                    mouse_state = MouseState::Idle;

                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                    BuildingEditorEventRightClick(event);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    startMousePosition = mousePosition;
                    startWorldMousePosition = worldMousePosition;

                    palette->handleEvent(event);
                    menu_bar->handleEvent(event);
                    reset_camera->handleEvent(event);

                    if (context_menu != nullptr)
                        context_menu->handleEvent(event);

                    if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                        if (!GUIwasOpen && !GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork
                            if (mouse_state == MouseState::Idle) {

                                clicked_gameObject = getGameObject(worldMousePosition);

                                if (clicked_gameObject != nullptr && clicked_gameObject->isSelected) {
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
                                else {
                                    unselectGameObjects();
                                }
                            }

                        }
                    }
                }
                else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    if (mouse_state == MouseState::Idle) {
                        float distance = sqrt(pow(startWorldMousePosition.x - worldMousePosition.x, 2) + pow(startWorldMousePosition.y - worldMousePosition.y, 2));

                        if (distance > 8) {
                            mouse_state = MouseState::Selecting;
                        }
                    }

                    if (mouse_state == MouseState::Selecting) {
                        mouseSelection();
                        selectGameObjects();
                        //std::cout << "selecting\n";
                    }
                    else if (mouse_state == MouseState::MovingGameObjects) {
                        for (auto& obj : selectedGameObjects) {
                            
                            sf::Vector2f pos = obj->_object->position;
                            obj->update();
                            pos = obj->_object->position;
                        }
                    }
                }
                else if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                        exit(0);
                    }

                    if (event.key.code == sf::Keyboard::B) {
                        menu_bar->BE_show_paletteBtn->click();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                        // TO-DO - UNDO ACTION
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        // DO NOTHING
                    }

                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    palette->handleEvent(event);
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
                                        m->state = State::Idle;
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

            renderer->update();

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
            
            renderer->getTheCurrentFrame()->draw(*terrain);
            drawGameObjectsOnRenderer();
            renderer->draw();

            painter->draw();
            palette->draw();
            menu_bar->draw();
            reset_camera->draw();

            for (auto& dial : dialogs)
                dial->draw();

            if (context_menu != nullptr)
                context_menu->draw();

            if (tip != nullptr)
                tip->draw();

            

            window->display();
        }

        else if (editor_state == EditorStates::MeshEditorInit) {

            config = new Config();
            config->save();

            clearAllMainListsOfGameObjects();

            menu_bar = new MenuBar(MenuBarType::MeshEditor);
            palette = nullptr;
            tip = nullptr;
            painter = nullptr;
            context_menu = nullptr;
            clipboard = nullptr;

            cam = new Camera();

            unselectGameObjects();

            /////////////////////////////////////////////////////////////////////////////////////////

            mesh_to_edit = mesh_to_edit_gameobject->mesh;
            if (mesh_to_edit == nullptr) {
                mesh_to_edit = new Mesh(mesh_to_edit_gameobject->name);

                getPrefab(mesh_to_edit_gameobject->name)->mesh = mesh_to_edit;

                for (auto& chunk : mapa->chunks) {
                    std::vector < GameObject* > objects_from_chunk = chunk->getAllGameObjects();

                    for (auto& o : objects_from_chunk) {
                        if (o->name == mesh_to_edit_gameobject->name) {
                            o->mesh = mesh_to_edit;
                        }
                    }
                }
            }

            sf::Vector2f cam_position;
            cam_position.x = 0;
            cam_position.y = -int(mesh_to_edit_gameobject->height);
            cam->setPosition(cam_position);

            if (mesh_to_edit->triangles.size() > 0)
                mesh_to_edit_vertices = mesh_to_edit->getVertices();
            else
                mesh_to_edit_vertices.clear();
                
            /////////////////////////////////////////////////////////////////////////////////////////

            ElementGUI_hovered = nullptr;
            ElementGUI_pressed = nullptr;

            std::cout << "Mesh Editor run\n";
            editor_state = EditorStates::MeshEditor;
        }
        else if (editor_state == EditorStates::MeshEditor) {
            
            GUIwasHover = false;
            GUIwasClicked = false;
            GUIwasOpen = false;

            ElementGUI_hovered = nullptr;

            cam->update();
            window->setView(cam->view);

            mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
            worldMousePosition = window->mapPixelToCoords(mousePosition);

            menu_bar->cursorHover();
            menu_bar->update();

            // EVENTS ////////////////////////////////////////////////////////////////////////////
            sf::Event event;
            while (window->pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                menu_bar->handleEvent(event);

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        
                        

                        if (ElementGUI_hovered == nullptr && ElementGUI_pressed == nullptr) {
                            sf::Vector2f position;
                            position.x = (int(worldMousePosition.x) / 16) * 16;
                            position.y = (int(worldMousePosition.y) / 16) * 16;

                            bool pointExists = false;

                            for (auto& v : mesh_to_edit_vertices) {
                                if (abs(v.x - position.x) < 16/2 && abs(v.y - position.y) < 16/2)
                                    pointExists = true;
                            }

                            if (!pointExists) {
                                sf::Vector2f p = sf::Vector2f(position.x / 2, position.y / 2);
                                mesh_to_edit_vertices.push_back(p);
                                mesh_to_edit->triangulate(mesh_to_edit_vertices);
                                std::cout << "added point " << position.x << ", " << position.y << "\n";
                            }
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2f position;
                        position.x = (int(worldMousePosition.x) / 16) * 16;
                        position.y = (int(worldMousePosition.y) / 16) * 16;
                        sf::Vector2f p = sf::Vector2f(position.x / 2, position.y / 2);

                        auto v = std::find(mesh_to_edit_vertices.begin(), mesh_to_edit_vertices.end(), p);

                        if (v != mesh_to_edit_vertices.end()) {
                            mesh_to_edit_vertices.erase(v);
                            mesh_to_edit->triangulate(mesh_to_edit_vertices);
                            std::cout << "delete point " << position.x << ", " << position.y << "\n";
                        }
                            
                    }
                }
            }
            // UPDATE ////////////////////////////////////////////////////////////////////////////
            
            renderer->update();

            // RENDER ////////////////////////////////////////////////////////////////////////////

            window->clear(backgroundColor);
            

            float scale = 2.0f;

            sf::Sprite spr;
            spr.setTexture(*mesh_to_edit_gameobject->textures[0]->texture);
            spr.setOrigin(int(mesh_to_edit_gameobject->textures[0]->cx), int(mesh_to_edit_gameobject->textures[0]->cy));
            spr.setScale(scale, scale);
            spr.setPosition(0, 0);
            renderer->getTheCurrentFrame()->draw(spr);
            
            // render grid
            sf::FloatRect bounds = spr.getGlobalBounds();

            float gridSize = 16.0f;
            // linie pionowe
            for (float x = bounds.left; x <= bounds.left + bounds.width; x += gridSize) {
                sf::Vector2f start(x, bounds.top);
                sf::Vector2f end(x, bounds.top + bounds.height);
                drawThickLine(start, end, 1.0f, sf::Color(64, 64, 64));
            }

            // linie poziome
            for (float y = bounds.top; y <= bounds.top + bounds.height; y += gridSize) {
                sf::Vector2f start(bounds.left, y);
                sf::Vector2f end(bounds.left + bounds.width, y);
                drawThickLine(start, end, 1.0f, sf::Color(64, 64, 64));
            }


            mesh_to_edit->draw(scale);

            for (auto& v : mesh_to_edit_vertices) {
                sf::CircleShape point(4.0f);
                point.setFillColor(sf::Color::Blue);
                point.setOrigin(4.0f, 4.0f);
                point.setPosition(v.x * scale, v.y * scale);
                renderer->getTheCurrentFrame()->draw(point);
            }

            sf::CircleShape cursor(4.0f);
            cursor.setFillColor(sf::Color::Magenta);
            cursor.setOrigin(4.0f, 4.0f);
            sf::Vector2f pos(int(worldMousePosition.x)/16*16, int(worldMousePosition.y)/16*16);
            cursor.setPosition(pos);
            renderer->getTheCurrentFrame()->draw(cursor);

            renderer->draw();
            menu_bar->draw();

            for (auto& dial : dialogs)
                dial->draw();

            if (context_menu != nullptr)
                context_menu->draw();

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

    GameObject* clickedObject = getGameObject(worldMousePosition);

    if (clickedObject!=nullptr && isPartOfBuilding(clickedObject))
        clickedObject = isPartOfBuilding(clickedObject);

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

    GameObject* clickedObject = getGameObject(worldMousePosition);

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