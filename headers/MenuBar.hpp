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

enum class MenuBarType { MapEditor, BuildingEditor };

class MenuBar {
public:

    MenuBarType type;

    sf::Sprite logo;
    sf::RectangleShape bar;

    MenuButton* fileBtn;
    MenuButton* renderBtn;
    MenuButton* helpBtn;

    ButtonWithText* newWorldBtn;
    ButtonWithText* loadWorldBtn;
    ButtonWithText* saveWorldBtn;

    ButtonWithText* newBuildingBtn;
    ButtonWithText* loadBuildingBtn;
    ButtonWithText* saveBuildingBtn;
    ButtonWithText* closeBuildingBtn;

    OptionButton* bordersBtn;
    OptionButton* coordsBtn;
    OptionButton* tilesBordersBtn;
    OptionButton* actionRangeBtn;
    OptionButton* viewRangeBtn;
    OptionButton* collidersBtn;
    OptionButton* meshesBtn;
    OptionButton* monsterBasesBtn;

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
        logo.setTexture(*getSingleTexture("GUI/icons/MapEditor_small_ico")->texture);
        logo.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);

        createButtons();
        createMenu();
        clickedMenuButton = nullptr;
    }

    void createButtons() {
        sf::Vector2f position;

        fileBtn = new MenuButton("FILE");
        position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x;
        position.y = -screenHeight / 2;
        fileBtn->setPosition(position);
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

        renderBtn = new MenuButton("RENDER");
        position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x + fileBtn->rect.getLocalBounds().width;
        position.y = -screenHeight / 2;
        renderBtn->setPosition(position);
        renderBtn->onclick_func = [this]() {
            if (clickedMenuButton != nullptr)
                clickedMenuButton->isOpen = false;

            if (!renderBtn->isOpen) {
                renderBtn->isOpen = true;
                clickedMenuButton = renderBtn;
            }
            else
                renderBtn->isOpen = false;
            };

        helpBtn = new MenuButton("HELP");
        position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x + fileBtn->rect.getLocalBounds().width + renderBtn->rect.getLocalBounds().width;
        position.y = -screenHeight / 2;
        helpBtn->setPosition(position);
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
            dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Map", ".map"));
            };

        saveWorldBtn = new ButtonWithText("Save Map");
        saveWorldBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::SaveFile, L"Save Map", ".map"));
            };

        newBuildingBtn = new ButtonWithText("New Building");
        newBuildingBtn->onclick_func = [this]() {
            //createNewBuilding();
            };

        loadBuildingBtn = new ButtonWithText("Load Building");
        loadBuildingBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Building", ".building"));
            };

        saveBuildingBtn = new ButtonWithText("Save Building");
        saveBuildingBtn->onclick_func = [this]() {
            building_to_edit->save();
            };

        closeBuildingBtn = new ButtonWithText("Close Building");
        closeBuildingBtn->onclick_func = [this]() {
            editor_state = EditorStates::MapEditorInit;
            };

        bordersBtn = new OptionButton("Map Borders");
        bordersBtn->checkbox = new CheckBox();
        bordersBtn->checkbox->value = renderBorders;
        bordersBtn->onclick_func = [this]() {
            (renderBorders) ? renderBorders = false : renderBorders = true;
            bordersBtn->checkbox->value = renderBorders;
            };

        coordsBtn = new OptionButton("Map Coords");
        coordsBtn->checkbox = new CheckBox();
        coordsBtn->checkbox->value = renderCoords;
        coordsBtn->onclick_func = [this]() {
            (renderCoords) ? renderCoords = false : renderCoords = true;
            coordsBtn->checkbox->value = renderCoords;
            };

        tilesBordersBtn = new OptionButton("Tiles Borders");
        tilesBordersBtn->checkbox = new CheckBox();
        tilesBordersBtn->checkbox->value = renderTilesBorders;
        tilesBordersBtn->onclick_func = [this]() {
            (renderTilesBorders) ? renderTilesBorders = false : renderTilesBorders = true;
            tilesBordersBtn->checkbox->value = renderTilesBorders;
            };

        actionRangeBtn = new OptionButton("Action Range");
        actionRangeBtn->checkbox = new CheckBox();
        actionRangeBtn->checkbox->value = renderActionRange;
        actionRangeBtn->onclick_func = [this]() {
            (renderActionRange) ? renderActionRange = false : renderActionRange = true;
            actionRangeBtn->checkbox->value = renderActionRange;
            };

        viewRangeBtn = new OptionButton("View Range");
        viewRangeBtn->checkbox = new CheckBox();
        viewRangeBtn->checkbox->value = renderViewRange;
        viewRangeBtn->onclick_func = [this]() {
            (renderViewRange) ? renderViewRange = false : renderViewRange = true;
            viewRangeBtn->checkbox->value = renderViewRange;
            };

        collidersBtn = new OptionButton("Colliders");
        collidersBtn->checkbox = new CheckBox();
        collidersBtn->checkbox->value = renderColliders;
        collidersBtn->onclick_func = [this]() {
            (renderColliders) ? renderColliders = false : renderColliders = true;
            collidersBtn->checkbox->value = renderColliders;
            };

        meshesBtn = new OptionButton("Meshes");
        meshesBtn->checkbox = new CheckBox();
        meshesBtn->checkbox->value = renderMeshes;
        meshesBtn->onclick_func = [this]() {
            (renderMeshes) ? renderMeshes = false : renderMeshes = true;
            meshesBtn->checkbox->value = renderMeshes;
            };

        monsterBasesBtn = new OptionButton("Monsters Bases");
        monsterBasesBtn->checkbox = new CheckBox();
        monsterBasesBtn->checkbox->value = renderMonsterBases;
        monsterBasesBtn->onclick_func = [this]() {
            (renderMonsterBases) ? renderMonsterBases = false : renderMonsterBases = true;
            monsterBasesBtn->checkbox->value = renderMonsterBases;
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
                L"-N - wykonaj zapis mapy do pliku PNG (w głównym folderze z programem tworzy plik \"mapa.png\")\n"
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
            menu.push_back(renderBtn);
            menu.push_back(helpBtn);

            menu[0]->addOption(newWorldBtn);
            menu[0]->addOption(loadWorldBtn);
            menu[0]->addOption(saveWorldBtn);

            menu[1]->addOption(bordersBtn);
            menu[1]->addOption(coordsBtn);
            menu[1]->addOption(tilesBordersBtn);
            menu[1]->addOption(actionRangeBtn);
            menu[1]->addOption(viewRangeBtn);
            menu[1]->addOption(collidersBtn);
            menu[1]->addOption(meshesBtn);
            menu[1]->addOption(monsterBasesBtn);

            menu[2]->addOption(instructionsMEBtn);
            menu[2]->addOption(aboutMEBtn);
            menu[2]->addOption(settingsMEBtn);
        }
        else if (type == MenuBarType::BuildingEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(renderBtn);
            menu.push_back(helpBtn);

            menu[0]->addOption(newBuildingBtn);
            menu[0]->addOption(loadBuildingBtn);
            menu[0]->addOption(saveBuildingBtn);
            menu[0]->addOption(closeBuildingBtn);

            menu[1]->addOption(collidersBtn);

            menu[2]->addOption(instructionsBEBtn);
            menu[2]->addOption(aboutBEBtn);
            menu[2]->addOption(settingsBEBtn);
        }
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

        for (auto& m : menu)
            m->cursorHover();

        if (clickedMenuButton) {
            for (auto& o : clickedMenuButton->options)
                o->cursorHover();
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

        if (state == MenuBarStates::Open) {
            if (clickedMenuButton) {
                for (auto& o : clickedMenuButton->options) {
                    o->update();
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