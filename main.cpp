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
#include "headers/Translate.hpp"

#include "headers/Fonts.hpp"
#include "headers/Textures.hpp"
#include "headers/Shaders.hpp"
#include "headers/Point.hpp"
#include "headers/Collisions.hpp"

#include "headers/Renderer.hpp"

#include "headers/ProgressBar.hpp"

#include "headers/GameStates.hpp"           
#include "headers/GUI.hpp"                  // GUIwasHover / GUIwasClicked / GUIwasOpen

#include "headers/EditorStates.hpp"

#include "headers/Mesh.hpp"

#include "headers/GameObjects.hpp"
#include "headers/TerrainAndFloors.hpp"     // Terrain and Floors
#include "headers/Water.hpp"
#include "headers/Borders.hpp"
#include "headers/Pathfinding.hpp"

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
#include "headers/Spell.hpp"            // manage of Spells

#include "headers/Prefabs.hpp"              // manage of all prefabs
#include "headers/Buildings.hpp"            // manage of Buildings
#include "headers/MouseMovedGameObjects.hpp"     // 
#include "headers/GameObjectsManager.hpp"   // manage of GameObjects - update/sort/render/
#include "headers/Map.hpp"
#include "headers/Quests.hpp"

#include "headers/PrefabToPaint.hpp"

#include "headers/Tips.hpp"
#include "headers/Palette.hpp"
#include "headers/MenuBar.hpp"

#include "headers/DialogueEditor.hpp"
#include "headers/CharacterInfoPanel.hpp"
//#include "headers/InstructionsWorldEditor.hpp"    // TO-DO
//#include "headers/InstructionsBuildingEditor.hpp" // TO-DO
//#include "headers/InstructionsMeshEditor.hpp"     // TO-DOS

#include "headers/Clipboard.hpp"
#include "headers/History.hpp"
#include "headers/ContextMenu.hpp"

#include "headers/Config.hpp"
    
#include "headers/ControlsPanel.hpp"
#include "headers/InventoryPanel.hpp"
#include "headers/TradePanel.hpp"
#include "headers/JournalPanel.hpp"
#include "headers/StatsPanel.hpp"

//#include "Game.hpp"
#include "WorldEditor.hpp"
//#include "BuildingEditor.hpp"
//#include "MeshEditor.hpp"



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
    sf::Color transparentColor = sf::Color(136, 68, 0, 255);
    //sf::Color transparentColor = sf::Color::Transparent;

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

void deleteHeadFromBodySet(std::string head_location, std::string body_location) {

    cout << "delete head from bodyset: " << body_location << "\n";

    //sf::Color whiteColor = sf::Color(255, 255, 255);
    sf::Color whiteColor = sf::Color(255, 255, 255);
    //sf::Color transparentColor = sf::Color(0, 0, 0, 0);
    sf::Color transparentColor = sf::Color::Transparent;

    std::vector < std::string > filenames;

    for (const auto& entry : filesystem::directory_iterator(body_location)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            filenames.push_back(entry.path().filename().string());
            std::cout << filenames.back() << "\n";
        }
    }

    for (auto& bodyfile : filenames) {

        sf::Image bodyimg;
        bodyimg.loadFromFile(body_location + "\\" + bodyfile.c_str());

        sf::Image headimg;
        headimg.loadFromFile(head_location + "\\" + bodyfile.c_str());

        std::cout << body_location + "\\" + bodyfile.c_str() << "\t";
        std::cout << head_location + "\\" + bodyfile.c_str() << "\n";

        for (int y = 0; y < bodyimg.getSize().y; y++)
            for (int x = 0; x < bodyimg.getSize().x; x++) {
                if (headimg.getPixel(x, y) != sf::Color::Transparent) {
                    bodyimg.setPixel(x, y, sf::Color::Transparent);
                }
            }
        
        bodyimg.saveToFile(body_location + "\\" + bodyfile.c_str());
    }

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

/*
float screenWidth = 1280;
float screenHeight = 720;
sf::RenderWindow* window;
Camera* cam;
Renderer* renderer;
*/

int main()
{

    // TOOLS - be careful with that
    //createSetsFromIdle("assets/monsters/kolcorozec/");
    //createSetsFromRuns("assets/monsters/jaszczur/");
    //editWhitePixelsToTransparent("assets/sets/items/shield");
    //convertPNGsToSet();
    ////
    //editWhitePixelsToTransparent("assets\\sets\\items\\chain mail");
    //
    
    //editWhitePixelsToTransparent("..\\new_bbody\\head\\boy-brown-haired");
    //editWhitePixelsToTransparent("..\\new_bbody\\head\\man-brown-haired");
    //editWhitePixelsToTransparent("..\\new_bbody\\head\\woman-brown-haired");
    //deleteHeadFromBodySet("assets\\sets\\heads\\woman-blackhaired", "assets\\sets\\body\\woman-blackhaired");
    
    ProgressBar* progress_bar = new ProgressBar();

    float steps = 9.0f;

    
    // LOADS
                        progress_bar->draw(0.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadFonts();        progress_bar->draw(1.0f / steps);   sf::sleep(sf::seconds(0.1f));

    save_textures_as_packet();  // TO-DO
        
    sf::Clock clock1;
    sf::Time start_time, end_time;
    start_time = clock1.getElapsedTime();
    loadTexturesFromPacket();
    end_time = clock1.getElapsedTime();
    std::cout << "-load time : " << (end_time - start_time).asSeconds() << " seconds \n";
	
	loadShaders();      progress_bar->draw(3.0f / steps);   sf::sleep(sf::seconds(0.1f));
	loadItems();        progress_bar->draw(4.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadInventories();  progress_bar->draw(5.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadDialogues();    progress_bar->draw(6.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadQuests();       progress_bar->draw(7.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadMeshes();       progress_bar->draw(8.0f / steps);   sf::sleep(sf::seconds(0.1f));
    loadPrefabs();      progress_bar->draw(9.0f / steps);   sf::sleep(sf::seconds(0.1f));

	window->setKeyRepeatEnabled(false);	// TO-DO commentary
    // TO-DO
    //window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true); 
    SetConsoleOutputCP(65001);  // for special letters ą,ć,ź etc 

    
    // 
    //window->setFramerateLimit(60);
    //window->setFramerateLimit(60);
    // TESTS
    //testSelectingFunction();
    //testElipseSelectingFunction();
    //testGLSL();
    //testOpenDialogBox();
    //testIntersectionTwoLines();
    //test_grid();
    //test_motion_blur();
    //test_load_textures();

    // PROGRAMS
    Editor();
    //BuildingEditor();
    //MeshEditor();
    //test_romb();

    return 0;
}

