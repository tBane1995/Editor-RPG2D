#ifndef scrollbar_hpp
#define scrollbar_hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class ScrollbarPartSize { _16, _20 };

class Scrollbar : ElementGUI {
public:
  
    sf::Vector2f size;
    sf::Vector2f position;

    sf::RectangleShape scroll_area; // area where mouseScroll active scrollbar
    sf::Vector2f scroll_area_size;
    sf::Vector2f scroll_area_position;

    sf::Color bar_color;
    sf::Color scroll_color;

    short min_value;
    short max_value;
    short scroll_value;         
    short scroll_step;          // shift value
    short scroll_length;        // length of scrollbar (in units)

    float start_mouse_y;
    bool is_pressed;

    std::function<void()> onclick_func;

    sf::RectangleShape bar_top;
    sf::RectangleShape bar_center;
    sf::RectangleShape bar_bottom;

    sf::RectangleShape scroll_top;
    sf::RectangleShape scroll_center;
    sf::RectangleShape scroll_bottom;

    sf::Sprite spr_bar_top;
    sf::Sprite spr_bar_center;
    sf::Sprite spr_bar_bottom;

    sf::Sprite spr_scroll_top;
    sf::Sprite spr_scroll_center;
    sf::Sprite spr_scroll_bottom;

    Scrollbar(sf::Vector2f size, sf::Vector2f position, short min_value, short max_value, short scroll_value, short scroll_step, short scroll_length, ScrollbarPartSize part_size = ScrollbarPartSize::_16) : ElementGUI() {

        this->size = size;
        this->position = position;

        this->min_value = min_value;
        this->max_value = max_value;
        this->scroll_step = scroll_step;
        this->scroll_length = scroll_length;

        setValue(scroll_value);

        this->start_mouse_y = 0;
        this->is_pressed = false;

        onclick_func = { };

        // COLORS
        bar_color = sf::Color::Red;
        scroll_color = sf::Color::Blue;

        sf::Vector2f p;
        p.x += cam->position.x + position.x;
        p.y += cam->position.y + position.y;

        // BAR RECT
        bar_top = sf::RectangleShape(sf::Vector2f(size.x, size.x));
        bar_top.setPosition(p);
        bar_top.setFillColor(bar_color);

        bar_center = sf::RectangleShape(sf::Vector2f(size.x, size.y - 2.0f * size.x));
        bar_center.setPosition(p.x, p.y + size.x);
        bar_center.setFillColor(bar_color);

        bar_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
        bar_bottom.setPosition(p.x, p.y + size.y - size.x);
        bar_bottom.setFillColor(bar_color);

        // SCROLL RECT
        scroll_top = sf::RectangleShape(sf::Vector2f(size.x, size.x));
        scroll_top.setPosition(p.x, p.y + size.x);
        scroll_top.setFillColor(scroll_color);

        scroll_center = sf::RectangleShape(sf::Vector2f(size.x, getScrollSizeY() - 2 * size.x));
        scroll_center.setPosition(p.x, p.y + size.x + size.x);
        scroll_center.setFillColor(sf::Color::Green);

        scroll_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
        scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);
        scroll_bottom.setFillColor(scroll_color);

