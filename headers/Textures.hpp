#ifndef Textures_hpp
#define Textures_hpp

using namespace std;

bool areImagesEqual(sf::Image& img1, sf::Image& img2) {
	if (img1.getSize() != img2.getSize()) {
		return false; // Rozmiary są różne
	}

	
	// Porównaj każdy piksel
	for (unsigned int y = 0; y < img1.getSize().y; y++) {
		for (unsigned int x = 0; x < img1.getSize().x; x++) {
			if (img1.getPixel(x, y) != img2.getPixel(x, y)) {
				return false; // Piksele są różne
			}
		}
	}
	return true; // Wszystkie piksele są identyczne

}

void save_texture(std::ofstream& packet, std::wstring pathfile, uint16_t cx, uint16_t cy) {
	std::ifstream file(L"assets\\" + pathfile + L".png", std::ios::binary);

	if (!file) {
		std::wcout << L"Nie można otworzyć pliku: " << L"assets\\" + pathfile + L".png" << L"\n";
		return;
	}

	std::wstring filename = pathfile;
	//cout << filename << "\n";

	uint8_t nameLength = filename.size();

	file.seekg(0, std::ios::end);
	uint32_t fileSize = file.tellg();
	file.seekg(0);

	std::vector < char > buffer(fileSize);
	file.read(buffer.data(), fileSize);

	uint8_t type = 0;

	// save the data
	packet.write(reinterpret_cast <char*>(&nameLength), sizeof(nameLength)); // 1 bajt
	packet.write(ConvertWideToUtf8(filename).c_str(), nameLength); // N bajtów
	packet.write(reinterpret_cast <char*>(&type), sizeof(uint8_t)); // 0 if texture (no set)
	packet.write(reinterpret_cast <char*>(&cx), sizeof(cx));
	packet.write(reinterpret_cast <char*>(&cy), sizeof(cy));
	packet.write(reinterpret_cast <char*>(&fileSize), sizeof(fileSize)); // 4 bajty
	packet.write(buffer.data(), fileSize); // X bajtów

	//std::cout << "zapisano teksture: " << filename << "\n";

	file.close();
}

void save_set(std::ofstream& packet, std::wstring pathfile, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
	std::ifstream file(L"assets\\" + pathfile + L".png", std::ios::binary);

	if (!file) {
		std::wcout << L"Nie można otworzyć pliku: " << L"assets\\" + pathfile + L".png" << L"\n";
		return;
	}

	std::wstring filename = pathfile;
	//cout << filename << "\n";

	uint8_t nameLength = filename.size();

	file.seekg(0, std::ios::end);
	uint32_t fileSize = file.tellg();
	file.seekg(0);

	std::vector < char > buffer(fileSize);
	file.read(buffer.data(), fileSize);

	uint8_t type = 1;

	// save the data
	packet.write(reinterpret_cast <char*>(&nameLength), sizeof(nameLength)); // 1 bajt
	packet.write(ConvertWideToUtf8(filename).c_str(), nameLength); // N bajtów
	packet.write(reinterpret_cast <char*>(&type), sizeof(uint8_t));
	packet.write(reinterpret_cast <char*>(&width), sizeof(width));
	packet.write(reinterpret_cast <char*>(&height), sizeof(height));
	packet.write(reinterpret_cast <char*>(&cx), sizeof(cx));
	packet.write(reinterpret_cast <char*>(&cy), sizeof(cy));
	packet.write(reinterpret_cast <char*>(&fileSize), sizeof(fileSize)); // 4 bajty
	packet.write(buffer.data(), fileSize); // X bajtów

	//std::cout << "zapisano set: " << filename << "\n";

	file.close();
}

void save_animation(std::ofstream& packet, std::wstring pathfile, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
	std::ifstream file(L"assets\\" + pathfile + L".png", std::ios::binary);

	if (!file) {
		std::wcout << L"Nie można otworzyć pliku: " << L"assets\\" + pathfile + L".png" << L"\n";
		return;
	}

	std::wstring filename = pathfile;
	//cout << filename << "\n";

	uint8_t nameLength = filename.size();

	file.seekg(0, std::ios::end);
	uint32_t fileSize = file.tellg();
	file.seekg(0);

	std::vector < char > buffer(fileSize);
	file.read(buffer.data(), fileSize);

	uint8_t type = 2;

	// save the data
	packet.write(reinterpret_cast <char*>(&nameLength), sizeof(nameLength)); // 1 bajt
	packet.write(ConvertWideToUtf8(filename).c_str(), nameLength); // N bajtów
	packet.write(reinterpret_cast <char*>(&type), sizeof(uint8_t));
	packet.write(reinterpret_cast <char*>(&width), sizeof(width));
	packet.write(reinterpret_cast <char*>(&height), sizeof(height));
	packet.write(reinterpret_cast <char*>(&cx), sizeof(cx));
	packet.write(reinterpret_cast <char*>(&cy), sizeof(cy));
	packet.write(reinterpret_cast <char*>(&fileSize), sizeof(fileSize)); // 4 bajty
	packet.write(buffer.data(), fileSize); // X bajtów

	//std::cout << "zapisano animacje: " << filename << "\n";

	file.close();
}

class Texture_To_Save {
public:

	std::wstring name;
	uint16_t cx;
	uint16_t cy;

	Texture_To_Save(std::wstring name, uint16_t cx, uint16_t cy) {
		this->name = name;
		this->cx = cx;
		this->cy = cy;
	}
};

class Set_To_Save {
public:
	std::wstring name;
	uint16_t width, height;
	uint16_t cx, cy;

	Set_To_Save(std::wstring name, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
		this->name = name;
		this->width = width;
		this->height = height;
		this->cx = cx;
		this->cy = cy;

	}
};

std::vector < Texture_To_Save* > unique_terrains_and_walls_textures_to_save;
std::vector < Texture_To_Save* > textures_to_save;
std::vector < Set_To_Save* > sets_to_save;
std::vector < Set_To_Save* > animations_to_save;
uint32_t textures_count = 0;

void add_Unique_Terrains_And_Walls_Textures_To_Save(std::wstring name, uint16_t cx, uint16_t cy) {
	unique_terrains_and_walls_textures_to_save.push_back(new Texture_To_Save(name, cx, cy));
	textures_count += 1;
}

void add_Texture_To_Save(std::wstring name, uint16_t cx, uint16_t cy) {
	textures_to_save.push_back(new Texture_To_Save(name, cx, cy));
	textures_count += 1;
}

void add_Set_To_Save(std::wstring name, uint16_t tile_width, uint16_t tile_height, uint16_t cx, uint16_t cy) {
	sets_to_save.push_back(new Set_To_Save(name, tile_width, tile_height, cx, cy));
	textures_count += 1;
}

void add_Animation_To_Save(std::wstring name, uint16_t tile_width, uint16_t tile_height, uint16_t cx, uint16_t cy) {
	animations_to_save.push_back(new Set_To_Save(name, tile_width, tile_height, cx, cy));
	textures_count += 1;
}

