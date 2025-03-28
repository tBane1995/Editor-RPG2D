#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>

#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <regex>    // for std::smatch
//#include <windows.h>

#include "headers/Window.hpp"
#include "headers/Time.hpp"
#include "headers/Camera.hpp"
#include "headers/Mouse.hpp"
#include "headers/Theme.hpp"

#include "headers/ProgressBar.hpp"

#include "headers/Fonts.hpp"
#include "headers/Textures.hpp"
#include "headers/Shaders.hpp"
#include "headers/Point.hpp"
#include "headers/Collisions.hpp"

#include "headers/GameStates.hpp"           
#include "headers/RenderParameters.hpp"     // bools of the render value for example renderCoords, renderBorders
#include "headers/GUI.hpp"                  // GUIwasHover / GUIwasClicked / GUIwasOpen

#include "headers/EditorStates.hpp"

#include "headers/GameObjects.hpp"
#include "headers/TerrainAndFloors.hpp"     // Terrain and Floors
#include "headers/Water.hpp"
#include "headers/Borders.hpp"
#include "headers/Pathfinding.hpp"

#include "headers/HitTexts.hpp"             // Hit texts
#include "headers/Items.hpp"                // manage of items, itemsOnMap, Inventory and InventoryOnMap
#include "headers/UnitStates.hpp"           // states for Units
#include "headers/Player.hpp"               // manage of Player
#include "headers/Units.hpp"                // manage of Units 
#include "headers/Monsters.hpp"             // manage of Monster (dziobak, kolcorozec, bies, etc.)
#include "headers/Natures.hpp"              // manage of Natures (tree, rock, boulder, etc.)
#include "headers/Objects.hpp"              // manage of Objects (palisade, etc.)
#include "headers/Furnitures.hpp"           // manage of Furnitures (barel, table, chest, etc.)
#include "headers/FlatObjects.hpp"          // manage of Flat Objects (flat plants, flat rocks, etc.)
#include "headers/Walls.hpp"                // manage of Walls 
#include "headers/Doors.hpp"                // manage of Doors
#include "headers/SmallObjects.hpp"         // manage of small objects (grass, etc.)
#include "headers/Dialogues.hpp"            
#include "headers/Character.hpp"            // manage of Characters
#include "headers/Prefabs.hpp"              // manage of all prefabs
#include "headers/BuildingsManager.hpp"     // manage of Buildings
#include "headers/MouseMovedGameObjects.hpp"     // 
#include "headers/GameObjectsManager.hpp"   // manage of GameObjects - update/sort/render/
#include "headers/Map.hpp"
#include "headers/Quests.hpp"

#include "headers/PrefabToPaint.hpp"

#include "headers/TextArea.hpp"
#include "headers/EditableTextArea.hpp"
#include "headers/Buttons.hpp"
#include "headers/Scrollbar.hpp"
#include "headers/Dialog.hpp"
#include "headers/Confirm.hpp"
#include "headers/Panel.hpp"
#include "headers/ScrollableText.hpp"
#include "headers/FileDialog.hpp"
#include "headers/CheckBox.hpp"

#include "headers/Tips.hpp"
#include "headers/MenuBar.hpp"

#include "headers/Palette.hpp"
#include "headers/CharacterInfoPanel.hpp"
#include "headers/Clipboard.hpp"
#include "headers/History.hpp"
#include "headers/ContextMenu.hpp"

#include "headers/Config.hpp"

#include "headers/ControlsPanel.hpp"
#include "headers/InventoryPanel.hpp"
#include "headers/TradePanel.hpp"
#include "headers/JournalPanel.hpp"
#include "headers/StatsPanel.hpp"

#include "Game.hpp"
#include "MapEditor.hpp"
#include "BuildingEditor.hpp"
#include "MeshEditor.hpp"



