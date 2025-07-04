#ifndef Mouse_hpp
#define Mouse_hpp

sf::Vector2i mousePosition;
sf::Vector2f worldMousePosition;

sf::Time mouse_start_time;

sf::Vector2i startMousePosition;
sf::Vector2f startWorldMousePosition;

sf::RectangleShape selectArea;

enum class MouseState { Idle, Press, Drawing, Selecting, MovingGameObjects };
MouseState mouse_state = MouseState::Idle;

void mouseSelection() {
    float start_x = std::min(startWorldMousePosition.x, worldMousePosition.x);
    float start_y = std::min(startWorldMousePosition.y, worldMousePosition.y);
    float end_x = std::max(startWorldMousePosition.x, worldMousePosition.x);
    float end_y = std::max(startWorldMousePosition.y, worldMousePosition.y);
    
    float width = end_x - start_x;
    float height = end_y - start_y;

    if (width == 0) width = 2;
    if (height == 0) height = 2;

    selectArea = sf::RectangleShape(sf::Vector2f(width, height));
    selectArea.setOrigin(width/2, height/2);
    selectArea.setPosition((start_x + end_x) / 2, (start_y + end_y) / 2);
    selectArea.setFillColor(sf::Color(128, 48, 48, 128));

}
#endif
