#ifndef DialogueEditor_hpp
#define DialogueEditor_hpp


/*

class DialogueOption {
public:

	class DialogueAnswer {
	public:
		std::wstring text;
		DialogueOption* next_option;

		DialogueAnswer(std::wstring text) {
			this->text = text;
			next_option = nullptr;
		}
	};

	std::wstring text;
	std::vector < DialogueAnswer* > answers;

	DialogueOption(std::wstring text) {
		this->text = text;
		answers.clear();
	}
};

class Dialogue {
public:
	int id;
	std::vector < DialogueOption* > options;

	Dialogue(int id) {
		this->id = id;
		load();
	}

	~Dialogue() { }
}


*/


class DialogueEditor : public Dialog {
public:

	Dialogue* dialogue_to_edit;
	std::wstring text;
	TextArea* text_area;

	DialogueEditor(Dialogue* dialogue_to_edit) : Dialog(DialogType::DialogueEditor, sf::Vector2f(720, 480)) {

		this->dialogue_to_edit = dialogue_to_edit;
		
		text = getTextFromDialogue();
		//std::cout << ConvertWideToUtf8(text) << "\n";

		float line_length = Dialog::getSize().x - 2 * corner_size;
		sf::Vector2f text_area_rect_size = Dialog::getSize() - sf::Vector2f(2 * corner_size, 2 * corner_size);
		
		sf::Vector2f text_area_pos(-Dialog::getSize().x/2.0f + corner_size, -Dialog::getSize().y/2.0f + corner_size);
		text_area = new TextArea(text, text_area_pos, line_length, text_area_rect_size, 
			TextAlignment::Left, VerticalAlignment::Top, WrapperType::Normal);
	}

	~DialogueEditor() { }

	std::wstring getText(DialogueOption* dial_opt) {

		if (dial_opt == nullptr)
			return L"";

		std::wstring text = dial_opt->text + L"\n";

		for (auto& answer : dial_opt->answers) {
			text += answer->text;
			text += L"\n";
			if (answer->next_option != dialogue_to_edit->options.back()) {
				text += getText(answer->next_option);
			}
		}

		return text;
	}

	std::wstring getTextFromDialogue() {
		if (dialogue_to_edit == nullptr || dialogue_to_edit->options.empty()) {
			return L"";
		}

		std::wstring text = L"";

		for (auto& dial_opt : dialogue_to_edit->options) {
			text += getText(dial_opt);
		}

		return text;
	}

	void cursorHover() {
	
	}

	void handleEvent(sf::Event& event) {

	}

	void update() {

	}

	void draw() {
		Dialog::draw();
		text_area->draw();
	}
};

#endif