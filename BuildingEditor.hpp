#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

enum class buildingEditorStates { start, editor };
buildingEditorStates buildingEditorState;

bool BuildingEditor_deleteChosenGameObject();

void BuildingEditor() {

    /*
    window->setTitle("Building Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    buildingEditorState = buildingEditorStates::start;

    sf::Text* welcomeText = new sf::Text("Building Editor", basicFont, 32);
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

    /////////////////////////////////////////////////////////////////////////////////////////////////

    buildingEditorState = buildingEditorStates::editor;

    clearAllMainListsOfGameObjects();

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    selectedGameObjects.clear();
    mouse_state = MouseState::Idle;

    menu_bar = new MenuBar(MenuBarType::BuildingEditor);
    palette = new Palette(PaletteType::BuildingEditor);
    tip = nullptr;
    painter = new Painter();

    loadBuildingFromFile(); // load building
    terrain = new Terrain(0, 0, building->size.x, building->size.y);
    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        palette->update();
        menu_bar->update();
        if (context_menu != nullptr)
            context_menu->update();

        for (auto& dialog : dialogs)
            dialog->update();


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
                            saveBuildingToFile();
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
                        loadBuildingFromFile(dial->getPathfile());
                        
                        if (terrain != nullptr)
                            delete terrain;

                        terrain = new Terrain(0, 0, building->size.x, building->size.y);
                        cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

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

            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                mouse_state = MouseState::Click;

                palette->handleEvent(event);
                menu_bar->handleEvent(event);
                if (context_menu != nullptr) {
                    context_menu->handleEvent(event);
                    if (context_menu->_state == ContextMenuState::Close) {
                        delete context_menu;
                        context_menu = nullptr;
                    }

                }




                if (!GUIwasHover && !GUIwasClicked)
                    if (painter->tool == toolType::AddGameObject) {
                        //addPrefabsToBuildingAndLists();
                    }


                mouse_state = MouseState::Idle;



            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                if (unselectGameObjects()) {
                    std::cout << "unselect GameObjects\n";
                }
                else if (BuildingEditor_deleteChosenGameObject()) {
                    std::cout << "delete chosen GameObject\n";
                }
                else {
                    palette->unselectPaletteButton();
                    std::cout << "unselect Palette Button\n";
                }


            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                    if (!GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork

                        if (mouse_state == MouseState::Idle) {

                            mouse_state = MouseState::Selecting;
                            mouse_start_time = currentTime;
                            startMousePosition = mousePosition;
                            startWorldMousePosition = worldMousePosition;

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
                    saveBuildingToFile();
                }

                if (event.key.code == sf::Keyboard::F6) {
                    dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Building"));
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                    // TO-DO - UNDO ACTION
                }

                if (event.key.code == sf::Keyboard::Space) {
                    // DO NOTHING
                }

            }
        } // events

        // drawing a terrain
        if (dialogs.empty()) {
            if (!GUIwasHover && !GUIwasClicked) {
                if (painter->prefabToPaint != nullptr) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (painter->tool == toolType::Brush || painter->tool == toolType::RectBrush) {
                            if (painter->prefabToPaint->type == GameObjectType::Floor)
                                for (auto& prefab : painter->prefabsToPaint) {
                                    building->floors->edit(prefab->_object->position, dynamic_cast<FloorPrefab*>(painter->prefabToPaint)->id);
                                }
                        }
                    }
                }
            }
        }

        // UPDATE ///////////////////////////////////////////////////////////////////////
        if (!dialogs.empty())
            dialogs.back()->update();

        updateShaders();

        cam->update();

        if (mouse_state == MouseState::Selecting)
            selectGameObjects();

        updateGameObjects();
        sortGameObjects();
        painter->update();
  
        if (tip != nullptr)
            tip->update();

        // RENDER ////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color::Black);
        window->setView(cam->view);
        window->draw(*terrain);

        window->draw(*building->floors);

        for (auto& go : gameObjects) {
            if (go->type != GameObjectType::FlatObject) {
                if (go->isVisible) {
                        go->drawStatistics();
                }
            }
        }

        drawGameObjects();
        painter->draw();
        palette->draw();
        menu_bar->draw();

        for (auto& dial : dialogs)
            dial->draw();

        if (tip != nullptr)
            tip->draw();

        window->display();
    }
}

bool BuildingEditor_deleteChosenGameObject() {
    bool was_delete = false;
    
    if (was_delete == false) {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
            GameObject* go = *it;

            if (go->type != GameObjectType::Building && go->mouseIsHover == true) {


                building->deleteGameObject(go);
                deleteGameObjectFromMainLists(go);  // erase
                delete go;      // delete

                was_delete = true;
                break;
            }
            else
                it++;
        }
    }

    return was_delete;
    */
}


#endif