void save_textures_as_packet() {

	// noise
	add_Texture_To_Save(L"noise", 256, 256);
	add_Texture_To_Save(L"noise2", 256, 256);
	add_Texture_To_Save(L"empty", 32, 32);

	// GUI
	add_Texture_To_Save(L"GUI\\slot1", 40, 40);
	add_Texture_To_Save(L"GUI\\slot2", 32, 32);
	add_Texture_To_Save(L"GUI\\selector", 40, 40);

	add_Texture_To_Save(L"GUI\\corner", 4, 4);
	add_Texture_To_Save(L"GUI\\border_horizontal", 3, 3);
	add_Texture_To_Save(L"GUI\\border_vertical", 3, 3);

	add_Texture_To_Save(L"GUI\\infoPanel", 300, 75);
	add_Texture_To_Save(L"GUI\\bigPanel", 300, 200);

	add_Texture_To_Save(L"GUI\\wideArrowUp1", 80, 20);
	add_Texture_To_Save(L"GUI\\wideArrowUp2", 80, 20);
	add_Texture_To_Save(L"GUI\\wideArrowDown1", 160, 18.5f);
	add_Texture_To_Save(L"GUI\\wideArrowDown2", 160, 18.5f);

	// group buttons textures
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton_to_left", 17, 52);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton_to_right", 17, 52);

	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-terrain", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-highlands", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-floors", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-water", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-furnitures", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-walls", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-monsters", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-flat_objects", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-items", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-natures", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-smallObjects", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-objects", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-buildings", 34, 26);
	add_Texture_To_Save(L"GUI\\groupButtons\\groupButton-directions", 34, 26);

	// small buttons textures
	add_Texture_To_Save(L"GUI\\smallButtons\\smallbutton", 20, 20);
	add_Texture_To_Save(L"GUI\\smallButtons\\smallbutton-ArrowUp", 20, 20);
	add_Texture_To_Save(L"GUI\\smallButtons\\smallbutton-ArrowDown", 20, 20);
	add_Texture_To_Save(L"GUI\\smallButtons\\smallbutton-ArrowLeft", 20, 20);
	add_Texture_To_Save(L"GUI\\smallButtons\\smallbutton-ArrowRight", 20, 20);

	// tool butttons textures
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-cursor", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-brush", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-rect_brush", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-increase", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-decrease", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-rectangle", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-elipse", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-fill", 20, 16);
	add_Texture_To_Save(L"GUI\\toolButtons\\toolbutton-eraser", 20, 16);

	// space
	add_Texture_To_Save(L"GUI\\spacebutton", 80, 20);

	// scrollbar textures
	add_Texture_To_Save(L"GUI\\scrollbar_16\\bar_bottom", 8, 8);
	add_Texture_To_Save(L"GUI\\scrollbar_16\\bar_top", 8, 8);
	add_Texture_To_Save(L"GUI\\scrollbar_16\\bar_center", 8, 8);
	add_Texture_To_Save(L"GUI\\scrollbar_16\\scroll_bottom", 8, 8);
	add_Texture_To_Save(L"GUI\\scrollbar_16\\scroll_top", 8, 8);
	add_Texture_To_Save(L"GUI\\scrollbar_16\\scroll_center", 8, 8);

	add_Texture_To_Save(L"GUI\\scrollbar_20\\bar_bottom", 10, 10);
	add_Texture_To_Save(L"GUI\\scrollbar_20\\bar_top", 10, 10);
	add_Texture_To_Save(L"GUI\\scrollbar_20\\bar_center", 10, 10);
	add_Texture_To_Save(L"GUI\\scrollbar_20\\scroll_bottom", 10, 10);
	add_Texture_To_Save(L"GUI\\scrollbar_20\\scroll_top", 10, 10);
	add_Texture_To_Save(L"GUI\\scrollbar_20\\scroll_center", 10, 10);

	// checkbox textures
	add_Texture_To_Save(L"GUI\\checkbox\\check", 8, 8);

	// interactions textures
	add_Texture_To_Save(L"GUI\\hand", 8, 8);
	add_Texture_To_Save(L"GUI\\grey_hand", 8, 8);
	add_Texture_To_Save(L"GUI\\talk", 8, 8);

	// icons texture
	add_Texture_To_Save(L"GUI\\icons\\MapEditor_small_ico", 15, 15);
	add_Texture_To_Save(L"GUI\\icons\\dictionary", 15, 15);
	add_Texture_To_Save(L"GUI\\icons\\file", 15, 15);
	add_Texture_To_Save(L"GUI\\icons\\empty", 15, 15);

	// context menu textures
	add_Texture_To_Save(L"GUI\\context_menu\\btn_default", 15, 15);
	add_Texture_To_Save(L"GUI\\context_menu\\btn_info", 15, 15);
	add_Texture_To_Save(L"GUI\\context_menu\\btn_edit", 15, 15);
	add_Texture_To_Save(L"GUI\\context_menu\\btn_remove", 15, 15);
	add_Texture_To_Save(L"GUI\\context_menu\\btn_cancel", 15, 15);

	// character mnenu textures
	add_Texture_To_Save(L"GUI\\character_menu\\menu_sider_left", 4, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_sider_right", 4, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_slot", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_statistics", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_layout", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_equipment", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_inventory", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_dialogues", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\menu_quests", 32, 20);
	add_Texture_To_Save(L"GUI\\character_menu\\layout_slot", 40, 40);
	add_Texture_To_Save(L"GUI\\character_menu\\item_slot", 32, 32);
	add_Texture_To_Save(L"GUI\\character_menu\\direction_top", 32, 32);
	add_Texture_To_Save(L"GUI\\character_menu\\direction_bottom", 32, 32);
	add_Texture_To_Save(L"GUI\\character_menu\\direction_left", 32, 32);
	add_Texture_To_Save(L"GUI\\character_menu\\direction_right", 32, 32);
	add_Texture_To_Save(L"GUI\\character_menu\\dialogue_prev", 16, 16);
	add_Texture_To_Save(L"GUI\\character_menu\\dialogue_next", 16, 16);
	add_Texture_To_Save(L"GUI\\character_menu\\value_less", 6, 11);
	add_Texture_To_Save(L"GUI\\character_menu\\value_more", 6, 11);

	// bbuilding editor 
	add_Texture_To_Save(L"GUI\\building_editor_side_menu\\reset_camera", 24, 24);

	// tiles textures
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\0_tileset", 0, 0);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_0_water", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_1_sands", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_2_grass", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_3_gravel", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_4_steps", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_5_highlands", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_6", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_7", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_8", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_9", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"tiles\\tile_10", 32, 32);

	// tiles sets
	add_Set_To_Save(L"tiles\\set_0_water_sands", 64, 64, 32, 32);
	add_Set_To_Save(L"tiles\\set_0_sands_water", 64, 64, 32, 32);
	add_Set_To_Save(L"tiles\\set_1_sands_grass", 64, 64, 32, 32);
	add_Set_To_Save(L"tiles\\set_1_grass_sands", 64, 64, 32, 32);
	add_Set_To_Save(L"tiles\\set_2_grass_gravel", 64, 64, 32, 32);
	add_Set_To_Save(L"tiles\\set_2_gravel_grass", 64, 64, 32, 32);

	// floors
	add_Texture_To_Save(L"floors\\0_floorset", 0, 0);
	add_Texture_To_Save(L"floors\\floor_0", 32, 32);
	add_Texture_To_Save(L"floors\\floor_1", 32, 32);
	add_Texture_To_Save(L"floors\\floor_2", 32, 32);
	add_Texture_To_Save(L"floors\\floor_3", 32, 32);
	add_Texture_To_Save(L"floors\\floor_4", 32, 32);
	add_Texture_To_Save(L"floors\\floor_5", 32, 32);

	// highlands textures
	add_Set_To_Save(L"highlands\\low_highlands", 64, 64, 32, 32);
	add_Set_To_Save(L"highlands\\high_highlands", 64, 64, 32, 32);

	// natures
	add_Texture_To_Save(L"natures\\tree9", 129, 213);
	add_Texture_To_Save(L"natures\\bush_1", 32, 44);
	add_Texture_To_Save(L"natures\\stump_1", 62, 90);
	add_Texture_To_Save(L"natures\\boulder_1", 66, 72);
	add_Texture_To_Save(L"natures\\boulder_2", 65, 78);
	add_Texture_To_Save(L"natures\\boulder_3", 60, 80);

	add_Texture_To_Save(L"natures\\column_2", 65, 85);
	add_Texture_To_Save(L"natures\\column_3", 65, 85);
	add_Texture_To_Save(L"natures\\stone_altar", 65, 85);
	add_Texture_To_Save(L"natures\\stone_platform", 65, 78);
	add_Texture_To_Save(L"natures\\driftwood", 59, 77);
	add_Texture_To_Save(L"natures\\rock_1", 32, 36);
	add_Texture_To_Save(L"natures\\rock_2", 32, 36);
	add_Texture_To_Save(L"natures\\reed_1", 32, 54);
	add_Texture_To_Save(L"natures\\reed_2", 32, 54);

	// small objects textures
	add_Texture_To_Save(L"smallObjects\\grass_1", 33, 32);
	add_Texture_To_Save(L"smallObjects\\grass_2", 33, 32);
	add_Texture_To_Save(L"smallObjects\\grass_3", 33, 32);

	// objects textures
	add_Texture_To_Save(L"objects\\palisade_1", 16, 112);
	add_Texture_To_Save(L"objects\\palisade_2", 16, 112);
	add_Texture_To_Save(L"objects\\stone_wall", 8, 56);
	add_Texture_To_Save(L"objects\\great_stone_wall", 16, 112);
	add_Texture_To_Save(L"objects\\well", 64, 96);
	add_Texture_To_Save(L"objects\\hunter_tent", 128, 175);
	add_Texture_To_Save(L"objects\\log_with_saw", 64, 70);
	add_Texture_To_Save(L"objects\\pile_of_wood_1", 64, 80);
	add_Texture_To_Save(L"objects\\pile_of_wood_2", 64, 80);
	add_Texture_To_Save(L"objects\\stone_altar_1", 66, 66);
	add_Texture_To_Save(L"objects\\wooden_stake_1", 34, 44);

	add_Animation_To_Save(L"objects\\brazier", 64, 64, 32, 40);

	// flat objects textures
	add_Texture_To_Save(L"flatObjects\\path_1", 32, 32);
	add_Texture_To_Save(L"flatObjects\\path_2", 32, 32);
	add_Texture_To_Save(L"flatObjects\\stonepath_1", 32, 32);
	add_Texture_To_Save(L"flatObjects\\stonepath_2", 32, 32);
	add_Texture_To_Save(L"flatObjects\\sandspath_1", 32, 32);
	add_Texture_To_Save(L"flatObjects\\sandspath_2", 32, 32);

	add_Texture_To_Save(L"flatObjects\\herb_1", 33, 32);
	add_Texture_To_Save(L"flatObjects\\herb_2", 33, 32);

	add_Texture_To_Save(L"flatObjects\\small_rock_1", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_rock_2", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_rock_3", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_rock_4", 16, 16);

	add_Texture_To_Save(L"flatObjects\\small_sands_rock_1", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_sands_rock_2", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_sands_rock_3", 16, 16);
	add_Texture_To_Save(L"flatObjects\\small_sands_rock_4", 16, 16);

	// spells textures
	add_Animation_To_Save(L"spells\\fireball", 32, 32, 16, 16);
	add_Animation_To_Save(L"spells\\water_cone", 32, 32, 16, 16);
	add_Animation_To_Save(L"spells\\magic_circle", 64, 64, 32, 32);

	// doors textures
	add_Texture_To_Save(L"doors\\wooden_door[0]", 32, 63);
	add_Texture_To_Save(L"doors\\wooden_door[1]", 32, 63);
	add_Texture_To_Save(L"doors\\wooden_door[2]", 32, 63);
	add_Texture_To_Save(L"doors\\wooden_door[3]", 32, 63);

	add_Texture_To_Save(L"doors\\wooden_gate[0]", 64, 127);
	add_Texture_To_Save(L"doors\\wooden_gate[1]", 64, 127);
	add_Texture_To_Save(L"doors\\wooden_gate[2]", 64, 127);
	add_Texture_To_Save(L"doors\\wooden_gate[3]", 64, 127);

	add_Texture_To_Save(L"doors\\great_stone_gate[0]", 64, 127);
	add_Texture_To_Save(L"doors\\great_stone_gate[1]", 64, 127);
	add_Texture_To_Save(L"doors\\great_stone_gate[2]", 64, 127);
	add_Texture_To_Save(L"doors\\great_stone_gate[3]", 64, 127);

	// furnitures textures
	add_Texture_To_Save(L"furnitures\\table", 32, 32);
	add_Texture_To_Save(L"furnitures\\table_alchemist", 32, 32);
	add_Texture_To_Save(L"furnitures\\table_alchemist_2", 32, 32);
	add_Texture_To_Save(L"furnitures\\table_herbalist", 32, 32);
	add_Texture_To_Save(L"furnitures\\table_herbalist_2", 32, 32);
	add_Texture_To_Save(L"furnitures\\stone_table_1", 32, 32);
	add_Texture_To_Save(L"furnitures\\bench", 32, 32);
	add_Texture_To_Save(L"furnitures\\stone_bench_1", 32, 32);
	add_Texture_To_Save(L"furnitures\\chest", 32, 32);
	add_Texture_To_Save(L"furnitures\\wardrobe", 32, 50);
	add_Texture_To_Save(L"furnitures\\bookshelf", 32, 50);
	add_Texture_To_Save(L"furnitures\\bookshelf_2", 32, 50);
	add_Texture_To_Save(L"furnitures\\furnace", 32, 50);
	add_Texture_To_Save(L"furnitures\\bed", 32, 50);
	add_Texture_To_Save(L"furnitures\\chair", 34, 38);
	add_Texture_To_Save(L"furnitures\\barrel", 34, 38);
	add_Texture_To_Save(L"furnitures\\shield_1", 32, 32);
	add_Texture_To_Save(L"furnitures\\shield_2", 32, 32);
	add_Texture_To_Save(L"furnitures\\shield_3", 32, 32);
	add_Texture_To_Save(L"furnitures\\lectern", 34, 38);

	// walls textures
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\empty_wall", 16, 16);

	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\mud_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\stone_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\wooden_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\brick_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\mulch_wall", 16, 16);

	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\mud_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\stone_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\wooden_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\brick_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save(L"walls\\mulch_wall_overgrown", 16, 16);


	add_Set_To_Save(L"walls\\set_mud_wall", 32, 32, 16, 16);
	add_Set_To_Save(L"walls\\set_stone_wall", 32, 32, 16, 16);
	add_Set_To_Save(L"walls\\set_wooden_wall", 32, 32, 16, 16);
	add_Set_To_Save(L"walls\\set_brick_wall", 32, 32, 16, 16);
	add_Set_To_Save(L"walls\\set_mulch_wall", 32, 32, 16, 16);

	// fortifications textures

	// buildings parts textures

	add_Texture_To_Save(L"buildings\\parts\\tile_left", 8, 8);
	add_Texture_To_Save(L"buildings\\parts\\tile_left_top", 8, 4);
	add_Texture_To_Save(L"buildings\\parts\\tile_left_bottom", 8, 4);
	add_Texture_To_Save(L"buildings\\parts\\tile_right", 8, 8);
	add_Texture_To_Save(L"buildings\\parts\\tile_right_top", 8, 4);
	add_Texture_To_Save(L"buildings\\parts\\tile_right_bottom", 8, 4);
	add_Texture_To_Save(L"buildings\\parts\\tile_center", 8, 8);
	add_Texture_To_Save(L"buildings\\parts\\tile_center_top", 8, 4);
	add_Texture_To_Save(L"buildings\\parts\\tile_center_bottom", 8, 4);

	add_Texture_To_Save(L"buildings\\parts\\window", 16, 16);
	add_Texture_To_Save(L"buildings\\parts\\window_2", 16, 16);
	add_Texture_To_Save(L"buildings\\parts\\bar", 32, 5);

	// items textures
	add_Texture_To_Save(L"items\\inventory", 28, 48);

	// bows
	add_Texture_To_Save(L"items\\bow", 32, 32);

	// weapons items
	add_Texture_To_Save(L"items\\club", 32, 32);
	add_Texture_To_Save(L"items\\knife", 32, 32);
	add_Texture_To_Save(L"items\\hatchet", 32, 32);
	add_Texture_To_Save(L"items\\sword", 32, 32);
	add_Texture_To_Save(L"items\\dagger", 32, 32);
	add_Texture_To_Save(L"items\\wooden club", 32, 32);
	add_Texture_To_Save(L"items\\long sword", 32, 32);
	add_Texture_To_Save(L"items\\curved sword", 32, 32);
	add_Texture_To_Save(L"items\\wide blade", 32, 32);
	add_Texture_To_Save(L"items\\gladius", 32, 32);
	add_Texture_To_Save(L"items\\iron club", 32, 32);
	add_Texture_To_Save(L"items\\axe", 32, 32);
	add_Texture_To_Save(L"items\\stone hammer", 32, 32);

	// helmets items
	add_Texture_To_Save(L"items\\skin helmet", 32, 32);
	add_Texture_To_Save(L"items\\wool hat", 32, 32);

	// armors items
	add_Texture_To_Save(L"items\\plate armor", 32, 32);
	add_Texture_To_Save(L"items\\chain mail", 32, 32);
	add_Texture_To_Save(L"items\\skin jacket", 32, 32);
	add_Texture_To_Save(L"items\\mage's robe", 32, 32);
	add_Texture_To_Save(L"items\\gray apron", 32, 32);
	add_Texture_To_Save(L"items\\torn shirt", 32, 32);
	add_Texture_To_Save(L"items\\wool shirt", 32, 32);

	// pants items
	add_Texture_To_Save(L"items\\chain mail pants", 32, 32);
	add_Texture_To_Save(L"items\\skin pants", 32, 32);
	add_Texture_To_Save(L"items\\wool pants", 32, 32);

	// shields items
	add_Texture_To_Save(L"items\\shield", 32, 32);	// TO-DO to delete

	// herbs items
	add_Texture_To_Save(L"items\\mana plant", 30, 50);
	add_Texture_To_Save(L"items\\health herb", 32, 34);
	add_Texture_To_Save(L"items\\health root", 31, 46);
	add_Texture_To_Save(L"items\\health plant", 30, 44);
	add_Texture_To_Save(L"items\\mushroom", 30, 44);

	// potions items
	add_Texture_To_Save(L"items\\potion", 32, 32);

	// food items
	add_Texture_To_Save(L"items\\raw meat", 32, 32);
	add_Texture_To_Save(L"items\\roasted meat", 32, 32);

	// other items
	add_Texture_To_Save(L"items\\bone", 32, 32);
	add_Texture_To_Save(L"items\\bone", 40, 40);
	add_Texture_To_Save(L"items\\tooth", 32, 32);
	add_Texture_To_Save(L"items\\spike", 32, 32);
	add_Texture_To_Save(L"items\\wolf skin", 32, 32);


	// items sets
	std::vector < std::wstring > itemSets;
	itemSets.push_back(L"skin pants");
	itemSets.push_back(L"skin helmet");
	itemSets.push_back(L"wool hat");
	itemSets.push_back(L"wool pants");
	itemSets.push_back(L"wooden club");
	itemSets.push_back(L"axe");
	itemSets.push_back(L"club");
	itemSets.push_back(L"iron club");
	itemSets.push_back(L"stone hammer");
	itemSets.push_back(L"sword");
	itemSets.push_back(L"long sword");
	itemSets.push_back(L"gladius");
	itemSets.push_back(L"wide blade");
	itemSets.push_back(L"knife");
	itemSets.push_back(L"dagger");
	itemSets.push_back(L"hatchet");
	itemSets.push_back(L"curved sword");
	itemSets.push_back(L"chain mail pants");
	itemSets.push_back(L"shield");
	itemSets.push_back(L"bow");

	for (auto& set : itemSets) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackLeft" + to_wstring(i), 32, 58);
		}
	}

	std::vector < std::wstring > armorSets;
	armorSets.push_back(L"skin jacket");
	armorSets.push_back(L"torn shirt");
	armorSets.push_back(L"mage's robe");
	armorSets.push_back(L"gray apron");
	armorSets.push_back(L"wool shirt");
	armorSets.push_back(L"chain mail");
	armorSets.push_back(L"plate armor");

	for (auto& set : armorSets) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\idleLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\runLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\attackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\bowAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\bowAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\bowAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\bowAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicBuffTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicBuffRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicBuffBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\items\\" + set + L"\\magicBuffLeft" + to_wstring(i), 32, 58);

		}
	}

	// monsters sets
	std::vector < std::wstring > monsters;
	monsters.push_back(L"dziobak");
	monsters.push_back(L"goblin");
	monsters.push_back(L"wilczur");
	monsters.push_back(L"jaszczur");
	monsters.push_back(L"niedzwiedz");
	monsters.push_back(L"szpon");
	monsters.push_back(L"kolcorozec");
	monsters.push_back(L"golem");
	monsters.push_back(L"troll");
	monsters.push_back(L"bies");

	for (auto& m : monsters) {
		for (short i = 0; i < 4; i++) {

			add_Texture_To_Save(L"monsters\\" + m, 63, 87);

			add_Texture_To_Save(L"monsters\\" + m + L"\\idleTop" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\idleRight" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\idleBottom" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\idleLeft" + to_wstring(i), 63, 87);

			add_Texture_To_Save(L"monsters\\" + m + L"\\attackTop" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\attackRight" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\attackBottom" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\attackLeft" + to_wstring(i), 63, 87);

			add_Texture_To_Save(L"monsters\\" + m + L"\\runTop" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\runRight" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\runBottom" + to_wstring(i), 63, 87);
			add_Texture_To_Save(L"monsters\\" + m + L"\\runLeft" + to_wstring(i), 63, 87);

		}
	}

	// body sets
	std::vector < std::wstring > bodies;
	bodies.push_back(L"man");
	bodies.push_back(L"woman");

	for (auto& set : bodies) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\idleTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\idleRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\idleBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\idleLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\body\\" + set + L"\\runTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\runRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\runBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\runLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\body\\" + set + L"\\attackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\attackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\attackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\attackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\body\\" + set + L"\\bowAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\bowAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\bowAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\bowAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicBuffTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicBuffRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicBuffBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\body\\" + set + L"\\magicBuffLeft" + to_wstring(i), 32, 58);

		}
	}

	// head sets
	std::vector < std::wstring > heads;
	heads.push_back(L"man-black-haired");
	heads.push_back(L"boy-black-haired");
	heads.push_back(L"woman-black-haired");

	heads.push_back(L"man-brown-haired");
	heads.push_back(L"boy-brown-haired");
	heads.push_back(L"woman-brown-haired");

	heads.push_back(L"man-gray-haired");
	heads.push_back(L"boy-gray-haired");
	heads.push_back(L"woman-gray-haired");

	heads.push_back(L"man-red-haired");
	heads.push_back(L"boy-red-haired");
	heads.push_back(L"woman-red-haired");

	for (auto& set : heads) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\idleTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\idleRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\idleBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\idleLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\head\\" + set + L"\\runTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\runRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\runBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\runLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\head\\" + set + L"\\attackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\attackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\attackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\attackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\head\\" + set + L"\\bowAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\bowAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\bowAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\bowAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicAttackTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicAttackRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicAttackBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicAttackLeft" + to_wstring(i), 32, 58);

			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicBuffTop" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicBuffRight" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicBuffBottom" + to_wstring(i), 32, 58);
			add_Texture_To_Save(L"sets\\head\\" + set + L"\\magicBuffLeft" + to_wstring(i), 32, 58);

		}
	}
	//////////////////////////////////////////////////////////////////////////

	std::ofstream packet("assets\\atex.assets", std::ios::binary);
	packet.write(reinterpret_cast <char*>(&textures_count), sizeof(textures_count));

	for (auto& ter : unique_terrains_and_walls_textures_to_save) {
		save_texture(packet, ter->name, ter->cx, ter->cy);
	}

	for (auto& set : sets_to_save) {
		save_set(packet, set->name, set->width, set->height, set->cx, set->cy);
	}

	for (auto& anim : animations_to_save) {
		save_animation(packet, anim->name, anim->width, anim->height, anim->cx, anim->cy);
	}

	for (auto& tex : textures_to_save) {
		save_texture(packet, tex->name, tex->cx, tex->cy);
	}

	packet.close();
}

