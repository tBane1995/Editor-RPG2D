#ifndef EditorStates_hpp
#define EditorStates_hpp

enum class EditorStates { Start, Close, 
	MapEditorInit, MapEditor,
	BuildingEditorInit, BuildingEditor,
	MeshEditorInit, MeshEditor
};

EditorStates editor_state = EditorStates::Start;

#endif;