void createSetsFromIdle(string idlePath) {

    cout << "creating set from idles for monster: " << idlePath;

    sf::Image idle_0;
    sf::Image idle_1;

    idle_0.loadFromFile(idlePath + "0.png");
    idle_1.loadFromFile(idlePath + "1.png");

    // IDLE
    idle_0.saveToFile(idlePath + "idleBottom0.png");
    idle_1.saveToFile(idlePath + "idleBottom1.png");
    idle_0.saveToFile(idlePath + "idleBottom2.png");
    idle_1.saveToFile(idlePath + "idleBottom3.png");

    idle_0.saveToFile(idlePath + "idleTop0.png");
    idle_1.saveToFile(idlePath + "idleTop1.png");
    idle_0.saveToFile(idlePath + "idleTop2.png");
    idle_1.saveToFile(idlePath + "idleTop3.png");

    idle_0.saveToFile(idlePath + "idleLeft0.png");
    idle_1.saveToFile(idlePath + "idleLeft1.png");
    idle_0.saveToFile(idlePath + "idleLeft2.png");
    idle_1.saveToFile(idlePath + "idleLeft3.png");

    idle_0.saveToFile(idlePath + "idleRight0.png");
    idle_1.saveToFile(idlePath + "idleRight1.png");
    idle_0.saveToFile(idlePath + "idleRight2.png");
    idle_1.saveToFile(idlePath + "idleRight3.png");

    // RUN
    idle_0.saveToFile(idlePath + "runBottom0.png");
    idle_1.saveToFile(idlePath + "runBottom1.png");
    idle_0.saveToFile(idlePath + "runBottom2.png");
    idle_1.saveToFile(idlePath + "runBottom3.png");

    idle_0.saveToFile(idlePath + "runTop0.png");
    idle_1.saveToFile(idlePath + "runTop1.png");
    idle_0.saveToFile(idlePath + "runTop2.png");
    idle_1.saveToFile(idlePath + "runTop3.png");

    idle_0.saveToFile(idlePath + "runLeft0.png");
    idle_1.saveToFile(idlePath + "runLeft1.png");
    idle_0.saveToFile(idlePath + "runLeft2.png");
    idle_1.saveToFile(idlePath + "runLeft3.png");

    idle_0.saveToFile(idlePath + "runRight0.png");
    idle_1.saveToFile(idlePath + "runRight1.png");
    idle_0.saveToFile(idlePath + "runRight2.png");
    idle_1.saveToFile(idlePath + "runRight3.png");

    // ATTACK
    idle_0.saveToFile(idlePath + "attackBottom0.png");
    idle_1.saveToFile(idlePath + "attackBottom1.png");
    idle_0.saveToFile(idlePath + "attackBottom2.png");
    idle_1.saveToFile(idlePath + "attackBottom3.png");

    idle_0.saveToFile(idlePath + "attackTop0.png");
    idle_1.saveToFile(idlePath + "attackTop1.png");
    idle_0.saveToFile(idlePath + "attackTop2.png");
    idle_1.saveToFile(idlePath + "attackTop3.png");

    idle_0.saveToFile(idlePath + "attackLeft0.png");
    idle_1.saveToFile(idlePath + "attackLeft1.png");
    idle_0.saveToFile(idlePath + "attackLeft2.png");
    idle_1.saveToFile(idlePath + "attackLeft3.png");

    idle_0.saveToFile(idlePath + "attackRight0.png");
    idle_1.saveToFile(idlePath + "attackRight1.png");
    idle_0.saveToFile(idlePath + "attackRight2.png");
    idle_1.saveToFile(idlePath + "attackRight3.png");

}

void createSetsFromRuns(string path) {

    cout << "creating set from runs for monster: " << path;

    sf::Image run_0;
    sf::Image run_1;
    sf::Image run_2;
    sf::Image run_3;

    run_0.loadFromFile(path + "0.png");
    run_1.loadFromFile(path + "1.png");
    run_2.loadFromFile(path + "2.png");
    run_3.loadFromFile(path + "3.png");

    // IDLE
    run_0.saveToFile(path + "idleBottom0.png");
    run_1.saveToFile(path + "idleBottom1.png");
    run_2.saveToFile(path + "idleBottom2.png");
    run_3.saveToFile(path + "idleBottom3.png");

    run_0.saveToFile(path + "idleTop0.png");
    run_1.saveToFile(path + "idleTop1.png");
    run_2.saveToFile(path + "idleTop2.png");
    run_3.saveToFile(path + "idleTop3.png");

    run_0.saveToFile(path + "idleLeft0.png");
    run_1.saveToFile(path + "idleLeft1.png");
    run_2.saveToFile(path + "idleLeft2.png");
    run_3.saveToFile(path + "idleLeft3.png");

    run_0.saveToFile(path + "idleRight0.png");
    run_1.saveToFile(path + "idleRight1.png");
    run_2.saveToFile(path + "idleRight2.png");
    run_3.saveToFile(path + "idleRight3.png");

    // RUN
    run_0.saveToFile(path + "runBottom0.png");
    run_1.saveToFile(path + "runBottom1.png");
    run_2.saveToFile(path + "runBottom2.png");
    run_3.saveToFile(path + "runBottom3.png");

    run_0.saveToFile(path + "runTop0.png");
    run_1.saveToFile(path + "runTop1.png");
    run_2.saveToFile(path + "runTop2.png");
    run_3.saveToFile(path + "runTop3.png");

    run_0.saveToFile(path + "runLeft0.png");
    run_1.saveToFile(path + "runLeft1.png");
    run_2.saveToFile(path + "runLeft2.png");
    run_3.saveToFile(path + "runLeft3.png");

    run_0.saveToFile(path + "runRight0.png");
    run_1.saveToFile(path + "runRight1.png");
    run_2.saveToFile(path + "runRight2.png");
    run_3.saveToFile(path + "runRight3.png");

    // ATTACK
    run_0.saveToFile(path + "attackBottom0.png");
    run_1.saveToFile(path + "attackBottom1.png");
    run_2.saveToFile(path + "attackBottom2.png");
    run_3.saveToFile(path + "attackBottom3.png");

    run_0.saveToFile(path + "attackTop0.png");
    run_1.saveToFile(path + "attackTop1.png");
    run_2.saveToFile(path + "attackTop2.png");
    run_3.saveToFile(path + "attackTop3.png");

    run_0.saveToFile(path + "attackLeft0.png");
    run_1.saveToFile(path + "attackLeft1.png");
    run_2.saveToFile(path + "attackLeft2.png");
    run_3.saveToFile(path + "attackLeft3.png");

    run_0.saveToFile(path + "attackRight0.png");
    run_1.saveToFile(path + "attackRight1.png");
    run_2.saveToFile(path + "attackRight2.png");
    run_3.saveToFile(path + "attackRight3.png");

}


