#ifndef Dialogues_hpp
#define Dialogues_hpp

short count_tabs(const std::string& line) {
	short count = 0;
	for (char c : line) {
		if (c == '\t') count++;
		else break;
	}
	return count;
}

short count_tabs(const std::wstring& line) {
	short count = 0;
	for (char c : line) {
		if (c == L'\t') count++;
		else break;
	}
	return count;
}
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

	void load() {

		std::vector < DialogueOption* > stack;
		std::string line;

		std::string filename = to_string(id);

		if (filename.size() == 1)
			filename = "00" + filename;

		else if (filename.size() == 2)
			filename = "0" + filename;

		filename = "dialogues\\new\\pl-" + filename + ".txt";

		std::ifstream file(filename);

		while (std::getline(file, line)) {

			if (line.empty())
				continue;

			if (stack.empty()) {
				stack.push_back(new DialogueOption(ConvertUtf8ToWide(line)));
			}
			else {
				short tabs = count_tabs(line);
				short stack_tabs = count_tabs(stack.back()->text);

				//std::wcout << L"t: " << tabs << " st: " << stack_tabs << L"\n";

				if (tabs == stack_tabs) {
					if (line[tabs] == '-') {
						// is Dialogue Answer
						DialogueOption::DialogueAnswer* answer = new DialogueOption::DialogueAnswer(ConvertUtf8ToWide(line));
						answer->next_option = stack.front();
						stack.back()->answers.push_back(answer);
					}
					else {
						DialogueOption* option = new DialogueOption(ConvertUtf8ToWide(line));
						if (!stack.back()->answers.empty())
							stack.back()->answers.back()->next_option = option;

						stack.push_back(option);
					}
				}
				else if (tabs > stack_tabs) {
					// is new Dialogue Option
					DialogueOption* option = new DialogueOption(ConvertUtf8ToWide(line));
					if (!stack.back()->answers.empty())
						stack.back()->answers.back()->next_option = option;

					stack.push_back(option);
				}
				else if (tabs < stack_tabs) {
					// undo
					for (short i = tabs; i < stack_tabs; i++)
						stack.pop_back();

					// dopisane jak radził pekfos
					DialogueOption::DialogueAnswer* answer = new DialogueOption::DialogueAnswer(ConvertUtf8ToWide(line));
					answer->next_option = stack.front();
					stack.back()->answers.push_back(answer);
				}
			}


		}
		file.close();

		options.push_back(stack.back());

	}
};

/*
Dialogue* dialogue = new Dialogue(0);
DialogueOption* current_option = dialogue->options.front();

std::cout << "options: " << dialogue->options.size() << "\n";

while (true) {


	std::wstring text = current_option->text;
	text.erase(0, text.find_first_not_of(L'\t'));

	std::wcout << text.c_str() << L"\n";

	if (current_option->answers.empty()) {
		current_option = dialogue->options.front();
		continue;
	}

	for (auto& answer : current_option->answers) {
		std::wstring text = answer->text;
		text.erase(0, text.find_first_not_of(L'\t'));
		std::wcout << text << "\n";
	}

	std::wcout << "your answer: ";

	short choice = 0;
	std::cin >> choice;

	if (choice >= 0 && choice < current_option->answers.size()) {
		current_option = current_option->answers[choice]->next_option;
	}

	std::wcout << L"\n";
};
*/

std::vector < Dialogue* > dialogues;

Dialogue* getDialogue(int id) {
	for (auto& d : dialogues)
		if (d->id == id)
			return d;

	//wcout << L"incorrect dialog id: " << id << L"\n";
	return nullptr;
}

enum class DialogueState { Showing, Choosing, Answering, End};

