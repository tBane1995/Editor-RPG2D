#ifndef JournalPanel_hpp
#define JournalPanel_hpp

class JournalPanel {
public:

	sf::Sprite panel;
	std::vector < sf::Text > titles;
	sf::Text description;

	JournalPanel() {
		panel = sf::Sprite();
		panel.setTexture(*getSingleTexture(L"GUI\\bigPanel")->texture);
		panel.setOrigin(300, 200);

		description = sf::Text();
		description.setFont(basicFont);
		description.setFillColor(dialoguesColor);
		description.setCharacterSize(18);
	}

	void update() {

		panel.setPosition(cam->position);
		  
		// TITLES OF QUESTS
		std::vector < Quest* > actualQuests;
		actualQuests.clear();
		for (auto& quest : quests)
			if (quest->state == questState::actual)
				actualQuests.push_back(quest);

		titles.clear();
		for (short i = 0; i < 18; i++) {
			titles.push_back(sf::Text());
			titles[i].setFont(basicFont);
			titles[i].setFillColor((i == cursor) ? dialoguesActiveColor : dialoguesColor);
			titles[i].setCharacterSize(18);
			titles[i].setPosition(cam->position.x - 280, cam->position.y + (20 * i) - 180);
			titles[i].setString((i < actualQuests.size()) ? actualQuests[i]->name : L"-");
		}
		

		// DESCRIPTION OF QUEST
		description.setPosition(cam->position.x-100, cam->position.y-180);
		std::vector < std::wstring > descriptionLines = wrapText((cursor < actualQuests.size()) ? actualQuests[cursor]->steps[actualQuests[cursor]->currentStep]->text : L"-",basicFont, 18, 490);
		
		std::wstring descriptionText = L"";

		for (short i = 0; i < descriptionLines.size(); i++)
			descriptionText += descriptionLines[i] + L"\n";

		description.setString(descriptionText);

	}

	void draw() {

		window->draw(panel);

		for (auto& title : titles)
			window->draw(title);

		window->draw(description);
	}

};

JournalPanel* journal = nullptr;

#endif