void editWhitePixelsToTransparent(string monster_path) {

    cout << "editing white pixels to transparent: " << monster_path << "\n";

    //sf::Color whiteColor = sf::Color(255, 255, 255);
    sf::Color whiteColor = sf::Color(48, 48, 48);
    //sf::Color transparentColor = sf::Color(0, 0, 0, 0);
    sf::Color transparentColor = sf::Color(127, 127, 127);

    std::vector < std::string > png_files;

    for (const auto& entry : filesystem::directory_iterator(monster_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            png_files.push_back(entry.path().string());
        }
    }

    for (auto& png : png_files) {
        sf::Image img;
        img.loadFromFile(png.c_str());

        for (int y = 0; y < img.getSize().y; y++)
            for (int x = 0; x < img.getSize().x; x++) {
                if (img.getPixel(x, y) == whiteColor) {
                    img.setPixel(x, y, transparentColor);
                }

            }

        img.saveToFile(png.c_str());
    }

}

void test()
{
    printf("     ");
    for (int a = 1; a < 20; ++a)
        printf("%4d ", a);

    printf("\ratk\\def\n");

    for (int dex_atk = 1; dex_atk < 30; ++dex_atk)
    {
        printf("%4d", dex_atk);
        for (int dex_def = 1; dex_def < 30; ++dex_def)
        {
            int hit = 0, tests = 1000;

            //srand(0);
            for (int i = 0; i < tests; ++i)
            {
                if (rand() % (dex_atk+10) - rand() % (dex_def+5) > 0)
                    ++hit;

            }

            printf(" %3.0f%%", 100.f * hit / tests);
        }
        printf("\n");
    }
}

void createTab(int width, int height) {
    

    //int tab[width][height];
    std::vector<std::vector<int>> tab(width, std::vector<int>(height));
     
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            std::cout << tab[i][j] << " ";
}

void testSelectingFunction() {

    sf::Vector2i mousePosition;
    sf::Vector2i startMousePosition;

    sf::Vector2f worldMousePosition;
    sf::Vector2f startWorldMousePosition;

    sf::RectangleShape rect;
    sf::RenderWindow* window;

    bool selection_state = false;

    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RECT");
    
    while (window->isOpen()) {

        mousePosition = sf::Mouse::getPosition(*window); // Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    startMousePosition = sf::Mouse::getPosition(*window);
                    startWorldMousePosition = window->mapPixelToCoords(startMousePosition);
                }   selection_state = true;;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selection_state = false;
                    // action
                }
            }
        }

        if (selection_state == true) {

            int start_x = std::min(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
            int start_y = std::min(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));
            int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
            int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

            cout << "selected area: \n";
            cout << "start: " << start_x << ", " << start_y << "\n";
            cout << "end: " << end_x << ", " << end_y << "\n";
            cout << "\n\n";

            rect = sf::RectangleShape(sf::Vector2f((end_x - start_x)*tileSide, (end_y - start_y)*tileSide));
            rect.setPosition(start_x*tileSide, start_y*tileSide);
        }

        window->clear();
        if(selection_state == true)
            window->draw(rect);
        window->display();
    }

    delete window;
 
}

