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

void save_texture(std::ofstream& packet, std::string pathfile, uint16_t cx, uint16_t cy) {
	std::ifstream file("assets\\" + pathfile + ".png", std::ios::binary);

	if (!file) {
		std::cerr << "Nie można otworzyć pliku: " << "assets\\" + pathfile + ".png" << "\n";
		return;
	}

	string filename = pathfile;
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
	packet.write(filename.c_str(), nameLength); // N bajtów
	packet.write(reinterpret_cast <char*>(&type), sizeof(uint8_t)); // 0 if texture (no set)
	packet.write(reinterpret_cast <char*>(&cx), sizeof(cx));
	packet.write(reinterpret_cast <char*>(&cy), sizeof(cy));
	packet.write(reinterpret_cast <char*>(&fileSize), sizeof(fileSize)); // 4 bajty
	packet.write(buffer.data(), fileSize); // X bajtów

	//std::cout << "zapisano teksture: " << filename << "\n";

	file.close();
}

void save_set(std::ofstream& packet, std::string pathfile, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
	std::ifstream file("assets\\" + pathfile + ".png", std::ios::binary);

	if (!file) {
		std::cerr << "Nie można otworzyć pliku: " << "assets\\" + pathfile + ".png" << "\n";
		return;
	}

	string filename = pathfile;
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
	packet.write(filename.c_str(), nameLength); // N bajtów
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

void save_animation(std::ofstream& packet, std::string pathfile, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
	std::ifstream file("assets\\" + pathfile + ".png", std::ios::binary);

	if (!file) {
		std::cerr << "Nie można otworzyć pliku: " << "assets\\" + pathfile + ".png" << "\n";
		return;
	}

	string filename = pathfile;
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
	packet.write(filename.c_str(), nameLength); // N bajtów
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

	std::string name;
	uint16_t cx;
	uint16_t cy;

	Texture_To_Save(std::string name, uint16_t cx, uint16_t cy) {
		this->name = name;
		this->cx = cx;
		this->cy = cy;
	}
};

class Set_To_Save {
public:
	std::string name;
	uint16_t width, height;
	uint16_t cx, cy;

	Set_To_Save(std::string name, uint16_t width, uint16_t height, uint16_t cx, uint16_t cy) {
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

void add_Unique_Terrains_And_Walls_Textures_To_Save(std::string name, uint16_t cx, uint16_t cy) {
	unique_terrains_and_walls_textures_to_save.push_back(new Texture_To_Save(name, cx, cy));
	textures_count += 1;
}

void add_Texture_To_Save(std::string name, uint16_t cx, uint16_t cy) {
	textures_to_save.push_back(new Texture_To_Save(name, cx, cy));
	textures_count += 1;
}

void add_Set_To_Save(string name, uint16_t tile_width, uint16_t tile_height, uint16_t cx, uint16_t cy) {
	sets_to_save.push_back(new Set_To_Save(name, tile_width, tile_height, cx, cy));
	textures_count += 1;
}

void add_Animation_To_Save(string name, uint16_t tile_width, uint16_t tile_height, uint16_t cx, uint16_t cy) {
	animations_to_save.push_back(new Set_To_Save(name, tile_width, tile_height, cx, cy));
	textures_count += 1;
}

void save_textures_as_packet() {

	// noise
	add_Texture_To_Save("noise", 256, 256);
	add_Texture_To_Save("noise2", 256, 256);
	add_Texture_To_Save("empty", 32, 32);

	// GUI
	add_Texture_To_Save("GUI\\slot1", 40, 40);
	add_Texture_To_Save("GUI\\slot2", 32, 32);
	add_Texture_To_Save("GUI\\selector", 40, 40);

	add_Texture_To_Save("GUI\\corner", 4, 4);
	add_Texture_To_Save("GUI\\border_horizontal", 3, 3);
	add_Texture_To_Save("GUI\\border_vertical", 3, 3);

	add_Texture_To_Save("GUI\\infoPanel", 300, 75);
	add_Texture_To_Save("GUI\\bigPanel", 300, 200);

	add_Texture_To_Save("GUI\\wideArrowUp1", 80, 20);
	add_Texture_To_Save("GUI\\wideArrowUp2", 80, 20);
	add_Texture_To_Save("GUI\\wideArrowDown1", 160, 18.5f);
	add_Texture_To_Save("GUI\\wideArrowDown2", 160, 18.5f);

	// group buttons textures
	add_Texture_To_Save("GUI\\groupButtons\\groupButton_to_left", 17, 52);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton_to_right", 17, 52);

	add_Texture_To_Save("GUI\\groupButtons\\groupButton", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-terrain", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-highlands", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-floors", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-water", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-furnitures", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-walls", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-monsters", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-flat_objects", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-items", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-natures", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-smallObjects", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-objects", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-buildings", 34, 26);
	add_Texture_To_Save("GUI\\groupButtons\\groupButton-directions", 34, 26);

	// small buttons textures
	add_Texture_To_Save("GUI\\smallButtons\\smallbutton", 20, 20);
	add_Texture_To_Save("GUI\\smallButtons\\smallbutton-ArrowUp", 20, 20);
	add_Texture_To_Save("GUI\\smallButtons\\smallbutton-ArrowDown", 20, 20);
	add_Texture_To_Save("GUI\\smallButtons\\smallbutton-ArrowLeft", 20, 20);
	add_Texture_To_Save("GUI\\smallButtons\\smallbutton-ArrowRight", 20, 20);

	// tool butttons textures
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-cursor", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-brush", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-rect_brush", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-increase", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-decrease", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-rectangle", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-elipse", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-fill", 20, 16);
	add_Texture_To_Save("GUI\\toolButtons\\toolbutton-eraser", 20, 16);

	// space
	add_Texture_To_Save("GUI\\spacebutton", 80, 20);

	// scrollbar textures
	add_Texture_To_Save("GUI\\scrollbar_16\\bar_bottom", 8, 8);
	add_Texture_To_Save("GUI\\scrollbar_16\\bar_top", 8, 8);
	add_Texture_To_Save("GUI\\scrollbar_16\\bar_center", 8, 8);
	add_Texture_To_Save("GUI\\scrollbar_16\\scroll_bottom", 8, 8);
	add_Texture_To_Save("GUI\\scrollbar_16\\scroll_top", 8, 8);
	add_Texture_To_Save("GUI\\scrollbar_16\\scroll_center", 8, 8);

	add_Texture_To_Save("GUI\\scrollbar_20\\bar_bottom", 10, 10);
	add_Texture_To_Save("GUI\\scrollbar_20\\bar_top", 10, 10);
	add_Texture_To_Save("GUI\\scrollbar_20\\bar_center", 10, 10);
	add_Texture_To_Save("GUI\\scrollbar_20\\scroll_bottom", 10, 10);
	add_Texture_To_Save("GUI\\scrollbar_20\\scroll_top", 10, 10);
	add_Texture_To_Save("GUI\\scrollbar_20\\scroll_center", 10, 10);

	// checkbox textures
	add_Texture_To_Save("GUI\\checkbox\\check", 8, 8);

	// interactions textures
	add_Texture_To_Save("GUI\\hand", 8, 8);
	add_Texture_To_Save("GUI\\grey_hand", 8, 8);
	add_Texture_To_Save("GUI\\talk", 8, 8);

	// icons texture
	add_Texture_To_Save("GUI\\icons\\MapEditor_small_ico", 15, 15);
	add_Texture_To_Save("GUI\\icons\\dictionary", 15, 15);
	add_Texture_To_Save("GUI\\icons\\file", 15, 15);
	add_Texture_To_Save("GUI\\icons\\empty", 15, 15);

	// context menu textures
	add_Texture_To_Save("GUI\\context_menu\\btn_default", 15, 15);
	add_Texture_To_Save("GUI\\context_menu\\btn_info", 15, 15);
	add_Texture_To_Save("GUI\\context_menu\\btn_edit", 15, 15);
	add_Texture_To_Save("GUI\\context_menu\\btn_remove", 15, 15);
	add_Texture_To_Save("GUI\\context_menu\\btn_cancel", 15, 15);

	// character mnenu textures
	add_Texture_To_Save("GUI\\character_menu\\menu_sider_left", 4, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_sider_right", 4, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_slot", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_statistics", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_layout", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_equipment", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_inventory", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_dialogues", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\menu_quests", 32, 20);
	add_Texture_To_Save("GUI\\character_menu\\layout_slot", 40, 40);
	add_Texture_To_Save("GUI\\character_menu\\item_slot", 32, 32);
	add_Texture_To_Save("GUI\\character_menu\\direction_top", 32, 32);
	add_Texture_To_Save("GUI\\character_menu\\direction_bottom", 32, 32);
	add_Texture_To_Save("GUI\\character_menu\\direction_left", 32, 32);
	add_Texture_To_Save("GUI\\character_menu\\direction_right", 32, 32);
	add_Texture_To_Save("GUI\\character_menu\\dialogue_prev", 16, 16);
	add_Texture_To_Save("GUI\\character_menu\\dialogue_next", 16, 16);
	add_Texture_To_Save("GUI\\character_menu\\value_less", 6, 11);
	add_Texture_To_Save("GUI\\character_menu\\value_more", 6, 11);

	// tiles textures
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\0_tileset", 0, 0);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_0_water", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_1_sands", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_2_grass", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_3_gravel", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_4_steps", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_5_highlands", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_6", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_7", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_8", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_9", 32, 32);
	add_Unique_Terrains_And_Walls_Textures_To_Save("tiles\\tile_10", 32, 32);

	// tiles sets
	add_Set_To_Save("tiles\\set_0_water_sands", 64, 64, 32, 32);
	add_Set_To_Save("tiles\\set_0_sands_water", 64, 64, 32, 32);
	add_Set_To_Save("tiles\\set_1_sands_grass", 64, 64, 32, 32);
	add_Set_To_Save("tiles\\set_1_grass_sands", 64, 64, 32, 32);
	add_Set_To_Save("tiles\\set_2_grass_gravel", 64, 64, 32, 32);
	add_Set_To_Save("tiles\\set_2_gravel_grass", 64, 64, 32, 32);

	// floors
	add_Texture_To_Save("floors\\0_floorset", 0, 0);
	add_Texture_To_Save("floors\\floor_0", 32, 32);
	add_Texture_To_Save("floors\\floor_1", 32, 32);
	add_Texture_To_Save("floors\\floor_2", 32, 32);
	add_Texture_To_Save("floors\\floor_3", 32, 32);

	// highlands textures
	add_Set_To_Save("highlands\\low_highlands", 64, 64, 32, 32);
	add_Set_To_Save("highlands\\high_highlands", 64, 64, 32, 32);

	// natures
	add_Texture_To_Save("natures\\tree9", 129, 213);
	add_Texture_To_Save("natures\\bush_1", 32, 44);
	add_Texture_To_Save("natures\\stump_1", 62, 90);
	add_Texture_To_Save("natures\\boulder_1", 66, 72);
	add_Texture_To_Save("natures\\boulder_2", 65, 78);
	add_Texture_To_Save("natures\\boulder_3", 60, 80);

	add_Texture_To_Save("natures\\column_2", 65, 85);
	add_Texture_To_Save("natures\\column_3", 65, 85);
	add_Texture_To_Save("natures\\stone_altar", 65, 85);
	add_Texture_To_Save("natures\\stone_platform", 65, 78);
	add_Texture_To_Save("natures\\driftwood", 59, 77);
	add_Texture_To_Save("natures\\rock_1", 32, 36);
	add_Texture_To_Save("natures\\rock_2", 32, 36);
	add_Texture_To_Save("natures\\reed_1", 32, 54);
	add_Texture_To_Save("natures\\reed_2", 32, 54);

	// small objects textures
	add_Texture_To_Save("smallObjects\\grass_1", 33, 32);
	add_Texture_To_Save("smallObjects\\grass_2", 33, 32);
	add_Texture_To_Save("smallObjects\\grass_3", 33, 32);

	// objects textures
	add_Texture_To_Save("objects\\palisade_1", 16, 112);
	add_Texture_To_Save("objects\\palisade_2", 16, 112);
	add_Texture_To_Save("objects\\stone_wall", 8, 56);
	add_Texture_To_Save("objects\\great_stone_wall", 16, 112);
	add_Texture_To_Save("objects\\well", 64, 96);
	add_Texture_To_Save("objects\\hunter_tent", 128, 175);
	add_Texture_To_Save("objects\\log_with_saw", 64, 70);
	add_Texture_To_Save("objects\\pile_of_wood_1", 64, 80);
	add_Texture_To_Save("objects\\pile_of_wood_2", 64, 80);
	add_Texture_To_Save("objects\\stone_altar_1", 66, 66);
	add_Texture_To_Save("objects\\wooden_stake_1", 34, 44);

	add_Animation_To_Save("objects\\brazier", 64, 64, 32, 40);

	// flat objects textures
	add_Texture_To_Save("flatObjects\\path_1", 32, 32);
	add_Texture_To_Save("flatObjects\\path_2", 32, 32);
	add_Texture_To_Save("flatObjects\\stonepath_1", 32, 32);
	add_Texture_To_Save("flatObjects\\stonepath_2", 32, 32);
	add_Texture_To_Save("flatObjects\\sandspath_1", 32, 32);
	add_Texture_To_Save("flatObjects\\sandspath_2", 32, 32);

	add_Texture_To_Save("flatObjects\\herb_1", 33, 32);
	add_Texture_To_Save("flatObjects\\herb_2", 33, 32);

	add_Texture_To_Save("flatObjects\\small_rock_1", 16, 16);
	add_Texture_To_Save("flatObjects\\small_rock_2", 16, 16);
	add_Texture_To_Save("flatObjects\\small_rock_3", 16, 16);
	add_Texture_To_Save("flatObjects\\small_rock_4", 16, 16);

	add_Texture_To_Save("flatObjects\\small_sands_rock_1", 16, 16);
	add_Texture_To_Save("flatObjects\\small_sands_rock_2", 16, 16);
	add_Texture_To_Save("flatObjects\\small_sands_rock_3", 16, 16);
	add_Texture_To_Save("flatObjects\\small_sands_rock_4", 16, 16);

	// doors textures
	add_Texture_To_Save("doors\\wooden_door[0]", 32, 63);
	add_Texture_To_Save("doors\\wooden_door[1]", 32, 63);
	add_Texture_To_Save("doors\\wooden_door[2]", 32, 63);
	add_Texture_To_Save("doors\\wooden_door[3]", 32, 63);

	add_Texture_To_Save("doors\\wooden_gate[0]", 64, 127);
	add_Texture_To_Save("doors\\wooden_gate[1]", 64, 127);
	add_Texture_To_Save("doors\\wooden_gate[2]", 64, 127);
	add_Texture_To_Save("doors\\wooden_gate[3]", 64, 127);

	add_Texture_To_Save("doors\\great_stone_gate[0]", 64, 127);
	add_Texture_To_Save("doors\\great_stone_gate[1]", 64, 127);
	add_Texture_To_Save("doors\\great_stone_gate[2]", 64, 127);
	add_Texture_To_Save("doors\\great_stone_gate[3]", 64, 127);

	// furnitures textures
	add_Texture_To_Save("furnitures\\table", 32, 32);
	add_Texture_To_Save("furnitures\\table_alchemist", 32, 32);
	add_Texture_To_Save("furnitures\\table_alchemist_2", 32, 32);
	add_Texture_To_Save("furnitures\\table_herbalist", 32, 32);
	add_Texture_To_Save("furnitures\\table_herbalist_2", 32, 32);
	add_Texture_To_Save("furnitures\\bench", 32, 32);
	add_Texture_To_Save("furnitures\\chest", 32, 32);
	add_Texture_To_Save("furnitures\\wardrobe", 32, 50);
	add_Texture_To_Save("furnitures\\bookshelf", 32, 50);
	add_Texture_To_Save("furnitures\\bookshelf_2", 32, 50);
	add_Texture_To_Save("furnitures\\furnace", 32, 50);
	add_Texture_To_Save("furnitures\\bed", 32, 50);
	add_Texture_To_Save("furnitures\\chair", 34, 38);
	add_Texture_To_Save("furnitures\\barrel", 34, 38);
	add_Texture_To_Save("furnitures\\shield_1", 32, 32);
	add_Texture_To_Save("furnitures\\shield_2", 32, 32);
	add_Texture_To_Save("furnitures\\shield_3", 32, 32);
	add_Texture_To_Save("furnitures\\lectern", 34, 38);

	// walls textures
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\empty_wall", 16, 16);

	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\mud_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\stone_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\wooden_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\brick_wall", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\mulch_wall", 16, 16);

	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\mud_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\stone_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\wooden_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\brick_wall_overgrown", 16, 16);
	add_Unique_Terrains_And_Walls_Textures_To_Save("walls\\mulch_wall_overgrown", 16, 16);


	add_Set_To_Save("walls\\set_mud_wall", 32, 32, 16, 16);
	add_Set_To_Save("walls\\set_stone_wall", 32, 32, 16, 16);
	add_Set_To_Save("walls\\set_wooden_wall", 32, 32, 16, 16);
	add_Set_To_Save("walls\\set_brick_wall", 32, 32, 16, 16);
	add_Set_To_Save("walls\\set_mulch_wall", 32, 32, 16, 16);

	// fortifications textures

	// buildings parts textures

	add_Texture_To_Save("buildings\\parts\\tile_left", 8, 8);
	add_Texture_To_Save("buildings\\parts\\tile_left_top", 8, 4);
	add_Texture_To_Save("buildings\\parts\\tile_left_bottom", 8, 4);
	add_Texture_To_Save("buildings\\parts\\tile_right", 8, 8);
	add_Texture_To_Save("buildings\\parts\\tile_right_top", 8, 4);
	add_Texture_To_Save("buildings\\parts\\tile_right_bottom", 8, 4);
	add_Texture_To_Save("buildings\\parts\\tile_center", 8, 8);
	add_Texture_To_Save("buildings\\parts\\tile_center_top", 8, 4);
	add_Texture_To_Save("buildings\\parts\\tile_center_bottom", 8, 4);

	add_Texture_To_Save("buildings\\parts\\window", 16, 16);
	add_Texture_To_Save("buildings\\parts\\window_2", 16, 16);
	add_Texture_To_Save("buildings\\parts\\bar", 32, 5);

	// items textures
	add_Texture_To_Save("items\\inventory", 28, 48);

	// bows
	add_Texture_To_Save("items\\bow", 32, 32);

	// weapons items
	add_Texture_To_Save("items\\club", 32, 32);
	add_Texture_To_Save("items\\knife", 32, 32);
	add_Texture_To_Save("items\\hatchet", 32, 32);
	add_Texture_To_Save("items\\sword", 32, 32);
	add_Texture_To_Save("items\\dagger", 32, 32);
	add_Texture_To_Save("items\\wooden club", 32, 32);
	add_Texture_To_Save("items\\long sword", 32, 32);
	add_Texture_To_Save("items\\curved sword", 32, 32);
	add_Texture_To_Save("items\\wide blade", 32, 32);
	add_Texture_To_Save("items\\gladius", 32, 32);
	add_Texture_To_Save("items\\iron club", 32, 32);
	add_Texture_To_Save("items\\axe", 32, 32);
	add_Texture_To_Save("items\\stone hammer", 32, 32);

	// helmets items
	add_Texture_To_Save("items\\skin helmet", 32, 32);
	add_Texture_To_Save("items\\wool hat", 32, 32);

	// armors items
	add_Texture_To_Save("items\\plate armor", 32, 32);
	add_Texture_To_Save("items\\chain mail", 32, 32);
	add_Texture_To_Save("items\\skin jacket", 32, 32);
	add_Texture_To_Save("items\\torn shirt", 32, 32);
	add_Texture_To_Save("items\\wool shirt", 32, 32);

	// pants items
	add_Texture_To_Save("items\\chain mail pants", 32, 32);
	add_Texture_To_Save("items\\skin pants", 32, 32);
	add_Texture_To_Save("items\\wool pants", 32, 32);

	// shields items
	add_Texture_To_Save("items\\shield", 32, 32);	// TO-DO to delete

	// herbs items
	add_Texture_To_Save("items\\mana plant", 30, 50);
	add_Texture_To_Save("items\\health herb", 32, 34);
	add_Texture_To_Save("items\\health root", 31, 46);
	add_Texture_To_Save("items\\health plant", 30, 44);
	add_Texture_To_Save("items\\mushroom", 30, 44);

	// potions items
	add_Texture_To_Save("items\\potion", 32, 32);

	// food items
	add_Texture_To_Save("items\\raw meat", 32, 32);
	add_Texture_To_Save("items\\roasted meat", 32, 32);

	// other items
	add_Texture_To_Save("items\\bone", 32, 32);
	add_Texture_To_Save("items\\bone", 40, 40);
	add_Texture_To_Save("items\\tooth", 32, 32);
	add_Texture_To_Save("items\\spike", 32, 32);
	add_Texture_To_Save("items\\wolf skin", 32, 32);


	// items sets
	std::vector < string > itemSets;
	itemSets.push_back("skin pants");
	itemSets.push_back("skin helmet");
	itemSets.push_back("wool hat");
	itemSets.push_back("wool pants");
	itemSets.push_back("wooden club");
	itemSets.push_back("axe");
	itemSets.push_back("club");
	itemSets.push_back("iron club");
	itemSets.push_back("stone hammer");
	itemSets.push_back("sword");
	itemSets.push_back("long sword");
	itemSets.push_back("gladius");
	itemSets.push_back("wide blade");
	itemSets.push_back("knife");
	itemSets.push_back("dagger");
	itemSets.push_back("hatchet");
	itemSets.push_back("curved sword");
	itemSets.push_back("chain mail pants");
	itemSets.push_back("shield");
	itemSets.push_back("bow");

	for (auto& set : itemSets) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save("sets\\items\\" + set + "\\idleTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\runTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\attackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackLeft" + to_string(i), 32, 58);
		}
	}

	std::vector < std::string > armorSets;
	armorSets.push_back("skin jacket");
	armorSets.push_back("torn shirt");
	armorSets.push_back("wool shirt");
	armorSets.push_back("chain mail");
	armorSets.push_back("plate armor");

	for (auto& set : armorSets) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save("sets\\items\\" + set + "\\idleTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\idleLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\runTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\runLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\attackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\attackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\bowAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\bowAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\bowAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\bowAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\magicAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\items\\" + set + "\\magicBuffTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicBuffRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicBuffBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\items\\" + set + "\\magicBuffLeft" + to_string(i), 32, 58);

		}
	}

	// monsters sets
	std::vector < string > monsters;
	monsters.push_back("dziobak");
	monsters.push_back("goblin");
	monsters.push_back("wilczur");
	monsters.push_back("jaszczur");
	monsters.push_back("niedzwiedz");
	monsters.push_back("szpon");
	monsters.push_back("kolcorozec");
	monsters.push_back("golem");
	monsters.push_back("troll");
	monsters.push_back("bies");

	for (auto& m : monsters) {
		for (short i = 0; i < 4; i++) {

			add_Texture_To_Save("monsters\\" + m, 63, 87);

			add_Texture_To_Save("monsters\\" + m + "\\idleTop" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\idleRight" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\idleBottom" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\idleLeft" + to_string(i), 63, 87);

			add_Texture_To_Save("monsters\\" + m + "\\attackTop" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\attackRight" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\attackBottom" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\attackLeft" + to_string(i), 63, 87);

			add_Texture_To_Save("monsters\\" + m + "\\runTop" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\runRight" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\runBottom" + to_string(i), 63, 87);
			add_Texture_To_Save("monsters\\" + m + "\\runLeft" + to_string(i), 63, 87);

		}
	}

	// body sets
	std::vector < string > bodies;
	bodies.push_back("man");
	bodies.push_back("woman");

	for (auto& set : bodies) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save("sets\\body\\" + set + "\\idleTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\idleRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\idleBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\idleLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\body\\" + set + "\\runTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\runRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\runBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\runLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\body\\" + set + "\\attackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\attackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\attackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\attackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\body\\" + set + "\\bowAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\bowAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\bowAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\bowAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\body\\" + set + "\\magicAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\body\\" + set + "\\magicBuffTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicBuffRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicBuffBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\body\\" + set + "\\magicBuffLeft" + to_string(i), 32, 58);

		}
	}

	// head sets
	std::vector < string > heads;
	heads.push_back("man-black-haired");
	heads.push_back("boy-black-haired");
	heads.push_back("woman-black-haired");

	heads.push_back("man-brown-haired");
	heads.push_back("boy-brown-haired");
	heads.push_back("woman-brown-haired");

	heads.push_back("man-gray-haired");
	heads.push_back("boy-gray-haired");
	heads.push_back("woman-gray-haired");

	heads.push_back("man-red-haired");
	heads.push_back("boy-red-haired");
	heads.push_back("woman-red-haired");

	for (auto& set : heads) {
		for (short i = 0; i < 4; i++) {
			add_Texture_To_Save("sets\\head\\" + set + "\\idleTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\idleRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\idleBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\idleLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\head\\" + set + "\\runTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\runRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\runBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\runLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\head\\" + set + "\\attackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\attackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\attackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\attackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\head\\" + set + "\\bowAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\bowAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\bowAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\bowAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\head\\" + set + "\\magicAttackTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicAttackRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicAttackBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicAttackLeft" + to_string(i), 32, 58);

			add_Texture_To_Save("sets\\head\\" + set + "\\magicBuffTop" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicBuffRight" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicBuffBottom" + to_string(i), 32, 58);
			add_Texture_To_Save("sets\\head\\" + set + "\\magicBuffLeft" + to_string(i), 32, 58);

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
	string name;
	float cx, cy;	// coordinates of center on the texture
	sf::Texture* texture = nullptr;

	SingleTexture(string pathfile, float cx, float cy) {

		name = "";

		short i = int(pathfile.size()) - 5;
		while (i >= 0)
			name = pathfile[i--] + name;

		texture = new sf::Texture;
		texture->loadFromFile("assets\\" + pathfile);
		texture->setRepeated(true);

		this->cx = cx;
		this->cy = cy;

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

	SingleTexture(string name, sf::Image image, float cx, float cy) {

		this->name = name;

		texture = new sf::Texture;
		texture->loadFromImage(image);
		texture->setRepeated(true);

		this->cx = cx;
		this->cy = cy;
		//cout << "load texture from set as: " << name << endl;
	}


	SingleTexture(sf::Image image) {

		name = "texture";

		this->texture = new sf::Texture();
		this->texture->loadFromImage(image);
		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
	}

	SingleTexture(std::string pathfile, unsigned width, unsigned height, std::vector<sf::Uint8>& pixels, float cx = 0, float cy = 0) {

		this->name = pathfile;

		texture = new sf::Texture;

		texture->create(width, height);
		texture->update(pixels.data());
		texture->setRepeated(true);

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

		std::string fileName(nameLength, '\0');
		packet.read(&fileName[0], nameLength);
		//std::cout << "name: " << fileName << "\n";

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
				std::cerr << "Nie udało się załadować obrazka: " << "assets\\" + fileName + ".png" << "(" << i << ")" << "\n";
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
				std::cerr << "Nie udało się załadować obrazka: " << "assets\\" + fileName + ".png" << "(" << i << ")" << "\n";
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

						SingleTexture* new_texture = new SingleTexture(fileName + "_" + to_string(counter), tile, cx, cy);
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
				std::cerr << "Nie udało się załadować obrazka: " << "assets\\" + fileName + ".png" << "(" << i << ")" << "\n";
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

					SingleTexture* new_texture = new SingleTexture(fileName + "[" + to_string(counter) + "]", tile, cx, cy);
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


SingleTexture* getSingleTexture(string name) {

	for (auto& t : singleTextures) {
		if (t->name == name) {
			return t;
		}
	}

	std::cout << "error - get Texture - Texture: \"" << name << "\" not exists\n";
	return nullptr;
}

std::vector < SingleTexture* > getAnimation(string name) {

	std::vector < SingleTexture* > animation;
	animation.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name + "[") == 0)
			animation.push_back(tex);

	if (animation.empty()) {

		SingleTexture* tex = getSingleTexture(name);
		if (tex != nullptr)
			animation.push_back(tex);
	}

	if (animation.empty()) {
		std::cout << "error - get Animation - Animation: \"" << name << "\" is empty\n";
	}

	return animation;
}

std::vector < SingleTexture* > getSingleTextures(string name) {

	std::vector < SingleTexture* > textures;
	textures.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name) == 0)
			textures.push_back(tex);

	if (textures.empty()) {
		std::cout << "error - get Textures - Textures: \"" << name << "\" is empty\n";
	}

	return textures;
}

