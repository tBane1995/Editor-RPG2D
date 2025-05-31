#ifndef MenuBar_hpp
#define MenuBar_hpp

enum class MenuBarStates { Close, Open, Closing };

class OptionButton : public ButtonWithText {
public:
    CheckBox* checkbox;

    OptionButton(std::string text) : ButtonWithText(text) {

        this->position = position;
        checkbox = nullptr;
    }

    ~OptionButton() {
        delete checkbox;
    }

    void update(bool hover_action = true) {
        ButtonWithText::update(hover_action);

        if (checkbox)
            checkbox->update();
    }

    void draw() {
        ButtonWithText::draw();
        checkbox->draw();
    }

};

class MenuButton : public ButtonWithText {
public:
    std::vector < ButtonWithText* > options;
    bool isOpen;

    MenuButton(std::string text) : ButtonWithText(text) {
        isOpen = false;
        options.clear();
    }

    void addOption(ButtonWithText* btn) {

        options.push_back(btn);

        // width alignment
        float max_width = 0;

        for (auto& o : options) {
            float wdt = o->text.getLocalBounds().getSize().x + 2 * o->margin;

            if (dynamic_cast<OptionButton*>(o))
                wdt += o->rect.getSize().y;

            if (wdt > max_width)
                max_width = wdt;
        }

        // SET THE WIDTH FOR ANY BUTTON
        for (auto& o : options) {
            o->rect.setSize(sf::Vector2f(max_width, o->rect.getSize().y));
        }

        // positioning pos Y
        float pos_y = -screenHeight / 2;
        for (int i = 0; i < options.size(); i++) {
            float pos_y2 = rect.getSize().y;
            for (int j = 0; j < i; j++) {
                pos_y2 += options[j]->rect.getSize().y;
            }
            options[i]->setPosition(sf::Vector2f(position.x, pos_y + pos_y2));
        }

        // positioning checkboxes
        for (auto& o : options) {
            OptionButton* ob = dynamic_cast<OptionButton*>(o);
            if (ob != nullptr && ob->checkbox != nullptr) {
                sf::Vector2f size = sf::Vector2f(o->rect.getSize().y, o->rect.getSize().y);
                sf::Vector2f pos2;
                pos2.x = position.x + max_width - size.x / 2.0f;
                pos2.y = o->position.y + size.y / 2.0f;
                ob->checkbox->edit(size, pos2);
            }
        }

    }

    void draw() {
        ButtonWithText::draw();

        if (isOpen)
            for (auto& o : options)
                o->draw();
    }
};

enum class MenuBarType { MapEditor, BuildingEditor, MeshEditor };

class MenuBar {
public:

    MenuBarType type;

    sf::Sprite logo;
    sf::RectangleShape bar;

    MenuButton* fileBtn;
    MenuButton* viewBtn;
    MenuButton* toolsBtn;
    MenuButton* helpBtn;

    // FILE
    // Editor (main)
    ButtonWithText* newWorldBtn;    
    ButtonWithText* loadWorldBtn;
    ButtonWithText* saveWorldBtn;

    // Building Editor
    ButtonWithText* closeBEBtn;

    // Mesh Editor
    ButtonWithText* closeMEBtn;    

    // RENDER
    OptionButton* show_bordersBtn;
    OptionButton* show_coordsBtn;
    OptionButton* show_tilesBordersBtn;
    OptionButton* show_actionRangeBtn;
    OptionButton* show_viewRangeBtn;
    OptionButton* show_collidersBtn;
    OptionButton* show_meshesBtn;
    OptionButton* show_monsterBasesBtn;
    OptionButton* show_buildingsOutsidesBtn;

    // TOOLS
    OptionButton* show_paletteBtn;
    OptionButton* show_gridBEBtn;
    OptionButton* show_gridMEBtn;

    // HELP
    ButtonWithText* instructionsMEBtn;
    ButtonWithText* instructionsBEBtn;
    ButtonWithText* aboutMEBtn;
    ButtonWithText* aboutBEBtn;
    ButtonWithText* settingsMEBtn;
    ButtonWithText* settingsBEBtn;

