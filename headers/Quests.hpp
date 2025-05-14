#ifndef Quests_hpp
#define Quests_hpp

enum class questCondition { currentHP, showDialogue, haveArmor, haveHelmet, havePants, position, is_dressed };
enum class questState { unstarted, actual, ended };

class Step {
public:
	questCondition condition;
	string value;
	std::wstring text;

	Step(questCondition condition, string value, std::wstring text) {
		this->condition = condition;
		this->value = value;
		this->text = text;
	}

	bool check() {

		if (condition == questCondition::currentHP) {
			if(player->HP >= atoi(value.c_str()))
				return true;
		}

		if (condition == questCondition::showDialogue) {
			//setDialogue(atoi(value.c_str()));
			return true;
		}

		if (condition == questCondition::haveArmor) {
			if (value == "true") {
				if (player->armor != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->armor == nullptr)
					return true;
			}
		}

		if (condition == questCondition::haveHelmet) {
			if (value == "true") {
				if (player->helmet != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->helmet == nullptr)
					return true;
			}
		}

		if (condition == questCondition::havePants) {
			if (value == "true") {
				if (player->pants != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->pants == nullptr)
					return true;
			}
		}

		if (condition == questCondition::position)
		{
			std::istringstream iss(value);
			short pos_x, pos_y;

			iss >> pos_x >> pos_y;

			if (abs(player->position.x - pos_x) < 50 && abs(player->position.y - pos_y) < 50)
				return true;
		}

		if (condition == questCondition::is_dressed)
		{
			if (player->armor != nullptr && player->pants != nullptr) {
				return true;
			}
		}

		return false;
	}

};

class Quest {
public:
	short id;
	std::wstring name;
	questState state;
	std::vector < Step* > steps;
	short currentStep;

	Quest(short id, std::wstring name) {
		
		this->id = id;
		this->name = name;
		steps.clear();
		state = questState::unstarted;
		currentStep = 0;

	}
	
	void addStep(questCondition condition, string value, std::wstring text) {
		Step* step = new Step(condition, value, text);
		steps.push_back(step);
	}

	void check() {

		if (currentStep >= steps.size() - 1)
			state = questState::ended;

		if (steps[currentStep]->check())
			currentStep++;
		
	}


};

std::vector < Quest* > quests;

void loadQuests() {
	quests.clear();

	Quest* quest;

	quest = new Quest(0, L"Jeść!");
	quest->addStep(questCondition::currentHP, "40", L"jestem głodny, powinienem coś zjeść. W tej chacie pewnie znajdzie się jakieś pożywienie.");
	quest->addStep(questCondition::showDialogue, "13", L"Nie ma to jak się dobrze najeść");
	quests.push_back(quest);

	quest = new Quest(1, L"Ubranie!");
	quest-> addStep(questCondition::is_dressed, "true", L"powinienem się w coś ubrać");
	quest->addStep(questCondition::showDialogue, "14", L"Ubralem się. Przynajmniej nie wyglądam jak obdartus.");
	quests.push_back(quest);

	quest = new Quest(2, L"Wzdłóż ścieżki");
	quest->addStep(questCondition::position, "4100 650", L"Powinienem sprawdzić dokąd zaprowadzi mnie ta ścieżka.");
	quest->addStep(questCondition::showDialogue, "15", L"ścieżka się skończyła, jak na razie nic więcej nie wymyślę.");
	quests.push_back(quest);

	quests[0]->state = questState::actual;
	quests[1]->state = questState::actual;
	quests[2]->state = questState::actual;

}

void checkQuests() {

	for (auto& quest : quests) {

		if (quest->state == questState::actual) {
			quest->check();

		}

	}

}


#endif