void loadSingleTexture(string pathfile, float cx, float cy) {
	singleTextures.push_back(new SingleTexture(pathfile, cx, cy));
}

void loadTextureSets(string pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;
	image.loadFromFile("assets\\" + pathfile + ".png");

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
				SingleTexture* new_texture = new SingleTexture(pathfile + "_" + to_string(counter), tile, cx, cy);
				//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
				singleTextures.push_back(new_texture);

				counter += 1;

			}

		}

}

void loadAnimation(string pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;
	image.loadFromFile("assets\\" + pathfile + ".png");

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

			SingleTexture* new_texture = new SingleTexture(pathfile + "[" + to_string(counter) + "]", tile, cx, cy);
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

	std::vector<SingleTexture*> tiles = getSingleTextures("tiles\\tile_");
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
	loadSingleTexture("noise.png", 256, 256);
	loadSingleTexture("noise2.png", 256, 256);
	loadSingleTexture("empty.png", 32, 32);

	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("GUI\\slot1.png", 40, 40);
	loadSingleTexture("GUI\\slot2.png", 32, 32);
	loadSingleTexture("GUI\\selector.png", 40, 40);

	loadSingleTexture("GUI\\corner.png", 4, 4);
	loadSingleTexture("GUI\\border_horizontal.png", 3, 3);
	loadSingleTexture("GUI\\border_vertical.png", 3, 3);

	loadSingleTexture("GUI\\infoPanel.png", 300, 75);
	loadSingleTexture("GUI\\bigPanel.png", 300, 200);

	loadSingleTexture("GUI\\wideArrowUp1.png", 80, 20);
	loadSingleTexture("GUI\\wideArrowUp2.png", 80, 20);
	loadSingleTexture("GUI\\wideArrowDown1.png", 160, 18.5f);
	loadSingleTexture("GUI\\wideArrowDown2.png", 160, 18.5f);

	// group buttons textures
	loadSingleTexture("GUI\\groupButtons\\groupButton_to_left.png", 17, 52);
	loadSingleTexture("GUI\\groupButtons\\groupButton_to_right.png", 17, 52);
	
	loadSingleTexture("GUI\\groupButtons\\groupButton.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-terrain.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-highlands.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-floors.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-water.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-furnitures.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-walls.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-monsters.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-flat_objects.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-items.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-natures.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-smallObjects.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-objects.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-buildings.png", 34, 26);
	loadSingleTexture("GUI\\groupButtons\\groupButton-directions.png", 34, 26);

	// small buttons textures
	loadSingleTexture("GUI\\smallButtons\\smallbutton.png", 20, 20);
	loadSingleTexture("GUI\\smallButtons\\smallbutton-ArrowUp.png", 20, 20);
	loadSingleTexture("GUI\\smallButtons\\smallbutton-ArrowDown.png", 20, 20);
	loadSingleTexture("GUI\\smallButtons\\smallbutton-ArrowLeft.png", 20, 20);
	loadSingleTexture("GUI\\smallButtons\\smallbutton-ArrowRight.png", 20, 20);

	// tool butttons textures
	loadSingleTexture("GUI\\toolButtons\\toolbutton.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-cursor.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-brush.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-rect_brush.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-increase.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-decrease.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-rectangle.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-elipse.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-fill.png", 20, 16);
	loadSingleTexture("GUI\\toolButtons\\toolbutton-eraser.png", 20, 16);

	// space
	loadSingleTexture("GUI\\spacebutton.png", 80, 20);

	// scrollbar textures
	loadSingleTexture("GUI\\scrollbar_16\\bar_bottom.png", 8, 8);
	loadSingleTexture("GUI\\scrollbar_16\\bar_top.png", 8, 8);
	loadSingleTexture("GUI\\scrollbar_16\\bar_center.png", 8, 8);
	loadSingleTexture("GUI\\scrollbar_16\\scroll_bottom.png", 8, 8);
	loadSingleTexture("GUI\\scrollbar_16\\scroll_top.png", 8, 8);
	loadSingleTexture("GUI\\scrollbar_16\\scroll_center.png", 8, 8);

	loadSingleTexture("GUI\\scrollbar_20\\bar_bottom.png", 10, 10);
	loadSingleTexture("GUI\\scrollbar_20\\bar_top.png", 10, 10);
	loadSingleTexture("GUI\\scrollbar_20\\bar_center.png", 10, 10);
	loadSingleTexture("GUI\\scrollbar_20\\scroll_bottom.png", 10, 10);
	loadSingleTexture("GUI\\scrollbar_20\\scroll_top.png", 10, 10);
	loadSingleTexture("GUI\\scrollbar_20\\scroll_center.png", 10, 10);

	// checkbox textures
	loadSingleTexture("GUI\\checkbox\\check.png", 8, 8);

	// interactions textures
	loadSingleTexture("GUI\\hand.png", 8, 8);
	loadSingleTexture("GUI\\grey_hand.png", 8, 8);
	loadSingleTexture("GUI\\talk.png", 8, 8);

	// icons texture
	loadSingleTexture("GUI\\icons\\MapEditor_small_ico.png", 15, 15);
	loadSingleTexture("GUI\\icons\\dictionary.png", 15, 15);
	loadSingleTexture("GUI\\icons\\file.png", 15, 15);
	loadSingleTexture("GUI\\icons\\empty.png", 15, 15);

	// context menu textures
	loadSingleTexture("GUI\\context_menu\\btn_default.png", 15, 15);
	loadSingleTexture("GUI\\context_menu\\btn_info.png", 15, 15);
	loadSingleTexture("GUI\\context_menu\\btn_edit.png", 15, 15);
	loadSingleTexture("GUI\\context_menu\\btn_remove.png", 15, 15);
	loadSingleTexture("GUI\\context_menu\\btn_cancel.png", 15, 15);

	// character mnenu textures
	loadSingleTexture("GUI\\character_menu\\menu_slot.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_statistics.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_layout.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_equipment.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_inventory.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_dialogues.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\menu_quests.png", 32, 20);
	loadSingleTexture("GUI\\character_menu\\layout_slot.png", 40, 40);
	loadSingleTexture("GUI\\character_menu\\item_slot.png", 32, 32);
	loadSingleTexture("GUI\\character_menu\\direction_top.png", 32, 32);
	loadSingleTexture("GUI\\character_menu\\direction_bottom.png", 32, 32);
	loadSingleTexture("GUI\\character_menu\\direction_left.png", 32, 32);
	loadSingleTexture("GUI\\character_menu\\direction_right.png", 32, 32);


	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("tiles\\0_tileset.png", 0, 0);
	loadSingleTexture("tiles\\tile_0_water.png", 32, 32);
	loadSingleTexture("tiles\\tile_1_sands.png", 32, 32);
	loadSingleTexture("tiles\\tile_2_grass.png", 32, 32);
	loadSingleTexture("tiles\\tile_3_gravel.png", 32, 32);
	loadSingleTexture("tiles\\tile_4_steps.png", 32, 32);
	loadSingleTexture("tiles\\tile_5_highlands.png", 32, 32);
	loadSingleTexture("tiles\\tile_6.png", 32, 32);
	loadSingleTexture("tiles\\tile_7.png", 32, 32);
	loadSingleTexture("tiles\\tile_8.png", 32, 32);
	loadSingleTexture("tiles\\tile_9.png", 32, 32);
	loadSingleTexture("tiles\\tile_10.png", 32, 32);

	//generateTileSet();

	loadTextureSets("tiles\\set_0_water_sands", 64, 64, 32, 32);
	loadTextureSets("tiles\\set_0_sands_water", 64, 64, 32, 32);
	loadTextureSets("tiles\\set_1_sands_grass", 64, 64, 32, 32);
	loadTextureSets("tiles\\set_1_grass_sands", 64, 64, 32, 32);
	loadTextureSets("tiles\\set_2_grass_gravel", 64, 64, 32, 32);
	loadTextureSets("tiles\\set_2_gravel_grass", 64, 64, 32, 32);

	// FLOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("floors\\0_floorset.png", 0, 0);
	loadSingleTexture("floors\\floor_0.png", 32, 32);
	loadSingleTexture("floors\\floor_1.png", 32, 32);
	loadSingleTexture("floors\\floor_2.png", 32, 32);
	loadSingleTexture("floors\\floor_3.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("natures\\tree9.png", 129, 213);
	loadSingleTexture("natures\\bush_1.png", 32, 44);
	loadSingleTexture("natures\\stump_1.png", 62, 90);
	loadSingleTexture("natures\\boulder_1.png", 66, 72);
	loadSingleTexture("natures\\boulder_2.png", 65, 78);
	loadSingleTexture("natures\\boulder_3.png", 60, 80);

	loadSingleTexture("natures\\column_2.png", 65, 85);
	loadSingleTexture("natures\\column_3.png", 65, 85);
	loadSingleTexture("natures\\stone_altar.png", 65, 85);
	loadSingleTexture("natures\\stone_platform.png", 65, 78);
	loadSingleTexture("natures\\driftwood.png", 59, 77);
	loadSingleTexture("natures\\rock_1.png", 32, 36);
	loadSingleTexture("natures\\rock_2.png", 32, 36);
	loadSingleTexture("natures\\reed_1.png", 32, 54);
	loadSingleTexture("natures\\reed_2.png", 32, 54);

	// HIGHLANDS

	loadTextureSets("highlands\\low_highlands", 64, 64, 32, 32);
	loadTextureSets("highlands\\high_highlands", 64, 64, 32, 32);

	// SMALL OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("smallObjects\\grass_1.png", 33, 32);
	loadSingleTexture("smallObjects\\grass_2.png", 33, 32);
	loadSingleTexture("smallObjects\\grass_3.png", 33, 32);

	// OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("objects\\palisade_1.png", 16, 112);
	loadSingleTexture("objects\\palisade_2.png", 16, 112);
	loadSingleTexture("objects\\stone_wall.png", 8, 56);
	loadSingleTexture("objects\\great_stone_wall.png", 16, 112);
	loadSingleTexture("objects\\well.png", 64, 96);
	loadSingleTexture("objects\\hunter_tent.png", 128, 175);
	loadSingleTexture("objects\\log_with_saw.png", 64, 70);
	loadSingleTexture("objects\\pile_of_wood_1.png", 64, 80);
	loadSingleTexture("objects\\pile_of_wood_2.png", 64, 80);
	loadSingleTexture("objects\\stone_altar_1.png", 66, 66);

	loadAnimation("objects\\brazier", 64, 64, 32, 40);

	// FLAT OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("flatObjects\\path_1.png", 32, 32);
	loadSingleTexture("flatObjects\\path_2.png", 32, 32);
	loadSingleTexture("flatObjects\\stonepath_1.png", 32, 32);
	loadSingleTexture("flatObjects\\stonepath_2.png", 32, 32);
	loadSingleTexture("flatObjects\\sandspath_1.png", 32, 32);
	loadSingleTexture("flatObjects\\sandspath_2.png", 32, 32);

	loadSingleTexture("flatObjects\\herb_1.png", 33, 32);
	loadSingleTexture("flatObjects\\herb_2.png", 33, 32);

	loadSingleTexture("flatObjects\\small_rock_1.png", 16, 16);
	loadSingleTexture("flatObjects\\small_rock_2.png", 16, 16);
	loadSingleTexture("flatObjects\\small_rock_3.png", 16, 16);
	loadSingleTexture("flatObjects\\small_rock_4.png", 16, 16);

	loadSingleTexture("flatObjects\\small_sands_rock_1.png", 16, 16);
	loadSingleTexture("flatObjects\\small_sands_rock_2.png", 16, 16);
	loadSingleTexture("flatObjects\\small_sands_rock_3.png", 16, 16);
	loadSingleTexture("flatObjects\\small_sands_rock_4.png", 16, 16);

	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("items\\inventory.png", 28, 48);

	// BOWS
	loadSingleTexture("items\\bow.png", 32, 32);

	// WEAPONS
	loadSingleTexture("items\\club.png", 32, 32);
	loadSingleTexture("items\\knife.png", 32, 32);
	loadSingleTexture("items\\hatchet.png", 32, 32);
	loadSingleTexture("items\\sword.png", 32, 32);
	loadSingleTexture("items\\dagger.png", 32, 32);
	loadSingleTexture("items\\wooden club.png", 32, 32);
	loadSingleTexture("items\\long sword.png", 32, 32);
	loadSingleTexture("items\\curved sword.png", 32, 32);
	loadSingleTexture("items\\wide blade.png", 32, 32);
	loadSingleTexture("items\\gladius.png", 32, 32);
	loadSingleTexture("items\\iron club.png", 32, 32);
	loadSingleTexture("items\\axe.png", 32, 32);
	loadSingleTexture("items\\stone hammer.png", 32, 32);

	// HELMET
	loadSingleTexture("items\\skin helmet.png", 32, 32);
	loadSingleTexture("items\\wool hat.png", 32, 32);

	// ARMORS
	loadSingleTexture("items\\plate armor.png", 32, 32);
	loadSingleTexture("items\\chain mail.png", 32, 32);
	loadSingleTexture("items\\skin jacket.png", 32, 32);
	loadSingleTexture("items\\torn shirt.png", 32, 32);
	loadSingleTexture("items\\wool shirt.png", 32, 32);

	// PANTS
	loadSingleTexture("items\\chain mail pants.png", 32, 32);
	loadSingleTexture("items\\skin pants.png", 32, 32);
	loadSingleTexture("items\\wool pants.png", 32, 32);

	// SHIELDS
	loadSingleTexture("items\\shield.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadSingleTexture("items\\mana plant.png", 30, 50);
	loadSingleTexture("items\\health herb.png", 32, 34);
	loadSingleTexture("items\\health root.png", 31, 46);
	loadSingleTexture("items\\health plant.png", 30, 44);
	loadSingleTexture("items\\mushroom.png", 30, 44);

	// POTIONS
	loadSingleTexture("items\\potion.png", 32, 32);

	// FOOD
	loadSingleTexture("items\\raw meat.png", 32, 32);
	loadSingleTexture("items\\roasted meat.png", 32, 32);

	// OTHERS
	loadSingleTexture("items\\bone.png", 32, 32);
	loadSingleTexture("items\\bone.png", 40, 40);
	loadSingleTexture("items\\tooth.png", 32, 32);
	loadSingleTexture("items\\spike.png", 32, 32);
	loadSingleTexture("items\\wolf skin.png", 32, 32);

	// DOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("doors\\wooden_door[0].png", 32, 63);
	loadSingleTexture("doors\\wooden_door[1].png", 32, 63);
	loadSingleTexture("doors\\wooden_door[2].png", 32, 63);
	loadSingleTexture("doors\\wooden_door[3].png", 32, 63);

	loadSingleTexture("doors\\wooden_gate[0].png", 64, 127);
	loadSingleTexture("doors\\wooden_gate[1].png", 64, 127);
	loadSingleTexture("doors\\wooden_gate[2].png", 64, 127);
	loadSingleTexture("doors\\wooden_gate[3].png", 64, 127);

	loadSingleTexture("doors\\great_stone_gate[0].png", 64, 127);
	loadSingleTexture("doors\\great_stone_gate[1].png", 64, 127);
	loadSingleTexture("doors\\great_stone_gate[2].png", 64, 127);
	loadSingleTexture("doors\\great_stone_gate[3].png", 64, 127);


	// MONSTERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector < string > monsters;

	monsters.push_back("dziobak");
	monsters.push_back("goblin");
	monsters.push_back("wilczur");
	monsters.push_back("jaszczur");
	monsters.push_back("niedzwiedz");
	monsters.push_back("szpon");
	monsters.push_back("kolcorozec");
	monsters.push_back("golem");
	monsters.push_back("troll");
	monsters.push_back("bies");

	for (auto& m : monsters) {
		for (i = 0; i < 4; i++) {

			loadSingleTexture("monsters\\" + m + ".png", 63, 87);

			loadSingleTexture("monsters\\" + m + "\\idleTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\idleRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\idleBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\idleLeft" + to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters\\" + m + "\\attackTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\attackRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\attackBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\attackLeft" + to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters\\" + m + "\\runTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\runRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\runBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters\\" + m + "\\runLeft" + to_string(i) + ".png", 63, 87);

		}
	}

	// FURNITURES
	loadSingleTexture("furnitures\\table.png", 32, 32);
	loadSingleTexture("furnitures\\table_alchemist.png", 32, 32);
	loadSingleTexture("furnitures\\table_alchemist_2.png", 32, 32);
	loadSingleTexture("furnitures\\table_herbalist.png", 32, 32);
	loadSingleTexture("furnitures\\table_herbalist_2.png", 32, 32);
	loadSingleTexture("furnitures\\bench.png", 32, 32);
	loadSingleTexture("furnitures\\chest.png", 32, 32);
	loadSingleTexture("furnitures\\wardrobe.png", 32, 50);
	loadSingleTexture("furnitures\\bookshelf.png", 32, 50);
	loadSingleTexture("furnitures\\furnace.png", 32, 50);
	loadSingleTexture("furnitures\\bed.png", 32, 50);
	loadSingleTexture("furnitures\\chair.png", 34, 38);
	loadSingleTexture("furnitures\\barrel.png", 34, 38);
	loadSingleTexture("furnitures\\shield_1.png", 32, 32);
	loadSingleTexture("furnitures\\shield_2.png", 32, 32);
	loadSingleTexture("furnitures\\shield_3.png", 32, 32);
	loadSingleTexture("furnitures\\lectern.png", 34, 38);


	// WALLS
	loadSingleTexture("walls\\empty_wall.png", 16, 16);

	loadSingleTexture("walls\\mud_wall.png", 16, 16);
	loadSingleTexture("walls\\stone_wall.png", 16, 16);
	loadSingleTexture("walls\\wooden_wall.png", 16, 16);
	loadSingleTexture("walls\\brick_wall.png", 16, 16);
	loadSingleTexture("walls\\mulch_wall.png", 16, 16);

	loadSingleTexture("walls\\mud_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls\\stone_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls\\wooden_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls\\brick_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls\\mulch_wall_overgrown.png", 16, 16);


	loadTextureSets("walls\\set_mud_wall", 32, 32, 16, 16);
	loadTextureSets("walls\\set_stone_wall", 32, 32, 16, 16);
	loadTextureSets("walls\\set_wooden_wall", 32, 32, 16, 16);
	loadTextureSets("walls\\set_brick_wall", 32, 32, 16, 16);
	loadTextureSets("walls\\set_mulch_wall", 32, 32, 16, 16);

	// FORTIFICATIONS

	// BODY SETS
	std::vector < string > bodySets;
	bodySets.clear();
	bodySets.push_back("boy-redhaired");		// face without beard
	bodySets.push_back("boy-blackhaired");		// face without beard
	bodySets.push_back("boy-brownhaired");		// face without beard
	bodySets.push_back("boy-greyhaired");		// face without beard

	bodySets.push_back("man-redhaired");		// face have a beard
	bodySets.push_back("man-blackhaired");		// face have a beard
	bodySets.push_back("man-brownhaired");		// face have a beard
	bodySets.push_back("man-greyhaired");		// face have a beard

	bodySets.push_back("woman-redhaired");		// face with long hair
	bodySets.push_back("woman-blackhaired");	// face with long hair
	bodySets.push_back("woman-brownhaired");	// face with long hair
	bodySets.push_back("woman-greyhaired");	// face with long hair


	for (auto& set : bodySets) {
		for (i = 0; i < 4; i++) {

			loadSingleTexture("sets\\body\\" + set + "\\idleTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\idleRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\idleBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\idleLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\body\\" + set + "\\runTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\runRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\runBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\runLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\body\\" + set + "\\attackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\attackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\attackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\attackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\body\\" + set + "\\bowAttackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\bowAttackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\bowAttackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\bowAttackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\body\\" + set + "\\magicAttackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicAttackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicAttackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicAttackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\body\\" + set + "\\magicBuffTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicBuffRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicBuffBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\body\\" + set + "\\magicBuffLeft" + to_string(i) + ".png", 32, 58);

		}
	}


	// ITEMS SETS
	std::vector < string > itemSets;
	itemSets.clear();
	itemSets.push_back("skin pants");
	itemSets.push_back("skin helmet");
	itemSets.push_back("wool hat");
	itemSets.push_back("wool pants");
	itemSets.push_back("wooden club");
	itemSets.push_back("axe");
	itemSets.push_back("club");
	itemSets.push_back("iron club");
	itemSets.push_back("stone hammer");
	itemSets.push_back("sword");
	itemSets.push_back("long sword");
	itemSets.push_back("gladius");
	itemSets.push_back("wide blade");
	itemSets.push_back("knife");
	itemSets.push_back("dagger");
	itemSets.push_back("hatchet");
	itemSets.push_back("curved sword");
	itemSets.push_back("chain mail pants");
	itemSets.push_back("shield");
	itemSets.push_back("bow");

	for (auto& set : itemSets) {

		for (i = 0; i < 4; i++) {

			loadSingleTexture("sets\\items\\" + set + "\\idleTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\runTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\attackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}

	std::vector < string > armorSets;
	armorSets.push_back("skin jacket");
	armorSets.push_back("torn shirt");
	armorSets.push_back("wool shirt");
	armorSets.push_back("chain mail");
	armorSets.push_back("plate armor");

	for (auto& set : armorSets) {

		for (i = 0; i < 4; i++) {

			loadSingleTexture("sets\\items\\" + set + "\\idleTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\idleLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\runTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\runLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\attackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\attackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\bowAttackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\bowAttackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\bowAttackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\bowAttackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\magicAttackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicAttackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicAttackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicAttackLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets\\items\\" + set + "\\magicBuffTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicBuffRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicBuffBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets\\items\\" + set + "\\magicBuffLeft" + to_string(i) + ".png", 32, 58);

		}
	}

	// BUILDING PARTS

	loadSingleTexture("buildings\\parts\\tile_left.png", 8, 8);
	loadSingleTexture("buildings\\parts\\tile_left_top.png", 8, 4);
	loadSingleTexture("buildings\\parts\\tile_left_bottom.png", 8, 4);
	loadSingleTexture("buildings\\parts\\tile_right.png", 8, 8);
	loadSingleTexture("buildings\\parts\\tile_right_top.png", 8, 4);
	loadSingleTexture("buildings\\parts\\tile_right_bottom.png", 8, 4);
	loadSingleTexture("buildings\\parts\\tile_center.png", 8, 8);
	loadSingleTexture("buildings\\parts\\tile_center_top.png", 8, 4);
	loadSingleTexture("buildings\\parts\\tile_center_bottom.png", 8, 4);

	loadSingleTexture("buildings\\parts\\window.png", 16, 16);
	loadSingleTexture("buildings\\parts\\window_2.png", 16, 16);
	loadSingleTexture("buildings\\parts\\bar.png", 32, 5);

	std::cout << "wczytano " << singleTextures.size() << " tekstur\n";

}



#endif