#ifndef FileDialog_hpp
#define FileDialog_hpp

bool sortkey(std::filesystem::directory_entry first, std::filesystem::directory_entry second) {

    if (first.is_directory() && second.is_directory()) {
        std::string name_1 = first.path().filename().string();
        std::string name_2 = second.path().filename().string();

        std::transform(name_1.begin(), name_1.end(), name_1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), [](unsigned char c) { return std::tolower(c); });

        if (name_1 < name_2)
            return true;
        else
            return false;
    }
    else if (first.is_directory() && !second.is_directory()) {
        return true;
    }
    else if (!first.is_directory() && second.is_directory()) {
        return false;
    }
    else {
        // both are file
        std::string name_1 = first.path().filename().string();
        std::string name_2 = second.path().filename().string();

        std::transform(name_1.begin(), name_1.end(), name_1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), [](unsigned char c) { return std::tolower(c); });

        if (name_1 < name_2)
            return true;
        else
            return false;
    }
}

class FileDialog : public Dialog {
public:

    class Entry : public TextArea, public ElementGUI {
    public:

        ButtonState state;
        std::function<void()> onclick_func;
        sf::Time clickTime;

        sf::RectangleShape rectangle;
        sf::Sprite icon;
        std::filesystem::path path;
        

        Entry(sf::Vector2f size) : TextArea(L"..", sf::Vector2f(0,0), size.x, size, TextAlignment::Left, VerticalAlignment::Center) {

            rectangle = sf::RectangleShape(size+sf::Vector2f(30,0));
            rectangle.setFillColor(panelColor_normal);

            this->setRectColor(sf::Color::Transparent);

            state = ButtonState::Idle;
            clickTime = currentTime;

            this->path = std::filesystem::path();   // empty path
            icon.setTexture(*getSingleTexture(L"GUI\\icons\\empty")->texture);
        }

        ~Entry() {
            
        }

        void setPosition(sf::Vector2f position) {
            rectangle.setPosition(position + cam->position);
            icon.setPosition(position + cam->position);
            TextArea::setPosition(sf::Vector2f(position.x + 30, position.y));
        }

        void setPathfile(std::filesystem::path pathfile, std::wstring pathname = L"") {
            
            this->path = pathfile;
            (pathname == L"") ? setWstring(path.filename().wstring()) : setWstring(pathname);

            if (path != std::filesystem::path()) {
                if (std::filesystem::is_directory(path)) {
                    icon.setTexture(*getSingleTexture(L"GUI\\icons\\dictionary")->texture);
                }
                else {
                    icon.setTexture(*getSingleTexture(L"GUI\\icons\\file")->texture);
                }
            }
            else {
                icon.setTexture(*getSingleTexture(L"GUI\\icons\\empty")->texture);
            }
        }

        void unclick() {
            state = ButtonState::Idle;
            rectangle.setFillColor(panelColor_normal);
            setRectColor(sf::Color::Transparent);
        }

        void hover() {

            state = ButtonState::Hover;
            rectangle.setFillColor(panelColor_medium);
            setRectColor(sf::Color::Transparent);
            GUIwasHover = true;
        }

        void click() {

            state = ButtonState::Pressed;
            rectangle.setFillColor(panelColor_medium);
            setRectColor(sf::Color::Transparent);
            GUIwasClicked = true;
            clickTime = currentTime;
        }

        void cursorHover() {
            if (mouse_state != MouseState::Selecting) {

                if (path != std::filesystem::path()) {
                    if (rect.getGlobalBounds().contains(worldMousePosition)) {

                        ElementGUI_hovered = this;
                    }
                }
            }
        }

        void update(bool hover_action = true) {

            rect.setPosition(position + cam->position);

            if (state == ButtonState::Pressed) {
                if ((currentTime - clickTime).asSeconds() > 0.05f) {
                    if (onclick_func)
                        onclick_func();

                    unclick();
                }

            }
            else if (hover_action && ElementGUI_hovered == this) {
                hover();
            }
            else
                unclick();


        }