        if (part_size == ScrollbarPartSize::_16) {
            // BAR SPRITES
            spr_bar_top = sf::Sprite();
            spr_bar_top.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\bar_top")->texture);
            spr_bar_top.setScale(size.x / 16.0f, size.x / 16.0f);
            spr_bar_top.setPosition(p);

            spr_bar_center = sf::Sprite();
            spr_bar_center.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\bar_center")->texture);
            spr_bar_center.setScale(size.x / 16.0f, (size.y - 2.0f * size.x) / 16.0f);
            spr_bar_center.setPosition(p.x, p.y + size.x);

            spr_bar_bottom = sf::Sprite();
            spr_bar_bottom.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\bar_bottom")->texture);
            spr_bar_bottom.setScale(size.x / 16.0f, size.x / 16.0f);
            spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

            // SCROLL SPRITES
            spr_scroll_top = sf::Sprite();
            spr_scroll_top.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\scroll_top")->texture);
            spr_scroll_top.setScale(size.x / 16.0f, size.x / 16.0f);
            spr_scroll_top.setPosition(p.x, p.y + size.x);

            spr_scroll_center = sf::Sprite();
            spr_scroll_center.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\scroll_center")->texture);
            spr_scroll_center.setScale(size.x / 16.0f, (getScrollSizeY() - 2.0f * size.x) / 16.0f);
            spr_scroll_center.setPosition(p.x, p.y + size.x + size.x);

            spr_scroll_bottom = sf::Sprite();
            spr_scroll_bottom.setTexture(*getSingleTexture(L"GUI\\scrollbar_16\\scroll_bottom")->texture);
            spr_scroll_bottom.setScale(size.x / 16.0f, size.x / 16.0f);
            spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2.0f * size.x);
        }
        else if (part_size == ScrollbarPartSize::_20) {
            // BAR SPRITES
            spr_bar_top = sf::Sprite();
            spr_bar_top.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\bar_top")->texture);
            spr_bar_top.setScale(size.x / 20.0f, size.x / 20.0f);
            spr_bar_top.setPosition(p);

            spr_bar_center = sf::Sprite();
            spr_bar_center.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\bar_center")->texture);
            spr_bar_center.setScale(size.x / 20.0f, (size.y - 2.0f * size.x) / 20.0f);
            spr_bar_center.setPosition(p.x, p.y + size.x);

            spr_bar_bottom = sf::Sprite();
            spr_bar_bottom.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\bar_bottom")->texture);
            spr_bar_bottom.setScale(size.x / 20.0f, size.x / 20.0f);
            spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

            // SCROLL SPRITES
            spr_scroll_top = sf::Sprite();
            spr_scroll_top.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\scroll_top")->texture);
            spr_scroll_top.setScale(size.x / 20.0f, size.x / 20.0f);
            spr_scroll_top.setPosition(p.x, p.y + size.x);

            spr_scroll_center = sf::Sprite();
            spr_scroll_center.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\scroll_center")->texture);
            spr_scroll_center.setScale(size.x / 20.0f, (getScrollSizeY() - 2 * size.x) / 20.0f);
            spr_scroll_center.setPosition(p.x, p.y + size.x + size.x);

            spr_scroll_bottom = sf::Sprite();
            spr_scroll_bottom.setTexture(*getSingleTexture(L"GUI\\scrollbar_20\\scroll_bottom")->texture);
            spr_scroll_bottom.setScale(size.x / 20.0f, size.x / 20.0f);
            spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);
        }

        scroll_area = sf::RectangleShape();
        scroll_area.setFillColor(sf::Color(128, 48, 8, 128));
        scroll_area_size = size;
        scroll_area_position = position;

        setScrollAreaSize(scroll_area_size);
        setScrollAreaPosition(scroll_area_position);
        
    }

    void setPosition(sf::Vector2f pos) {
        this->position = pos;

        sf::Vector2f p;
        p.x += cam->position.x + position.x;
        p.y += cam->position.y + position.y;

        // BAR RECT
        bar_top.setPosition(p);
        bar_center.setPosition(p.x, p.y + size.x);
        bar_bottom.setPosition(p.x, p.y + size.y - size.x);

        // BAR SPRITES
        spr_bar_top.setPosition(p);
        spr_bar_center.setPosition(p.x, p.y + size.x);
        spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

        // SCROLL RECT
        scroll_top.setPosition(p.x, p.y + size.x);
        scroll_center.setPosition(p.x, p.y + size.x + size.x);
        scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);

        // SCROLL SPRITES
        spr_scroll_top.setPosition(p.x, p.y + size.x);
        spr_scroll_center.setPosition(p.x, p.y + size.x + size.x);
        spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);

    }

    void setScrollAreaSize(sf::Vector2f size) {
        scroll_area_size = size;
        scroll_area.setSize(scroll_area_size);
    }

    void setScrollAreaPosition(sf::Vector2f position) {
        scroll_area_position = position;
        scroll_area.setPosition(scroll_area_position + cam->position);
    }

    void setValue(short value) {
        scroll_value = value;

        if (scroll_value > max_value - scroll_length + 1)
            scroll_value = max_value - scroll_length + 1;

        if (scroll_value < min_value)
            scroll_value = min_value;
    }

    float getScrollSizeY() {
        if (scroll_length > max_value - min_value + 1)
            return size.y - 2 * size.x;
        else
            return round(float(size.y - 2.0f * size.x) * float(scroll_length) / float(max_value - min_value + 1));
    }

    void scrollPositioning() {

        float delta_y = float(scroll_value) * ((size.y - 2 * size.x) / float(max_value - min_value + 1));

        sf::Vector2f p;
        p.x = cam->position.x + position.x;
        p.y = cam->position.y + position.y;

        // SCROLL RECT
        scroll_top.setPosition(p.x, p.y + size.x + delta_y);
        scroll_center.setPosition(p.x, p.y + size.x + size.x + delta_y);
        scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x + delta_y);

        // SCROLL SPRITES
        spr_scroll_top.setPosition(p.x, p.y + size.x + delta_y);
        spr_scroll_center.setPosition(p.x, p.y + size.x + size.x + delta_y);
        spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x + delta_y);
    }

    bool isScrollHover() {

        float min_x = scroll_top.getPosition().x;
        float min_y = scroll_top.getPosition().y;
        float max_x = scroll_bottom.getPosition().x + scroll_bottom.getSize().x;
        float max_y = scroll_bottom.getPosition().y + scroll_bottom.getSize().y;

        if (worldMousePosition.x >= min_x && worldMousePosition.x <= max_x && worldMousePosition.y >= min_y && worldMousePosition.y <= max_y)
            return true;
        else
            return false;
    }

    bool isBarHover() {
        sf::Vector2f barPos(cam->position.x + position.x, cam->position.y + position.y + size.x);
        sf::Vector2f barSize(size.x, size.y - 2 * size.x);

        if (worldMousePosition.x >= barPos.x && worldMousePosition.x <= barPos.x + barSize.x &&
            worldMousePosition.y >= barPos.y && worldMousePosition.y <= barPos.y + barSize.y)
            return true;
        else
            return false;
    }

    void handleEvent(sf::Event& event) {

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (scroll_area.getGlobalBounds().contains(worldMousePosition)) {
                //std::cout << "scroll\n";

                int d = 0;
                if (event.mouseWheelScroll.delta > 0) d = 1;
                if (event.mouseWheelScroll.delta < 0) d = -1;

                int newValue = scroll_value - d * scroll_step;

                setValue(newValue);
                scrollPositioning();

                GUIwasClicked = true;
                ElementGUI_pressed = this;
                if (onclick_func) {
                    onclick_func();
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (isScrollHover()) {
                    start_mouse_y = worldMousePosition.y - scroll_top.getPosition().y;
                    is_pressed = true;
                    GUIwasClicked = true;
                    ElementGUI_pressed = this;
                    if(onclick_func)
                        onclick_func();
                }
                else if(isBarHover()){
                    sf::Vector2f barPos(cam->position.x + position.x, cam->position.y + position.y + size.x);
                    sf::Vector2f barSize(size.x, size.y - 2 * size.x);

                    float relY = worldMousePosition.y - barPos.y;
                    int newValue = (relY / barSize.y) * (max_value - min_value + 1);
                    setValue(newValue);
                    scrollPositioning();

                    GUIwasClicked = true;
                    ElementGUI_pressed = this;
                    if (onclick_func) {
                        onclick_func();
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                is_pressed = false;
            }
        }
        else if (is_pressed) {
            float scrollPos = worldMousePosition.y - start_mouse_y;
            sf::Vector2f p;
            p.x += cam->position.x + position.x;
            p.y += cam->position.y + position.y;

            if (scrollPos < p.y)
                scrollPos = p.y;

            if (scrollPos > p.y + size.y - getScrollSizeY())
                scrollPos = p.y + size.y - getScrollSizeY();

            setValue((scrollPos - p.y) * (max_value - min_value + 1) / size.y);
            scrollPositioning();
            GUIwasClicked = true;
            if(onclick_func)
                onclick_func();
        }


    }

    void update() {
        sf::Vector2f p;
        p.x += cam->position.x + position.x;
        p.y += cam->position.y + position.y;

        // BAR RECT
        bar_top.setPosition(p);
        bar_center.setPosition(p.x, p.y + size.x);
        bar_bottom.setPosition(p.x, p.y + size.y - size.x);

        // BAR SPRITES
        spr_bar_top.setPosition(p);
        spr_bar_center.setPosition(p.x, p.y + size.x);
        spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

        scrollPositioning();

        if (isScrollHover() || isBarHover()) {
            GUIwasHover = true;
        }

        scroll_area.setPosition(scroll_area_position + cam->position);
    }

    void draw() {

        // BAR RECT
        window->draw(bar_top);
        window->draw(bar_center);
        window->draw(bar_bottom);

        // BAR SPRITES
        window->draw(spr_bar_top);
        window->draw(spr_bar_center);
        window->draw(spr_bar_bottom);

        // SCROLL RECT
        window->draw(scroll_top);
        window->draw(scroll_center);
        window->draw(scroll_bottom);

        // SCROLL SPRITES
        window->draw(spr_scroll_top);
        window->draw(spr_scroll_center);
        window->draw(spr_scroll_bottom);

        // SCROLL AREA
        window->draw(scroll_area);
    }
};


#endif