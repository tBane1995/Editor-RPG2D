#ifndef Dialogues_hpp
#define Dialogues_hpp

class DialogueOption {
public:
	std::wstring text;
	short nextDialogueID;

	DialogueOption(int nextDialogueID, std::wstring text) {
		this->nextDialogueID = nextDialogueID;
		this->text = text;
	}
};

class Dialogue {
public:
	short id;
	std::wstring text;
	std::vector < DialogueOption > options;

	Dialogue(short id, std::wstring text) {
		this->id = id;
		this->text = text;
	}
};

// TO-DO //////////////////////////////

std::vector < Dialogue* > dialogues;

Dialogue* getDialogue(short id) {
	for (auto& d : dialogues)
		if (d->id == id)
			return d;

	cout << "incorrect dialog id\n";
	return nullptr;
}

enum class DialogueState { Showing, Choosing, Answering, End};

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
		background.setTexture(*getSingleTexture("GUI/infoPanel")->texture);
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


void loadDialogue(int dialogID) {

	string textID = to_string(dialogID);

	while (textID.size() < 3)
		textID = "0" + textID;

	string filename = "dialogues/" + textID + ".txt";

	ifstream file(filename);
	if (!file.is_open()) {
		cout << "cant open dialogue " << filename << "\n";
		return;
	}

	string lineUTF8;
	getline(file, lineUTF8);
	std::istringstream lineStream(lineUTF8);

	string textPart;
	lineStream >> std::quoted(textPart);

	// stworzenie dialogu
	Dialogue* dial = new Dialogue(dialogID, ConvertUtf8ToWide(textPart));

	short id = -1;
	char comma;

	// wczytanie odpowiedzi do dialogu
	while (std::getline(file, lineUTF8)) {

		std::istringstream lineStream(lineUTF8);
		lineStream >> id >> comma;
		lineStream >> quoted(textPart);	// wczytywanie between cudzysłowami " "
		dial->options.push_back(DialogueOption(id, ConvertUtf8ToWide(textPart)));
	}

	// dodanie dialogu do listy wszystkich dialogow
	dialogues.push_back(dial);

	file.close();
}

void loadDialogues() {
	dialogues.clear();

	// LOADING THE DIALOGUES FROM FILES

	loadDialogue(0);	// WELCOME DIALOG

	loadDialogue(1);
	loadDialogue(2);
	loadDialogue(3);

	loadDialogue(4);
	loadDialogue(12);

	loadDialogue(5);
	loadDialogue(6);
	loadDialogue(7);
	loadDialogue(8);
	loadDialogue(9);
	loadDialogue(10);
	loadDialogue(11);
	loadDialogue(12);

	loadDialogue(13);
	loadDialogue(14);
	loadDialogue(15);

}
#endif