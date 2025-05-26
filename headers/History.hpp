#ifndef History_hpp
#define History_hpp

class ActionHistory {
public:

	class Action {
	public:
		std::vector < GameObject* > objects;

		Action() { }
		~Action() { }
		virtual void undo() { }
		virtual void redo() { }

	};

	class Move : public Action {
	public:
		Move() : Action() { }
		~Move() { }
		virtual void undo() { }
		virtual void redo() { }
	};

	std::vector < Action* > actions;

	ActionHistory() {

	}

	~ActionHistory() {

	}

	void addAction(Action* action) {

	}

	void undo() {

	}

	void redo() {

	}
};

#endif // ! History_hpp
