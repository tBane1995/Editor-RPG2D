#ifndef EditorStates_hpp
#define EditorStates_hpp

enum class EditorStates { Start, Close, 
	MapEditorInit, MapEditor,
	BuildingEditorInit, BuildingEditor
};

EditorStates editor_state = EditorStates::Start;

#endif;