class SingleTexture {
public:
	std::wstring name;
	float cx, cy;	// coordinates of center on the texture
	sf::Texture* texture = nullptr;

	SingleTexture(std::wstring pathfile, float cx, float cy) {

		name = L"";

		short i = int(pathfile.size()) - 5;
		while (i >= 0)
			name = pathfile[i--] + name;

		texture = new sf::Texture;
		texture->loadFromFile(ConvertWideToUtf8(L"assets\\" + pathfile));
		texture->setRepeated(true);
		texture->setSmooth(true);
		
		this->cx = cx;
		this->cy = cy;

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

	SingleTexture(std::wstring name, sf::Image image, float cx, float cy) {

		this->name = name;

		texture = new sf::Texture;
		texture->loadFromImage(image);
		texture->setRepeated(true);
		texture->setSmooth(true);

		this->cx = cx;
		this->cy = cy;
		//cout << "load texture from set as: " << name << endl;
	}


	SingleTexture(sf::Image image) {

		name = L"texture";

		this->texture = new sf::Texture();
		this->texture->loadFromImage(image);
		texture->setRepeated(true);
		texture->setSmooth(true);
		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
	}

	SingleTexture(std::wstring pathfile, unsigned width, unsigned height, std::vector<sf::Uint8>& pixels, float cx = 0, float cy = 0) {

		this->name = pathfile;

		texture = new sf::Texture;

		texture->create(width, height);
		texture->update(pixels.data());
		texture->setRepeated(true);
		texture->setSmooth(true);

		this->cx = cx;
		this->cy = cy;
	}
};

std::vector < SingleTexture* > singleTextures;

void loadTexturesFromPacket() {
	std::ifstream packet("assets\\atex.assets", std::ios::binary);
	if (!packet) {
		//std::cerr << "Nie można otworzyć pliku pakiet.bin\n";
		return;
	}

	uint32_t fileCount;
	packet.read(reinterpret_cast <char*>(&fileCount), sizeof(fileCount));

	std::vector < SingleTexture* > textures;
	for (uint32_t i = 0; i < fileCount; ++i) {

		uint8_t nameLength;
		packet.read(reinterpret_cast <char*>(&nameLength), sizeof(nameLength));

		std::string f(nameLength, '\0');
		packet.read(&f[0], nameLength);
		std::wstring fileName = ConvertUtf8ToWide(f);
		//std::wcout << L"name: " << fileName << L"\n";

		uint8_t type;
		packet.read(reinterpret_cast <char*>(&type), sizeof(uint8_t));
		if (type == 0) {
			// load texture
			uint16_t cx, cy;
			packet.read(reinterpret_cast <char*>(&cx), sizeof(cx));
			packet.read(reinterpret_cast <char*>(&cy), sizeof(cy));

			uint32_t fileSize;
			packet.read(reinterpret_cast <char*>(&fileSize), sizeof(fileSize));

			std::vector < char > buffer(fileSize);
			packet.read(buffer.data(), fileSize);

			sf::Image img = sf::Image();
			if (!img.loadFromMemory(buffer.data(), buffer.size())) {
				std::wcout << L"Nie udało się załadować obrazka: " << L"assets\\" + fileName + L".png" << L"(" << i << L")" << "\n";
				continue; // pomiń ten plik
			}

			SingleTexture* t = new SingleTexture(fileName, img, cx, cy);
			textures.push_back(t);

			//std::cout << "wczytano teksture:\n";
			//std::cout << t->name << "(" << t->cx << ", " << t->cy << ")\n";
		}
		else if (type == 1) {
			// load set
			uint16_t tile_width, tile_height, cx, cy;

			packet.read(reinterpret_cast <char*>(&tile_width), sizeof(tile_width));
			packet.read(reinterpret_cast <char*>(&tile_height), sizeof(tile_height));
			packet.read(reinterpret_cast <char*>(&cx), sizeof(cx));
			packet.read(reinterpret_cast <char*>(&cy), sizeof(cy));

			uint32_t fileSize;
			packet.read(reinterpret_cast <char*>(&fileSize), sizeof(fileSize));

			std::vector < char > buffer(fileSize);
			packet.read(buffer.data(), fileSize);

			sf::Image img = sf::Image();
			if (!img.loadFromMemory(buffer.data(), buffer.size())) {
				std::wcout << L"Nie udało się załadować obrazka: " << L"assets\\" + fileName + L".png" << L"(" << i << L")" << L"\n";
				continue; // pomiń ten plik
			}

			short image_width = img.getSize().x;
			short image_height = img.getSize().y;

			//cout << image_width << "x" << image_height << "\n";

			int counter = 0;

			for (short y = 0; y < image_height; y += tile_height)
				for (short x = 0; x < image_width; x += tile_width) {

					// create tile - fragment of texture
					sf::Image tile;
					tile.create(tile_width, tile_height);
					tile.copy(img, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

					bool isEmpty = true;
					for (short yy = 0; yy < tile_height && isEmpty; yy++) {
						for (short xx = 0; xx < tile_width; xx++) {
							if (tile.getPixel(xx, yy) != sf::Color::Transparent) {
								isEmpty = false;
								break;
							}
						}
					}

					if (isEmpty)
						continue;


					// searching - exist doubles or no
					bool existed = false;

					for (short i = 0; i < textures.size(); i++) {

						sf::Image img = textures[i]->texture->copyToImage();

						if (areImagesEqual(tile, img)) {
							existed = true;
							//cout << "exits now\n";
							break;
						}
					}

					// if no exist then add
					if (existed == false) {

						SingleTexture* new_texture = new SingleTexture(fileName + L"_" + to_wstring(counter), tile, cx, cy);
						//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
						textures.push_back(new_texture);

						counter += 1;

					}

				}

			//std::cout << "wczytano set: " << fileName << "\n";
		}
		else if (type == 2) {
			// laod animation
			uint16_t tile_width, tile_height, cx, cy;

			packet.read(reinterpret_cast <char*>(&tile_width), sizeof(tile_width));
			packet.read(reinterpret_cast <char*>(&tile_height), sizeof(tile_height));
			packet.read(reinterpret_cast <char*>(&cx), sizeof(cx));
			packet.read(reinterpret_cast <char*>(&cy), sizeof(cy));

			uint32_t fileSize;
			packet.read(reinterpret_cast <char*>(&fileSize), sizeof(fileSize));

			std::vector < char > buffer(fileSize);
			packet.read(buffer.data(), fileSize);

			sf::Image img = sf::Image();
			if (!img.loadFromMemory(buffer.data(), buffer.size())) {
				std::wcout << L"Nie udało się załadować obrazka: " << L"assets\\" + fileName + L".png" << L"(" << i << L")" << L"\n";
				continue; // pomiń ten plik
			}

			short image_width = img.getSize().x;
			short image_height = img.getSize().y;

			//cout << image_width << "x" << image_height << "\n";

			int counter = 0;

			for (short y = 0; y < image_height; y += tile_height)
				for (short x = 0; x < image_width; x += tile_width) {

					// create tile - fragment of texture
					sf::Image tile;
					tile.create(tile_width, tile_height);
					tile.copy(img, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

					bool isEmpty = true;
					for (short yy = 0; yy < tile_height && isEmpty; yy++) {
						for (short xx = 0; xx < tile_width; xx++) {
							if (tile.getPixel(xx, yy) != sf::Color::Transparent) {
								isEmpty = false;
								break;
							}
						}
					}

					if (isEmpty)
						continue;

					SingleTexture* new_texture = new SingleTexture(fileName + L"[" + to_wstring(counter) + L"]", tile, cx, cy);
					//cout << "created texture: " << pathfile + "[" + to_string(counter) << "]\n";
					textures.push_back(new_texture);
					counter += 1;

				}

			//std::cout << "wczytano set: " << fileName << "\n";
		}
	}


	packet.close();

	std::cout << "wczytano " << textures.size() << " tekstur\n";

	singleTextures = textures;
}


SingleTexture* getSingleTexture(std::wstring name) {

	for (auto& t : singleTextures) {
		if (t->name == name) {
			return t;
		}
	}

	std::wcout << L"error - get Texture - Texture: \"" << name << L"\" not exists\n";
	return nullptr;
}

std::vector < SingleTexture* > getAnimation(std::wstring name) {

	std::vector < SingleTexture* > animation;
	animation.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name + L"[") == 0)
			animation.push_back(tex);

	if (animation.empty()) {

		SingleTexture* tex = getSingleTexture(name);
		if (tex != nullptr)
			animation.push_back(tex);
	}

	if (animation.empty()) {
		std::wcout << L"error - get Animation - Animation: \"" << name << L"\" is empty\n";
	}

	return animation;
}

std::vector < SingleTexture* > getSingleTextures(std::wstring name) {

	std::vector < SingleTexture* > textures;
	textures.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name) == 0)
			textures.push_back(tex);

	if (textures.empty()) {
		std::wcout << L"error - get Textures - Textures: \"" << name << L"\" is empty\n";
	}

	return textures;
}

