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

enum class FileDialogState { Idle, Canceled, FileSelected };

class FileDialog : public Dialog {
public:
    sf::Vector2f position = sf::Vector2f(0, 0);

    FileDialogState state;

    sf::RectangleShape rect;        // main big panel
    float rect_width;
    float rect_height;
    float margin_vert;
    float margin_hor;
    float line_height;

    // title bar
    sf::RectangleShape titlebar;
    TextArea* titleText;

    // filenames 
    sf::RectangleShape filenamesRect;
    sf::Sprite icons[7];
    TextArea* filenames[7];

    // submit bar
    sf::RectangleShape submitbar;
    TextArea* filenameInfo;
    EditableTextArea* selectedFilename;

    ButtonFromDialog* selectButton;
    ButtonFromDialog* cancelButton;

    std::string acceptable_extensions;

    std::filesystem::path current_path;                     // current path of directory  
    std::vector < std::filesystem::directory_entry > paths; // list of paths

    Scrollbar* scrollbar = nullptr;

    

    FileDialog(DialogType type, std::wstring title, std::string acceptable_extension="") : Dialog(type, sf::Vector2f(512+(dialog_border_width +8)*2, 304+(dialog_border_width +8)*2)) {

        state = FileDialogState::Idle;

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
        titleText->setBackgroundColor(sf::Color::Transparent);
        titleText->setRectColor(sf::Color::Transparent);
        titleText->setRectSize(titlebar.getSize());

        ////////////////////////////////////
        // FILENAMES AND SCROLLBAR
        current_path = std::filesystem::current_path();
        loadDirectory();

        loadScrollbar();
        createFilenamesTexts();
        setFilenamesTexts();

        filenamesRect = sf::RectangleShape(sf::Vector2f(titlebar.getSize().x, 7 * line_height));
        filenamesRect.setFillColor(sf::Color::Transparent);

        rect_height += filenamesRect.getSize().y;

        ///////////////////////////////////////
        // SUBMIT BAR

        filenameInfo = new TextArea(L"File name: ");
        filenameInfo->setCharacterSize(17);
        filenameInfo->setTextColor(textColor);
        filenameInfo->setBackgroundColor(sf::Color::Transparent);
        filenameInfo->setRectColor(sf::Color::Transparent);
        filenameInfo->generateRect();

        selectedFilename = new EditableTextArea(L"");
        selectedFilename->setCharacterSize(17);
        sf::Vector2f size;
        size.x = rect_width - filenameInfo->getSize().x - 3 * margin_vert;
        size.y = selectedFilename->getLineHeight();
        selectedFilename->setRectSize(size);
        selectedFilename->setTextColor(textColor);
        selectedFilename->setBackgroundColor(sf::Color::Transparent);
        selectedFilename->setRectColor(panelColor_dark);

        selectButton = (type == DialogType::OpenFile) ? new ButtonFromDialog("open") : new ButtonFromDialog("save");
        cancelButton = new ButtonFromDialog("cancel");

        submitbar = sf::RectangleShape(sf::Vector2f(rect_width, selectedFilename->getSize().y + 3 * margin_vert + selectButton->getSize().y));
        submitbar.setFillColor(panelColor_medium);

        rect_height += submitbar.getSize().y;
        
        cout << "rect hgh : " << rect_height << "\n";

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
        filenamesRect.setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + (titleText->texts[0].getPosition().x - titleText->background.getPosition().x);
        for (short i = 0; i < 7; i++) {

            pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + i * line_height;

            icons[i].setPosition(pos.x + cam->position.x, pos.y + cam->position.y);
            filenames[i]->setPosition(sf::Vector2f(pos.x + 30, pos.y + line_height / 8.0f));
        }

        // scrollbar
        pos.x = position.x + rect_width / 2.0f - scrollbar->size.x;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y;
        scrollbar->setPosition(pos);

        // submit bar
        pos.x = position.x - rect_width / 2.0f + cam->position.x;
        pos.y = position.y - rect_height / 2.0f + cam->position.y + titlebar.getSize().y + 7 * filenames[0]->getSize().y;
        submitbar.setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + margin_vert;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * filenames[0]->getSize().y + margin_vert;
        filenameInfo->setPosition(pos);

        pos.x = position.x - rect_width / 2.0f + filenameInfo->getSize().x + 2.0f * margin_hor;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * filenames[0]->getSize().y + margin_vert;

        selectedFilename->setPosition(pos);

        pos.x = position.x + rect_width / 2.0f - cancelButton->getSize().x/2 - margin_hor;
        pos.y = position.y + rect_height / 2.0f - cancelButton->getSize().y/2 - margin_vert;
        cancelButton->setPosition(pos);

        pos.x = position.x + rect_width / 2.0f - cancelButton->getSize().x - margin_hor - selectButton->getSize().x/2 - margin_hor;
        selectButton->setPosition(pos);

        std::cout << "hgh: " << rect_height << "\n";
    }

