#ifndef Window_hpp
#define Window_hpp

float screenWidth = 1280;
float screenHeight = 720;

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(int(screenWidth), int(screenHeight)), "Editor RPG2D");
float FPS = 0;
#endif