void loadSingleTexture(std::wstring pathfile, float cx, float cy) {
	singleTextures.push_back(new SingleTexture(pathfile, cx, cy));
}

void loadTextureSets(std::wstring pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;
	image.loadFromFile(ConvertWideToUtf8(L"assets\\" + pathfile + L".png"));

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;

	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			bool isEmpty = true;
			for (short yy = 0; yy < tile_height && isEmpty; yy++) {
				for (short xx = 0; xx < tile_width; xx++) {
					if (tile.getPixel(xx, yy) != sf::Color::Transparent) {
						isEmpty = false;
						break;
					}
				}
			}

			if (isEmpty)
				continue;


			// searching - exist doubles or no
			bool existed = false;
			
			for (short i = 0; i < singleTextures.size(); i++) {
				sf::Image img = singleTextures[i]->texture->copyToImage();
				
				if (areImagesEqual(tile, img)) {
					existed = true;
					//cout << "exits now\n";
					break;
				}
			}

			// if no exist then add
			if (existed == false) {
				SingleTexture* new_texture = new SingleTexture(pathfile + L"_" + to_wstring(counter), tile, cx, cy);
				//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
				singleTextures.push_back(new_texture);

				counter += 1;

			}

		}

}

void loadAnimation(std::wstring pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;

	image.loadFromFile(ConvertWideToUtf8(L"assets\\" + pathfile + L".png"));

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;

	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			SingleTexture* new_texture = new SingleTexture(pathfile + L"[" + to_wstring(counter) + L"]", tile, cx, cy);
			//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
			singleTextures.push_back(new_texture);
			counter += 1;


		}
}