    ~FileDialog() {
        delete titleText;
        delete filenameInfo;
        delete selectedFilename;
        delete selectButton;
        delete cancelButton;

        for (auto& t : filenames)
            delete t;

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
        scrollbar = new Scrollbar(scrollbarSize, scrollbarPos, 0, paths.size() - 1, 0, 7);

    }

    void createFilenamesTexts() {

        float filename_rect_width = rect_width - scrollbar->size.x - 30 - 2 * margin_vert;

        for (int i = 0; i < 7; i++) {

            filenames[i] = new TextArea(L"");
            filenames[i]->setCharacterSize(17);
            filenames[i]->setRectSize(sf::Vector2f(filename_rect_width, line_height));
            filenames[i]->setTextColor(textColor);
            filenames[i]->setBackgroundColor(sf::Color::Transparent);
            filenames[i]->setRectColor(sf::Color::Transparent);

            icons[i] = sf::Sprite();
        }

    }

    void setFilenamesTexts() {

        //std::cout << "scrollVal: " << scrollbar->scroll_value << "\n";

        for (short i = 0; i < 7; i++) {

            if (short(scrollbar->scroll_value) + i < paths.size()) {
                if (short(scrollbar->scroll_value) + i == 0) {
                    filenames[i]->setWstring(L"..");
                }
                else {
                    filenames[i]->setWstring(paths[+short(scrollbar->scroll_value) + i].path().filename().wstring());
                }

                std::string extension = paths[short(scrollbar->scroll_value) + i].path().extension().string();
                if (paths[i + short(scrollbar->scroll_value)].is_directory()) {
                    icons[i].setTexture(*getSingleTexture("GUI\\icons\\dictionary")->texture);
                } else {
                    icons[i].setTexture(*getSingleTexture("GUI\\icons\\file")->texture);
                }
            }
            else {
                filenames[i]->setWstring(L"");
                icons[i].setTexture(*getSingleTexture("GUI\\icons\\empty")->texture);
            }
        
        }

       
    }

    std::wstring getPathfile() {
        std::wstring pathfile = current_path.wstring() + L"\\" + ConvertUtf8ToWide(selectedFilename->texts[0].getString());
        //std::wcout << pathfile << "\n";
        return pathfile;
    }

    void handleEvent(sf::Event& event) {
        scrollbar->handleEvent(event);
        selectedFilename->handleEvent(event);

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                selectButton->state = ButtonState::Pressed;
                state = FileDialogState::FileSelected;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {

                selectButton->handleEvent(event);
                cancelButton->handleEvent(event);

                if (selectButton->state == ButtonState::Pressed) {
                    state = FileDialogState::FileSelected;
                }
                else if (cancelButton->state == ButtonState::Pressed) {
                    state = FileDialogState::Canceled;
                }
                else {
                    for (short i = 0; i < 7; i++) {
                        if (filenames[i]->background.getGlobalBounds().contains(worldMousePosition)) {

                            // LOAD THE DIRECTORY
                            if (i + short(scrollbar->scroll_value) < paths.size()) {

                                if (!paths[i + short(scrollbar->scroll_value)].is_directory()) {
                                    std::cout << "is file";
                                    selectedFilename->setWstring(filenames[i]->lines[0]);
                                }
                                else {
                                    current_path = std::filesystem::path(paths[i + short(scrollbar->scroll_value)].path().wstring());
                                    selectedFilename->setWstring(L"");
                                    loadDirectory();
                                    loadScrollbar();

                                }

                            }

                        }
                    }
                }
            }
        }

        setFilenamesTexts();

    }

    virtual void update() {

        GUIwasOpen = true;
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
        window->draw(filenamesRect);
        for (short i = 0; i < 7; i++) {
            filenames[i]->draw();
            window->draw(icons[i]);
        }

        scrollbar->draw();

        // submit bar
        window->draw(submitbar);

        filenameInfo->draw();
        selectedFilename->draw();
        selectButton->draw();
        cancelButton->draw();
    }
};

#endif