void testElipseSelectingFunction() {

    sf::Vector2i mousePosition;
    sf::Vector2i startMousePosition;

    sf::Vector2f worldMousePosition;
    sf::Vector2f startWorldMousePosition;

    float tileSide = 16.0f;



    std::vector < sf::RectangleShape > rects;

    bool selection_state = false;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RECT");

    while (window->isOpen()) {

        mousePosition = sf::Mouse::getPosition(*window); // Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    startMousePosition = sf::Mouse::getPosition(*window);
                    startWorldMousePosition = window->mapPixelToCoords(startMousePosition);
                    selection_state = true;
                }   
                
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selection_state = false;
                }
            }
        }

        if (selection_state == true) {

            rects.clear();

            int start_x = std::min(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
            int start_y = std::min(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));
            int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
            int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

            cout << "selected area: \n";
            cout << "start: " << start_x << ", " << start_y << "\n";
            cout << "end: " << end_x << ", " << end_y << "\n";
            cout << "\n\n";

            int width = end_x - start_x;
            int height = end_y - start_y;

            // Środek pędzla
            float centerX = (start_x + end_x) / 2.0f;
            float centerY = (start_y + end_y) / 2.0f;

            // Półosie elipsy
            float a = width / 2.0f;
            float b = height / 2.0f;

            // Generowanie elipsy w oparciu o pędzel
            for (int y = start_y; y < end_y; ++y) {
                for (int x = start_x; x < end_x; ++x) {
                    // Obliczanie pozycji w stosunku do środka
                    float dx = (x - centerX) / a;
                    float dy = (y - centerY) / b;

                    // Sprawdź, czy pędzel na tej pozycji ma wartość 1
                    if (dx * dx + dy * dy <= 0.995f) {
                        int xx = x * int(tileSide);
                        int yy = y * int(tileSide);

                        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(tileSide, tileSide));
                        rect.setFillColor(sf::Color::Red);
                        rect.setPosition(xx, yy);
                        rects.push_back(rect);
                    }
                }
            }

        }

        window->clear();
        if (selection_state == true)
            for (auto& rect : rects)
                window->draw(rect);
        window->display();
    }

    delete window;
}

void convertPNGsToSet() {

    int frameWidth = 128;
    int frameHeight = 128;
    std::vector < string > PNGS;
    
    PNGS.clear();
    PNGS.push_back("assets/sets/water/frame_00.png");
    PNGS.push_back("assets/sets/water/frame_01.png");
    PNGS.push_back("assets/sets/water/frame_02.png");
    PNGS.push_back("assets/sets/water/frame_03.png");
    PNGS.push_back("assets/sets/water/frame_04.png");
    PNGS.push_back("assets/sets/water/frame_05.png");
    PNGS.push_back("assets/sets/water/frame_06.png");
    PNGS.push_back("assets/sets/water/frame_07.png");
    PNGS.push_back("assets/sets/water/frame_08.png");
    PNGS.push_back("assets/sets/water/frame_09.png");
    PNGS.push_back("assets/sets/water/frame_10.png");
    PNGS.push_back("assets/sets/water/frame_11.png");
    PNGS.push_back("assets/sets/water/frame_12.png");
    PNGS.push_back("assets/sets/water/frame_13.png");
    PNGS.push_back("assets/sets/water/frame_14.png");
    PNGS.push_back("assets/sets/water/frame_15.png");

    sf::Image set;
    sf::Texture tex;
    sf::Image img;

    set.create(frameWidth * (PNGS.size()+1), frameHeight);
    img.create(128, 128, sf::Color::Transparent);
    set.copy(img, 0, 0);

    for (int i = 0; i < PNGS.size();i++) {
        
        tex.loadFromFile(PNGS[i].c_str());
        img = tex.copyToImage();
        set.copy(img, frameWidth * (i+1), 0);
    }

    set.saveToFile("assets/sets/water/waterset.png");
}

void testGLSL() {

    sf::RenderWindow window(sf::VideoMode(512, 512), "test GLSL");
    
    sf::Texture texture;
    if (!texture.loadFromFile("assets/noise.png"))
        return;

    sf::Sprite sprite(texture);

    sf::Shader shader;
    if (!shader.loadFromFile("assets/shaders/circles.frag", sf::Shader::Fragment))
        return;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        float time = clock.getElapsedTime().asSeconds();
        shader.setUniform("u_resolution", sf::Vector2f(1024,1024));
        shader.setUniform("u_time", time);

        window.clear();
        window.draw(sprite, &shader);
        window.display();
    }

}

class Line {
public:
    sf::Vector2f start;
    sf::Vector2f end;
    sf::Vertex vertices[2];
    sf::Color color; 