void generateTileSet() {
	sf::Image masks[16];

	for (int i = 0; i < 16; i++) {
		masks[i].create(64, 64);
		if (!masks[i].loadFromFile("assets\\tiles\\basic2\\" + std::to_string(i) + ".png")) {
			std::cout << "Błąd wczytywania maski: " << i << "\n";
			return;
		}
	}

	std::cout << "Wczytano maski\n";

	std::vector<SingleTexture*> tiles = getSingleTextures(L"tiles\\tile_");
	std::cout << "Tiles: " << tiles.size() << "\n";

	unsigned int N = tiles.size();
	unsigned int M = 14;  // Liczba masek
	unsigned int totalTiles = (N * (N - 1) / 2) * M;

	// Obliczanie wymiarów wynikowej tekstury
	unsigned int tileSize = 64;
	unsigned int tilesPerRow = std::ceil(std::sqrt(totalTiles));  // Najbardziej kwadratowy układ
	unsigned int rows = (totalTiles + tilesPerRow - 1) / tilesPerRow;

	sf::Image tile_set_image;
	tile_set_image.create(tilesPerRow * tileSize, rows * tileSize, sf::Color::Transparent);

	sf::Image first_tile, second_tile, mask, result_tile;
	first_tile.create(tileSize, tileSize);
	second_tile.create(tileSize, tileSize);
	result_tile.create(tileSize, tileSize);

	// Na początku zapiszemy bazowe kafelki, by się nie powtarzały
	unsigned int tileIndex = 0;

	for (short tile_id = 0; tile_id < N; tile_id++) {
		unsigned int newX = (tileIndex % tilesPerRow) * tileSize;
		unsigned int newY = (tileIndex / tilesPerRow) * tileSize;

		tile_set_image.copy(tiles[tile_id]->texture->copyToImage(), newX, newY);
		tileIndex++;
	}

	// Teraz generujemy przejściowe kafelki
	for (short tile_1_id = 0; tile_1_id < N; tile_1_id++) {
		for (short tile_2_id = tile_1_id + 1; tile_2_id < N; tile_2_id++) {
			first_tile = tiles[tile_1_id]->texture->copyToImage();
			second_tile = tiles[tile_2_id]->texture->copyToImage();

			for (short mask_id = 1; mask_id < 15; mask_id++) { // Pomiń 0 i 15
				mask = masks[mask_id];

				for (unsigned int y = 0; y < tileSize; y++) {
					for (unsigned int x = 0; x < tileSize; x++) {
						sf::Color pixel = mask.getPixel(x, y);

						if (pixel.r == 237 && pixel.g == 28 && pixel.b == 36) {
							result_tile.setPixel(x, y, first_tile.getPixel(x, y));
						}
						else if (pixel.r == 127 && pixel.g == 127 && pixel.b == 127) {
							result_tile.setPixel(x, y, second_tile.getPixel(x, y));
						}
						else {
							result_tile.setPixel(x, y, pixel);
						}
					}
				}

				unsigned int newX = (tileIndex % tilesPerRow) * tileSize;
				unsigned int newY = (tileIndex / tilesPerRow) * tileSize;

				if (newY >= rows * tileSize) {
					std::cerr << "Za dużo kafelków! Przekracza rozmiar tekstury.\n";
					return;
				}

				tile_set_image.copy(result_tile, newX, newY);
				tileIndex++;
			}
		}
	}

	// Zapisujemy obraz do pliku
	tile_set_image.saveToFile("assets\\tiles\\tile_set_final.png");

	SingleTexture* texture_tile_set = new SingleTexture(tile_set_image);
	singleTextures.push_back(texture_tile_set);
	std::cout << "Zapisano tile_set_final.png\n";
}

