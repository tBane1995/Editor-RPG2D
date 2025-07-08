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
        if(checkbox != nullptr)
            delete checkbox;
    }

    void update(bool hover_action = true) {
        ButtonWithText::update(hover_action);

        if (checkbox)
            checkbox->update();
    }

    void draw() {
        ButtonWithText::draw();
        if(checkbox != nullptr)
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
    MenuButton* renderBtn;
    MenuButton* toolsBtn;
    MenuButton* helpBtn;

    // WE - WORLD EDITOR /////////////////////////////////////////////////////////////
    // FILE
    ButtonWithText* WE_newWorldBtn;                        
    ButtonWithText* WE_loadWorldBtn;                       
    ButtonWithText* WE_saveWorldBtn;                       

    // RENDER
    OptionButton* WE_show_bordersBtn;
    OptionButton* WE_show_coordsBtn;
    OptionButton* WE_show_tilesBordersBtn;
    OptionButton* WE_show_actionRangeBtn;
    OptionButton* WE_show_viewRangeBtn;
    OptionButton* WE_show_collidersBtn;
    OptionButton* WE_show_meshesBtn;
    OptionButton* WE_show_monsterBasesBtn;
    OptionButton* WE_show_buildingsOutsidesBtn;

    // TOOLS
    OptionButton* WE_show_paletteBtn;
    
    // HELP
    ButtonWithText* WE_settingsBtn;
    ButtonWithText* WE_instructionsBtn;
    ButtonWithText* WE_aboutBtn;

    // BE - Building Editor ///////////////////////////////////////////////////////////////////////////////////
    // FILE
    ButtonWithText* BE_closeBtn; 

    // RENDER
    OptionButton* BE_show_collidersBtn;
    OptionButton* BE_show_gridBtn;
    OptionButton* BE_show_buildingsOutsidesBtn;

    // TOOLS
    OptionButton* BE_show_paletteBtn;

    // HELP
    ButtonWithText* BE_settingsBtn;
    ButtonWithText* BE_instructionsBtn;
    ButtonWithText* BE_aboutBtn;

    // ME - Mesh Editor ////////////////////////////////////////////////////////////////////////////////////////////
    // FILE
    ButtonWithText* ME_closeBtn; 

    // RENDER
    OptionButton* ME_show_gridBtn;

    // HELP
    ButtonWithText* ME_settingsBtn;
    ButtonWithText* ME_instructionsBtn;
    ButtonWithText* ME_aboutBtn;
    

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        renderBtn = new MenuButton("RENDER");
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

        /////////////////////////////////////////////////////////////////////////////////////////////
        // WORLD EDITOR

        WE_newWorldBtn = new ButtonWithText("New Map");
        WE_newWorldBtn->onclick_func = [this]() {
            mapa = new Mapa();
            };

        WE_loadWorldBtn = new ButtonWithText("Load Map");
        WE_loadWorldBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Map", ".wrd"));
            };

        WE_saveWorldBtn = new ButtonWithText("Save Map");
        WE_saveWorldBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new FileDialog(DialogType::SaveFile, L"Save Map", ".wrd"));
            };

        WE_show_bordersBtn = new OptionButton("Map Borders");
        WE_show_bordersBtn->checkbox = new CheckBox();
        WE_show_bordersBtn->checkbox->value = renderer->WE_renderBorders;
        WE_show_bordersBtn->onclick_func = [this]() {
            (renderer->WE_renderBorders) ? renderer->WE_renderBorders = false : renderer->WE_renderBorders = true;
            WE_show_bordersBtn->checkbox->value = renderer->WE_renderBorders;
            };

        WE_show_coordsBtn = new OptionButton("Map Coords");
        WE_show_coordsBtn->checkbox = new CheckBox();
        WE_show_coordsBtn->checkbox->value = renderer->WE_renderCoords;
        WE_show_coordsBtn->onclick_func = [this]() {
            (renderer->WE_renderCoords) ? renderer->WE_renderCoords = false : renderer->WE_renderCoords = true;
            WE_show_coordsBtn->checkbox->value = renderer->WE_renderCoords;
            };

        WE_show_tilesBordersBtn = new OptionButton("Tiles Borders");
        WE_show_tilesBordersBtn->checkbox = new CheckBox();
        WE_show_tilesBordersBtn->checkbox->value = renderer->WE_renderTilesBorders;
        WE_show_tilesBordersBtn->onclick_func = [this]() {
            (renderer->WE_renderTilesBorders) ? renderer->WE_renderTilesBorders = false : renderer->WE_renderTilesBorders = true;
            WE_show_tilesBordersBtn->checkbox->value = renderer->WE_renderTilesBorders;
            };

        WE_show_actionRangeBtn = new OptionButton("Action Range");
        WE_show_actionRangeBtn->checkbox = new CheckBox();
        WE_show_actionRangeBtn->checkbox->value = renderer->WE_renderActionRange;
        WE_show_actionRangeBtn->onclick_func = [this]() {
            (renderer->WE_renderActionRange) ? renderer->WE_renderActionRange = false : renderer->WE_renderActionRange = true;
            WE_show_actionRangeBtn->checkbox->value = renderer->WE_renderActionRange;
            };

        WE_show_viewRangeBtn = new OptionButton("View Range");
        WE_show_viewRangeBtn->checkbox = new CheckBox();
        WE_show_viewRangeBtn->checkbox->value = renderer->WE_renderViewRange;
        WE_show_viewRangeBtn->onclick_func = [this]() {
            (renderer->WE_renderViewRange) ? renderer->WE_renderViewRange = false : renderer->WE_renderViewRange = true;
            WE_show_viewRangeBtn->checkbox->value = renderer->WE_renderViewRange;
            };

        WE_show_collidersBtn = new OptionButton("Colliders");
        WE_show_collidersBtn->checkbox = new CheckBox();
        WE_show_collidersBtn->checkbox->value = renderer->WE_renderColliders;
        WE_show_collidersBtn->onclick_func = [this]() {
            (renderer->WE_renderColliders) ? renderer->WE_renderColliders = false : renderer->WE_renderColliders = true;
            WE_show_collidersBtn->checkbox->value = renderer->WE_renderColliders;
            };

        WE_show_meshesBtn = new OptionButton("Meshes");
        WE_show_meshesBtn->checkbox = new CheckBox();
        WE_show_meshesBtn->checkbox->value = renderer->WE_renderMeshes;
        WE_show_meshesBtn->onclick_func = [this]() {
            (renderer->WE_renderMeshes) ? renderer->WE_renderMeshes = false : renderer->WE_renderMeshes = true;
            WE_show_meshesBtn->checkbox->value = renderer->WE_renderMeshes;
            };

        WE_show_monsterBasesBtn = new OptionButton("Monsters Bases");
        WE_show_monsterBasesBtn->checkbox = new CheckBox();
        WE_show_monsterBasesBtn->checkbox->value = renderer->WE_renderMonsterBases;
        WE_show_monsterBasesBtn->onclick_func = [this]() {
            (renderer->WE_renderMonsterBases) ? renderer->WE_renderMonsterBases = false : renderer->WE_renderMonsterBases = true;
            WE_show_monsterBasesBtn->checkbox->value = renderer->WE_renderMonsterBases;
            };

        WE_show_buildingsOutsidesBtn = new OptionButton("Buildings Outsides");
        WE_show_buildingsOutsidesBtn->checkbox = new CheckBox();
        WE_show_buildingsOutsidesBtn->checkbox->value = renderer->WE_renderBuildingsOutside;
        WE_show_buildingsOutsidesBtn->onclick_func = [this]() {
            (renderer->WE_renderBuildingsOutside) ? renderer->WE_renderBuildingsOutside = false : renderer->WE_renderBuildingsOutside = true;
            WE_show_buildingsOutsidesBtn->checkbox->value = renderer->WE_renderBuildingsOutside;
            };

        WE_show_paletteBtn = new OptionButton("Show Palette");
        WE_show_paletteBtn->checkbox = new CheckBox();
        WE_show_paletteBtn->checkbox->value = true;
        WE_show_paletteBtn->onclick_func = [this]() {

            if (palette->state == PaletteStates::Open) {
                palette->close();
                WE_show_paletteBtn->checkbox->value = false;

            }else if(palette->state == PaletteStates::Close) {
                palette->open();
                WE_show_paletteBtn->checkbox->value = true;
            }
            };

        WE_settingsBtn = new ButtonWithText("Settings");
        WE_settingsBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };

        WE_instructionsBtn = new ButtonWithText("Instructions");
        WE_instructionsBtn->onclick_func = [this]() {
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

        WE_aboutBtn = new ButtonWithText("About");
        WE_aboutBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"Program Editor RPG2D został zaprojektowany i zaprogramowany przez tBane.\n"
                L"Wersja 0.5\n"
                L"© 2025\n"
            ));
            };


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // BUILDING EDITOR

        // FILE
        BE_closeBtn = new ButtonWithText("Close Building Editor");
        BE_closeBtn->onclick_func = [this]() {
            editor_state = EditorStates::MapEditorInit;
            };


        // RENDER
        BE_show_collidersBtn = new OptionButton("Colliders");
        BE_show_collidersBtn->checkbox = new CheckBox();
        BE_show_collidersBtn->checkbox->value = renderer->BE_renderColliders;
        BE_show_collidersBtn->onclick_func = [this]() {
            (renderer->BE_renderColliders) ? renderer->BE_renderColliders = false : renderer->BE_renderColliders = true;
            BE_show_collidersBtn->checkbox->value = renderer->BE_renderColliders;
            };

        BE_show_gridBtn = new OptionButton("Show Grid");
        BE_show_gridBtn->checkbox = new CheckBox();
        BE_show_gridBtn->checkbox->value = false;
        BE_show_gridBtn->onclick_func = [this]() {

            (BE_show_gridBtn->checkbox->value == true) ? BE_show_gridBtn->checkbox->value = false : BE_show_gridBtn->checkbox->value = true;
            };

        BE_show_buildingsOutsidesBtn = new OptionButton("Buildings Outsides");
        BE_show_buildingsOutsidesBtn->checkbox = new CheckBox();
        BE_show_buildingsOutsidesBtn->checkbox->value = renderer->WE_renderBuildingsOutside;
        BE_show_buildingsOutsidesBtn->onclick_func = [this]() {
            (renderer->BE_renderBuildingsOutside) ? renderer->BE_renderBuildingsOutside = false : renderer->BE_renderBuildingsOutside = true;
            BE_show_buildingsOutsidesBtn->checkbox->value = renderer->BE_renderBuildingsOutside;
            };
        
        // TOOLS
        BE_show_paletteBtn = new OptionButton("Show Palette");
        BE_show_paletteBtn->checkbox = new CheckBox();
        BE_show_paletteBtn->checkbox->value = true;
        BE_show_paletteBtn->onclick_func = [this]() {

            if (palette->state == PaletteStates::Open) {
                palette->close();
                BE_show_paletteBtn->checkbox->value = false;

            }
            else if (palette->state == PaletteStates::Close) {
                palette->open();
                BE_show_paletteBtn->checkbox->value = true;
            }
            };

        // HELP
        BE_settingsBtn = new ButtonWithText("Settings");
        BE_settingsBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };

        BE_instructionsBtn = new ButtonWithText("Instructions");
        BE_instructionsBtn->onclick_func = [this]() {
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

        

        BE_aboutBtn = new ButtonWithText("About");
        BE_aboutBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"Program Editor RPG2D został zaprojektowany i zaprogramowany przez tBane.\n"
                L"Wersja 0.5\n"
                L"© 2025\n"
            ));
            };
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // MESH EDITOR

        // FILE
        ME_closeBtn = new ButtonWithText("Close Mesh Editor");
        ME_closeBtn->onclick_func = [this]() {
            editor_state = EditorStates::MapEditorInit;
            };

        // RENDER
        ME_show_gridBtn = new OptionButton("Show Grid");
        ME_show_gridBtn->checkbox = new CheckBox();
        ME_show_gridBtn->checkbox->value = false;
        ME_show_gridBtn->onclick_func = [this]() {

            (ME_show_gridBtn->checkbox->value == true) ? ME_show_gridBtn->checkbox->value = false : ME_show_gridBtn->checkbox->value = true;
            };

        // HELP
        ME_settingsBtn = new ButtonWithText("Settings");
        ME_settingsBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };

        ME_instructionsBtn = new ButtonWithText("Instructions");
        ME_instructionsBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new Panel());
            };

        ME_aboutBtn = new ButtonWithText("About");
        ME_aboutBtn->onclick_func = [this]() {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
            dialogs.push_back(new ScrollableText(
                L"Program Editor RPG2D został zaprojektowany i zaprogramowany przez tBane.\n"
                L"Wersja 0.5\n"
                L"© 2025\n"
            ));
            };
    }


    void createMenu() {
        if (type == MenuBarType::MapEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(renderBtn);
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

            menu[0]->addOption(WE_newWorldBtn);
            menu[0]->addOption(WE_loadWorldBtn);
            menu[0]->addOption(WE_saveWorldBtn);

            menu[1]->addOption(WE_show_bordersBtn);
            menu[1]->addOption(WE_show_coordsBtn);
            menu[1]->addOption(WE_show_tilesBordersBtn);
            menu[1]->addOption(WE_show_actionRangeBtn);
            menu[1]->addOption(WE_show_viewRangeBtn);
            menu[1]->addOption(WE_show_collidersBtn);
            menu[1]->addOption(WE_show_meshesBtn);
            menu[1]->addOption(WE_show_monsterBasesBtn);
            menu[1]->addOption(WE_show_buildingsOutsidesBtn);

            menu[2]->addOption(WE_show_paletteBtn);

            menu[3]->addOption(WE_settingsBtn);
            menu[3]->addOption(WE_instructionsBtn);
            menu[3]->addOption(WE_aboutBtn);
            
        }
        else if (type == MenuBarType::BuildingEditor) {
            menu.clear();
            menu.push_back(fileBtn);
            menu.push_back(renderBtn);
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

            menu[0]->addOption(BE_closeBtn);

            menu[1]->addOption(BE_show_collidersBtn);
            menu[1]->addOption(BE_show_gridBtn);
            menu[1]->addOption(BE_show_buildingsOutsidesBtn);

            menu[2]->addOption(BE_show_paletteBtn);

            menu[3]->addOption(BE_settingsBtn);
            menu[3]->addOption(BE_instructionsBtn);
            menu[3]->addOption(BE_aboutBtn);
            
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

            menu[0]->addOption(ME_closeBtn);

            menu[1]->addOption(ME_show_gridBtn);

            menu[2]->addOption(ME_settingsBtn);
            menu[2]->addOption(ME_instructionsBtn);
            menu[2]->addOption(ME_aboutBtn);
            
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