    std::vector < MenuButton* > menu;
    MenuButton* clickedMenuButton;
    MenuBarStates state = MenuBarStates::Close;

    MenuBar(MenuBarType type) {

        this->type = type;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f barSize = sf::Vector2f(screenWidth, 30.0f);
        bar = sf::RectangleShape(barSize);
        bar.setPosition(cam->position.x - screenWidth / 2, cam->position.y - screenHeight / 2);
        bar.setFillColor(sf::Color(32, 32, 32));

        logo = sf::Sprite();
        logo.setTexture(*getSingleTexture(L"GUI\\icons\\MapEditor_small_ico")->texture);
        logo.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);

        createButtons();
        createMenu();
        clickedMenuButton = nullptr;
    }

    void createButtons() {
        sf::Vector2f position;

        fileBtn = new MenuButton("FILE");
        fileBtn->onclick_func = [this]() {
            if (clickedMenuButton != nullptr)
                clickedMenuButton->isOpen = false;

            if (!fileBtn->isOpen) {
                fileBtn->isOpen = true;
                clickedMenuButton = fileBtn;
            }
            else
                fileBtn->isOpen = false;
            };

        viewBtn = new MenuButton("VIEW");
        viewBtn->onclick_func = [this]() {
            if (clickedMenuButton != nullptr)
                clickedMenuButton->isOpen = false;

            if (!viewBtn->isOpen) {
                viewBtn->isOpen = true;
                clickedMenuButton = viewBtn;
            }
            else
                viewBtn->isOpen = false;
            };

        toolsBtn = new MenuButton("TOOLS");
        toolsBtn->onclick_func = [this]() {
            if (clickedMenuButton != nullptr)
                clickedMenuButton->isOpen = false;

            if (!toolsBtn->isOpen) {
                toolsBtn->isOpen = true;
                clickedMenuButton = toolsBtn;
            }
            else
                toolsBtn->isOpen = false;
            };

        helpBtn = new MenuButton("HELP");
        helpBtn->onclick_func = [this]() {
            if (clickedMenuButton != nullptr)
                clickedMenuButton->isOpen = false;

            if (!helpBtn->isOpen) {
                helpBtn->isOpen = true;
                clickedMenuButton = helpBtn;
            }
            else
                helpBtn->isOpen = false;
            };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        newWorldBtn = new ButtonWithText("New Map");
        newWorldBtn->onclick_func = [this]() {
            mapa = new Mapa();
            };

        loadWorldBtn = new ButtonWithText("Load Map");
        loadWorldBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Map", ".wrd"));
            };

        saveWorldBtn = new ButtonWithText("Save Map");
        saveWorldBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::SaveFile, L"Save Map", ".wrd"));
            };

        closeBEBtn = new ButtonWithText("Close Building Editor");
        closeBEBtn->onclick_func = [this]() {
            editor_state = EditorStates::MapEditorInit;
            };

        closeMEBtn = new ButtonWithText("Close Mesh Editor");
        closeMEBtn->onclick_func = [this]() {
            editor_state = EditorStates::MapEditorInit;
            };

        show_bordersBtn = new OptionButton("Map Borders");
        show_bordersBtn->checkbox = new CheckBox();
        show_bordersBtn->checkbox->value = renderer->renderBorders;
        show_bordersBtn->onclick_func = [this]() {
            (renderer->renderBorders) ? renderer->renderBorders = false : renderer->renderBorders = true;
            show_bordersBtn->checkbox->value = renderer->renderBorders;
            };

        show_coordsBtn = new OptionButton("Map Coords");
        show_coordsBtn->checkbox = new CheckBox();
        show_coordsBtn->checkbox->value = renderer->renderCoords;
        show_coordsBtn->onclick_func = [this]() {
            (renderer->renderCoords) ? renderer->renderCoords = false : renderer->renderCoords = true;
            show_coordsBtn->checkbox->value = renderer->renderCoords;
            };

        show_tilesBordersBtn = new OptionButton("Tiles Borders");
        show_tilesBordersBtn->checkbox = new CheckBox();
        show_tilesBordersBtn->checkbox->value = renderer->renderTilesBorders;
        show_tilesBordersBtn->onclick_func = [this]() {
            (renderer->renderTilesBorders) ? renderer->renderTilesBorders = false : renderer->renderTilesBorders = true;
            show_tilesBordersBtn->checkbox->value = renderer->renderTilesBorders;
            };

        show_actionRangeBtn = new OptionButton("Action Range");
        show_actionRangeBtn->checkbox = new CheckBox();
        show_actionRangeBtn->checkbox->value = renderer->renderActionRange;
        show_actionRangeBtn->onclick_func = [this]() {
            (renderer->renderActionRange) ? renderer->renderActionRange = false : renderer->renderActionRange = true;
            show_actionRangeBtn->checkbox->value = renderer->renderActionRange;
            };

        show_viewRangeBtn = new OptionButton("View Range");
        show_viewRangeBtn->checkbox = new CheckBox();
        show_viewRangeBtn->checkbox->value = renderer->renderViewRange;
        show_viewRangeBtn->onclick_func = [this]() {
            (renderer->renderViewRange) ? renderer->renderViewRange = false : renderer->renderViewRange = true;
            show_viewRangeBtn->checkbox->value = renderer->renderViewRange;
            };

        show_collidersBtn = new OptionButton("Colliders");
        show_collidersBtn->checkbox = new CheckBox();
        show_collidersBtn->checkbox->value = renderer->renderColliders;
        show_collidersBtn->onclick_func = [this]() {
            (renderer->renderColliders) ? renderer->renderColliders = false : renderer->renderColliders = true;
            show_collidersBtn->checkbox->value = renderer->renderColliders;
            };

        show_meshesBtn = new OptionButton("Meshes");
        show_meshesBtn->checkbox = new CheckBox();
        show_meshesBtn->checkbox->value = renderer->renderMeshes;
        show_meshesBtn->onclick_func = [this]() {
            (renderer->renderMeshes) ? renderer->renderMeshes = false : renderer->renderMeshes = true;
            show_meshesBtn->checkbox->value = renderer->renderMeshes;
            };

        show_monsterBasesBtn = new OptionButton("Monsters Bases");
        show_monsterBasesBtn->checkbox = new CheckBox();
        show_monsterBasesBtn->checkbox->value = renderer->renderMonsterBases;
        show_monsterBasesBtn->onclick_func = [this]() {
            (renderer->renderMonsterBases) ? renderer->renderMonsterBases = false : renderer->renderMonsterBases = true;
            show_monsterBasesBtn->checkbox->value = renderer->renderMonsterBases;
            };

        show_buildingsOutsidesBtn = new OptionButton("Buildings Outsides");
        show_buildingsOutsidesBtn->checkbox = new CheckBox();
        show_buildingsOutsidesBtn->checkbox->value = renderer->renderBuildingsOutside;
        show_buildingsOutsidesBtn->onclick_func = [this]() {
            (renderer->renderBuildingsOutside) ? renderer->renderBuildingsOutside = false : renderer->renderBuildingsOutside = true;
            show_buildingsOutsidesBtn->checkbox->value = renderer->renderBuildingsOutside;
            };

        show_paletteBtn = new OptionButton("Show Palette");
        show_paletteBtn->checkbox = new CheckBox();
        show_paletteBtn->checkbox->value = true;
        show_paletteBtn->onclick_func = [this]() {

            if (palette->state == PaletteStates::Open) {
                palette->close();
                show_paletteBtn->checkbox->value = false;

            }else if(palette->state == PaletteStates::Close) {
                palette->open();
                show_paletteBtn->checkbox->value = true;
            }
            };

        show_gridBEBtn = new OptionButton("Show Grid");
        show_gridBEBtn->checkbox = new CheckBox();
        show_gridBEBtn->checkbox->value = false;
        show_gridBEBtn->onclick_func = [this]() {

            (show_gridBEBtn->checkbox->value == true) ? show_gridBEBtn->checkbox->value = false : show_gridBEBtn->checkbox->value = true;
            };

        show_gridMEBtn = new OptionButton("Show Grid");
        show_gridMEBtn->checkbox = new CheckBox();
        show_gridMEBtn->checkbox->value = false;
        show_gridMEBtn->onclick_func = [this]() {

            (show_gridBEBtn->checkbox->value == true) ? show_gridBEBtn->checkbox->value = false : show_gridBEBtn->checkbox->value = true;
            };

        instructionsMEBtn = new ButtonWithText("Instructions");
        instructionsMEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"1. O programie\n"
                L"-Map Editor jest to program do edycji mapy świata gry RPG 2D. W tym programie możesz tworzyć oraz edytować mapę, dodawać oraz usuwać różne obiekty takie jak drzewa, skały, rośliny i potworki. Program jest intuicyjny oraz prosty w obsłudze.\n"
                L"\n"

                L"2. Sterowanie\n"
                L"a) Program obsługuje zarówno klawiaturę jak i mysz\n"
                L"b) Sterowanie\n"
                L"-LPM - zaznacz, wybierz lub dodaj obiekt\n"
                L"-PPM - odznacz, anuluj lub usuń\n"
                L"-WASD lub strzałki - przesuwanie mapy świata\n"
                L"-F5 - zapisz mapę\n"
                L"-F6 - wczytaj mapę\n"
                L"-B - pokaż/ukryj paletę\n"
                L"-M - wykonaj zapis mapy do pliku PNG (w głównym folderze z programem tworzy plik \"mapa.png\")\n"
                L"-N - zapisz meshe GameObjectów\n"
                L"-G - zapis binarny mapy jako \"world\\test_world.wrd\"\n"
                L"-H - wczytanie zapisu binarnego mapy \"world\\test_world.wrd\"\n"
                L"\n"

                L"3. Paleta\n"
                L"-W programie paleta służy do wybierania prefabrykatów lub narzędzi\n"
                L"a) Grupy Obiektów:\n"
                L"-Teren - wybór rodzaju terenu np. plaża, trawa lub wyżyna\n"
                L"-Wody - wybór rodzaju wody np. jezioro, ocean lub bagno\n"
                L"-Obiekty naturalne - drzewa, kamienie, skały, kłody\n"
                L"-Obiekły płaskie - niekolizyjne obiekty takie jak ścieżka, kamyczki, płaskie rośliny po których można chodzić\n"
                L"-Potworki - dziobak, wilczur lub goblin\n"
                L"-Przedmioty - przedmioty, które może zbierać gracz\n"
                L"-Małe obiekty - niekolizyjne obiekty np. małe krzaczki, trawa\n"
                L"-Obiekty - palisada, mur, koksownik, studnia\n"
                L"-Budynki - kilka podstawowych budynków\n"
                L"\n"

            L"b) Narzędzia:\n"
                L"-Gdy wybierzemy grupę terenu lub wody aktywuje się panel z narzędziami\n"
                L"-Kursor\n"
                L"-Pędziel\n"
                L"-Kwadratowy pędzel\n"
                L"-Powiększ pędzel\n"
                L"-Pomniejsz pędzel\n"
                L"-Wypełnienie prostokątem (nie zaimplementowano)\n"
                L"-Wypełnienie elipsą (nie zaimplementowano)\n"
                L"-Wypełnij (nie zaimplementowano)\n"
                L"-Gumka (nie zaimplementowano)\n"
                L"\n"

                L"5. Opcje Renderowania\n"
                L"-W menu głównym jest opcja \"Render\". Poprzez wybranie którejś opcji render, można zobaczyć statystyki oraz parametry różnych obiektów znajdujących się na mapie.\n"
                L"-Map Borders - wyświetl granice fragmentów mapy\n"
                L"-Map Coords - wyświetl współrzędne fragmentów mapy\n"
                L"-Tiles Borders - wyświetl granice pomiędzy różnymi rodzajami terenu\n"
                L"-Action Range - wyświetl zasięg akcji potworków\n"
                L"-View Range - wyświetl zasięg widzenia potworków\n"
                L"-Colliders - wyświetl Collidery obiektów\n"
                L"-Meshes - wyświetl siatki mesh obiektów\n"
                L"-Monster Bases - wyświetl punkt celu oraz ścieżkę do niego dla każdego potworka\n"
            ));
            };
        aboutMEBtn = new ButtonWithText("About");

        instructionsBEBtn = new ButtonWithText("Instructions");
        instructionsBEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"1. O programie\n"
                L"-Building Editor jest to program do edycji budynków do gry RPG 2D. W tym programie możesz tworzyć oraz edytować budynki, dodawać oraz usuwać różne obiekty takie jak ściany, podłogi, różne itemy oraz meble. Program jest intuicyjny oraz prosty w obsłudze.\n"
                L"\n"

                L"2. Sterowanie\n"
                L"a) Program obsługuje zarówno klawiaturę jak i mysz\n"
                L"b) Sterowanie\n"
                L"-LPM - zaznacz, wybierz lub dodaj obiekt\n"
                L"-PPM - odznacz, anuluj lub usuń\n"
                L"-WASD lub strzałki - przesuwanie mapy świata\n"
                L"-F5 - zapisz budynek\n"
                L"-F6 - wczytaj budynek\n"
                L"\n"

                L"3. Paleta\n"
                L"-W programie paleta służy do wybierania prefabrykatów lub narzędzi\n"
                L"a) Grupy Obiektów:\n"
                L"-Podłoga - wybór rodzaju podłogi np. parkiet, kamienne płytki, ceglana podłoga\n"
                L"-Ściany - różne rodzaje ścian\n"
                L"-Meble - różne meble np. stół, kufer, łóżko\n"
                L"-Przedmioty - przedmioty, które może zbierać gracz\n"

                L"b) Narzędzia:\n"
                L"-Gdy wybierzemy grupę terenu lub wody aktywuje się panel z narzędziami\n"
                L"-Kursor\n"
                L"-Pędziel\n"
                L"-Kwadratowy pędzel\n"
                L"-Powiększ pędzel\n"
                L"-Pomniejsz pędzel\n"
                L"-Wypełnienie prostokątem (nie zaimplementowano)\n"
                L"-Wypełnienie elipsą (nie zaimplementowano)\n"
                L"-Wypełnij (nie zaimplementowano)\n"
                L"-Gumka (nie zaimplementowano)\n"
                L"\n"

                L"5. Opcje Renderowania\n"
                L"-W menu głównym jest opcja \"Render\". Poprzez wybranie którejś opcji render, można zobaczyć statystyki oraz parametry różnych obiektów znajdujących się na mapie.\n"
                L"-Colliders - wyświetl Collidery obiektów\n"
            ));
            };

        aboutMEBtn = new ButtonWithText("About");
        aboutMEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"Program Editor RPG2D został zaprojektowany i zaprogramowany przez tBane.\n"
                L"Wersja 0.5\n"
                L"© 2025\n"
            ));
            };

        aboutBEBtn = new ButtonWithText("About");
        aboutBEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };



        settingsMEBtn = new ButtonWithText("Settings");
        settingsMEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };

        settingsBEBtn = new ButtonWithText("Settings");
        settingsBEBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
        };

    }


    void createMenu() {
        if (type == MenuBarType::MapEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(viewBtn);
            menu.push_back(toolsBtn);
            menu.push_back(helpBtn);

            // positioning buttons of menu
            sf::Vector2f position;
            position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x;
            position.y = -screenHeight / 2;

            for (auto& btn : menu) {
                btn->setPosition(position);
                position.x += btn->rect.getLocalBounds().width;
            }

            menu[0]->addOption(newWorldBtn);
            menu[0]->addOption(loadWorldBtn);
            menu[0]->addOption(saveWorldBtn);

            menu[1]->addOption(show_bordersBtn);
            menu[1]->addOption(show_coordsBtn);
            menu[1]->addOption(show_tilesBordersBtn);
            menu[1]->addOption(show_actionRangeBtn);
            menu[1]->addOption(show_viewRangeBtn);
            menu[1]->addOption(show_collidersBtn);
            menu[1]->addOption(show_meshesBtn);
            menu[1]->addOption(show_monsterBasesBtn);
            menu[1]->addOption(show_buildingsOutsidesBtn);

            menu[2]->addOption(show_paletteBtn);

            menu[3]->addOption(instructionsMEBtn);
            menu[3]->addOption(aboutMEBtn);
            menu[3]->addOption(settingsMEBtn);
        }
        else if (type == MenuBarType::BuildingEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(viewBtn);
            menu.push_back(toolsBtn);
            menu.push_back(helpBtn);

            // positioning buttons of menu
            sf::Vector2f position;
            position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x;
            position.y = -screenHeight / 2;

            for (auto& btn : menu) {
                btn->setPosition(position);
                position.x += btn->rect.getLocalBounds().width;
            }

            menu[0]->addOption(closeBEBtn);

            menu[1]->addOption(show_collidersBtn);

            menu[2]->addOption(show_paletteBtn);

            menu[3]->addOption(instructionsBEBtn);
            menu[3]->addOption(aboutBEBtn);
            menu[3]->addOption(settingsBEBtn);
        }
        else if (type == MenuBarType::MeshEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(toolsBtn);
            menu.push_back(helpBtn);

            // positioning buttons of menu
            sf::Vector2f position;
            position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x;
            position.y = -screenHeight / 2;

            for (auto& btn : menu) {
                btn->setPosition(position);
                position.x += btn->rect.getLocalBounds().width;
            }

            menu[0]->addOption(closeMEBtn);

            //menu[1]->addOption(show_gridBtn);

            menu[2]->addOption(instructionsMEBtn);
            menu[2]->addOption(aboutMEBtn);
            menu[2]->addOption(settingsMEBtn);
        }   
    }

    sf::Vector2f getSize() {
        return bar.getSize();
    }

    bool bar_is_hover() {
        float left = bar.getGlobalBounds().left;
        float right = left + bar.getGlobalBounds().width;
        float top = bar.getGlobalBounds().top;
        float bottom = top + bar.getGlobalBounds().height;
        if (worldMousePosition.x > left && worldMousePosition.x < right && worldMousePosition.y > top && worldMousePosition.y < bottom)
            return true;
        else
            return false;
    }

    void cursorHover() {
        if (dialogs.empty()) {
            for (auto& m : menu)
                m->cursorHover();

            if (clickedMenuButton) {
                for (auto& o : clickedMenuButton->options)
                    o->cursorHover();
            }
        }
        

    }

    void handleEvent(sf::Event& event) {

        bool clicked_in_menu = false;
        // ElementGUI_pressed - kliknięty Element GUI
        for (auto& m : menu) {
            m->handleEvent(event);
            if (ElementGUI_pressed == m) {
                clicked_in_menu = true;
                state = MenuBarStates::Open;
            }
        }       

        if (clickedMenuButton) {
            for (auto& o : clickedMenuButton->options) {
                o->handleEvent(event);
                if (ElementGUI_pressed == o) {
                    clicked_in_menu = true;
                    state = MenuBarStates::Open;
                }
            }
        }

        if (clicked_in_menu == false) {
            state = MenuBarStates::Closing;
        }

    }

    void update() {

        bar.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);
        logo.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);

        bool hover_action = !GUIwasOpen;

        if (bar_is_hover())
            GUIwasHover = true;

        for (auto& m : menu)
            m->update();

        bool to_close = true;

        for (auto& btn : menu) {
            for (auto& option : btn->options) {
                option->update();
            }
        }

        if (state == MenuBarStates::Open) {
            if (clickedMenuButton) {
                for (auto& o : clickedMenuButton->options) {
                    if (o->state == ButtonState::Pressed) {
                        to_close = false;
                        state = MenuBarStates::Open;
                    }

                }
            }
        }

        if (state == MenuBarStates::Closing) {
            if (to_close) {
                if (clickedMenuButton != nullptr) {
                    clickedMenuButton->isOpen = false;
                    clickedMenuButton = nullptr;
                }

                state = MenuBarStates::Close;
            }
        }

    }

    void draw() {

        window->draw(bar);
        window->draw(logo);

        for (auto& m : menu)
            m->draw();
        
        if (state == MenuBarStates::Open) {
            if (clickedMenuButton) {
                for (auto& o : clickedMenuButton->options)
                    o->draw();
            }
        }
    }
};

MenuBar* menu_bar = nullptr;

#endif