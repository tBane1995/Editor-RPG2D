#ifndef GUI_hpp
#define GUI_hpp

bool GUIwasHover;		// element GUI was hover
bool GUIwasClicked;		// element GUI was clicked
bool GUIwasOpen;		// element GUI was open

class ElementGUI {
public:
	ElementGUI() { }
	~ElementGUI() { }
	void cursorHover() { }
};

ElementGUI* ElementGUI_hovered = nullptr;
ElementGUI* ElementGUI_pressed = nullptr;

#endif