    Line(const sf::Vector2f& _start, const sf::Vector2f& _end) {
        start = _start;
        end = _end;
        color = sf::Color::Blue;
    }

    void setColor(sf::Color _color) {
        color = _color;
    }

    sf::Vertex* getVertices() {
        vertices[0] = sf::Vertex(start, color);
        vertices[1] = sf::Vertex(end, color);
        return vertices;
    }
};

void testIntersectionTwoLines() {
    
    Line line1(sf::Vector2f(400, 300), sf::Vector2f(550, 300));
    Line line2(sf::Vector2f(450, 350), sf::Vector2f(600, 350));
    float len = 150;;
    float angle = 0;
    window->setFramerateLimit(30);

    while (window->isOpen()) {

        line1.end.x = line1.start.x - sin(angle*M_PI/180.0f)*len;
        line1.end.y = line1.start.y + cos(angle*M_PI/180.0f)*len;
        angle += 1;

        if (angle >= 360.0f)
            angle -= 360.0f;

        if (intersectionTwoLines(line1.start, line1.end, line2.start, line2.end)) {
            line1.setColor(sf::Color::Red);
            line2.setColor(sf::Color::Red);
        }
        else {
            line1.setColor(sf::Color::Blue);
            line2.setColor(sf::Color::Blue);
        }

        window->clear();
        window->draw(line1.getVertices(), 2, sf::Lines);
        window->draw(line2.getVertices(), 2, sf::Lines);
        window->display();
    }
}

void test_romb() {

    // Wczytanie tekstury
    sf::Texture texture;
    texture.loadFromFile("assets/buildings/parts/roof2.png");

    // Tworzenie rombu (kopniętego kwadratu) za pomocą VertexArray
    sf::VertexArray diamond(sf::Quads, 4);

    // Wierzchołki rombu
    float dx = 200;
    float dy = 100;
    diamond[0].position = sf::Vector2f(200, 200); // top left
    diamond[1].position = sf::Vector2f(200+dx, 200-dy); // bottom right
    diamond[2].position = sf::Vector2f(200+dx, 200- 2*dy); // top right
    diamond[3].position = sf::Vector2f(200, 200-dy); // top left

    // Ustawienie współrzędnych tekstury
    diamond[0].texCoords = sf::Vector2f(0, 0);
    diamond[1].texCoords = sf::Vector2f(texture.getSize().x, 0);
    diamond[2].texCoords = sf::Vector2f(texture.getSize().x, texture.getSize().y);
    diamond[3].texCoords = sf::Vector2f(0, texture.getSize().y);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear(sf::Color(48.0f, 48.0f, 48.0f));
        // Rysowanie rombu z teksturą
        sf::RenderStates states;
        states.texture = &texture;
        window->draw(diamond, states);
        window->display();
    }

    
}

int main()
{

    // TOOLS - be careful with that
    //createSetsFromIdle("assets/monsters/kolcorozec/");
    //createSetsFromRuns("assets/monsters/jaszczur/");
    //editWhitePixelsToTransparent("assets/sets/body/boy-greyhaired");
    //convertPNGsToSet();
    
    ProgressBar* progress_bar = new ProgressBar();

    float steps = 8.0f;


    // LOADS
                        progress_bar->draw(0.0f / steps);   sf::sleep(sf::seconds(1));
    loadFonts();        progress_bar->draw(1.0f / steps);   sf::sleep(sf::seconds(1));
	loadTextures();     progress_bar->draw(2.0f / steps);   sf::sleep(sf::seconds(1));
	loadShaders();      progress_bar->draw(3.0f / steps);   sf::sleep(sf::seconds(1));
	loadItems();        progress_bar->draw(4.0f / steps);   sf::sleep(sf::seconds(1));
    loadInventories();  progress_bar->draw(5.0f / steps);   sf::sleep(sf::seconds(1));
    loadDialogues();    progress_bar->draw(6.0f / steps);   sf::sleep(sf::seconds(1));
    loadQuests();       progress_bar->draw(7.0f / steps);   sf::sleep(sf::seconds(1));
	loadPrefabs();      progress_bar->draw(8.0f / steps);   sf::sleep(sf::seconds(1));
    
	window->setKeyRepeatEnabled(false);	// TO-DO commentary
    
    // TESTS
    //testSelectingFunction();
    //testElipseSelectingFunction();
    //testGLSL();
    //testOpenDialogBox();
    //testIntersectionTwoLines();
    
    // PROGRAMS
    Editor();
    //BuildingEditor();
    //MeshEditor();
    //test_romb();

    return 0;
}