void loadTextures() {

	singleTextures.clear();
	short i = 0;

	// NOISE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture(L"noise.png", 256, 256);
	loadSingleTexture(L"noise2.png", 256, 256);
	loadSingleTexture(L"empty.png", 32, 32);

	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture(L"GUI\\slot1.png", 40, 40);
	loadSingleTexture(L"GUI\\slot2.png", 32, 32);
	loadSingleTexture(L"GUI\\selector.png", 40, 40);

	loadSingleTexture(L"GUI\\corner.png", 4, 4);
	loadSingleTexture(L"GUI\\border_horizontal.png", 3, 3);
	loadSingleTexture(L"GUI\\border_vertical.png", 3, 3);

	loadSingleTexture(L"GUI\\infoPanel.png", 300, 75);
	loadSingleTexture(L"GUI\\bigPanel.png", 300, 200);

	loadSingleTexture(L"GUI\\wideArrowUp1.png", 80, 20);
	loadSingleTexture(L"GUI\\wideArrowUp2.png", 80, 20);
	loadSingleTexture(L"GUI\\wideArrowDown1.png", 160, 18.5f);
	loadSingleTexture(L"GUI\\wideArrowDown2.png", 160, 18.5f);

	// group buttons textures
	loadSingleTexture(L"GUI\\groupButtons\\groupButton_to_left.png", 17, 52);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton_to_right.png", 17, 52);
	
	loadSingleTexture(L"GUI\\groupButtons\\groupButton.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-terrain.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-highlands.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-floors.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-water.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-furnitures.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-walls.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-monsters.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-flat_objects.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-items.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-natures.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-smallObjects.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-objects.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-buildings.png", 34, 26);
	loadSingleTexture(L"GUI\\groupButtons\\groupButton-directions.png", 34, 26);

	// small buttons textures
	loadSingleTexture(L"GUI\\smallButtons\\smallbutton.png", 20, 20);
	loadSingleTexture(L"GUI\\smallButtons\\smallbutton-ArrowUp.png", 20, 20);
	loadSingleTexture(L"GUI\\smallButtons\\smallbutton-ArrowDown.png", 20, 20);
	loadSingleTexture(L"GUI\\smallButtons\\smallbutton-ArrowLeft.png", 20, 20);
	loadSingleTexture(L"GUI\\smallButtons\\smallbutton-ArrowRight.png", 20, 20);

	// tool butttons textures
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-cursor.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-brush.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-rect_brush.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-increase.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-decrease.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-rectangle.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-elipse.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-fill.png", 20, 16);
	loadSingleTexture(L"GUI\\toolButtons\\toolbutton-eraser.png", 20, 16);

	// space
	loadSingleTexture(L"GUI\\spacebutton.png", 80, 20);

	// scrollbar textures
	loadSingleTexture(L"GUI\\scrollbar_16\\bar_bottom.png", 8, 8);
	loadSingleTexture(L"GUI\\scrollbar_16\\bar_top.png", 8, 8);
	loadSingleTexture(L"GUI\\scrollbar_16\\bar_center.png", 8, 8);
	loadSingleTexture(L"GUI\\scrollbar_16\\scroll_bottom.png", 8, 8);
	loadSingleTexture(L"GUI\\scrollbar_16\\scroll_top.png", 8, 8);
	loadSingleTexture(L"GUI\\scrollbar_16\\scroll_center.png", 8, 8);

	loadSingleTexture(L"GUI\\scrollbar_20\\bar_bottom.png", 10, 10);
	loadSingleTexture(L"GUI\\scrollbar_20\\bar_top.png", 10, 10);
	loadSingleTexture(L"GUI\\scrollbar_20\\bar_center.png", 10, 10);
	loadSingleTexture(L"GUI\\scrollbar_20\\scroll_bottom.png", 10, 10);
	loadSingleTexture(L"GUI\\scrollbar_20\\scroll_top.png", 10, 10);
	loadSingleTexture(L"GUI\\scrollbar_20\\scroll_center.png", 10, 10);

	// checkbox textures
	loadSingleTexture(L"GUI\\checkbox\\check.png", 8, 8);

	// interactions textures
	loadSingleTexture(L"GUI\\hand.png", 8, 8);
	loadSingleTexture(L"GUI\\grey_hand.png", 8, 8);
	loadSingleTexture(L"GUI\\talk.png", 8, 8);

	// icons texture
	loadSingleTexture(L"GUI\\icons\\MapEditor_small_ico.png", 15, 15);
	loadSingleTexture(L"GUI\\icons\\dictionary.png", 15, 15);
	loadSingleTexture(L"GUI\\icons\\file.png", 15, 15);
	loadSingleTexture(L"GUI\\icons\\empty.png", 15, 15);

	// context menu textures
	loadSingleTexture(L"GUI\\context_menu\\btn_default.png", 15, 15);
	loadSingleTexture(L"GUI\\context_menu\\btn_info.png", 15, 15);
	loadSingleTexture(L"GUI\\context_menu\\btn_edit.png", 15, 15);
	loadSingleTexture(L"GUI\\context_menu\\btn_remove.png", 15, 15);
	loadSingleTexture(L"GUI\\context_menu\\btn_cancel.png", 15, 15);

	// character mnenu textures
	loadSingleTexture(L"GUI\\character_menu\\menu_slot.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_statistics.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_layout.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_equipment.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_inventory.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_dialogues.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\menu_quests.png", 32, 20);
	loadSingleTexture(L"GUI\\character_menu\\layout_slot.png", 40, 40);
	loadSingleTexture(L"GUI\\character_menu\\item_slot.png", 32, 32);
	loadSingleTexture(L"GUI\\character_menu\\direction_top.png", 32, 32);
	loadSingleTexture(L"GUI\\character_menu\\direction_bottom.png", 32, 32);
	loadSingleTexture(L"GUI\\character_menu\\direction_left.png", 32, 32);
	loadSingleTexture(L"GUI\\character_menu\\direction_right.png", 32, 32);

	// building editor
	loadSingleTexture(L"GUI\\building_editor_side_menu\\reset_camera.png", 24, 24);

	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture(L"tiles\\0_tileset.png", 0, 0);
	loadSingleTexture(L"tiles\\tile_0_water.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_1_sands.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_2_grass.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_3_gravel.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_4_steps.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_5_highlands.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_6.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_7.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_8.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_9.png", 32, 32);
	loadSingleTexture(L"tiles\\tile_10.png", 32, 32);

	//generateTileSet();

	loadTextureSets(L"tiles\\set_0_water_sands", 64, 64, 32, 32);
	loadTextureSets(L"tiles\\set_0_sands_water", 64, 64, 32, 32);
	loadTextureSets(L"tiles\\set_1_sands_grass", 64, 64, 32, 32);
	loadTextureSets(L"tiles\\set_1_grass_sands", 64, 64, 32, 32);
	loadTextureSets(L"tiles\\set_2_grass_gravel", 64, 64, 32, 32);
	loadTextureSets(L"tiles\\set_2_gravel_grass", 64, 64, 32, 32);

	// FLOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture(L"floors\\0_floorset.png", 0, 0);
	loadSingleTexture(L"floors\\floor_0.png", 32, 32);
	loadSingleTexture(L"floors\\floor_1.png", 32, 32);
	loadSingleTexture(L"floors\\floor_2.png", 32, 32);
	loadSingleTexture(L"floors\\floor_3.png", 32, 32);
	loadSingleTexture(L"floors\\floor_4.png", 32, 32);
	loadSingleTexture(L"floors\\floor_5.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"natures\\tree9.png", 129, 213);
	loadSingleTexture(L"natures\\bush_1.png", 32, 44);
	loadSingleTexture(L"natures\\stump_1.png", 62, 90);
	loadSingleTexture(L"natures\\boulder_1.png", 66, 72);
	loadSingleTexture(L"natures\\boulder_2.png", 65, 78);
	loadSingleTexture(L"natures\\boulder_3.png", 60, 80);

	loadSingleTexture(L"natures\\column_2.png", 65, 85);
	loadSingleTexture(L"natures\\column_3.png", 65, 85);
	loadSingleTexture(L"natures\\stone_altar.png", 65, 85);
	loadSingleTexture(L"natures\\stone_platform.png", 65, 78);
	loadSingleTexture(L"natures\\driftwood.png", 59, 77);
	loadSingleTexture(L"natures\\rock_1.png", 32, 36);
	loadSingleTexture(L"natures\\rock_2.png", 32, 36);
	loadSingleTexture(L"natures\\reed_1.png", 32, 54);
	loadSingleTexture(L"natures\\reed_2.png", 32, 54);

	// HIGHLANDS

	loadTextureSets(L"highlands\\low_highlands", 64, 64, 32, 32);
	loadTextureSets(L"highlands\\high_highlands", 64, 64, 32, 32);

	// SMALL OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"smallObjects\\grass_1.png", 33, 32);
	loadSingleTexture(L"smallObjects\\grass_2.png", 33, 32);
	loadSingleTexture(L"smallObjects\\grass_3.png", 33, 32);

	// OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"objects\\palisade_1.png", 16, 112);
	loadSingleTexture(L"objects\\palisade_2.png", 16, 112);
	loadSingleTexture(L"objects\\stone_wall.png", 8, 56);
	loadSingleTexture(L"objects\\great_stone_wall.png", 16, 112);
	loadSingleTexture(L"objects\\well.png", 64, 96);
	loadSingleTexture(L"objects\\hunter_tent.png", 128, 175);
	loadSingleTexture(L"objects\\log_with_saw.png", 64, 70);
	loadSingleTexture(L"objects\\pile_of_wood_1.png", 64, 80);
	loadSingleTexture(L"objects\\pile_of_wood_2.png", 64, 80);
	loadSingleTexture(L"objects\\stone_altar_1.png", 66, 66);

	loadAnimation(L"objects\\brazier", 64, 64, 32, 40);

	// FLAT OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"flatObjects\\path_1.png", 32, 32);
	loadSingleTexture(L"flatObjects\\path_2.png", 32, 32);
	loadSingleTexture(L"flatObjects\\stonepath_1.png", 32, 32);
	loadSingleTexture(L"flatObjects\\stonepath_2.png", 32, 32);
	loadSingleTexture(L"flatObjects\\sandspath_1.png", 32, 32);
	loadSingleTexture(L"flatObjects\\sandspath_2.png", 32, 32);

	loadSingleTexture(L"flatObjects\\herb_1.png", 33, 32);
	loadSingleTexture(L"flatObjects\\herb_2.png", 33, 32);

	loadSingleTexture(L"flatObjects\\small_rock_1.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_rock_2.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_rock_3.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_rock_4.png", 16, 16);

	loadSingleTexture(L"flatObjects\\small_sands_rock_1.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_sands_rock_2.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_sands_rock_3.png", 16, 16);
	loadSingleTexture(L"flatObjects\\small_sands_rock_4.png", 16, 16);

	// SPELLS OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadAnimation(L"spells\\fireball", 32, 32, 16, 16);
	loadAnimation(L"spells\\water_cone", 32, 32, 16, 16);
	loadAnimation(L"spells\\magic_circle", 64, 64, 32, 32);

	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"items\\inventory.png", 28, 48);

	// BOWS
	loadSingleTexture(L"items\\bow.png", 32, 32);

	// WEAPONS
	loadSingleTexture(L"items\\club.png", 32, 32);
	loadSingleTexture(L"items\\knife.png", 32, 32);
	loadSingleTexture(L"items\\hatchet.png", 32, 32);
	loadSingleTexture(L"items\\sword.png", 32, 32);
	loadSingleTexture(L"items\\dagger.png", 32, 32);
	loadSingleTexture(L"items\\wooden club.png", 32, 32);
	loadSingleTexture(L"items\\long sword.png", 32, 32);
	loadSingleTexture(L"items\\curved sword.png", 32, 32);
	loadSingleTexture(L"items\\wide blade.png", 32, 32);
	loadSingleTexture(L"items\\gladius.png", 32, 32);
	loadSingleTexture(L"items\\iron club.png", 32, 32);
	loadSingleTexture(L"items\\axe.png", 32, 32);
	loadSingleTexture(L"items\\stone hammer.png", 32, 32);

	// HELMET
	loadSingleTexture(L"items\\skin helmet.png", 32, 32);
	loadSingleTexture(L"items\\wool hat.png", 32, 32);

	// ARMORS
	loadSingleTexture(L"items\\plate armor.png", 32, 32);
	loadSingleTexture(L"items\\chain mail.png", 32, 32);
	loadSingleTexture(L"items\\skin jacket.png", 32, 32);
	loadSingleTexture(L"items\\mage's robe.png", 32, 32);
	loadSingleTexture(L"items\\gray apron.png", 32, 32);
	loadSingleTexture(L"items\\torn shirt.png", 32, 32);
	loadSingleTexture(L"items\\wool shirt.png", 32, 32);

	// PANTS
	loadSingleTexture(L"items\\chain mail pants.png", 32, 32);
	loadSingleTexture(L"items\\skin pants.png", 32, 32);
	loadSingleTexture(L"items\\wool pants.png", 32, 32);

	// SHIELDS
	loadSingleTexture(L"items\\shield.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadSingleTexture(L"items\\mana plant.png", 30, 50);
	loadSingleTexture(L"items\\health herb.png", 32, 34);
	loadSingleTexture(L"items\\health root.png", 31, 46);
	loadSingleTexture(L"items\\health plant.png", 30, 44);
	loadSingleTexture(L"items\\mushroom.png", 30, 44);

	// POTIONS
	loadSingleTexture(L"items\\potion.png", 32, 32);

	// FOOD
	loadSingleTexture(L"items\\raw meat.png", 32, 32);
	loadSingleTexture(L"items\\roasted meat.png", 32, 32);

	// OTHERS
	loadSingleTexture(L"items\\bone.png", 32, 32);
	loadSingleTexture(L"items\\bone.png", 40, 40);
	loadSingleTexture(L"items\\tooth.png", 32, 32);
	loadSingleTexture(L"items\\spike.png", 32, 32);
	loadSingleTexture(L"items\\wolf skin.png", 32, 32);

	// DOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture(L"doors\\wooden_door[0].png", 32, 63);
	loadSingleTexture(L"doors\\wooden_door[1].png", 32, 63);
	loadSingleTexture(L"doors\\wooden_door[2].png", 32, 63);
	loadSingleTexture(L"doors\\wooden_door[3].png", 32, 63);

	loadSingleTexture(L"doors\\wooden_gate[0].png", 64, 127);
	loadSingleTexture(L"doors\\wooden_gate[1].png", 64, 127);
	loadSingleTexture(L"doors\\wooden_gate[2].png", 64, 127);
	loadSingleTexture(L"doors\\wooden_gate[3].png", 64, 127);

	loadSingleTexture(L"doors\\great_stone_gate[0].png", 64, 127);
	loadSingleTexture(L"doors\\great_stone_gate[1].png", 64, 127);
	loadSingleTexture(L"doors\\great_stone_gate[2].png", 64, 127);
	loadSingleTexture(L"doors\\great_stone_gate[3].png", 64, 127);


	// MONSTERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector < std::wstring > monsters;

	monsters.push_back(L"dziobak");
	monsters.push_back(L"goblin");
	monsters.push_back(L"wilczur");
	monsters.push_back(L"jaszczur");
	monsters.push_back(L"niedzwiedz");
	monsters.push_back(L"szpon");
	monsters.push_back(L"kolcorozec");
	monsters.push_back(L"golem");
	monsters.push_back(L"troll");
	monsters.push_back(L"bies");

	for (auto& m : monsters) {
		for (i = 0; i < 4; i++) {

			loadSingleTexture(L"monsters\\" + m + L".png", 63, 87);

			loadSingleTexture(L"monsters\\" + m + L"\\idleTop" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\idleRight" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\idleBottom" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\idleLeft" + to_wstring(i) + L".png", 63, 87);

			loadSingleTexture(L"monsters\\" + m + L"\\attackTop" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\attackRight" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\attackBottom" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\attackLeft" + to_wstring(i) + L".png", 63, 87);

			loadSingleTexture(L"monsters\\" + m + L"\\runTop" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\runRight" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\runBottom" + to_wstring(i) + L".png", 63, 87);
			loadSingleTexture(L"monsters\\" + m + L"\\runLeft" + to_wstring(i) + L".png", 63, 87);

		}
	}

	// FURNITURES
	loadSingleTexture(L"furnitures\\table.png", 32, 32);
	loadSingleTexture(L"furnitures\\table_alchemist.png", 32, 32);
	loadSingleTexture(L"furnitures\\table_alchemist_2.png", 32, 32);
	loadSingleTexture(L"furnitures\\table_herbalist.png", 32, 32);
	loadSingleTexture(L"furnitures\\table_herbalist_2.png", 32, 32);
	loadSingleTexture(L"furnitures\\stone_table_1.png", 32, 32);
	loadSingleTexture(L"furnitures\\bench.png", 32, 32);
	loadSingleTexture(L"furnitures\\stone_bench_1.png", 32, 32);
	loadSingleTexture(L"furnitures\\chest.png", 32, 32);
	loadSingleTexture(L"furnitures\\wardrobe.png", 32, 50);
	loadSingleTexture(L"furnitures\\bookshelf.png", 32, 50);
	loadSingleTexture(L"furnitures\\furnace.png", 32, 50);
	loadSingleTexture(L"furnitures\\bed.png", 32, 50);
	loadSingleTexture(L"furnitures\\chair.png", 34, 38);
	loadSingleTexture(L"furnitures\\barrel.png", 34, 38);
	loadSingleTexture(L"furnitures\\shield_1.png", 32, 32);
	loadSingleTexture(L"furnitures\\shield_2.png", 32, 32);
	loadSingleTexture(L"furnitures\\shield_3.png", 32, 32);
	loadSingleTexture(L"furnitures\\lectern.png", 34, 38);


	// WALLS
	loadSingleTexture(L"walls\\empty_wall.png", 16, 16);

	loadSingleTexture(L"walls\\mud_wall.png", 16, 16);
	loadSingleTexture(L"walls\\stone_wall.png", 16, 16);
	loadSingleTexture(L"walls\\wooden_wall.png", 16, 16);
	loadSingleTexture(L"walls\\brick_wall.png", 16, 16);
	loadSingleTexture(L"walls\\mulch_wall.png", 16, 16);

	loadSingleTexture(L"walls\\mud_wall_overgrown.png", 16, 16);
	loadSingleTexture(L"walls\\stone_wall_overgrown.png", 16, 16);
	loadSingleTexture(L"walls\\wooden_wall_overgrown.png", 16, 16);
	loadSingleTexture(L"walls\\brick_wall_overgrown.png", 16, 16);
	loadSingleTexture(L"walls\\mulch_wall_overgrown.png", 16, 16);


	loadTextureSets(L"walls\\set_mud_wall", 32, 32, 16, 16);
	loadTextureSets(L"walls\\set_stone_wall", 32, 32, 16, 16);
	loadTextureSets(L"walls\\set_wooden_wall", 32, 32, 16, 16);
	loadTextureSets(L"walls\\set_brick_wall", 32, 32, 16, 16);
	loadTextureSets(L"walls\\set_mulch_wall", 32, 32, 16, 16);

	// FORTIFICATIONS

	// BODY SETS
	std::vector < std::wstring > bodySets;
	bodySets.clear();
	bodySets.push_back(L"boy-redhaired");		// face without beard
	bodySets.push_back(L"boy-blackhaired");		// face without beard
	bodySets.push_back(L"boy-brownhaired");		// face without beard
	bodySets.push_back(L"boy-greyhaired");		// face without beard

	bodySets.push_back(L"man-redhaired");		// face have a beard
	bodySets.push_back(L"man-blackhaired");		// face have a beard
	bodySets.push_back(L"man-brownhaired");		// face have a beard
	bodySets.push_back(L"man-greyhaired");		// face have a beard

	bodySets.push_back(L"woman-redhaired");		// face with long hair
	bodySets.push_back(L"woman-blackhaired");	// face with long hair
	bodySets.push_back(L"woman-brownhaired");	// face with long hair
	bodySets.push_back(L"woman-greyhaired");	// face with long hair


	for (auto& set : bodySets) {
		for (i = 0; i < 4; i++) {

			loadSingleTexture(L"sets\\body\\" + set + L"\\idleTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\idleRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\idleBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\idleLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\body\\" + set + L"\\runTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\runRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\runBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\runLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\body\\" + set + L"\\attackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\attackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\attackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\attackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\body\\" + set + L"\\bowAttackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\bowAttackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\bowAttackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\bowAttackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\body\\" + set + L"\\magicAttackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicAttackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicAttackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicAttackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\body\\" + set + L"\\magicBuffTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicBuffRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicBuffBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\body\\" + set + L"\\magicBuffLeft" + to_wstring(i) + L".png", 32, 58);

		}
	}


	// ITEMS SETS
	std::vector < std::wstring > itemSets;
	itemSets.clear();
	itemSets.push_back(L"skin pants");
	itemSets.push_back(L"skin helmet");
	itemSets.push_back(L"wool hat");
	itemSets.push_back(L"wool pants");
	itemSets.push_back(L"wooden club");
	itemSets.push_back(L"axe");
	itemSets.push_back(L"club");
	itemSets.push_back(L"iron club");
	itemSets.push_back(L"stone hammer");
	itemSets.push_back(L"sword");
	itemSets.push_back(L"long sword");
	itemSets.push_back(L"gladius");
	itemSets.push_back(L"wide blade");
	itemSets.push_back(L"knife");
	itemSets.push_back(L"dagger");
	itemSets.push_back(L"hatchet");
	itemSets.push_back(L"curved sword");
	itemSets.push_back(L"chain mail pants");
	itemSets.push_back(L"shield");
	itemSets.push_back(L"bow");

	for (auto& set : itemSets) {

		for (i = 0; i < 4; i++) {

			loadSingleTexture(L"sets\\items\\" + set + L"\\idleTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\runTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\attackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackLeft" + to_wstring(i) + L".png", 32, 58);

		}
	}

	std::vector < std::wstring > armorSets;
	armorSets.push_back(L"skin jacket");
	armorSets.push_back(L"torn shirt");
	armorSets.push_back(L"mage's robe");
	armorSets.push_back(L"gray apron");
	armorSets.push_back(L"wool shirt");
	armorSets.push_back(L"chain mail");
	armorSets.push_back(L"plate armor");

	for (auto& set : armorSets) {

		for (i = 0; i < 4; i++) {

			loadSingleTexture(L"sets\\items\\" + set + L"\\idleTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\idleLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\runTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\runLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\attackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\attackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\bowAttackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\bowAttackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\bowAttackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\bowAttackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\magicAttackTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicAttackRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicAttackBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicAttackLeft" + to_wstring(i) + L".png", 32, 58);

			loadSingleTexture(L"sets\\items\\" + set + L"\\magicBuffTop" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicBuffRight" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicBuffBottom" + to_wstring(i) + L".png", 32, 58);
			loadSingleTexture(L"sets\\items\\" + set + L"\\magicBuffLeft" + to_wstring(i) + L".png", 32, 58);

		}
	}

	// BUILDING PARTS

	loadSingleTexture(L"buildings\\parts\\tile_left.png", 8, 8);
	loadSingleTexture(L"buildings\\parts\\tile_left_top.png", 8, 4);
	loadSingleTexture(L"buildings\\parts\\tile_left_bottom.png", 8, 4);
	loadSingleTexture(L"buildings\\parts\\tile_right.png", 8, 8);
	loadSingleTexture(L"buildings\\parts\\tile_right_top.png", 8, 4);
	loadSingleTexture(L"buildings\\parts\\tile_right_bottom.png", 8, 4);
	loadSingleTexture(L"buildings\\parts\\tile_center.png", 8, 8);
	loadSingleTexture(L"buildings\\parts\\tile_center_top.png", 8, 4);
	loadSingleTexture(L"buildings\\parts\\tile_center_bottom.png", 8, 4);

	loadSingleTexture(L"buildings\\parts\\window.png", 16, 16);
	loadSingleTexture(L"buildings\\parts\\window_2.png", 16, 16);
	loadSingleTexture(L"buildings\\parts\\bar.png", 32, 5);

	std::wcout << L"wczytano " << singleTextures.size() << L" tekstur\n";

}



#endif