/*
class DialogueBox {
public:
	DialogueState state;
	Dialogue* currentDialogue;
	short page;
	short lastPage;
	short chooseScroll;
	short chooseCursor;

	sf::Sprite background;
	sf::Text texts[5];

	std::vector < std::wstring > lines;
	std::vector < std::wstring > answers;

	short animationingLine;	// animation
	short animationingChar; // animation
	sf::Time animStart;

	DialogueBox(Dialogue* dialogue) {
		state = DialogueState::Showing;
		
		currentDialogue = dialogue;
		
		page = 0;
		lastPage = 0;

		chooseScroll = 0;
		chooseCursor = 0;

		background = sf::Sprite();
		background.setTexture(*getSingleTexture("GUI\\infoPanel")->texture);
		background.setOrigin(300, 75);
		background.setPosition(cam->position.x, cam->position.y+screenHeight/2.0f-75.0f);

		loadDialogueAndAnswers();

		for (int i = 0; i < 5;i++) {
			texts[i] = sf::Text();

			sf::Vector2f pos;
			pos.x = cam->position.x - 300 + 10;	// margin 10 
			pos.y = cam->position.y + screenHeight/2.0f - 150 + 10 + i * 24;

			texts[i].setPosition(pos);
			texts[i].setFont(basicFont);
			texts[i].setCharacterSize(24);
			texts[i].setFillColor(dialoguesColor);
		}

		animationingLine = 0;
		animationingChar = 0;
		animStart = currentTime;
	}

	void loadPage() {

		if (state == DialogueState::Showing) {
			for (int i = 0; i < 5; i++) {
				if (page * 5 + i < lines.size()) {
					
					if (page * 5 + i < animationingLine) {
						texts[i].setString(lines[page * 5 + i]);
					}
					else if (animationingLine == page * 5 + i) {
						
						std::wstring animText = lines[page * 5 + i].substr(0, animationingChar);
						
						if ((currentTime - animStart).asSeconds() > 0.025f) {
							//cout << (currentTime - animStart).asSeconds() << "\n";
							animationingChar += 1;

							if (animationingChar == lines[page * 5 + i].size()) {
								animationingChar = 0;
								animationingLine += 1;
							}

							animStart = currentTime;
						}

						texts[i].setString(animText);
					}
					else {
						texts[i].setString("");
					}

					texts[i].setFillColor(dialoguesColor);
					
				}
				else
					texts[i].setString("");
					
			}
		}

		if (state == DialogueState::Choosing) {
			for (int i = 0; i < 5; i++) {
				if (chooseScroll + i < answers.size()) {
					if(chooseCursor == i)
						texts[i].setFillColor(dialoguesActiveColor);
					else
						texts[i].setFillColor(dialoguesColor);
					texts[i].setString(answers[chooseScroll + i]);
				}
				else
					texts[i].setString("");
			}
		}
	}

	void loadDialogueAndAnswers() {

		short maxLineWidth = 600 - 2 * 10;
		lines = wrapText(currentDialogue->text, basicFont, 24, maxLineWidth);			
		lastPage = ceil(float(lines.size()) / 5.0f);

		answers.clear();
		for (auto& option : currentDialogue->options) {
			answers.push_back(option.text);
		}
	}

	void update(sf::Event& event) {
		if (event.type == sf::Event::KeyPressed) {

			if (state == DialogueState::Showing) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					if (animationingLine == lines.size()) {
						state = DialogueState::End;
						//cout << "konczymy dialog\n";
					}
					else if (animationingLine == (page+1) * 5) {
						page += 1;

						if (page == lastPage) {

							if (answers.size() > 0) {
								state = DialogueState::Choosing;
								chooseCursor = 0;
								chooseScroll = 0;
							}
							else {
								state = DialogueState::End;
								//cout << "konczymy dialog\n";
							}
								
						}
					}
					else {
						animationingLine = (page+1) * 5;
						animationingChar = 0;
						animStart = currentTime;
					}
	
				}
			}
			else if (state == DialogueState::Choosing) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					
					if(chooseCursor > 0 || chooseScroll > 0)
						chooseCursor -= 1;

					if (chooseCursor < 0) {
						
						chooseCursor = 0;
						chooseScroll -= 1;
					}

					loadPage();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					chooseCursor += 1;
					if (chooseScroll + chooseCursor >= answers.size()) {
						chooseCursor -= 1;
					}else if (chooseCursor > 4) {
						chooseCursor = 4;
						chooseScroll += 1;
					}

					loadPage();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					int selectedOption = chooseScroll + chooseCursor;
					currentDialogue = getDialogue(currentDialogue->options[selectedOption].nextDialogueID);
					
					if (currentDialogue != nullptr) {
						loadDialogueAndAnswers();
						state = DialogueState::Showing;
						animationingLine = 0;
						animationingChar = 0;
						animStart = currentTime;
						page = 0;
						loadPage();
					}
					else {
						state = DialogueState::End;
					}
						
					
				}
			}

		}

		background.setPosition(cam->position.x, cam->position.y + screenHeight / 2.0f - 75.0f);
	}

	void draw() {
		
		window->draw(background);

		loadPage();

		for (auto& text : texts)
			window->draw(text);
	}
};

DialogueBox* dialogueBox = nullptr;
*/


void loadDialogues() {
	dialogues.clear();

	dialogues.push_back(new Dialogue(0));
	dialogues.push_back(new Dialogue(1));
	dialogues.push_back(new Dialogue(2));
	dialogues.push_back(new Dialogue(3));
}
#endif