        void handleEvent(sf::Event& event) {

            if (rect.getGlobalBounds().contains(worldMousePosition)) {

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    ElementGUI_pressed = this;
                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    if (ElementGUI_pressed == this) {
                        click();
                    }
                }
            }

        }

        void draw() {
            window->draw(rectangle);
            window->draw(icon);
            TextArea::draw();
        }
    };

    sf::Vector2f position = sf::Vector2f(0, 0);

    sf::RectangleShape rect;        // main big panel
    float rect_width;
    float rect_height;
    float margin_vert;
    float margin_hor;
    float line_height;

    // title bar
    sf::RectangleShape titlebar;
    TextArea* titleText;

    // entries 
    sf::RectangleShape entriesRect;
    std::vector < Entry* > entries;

    // submit bar
    sf::RectangleShape submitbar;
    TextArea* filenameInfo;
    EditableTextArea* selectedFilename;

    ButtonWithText* selectButton;
    ButtonWithText* cancelButton;

    std::string acceptable_extensions;

    std::filesystem::path current_path;                     // current path of directory  
    std::vector < std::filesystem::directory_entry > paths; // list of paths

    Scrollbar* scrollbar = nullptr;

    

    FileDialog(DialogType type, std::wstring title, std::string acceptable_extension="") : Dialog(type, sf::Vector2f(512+(dialog_border_width +8)*2, 304+(dialog_border_width +8)*2)) {

        rect_height = 0;
        rect_width = 512;
        margin_vert = 4;
        margin_hor = 4;
        line_height = 30;

        this->acceptable_extensions = acceptable_extension;

        // TITLE BAR
        titlebar = sf::RectangleShape(sf::Vector2f(512, line_height));
        titlebar.setFillColor(panelColor_medium);
        rect_height += titlebar.getSize().y;

        titleText = new TextArea(title);
        titleText->setCharacterSize(17);
        titleText->setTextColor(textColor);
        titleText->setRectColor(sf::Color::Transparent);
        titleText->setRectSize(titlebar.getSize());

        ////////////////////////////////////
        // FILENAMES AND SCROLLBAR
        current_path = std::filesystem::current_path();
        loadDirectory();

        loadScrollbar();
        createFilenamesTexts();
        setFilenamesTexts();

        entriesRect = sf::RectangleShape(sf::Vector2f(titlebar.getSize().x, 7 * line_height));
        entriesRect.setFillColor(sf::Color::Transparent);

        rect_height += entriesRect.getSize().y;

        ///////////////////////////////////////
        // SUBMIT BAR

        filenameInfo = new TextArea(L"File name: ");
        filenameInfo->setCharacterSize(17);
        filenameInfo->setTextColor(textColor);
        filenameInfo->setRectColor(sf::Color::Transparent);
        filenameInfo->setRectSize(sf::Vector2f(0, 0));

        selectedFilename = new EditableTextArea(L"");
        selectedFilename->setCharacterSize(17);
        sf::Vector2f size;
        size.x = rect_width - filenameInfo->getSize().x - 3 * margin_vert;
        size.y = selectedFilename->font.getLineSpacing(selectedFilename->characterSize) * 1.3f;
        selectedFilename->setRectSize(size);
        selectedFilename->setTextColor(textColor);
        selectedFilename->setRectColor(panelColor_dark);

        sf::Vector2f btn_size = sf::Vector2f(64, -1);
        if(type == DialogType::OpenFile){
            selectButton = new ButtonWithText("open", 17, TextAlignment::Center, btn_size);
            selectButton->onclick_func = [this]() {
                state = DialogState::Close;
                    mapa->load(getPathfile());
                };
        }
        else if(type == DialogType::SaveFile) {
            selectButton = new ButtonWithText("save", 17, TextAlignment::Center, btn_size);
            selectButton->onclick_func = [this]() {
                state = DialogState::Close;

                std::wstring filename = getShortName(getPathfile());
                Confirm* confirm = new Confirm(L"Plik " + filename + L" już istnieje. Czy chcesz go zamienić?");
                confirm->btn_yes->onclick_func = [this]() {
                    mapa->save(getPathfile());
                    delete dialogs.back();
                    dialogs.pop_back();
                    };
                dialogs.push_back(confirm);
                
                };
        }

        cancelButton = new ButtonWithText("cancel", 17, TextAlignment::Center, btn_size);
        cancelButton->onclick_func = [this]() {
            state = DialogState::Close;
            };

        submitbar = sf::RectangleShape(sf::Vector2f(rect_width, selectedFilename->getSize().y + 3 * margin_vert + selectButton->getSize().y));
        submitbar.setFillColor(panelColor_medium);

        rect_height += submitbar.getSize().y;
        
        // POSITIONING /////////////
        sf::Vector2f pos;

        // title bar
        sf::Vector2f p = sf::Vector2f(position.x - rect_width / 2.0f, + position.y - rect_height / 2.0f);
        //rect.setPosition(p.x + cam->position.x + borderWidth, p.y + cam->position.y + borderWidth);

        titlebar.setPosition(p.x + cam->position.x, p.y + cam->position.y);
        titleText->setPosition(sf::Vector2f(p.x + margin_hor, p.y + margin_vert));

        // filenames
        pos.x = cam->position.x + position.x - rect_width / 2.0f;
        pos.y = cam->position.y + position.y - rect_height / 2.0f + titlebar.getSize().y;
        entriesRect.setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + (titleText->texts[0].getPosition().x - titleText->rect.getPosition().x);
        for (short i = 0; i < 7; i++) {

            pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + i * line_height;
            entries[i]->setPosition(pos);

        }

        // scrollbar
        pos.x = position.x + rect_width / 2.0f - scrollbar->size.x;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y;
        scrollbar->setPosition(pos);

        // submit bar
        pos.x = position.x - rect_width / 2.0f + cam->position.x;
        pos.y = position.y - rect_height / 2.0f + cam->position.y + titlebar.getSize().y + 7 * entries[0]->getSize().y;
        submitbar.setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + margin_vert;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * entries[0]->getSize().y + margin_vert;
        filenameInfo->setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + filenameInfo->getSize().x + 2.0f * margin_hor;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * entries[0]->getSize().y + margin_vert;

        selectedFilename->setPosition(pos);

        pos.x = position.x + rect_width / 2.0f - cancelButton->getSize().x - margin_hor;
        pos.y = position.y + rect_height / 2.0f - cancelButton->getSize().y - margin_vert;
        cancelButton->setPosition(pos);

        pos.x = position.x + rect_width / 2.0f - cancelButton->getSize().x - margin_hor - selectButton->getSize().x - margin_hor;
        pos.y = position.y + rect_height / 2.0f - cancelButton->getSize().y - margin_vert;
        selectButton->setPosition(pos);

        scrollbar->setScrollAreaSize(entriesRect.getSize());
        scrollbar->setScrollAreaPosition(entriesRect.getPosition() - cam->position);
    }


    ~FileDialog() {
        delete titleText;
        delete filenameInfo;
        delete selectedFilename;
        delete selectButton;
        delete cancelButton;

        for (auto& entry : entries)
            delete entry;

        delete scrollbar;
    }

    void loadDirectory() {
        paths.clear();
        if (std::filesystem::exists(current_path) && std::filesystem::is_directory(current_path)) {

            if (acceptable_extensions != "") {

                for (auto& entry : std::filesystem::directory_iterator(current_path)) {
                    if (entry.is_directory()) {
                        paths.push_back(entry);
                    }
                    else {
                        std::string extension = entry.path().extension().string();
                        std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });

                        //std::cout << extension << "\n";

                        if (extension == acceptable_extensions) {
                            paths.push_back(entry);
                        }
                    }

                }

            }
            else {
                for (auto& entry : std::filesystem::directory_iterator(current_path)) {
                    //std::cout << entry.path().filename().string() << "\n";
                    paths.push_back(entry);
                }
                    
            }
        }
        std::sort(paths.begin(), paths.end(), sortkey);
        /*
        for (auto& p : paths)
            std::cout << p.path().filename() << "\n";
        */
        paths.emplace(paths.begin(), current_path.parent_path());
    }

    void loadScrollbar() {

        sf::Vector2f scrollbarSize = sf::Vector2f(16, 7 * line_height);
        sf::Vector2f scrollbarPos;
        scrollbarPos.x = position.x + (rect_width) / 2.0f - scrollbarSize.x;
        scrollbarPos.y = position.y - (rect_height) / 2.0f + titlebar.getSize().y;
        if (scrollbar != nullptr)
            delete scrollbar;
        scrollbar = new Scrollbar(scrollbarSize, scrollbarPos, 0, paths.size() - 1, 0, 1, 7);
        scrollbar->onclick_func = [this]() {
            setFilenamesTexts();
            };
    }

    void createFilenamesTexts() {

        float filename_rect_width = rect_width - scrollbar->size.x - 30 - 2 * margin_vert;

        for (int i = 0; i < 7; i++) {
            entries.push_back(new Entry(sf::Vector2f(filename_rect_width, line_height)));
        }

    }

    void setFilenamesTexts() {

        //std::cout << "scrollVal: " << scrollbar->scroll_value << "\n";

        for (short i = 0; i < 7; i++) {

            if (short(scrollbar->scroll_value) + i < paths.size()) {
                if (short(scrollbar->scroll_value) + i == 0) {
                    entries[i]->setPathfile(current_path.parent_path(), L"..");
                }
                else {
                    entries[i]->setPathfile(paths[short(scrollbar->scroll_value) + i].path());
                }

                entries[i]->onclick_func = [this, i]() {
                    
                    if (std::filesystem::exists(entries[i]->path)) {
                        if (std::filesystem::is_directory(entries[i]->path)) {
                            current_path = entries[i]->path;
                            selectedFilename->setWstring(L"");
                            loadDirectory();
                            loadScrollbar();
                            setFilenamesTexts();
                        }
                        else {
                            selectedFilename->setWstring(entries[i]->path.filename().wstring());
                        }
                    }
                    };
            }
            else {
                entries[i]->setPathfile(std::filesystem::path());
            }


        
        }

       
    }

    std::wstring getPathfile() {
        std::wstring pathfile = current_path.wstring() + L"\\" + ConvertUtf8ToWide(selectedFilename->texts[0].getString());
        //std::wcout << pathfile << "\n";
        return pathfile;
    }

    void cursorHover() {
        // TO-DO
        selectButton->cursorHover();
        cancelButton->cursorHover();

        for (auto& entry : entries)
            entry->cursorHover();

    }

    void handleEvent(sf::Event& event) {

        scrollbar->handleEvent(event);

        selectedFilename->handleEvent(event);

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                selectButton->state = ButtonState::Pressed;
                state = DialogState::Close;
            }
        }
        else {

            for (auto& entry : entries)
                entry->handleEvent(event);

            selectButton->handleEvent(event);
            cancelButton->handleEvent(event);

        }
    }

    virtual void update() {

        GUIwasOpen = true;
        for (auto& entry : entries)
            entry->update();

        selectButton->update();
        cancelButton->update();
        scrollbar->update();
        selectedFilename->update();
    }

    

    void draw() {
        Dialog::draw();

        // tile bar
        window->draw(titlebar);
        titleText->draw();

        // filenames and scrollbar
        window->draw(entriesRect);

        for (auto& entry : entries)
            entry->draw();

        

        // submit bar
        window->draw(submitbar);

        filenameInfo->draw();
        selectedFilename->draw();
        selectButton->draw();
        cancelButton->draw();

        scrollbar->draw();
    }
};

#endif