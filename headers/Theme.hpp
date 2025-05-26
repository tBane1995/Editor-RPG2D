#ifndef Theme_hpp
#define Theme_hpp

// GAME
sf::Color dialoguesColor = sf::Color(234, 224, 175);
sf::Color dialoguesActiveColor = sf::Color(255, 201, 14);

// EDITOR
float dialog_border_width = 8.0f;
float button_border_width = 1.0f;

sf::Color panelColor_normal = sf::Color(64, 64, 64);
sf::Color panelColor_light = sf::Color(80, 80, 80);
sf::Color panelColor_medium = sf::Color(48, 48, 48);
sf::Color panelColor_dark = sf::Color(32, 32, 32);
sf::Color panelColor_verydark = sf::Color(16, 16, 16);

sf::Color textColor = sf::Color::White;

float margin = 8;
sf::Vector2f border_part_size = sf::Vector2f(6, 6);
float corner_size = 8;

sf::Color backgroundColor = sf::Color(48, 48, 48);	// color of outside map

sf::Vector2f buttonSize = sf::Vector2f(0, 0);


#endif