#ifndef Water_hpp
#define Water_hpp

class WaterPrefab : public GameObject {
public:
	short id;
	TerrainPrefab* terrain;
	Shader* shader;

	WaterPrefab(std::wstring name, short id, TerrainPrefab* terrain) : GameObject(name) {
		type = GameObjectType::Water;

		this->terrain = terrain;
		this->id = id;

		if (terrain != nullptr)
			texture = terrain->texture;

		shader = getShader(L"shaders\\" + name);

		colliders[0]->shape->setPosition(position);
	}

	virtual ~WaterPrefab() {

	}

	virtual void update() {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
	}

	virtual void draw() {
		window->draw(*colliders[0]->shape);
	}
};

class Water : public sf::Drawable, public sf::Transformable {
public:
	int width, height;				// normal is a 16x16
	sf::Vector2i coords;			// multiply by 16x16
	sf::VertexArray vertexes;		// vertexes of water
	std::vector < short > tiles;	// tiles

	Water(int x, int y, int width, int height) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		tiles.resize(width * height, -1);
		generate();


	}

	void generate() {
		vertexes.clear();
		vertexes.setPrimitiveType(sf::Triangles);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (tiles[y * width + x] > -1)
				{
					sf::Vertex tile[6];

					int coord_x = (coords.x + x);
					int coord_y = (coords.y + y);

					tile[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
					tile[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

					short tu = (short(coord_x * tileSide) % 64) + ((tiles[y * width + x]) * 64);
					short tv = (short(coord_y * tileSide) % 64);

					tile[0].texCoords = sf::Vector2f(tu, tv);
					tile[1].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[2].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[3].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[4].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);

					for (int i = 0; i < 6; i++)
					{
						vertexes.append(tile[i]);
					}
				}
			}
		}
	}

	void edit(int x, int y, short value = -1) {
		tiles[y * width + x] = value;
		generate();
	}

	void edit(sf::Vector2f worldMousePosition, short value = -1) {

		short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
		short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		tiles[coord_y * width + coord_x] = value;
		generate();
	}
	void update() {

		
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &(*getSingleTexture(L"tiles\\0_tileset")->texture);
		states.shader = &(*getShader(L"shaders\\lake")->shader);
		target.draw(vertexes, states);
	}
};

std::vector < WaterPrefab* > waterGameObjects;
short countOfBasicWater;

void createWaterPrefabs() {

	waterGameObjects.clear();

	waterGameObjects.push_back(new WaterPrefab(L"empty", 0, nullptr));
	waterGameObjects.push_back(new WaterPrefab(L"palette_lake", 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[0])));
	countOfBasicWater = 2;

	/////////////////////////////////////////////////////
	for (int i = 0; i < countOfBasicWater; i++) {

		std::wstring shader_name = waterGameObjects[i + 1]->name;

		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 0])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 1])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 2])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 3])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 4])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 5])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 6])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 7])));

		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 8])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 9])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 10])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 11])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 12])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 13])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 14])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 15])));

	}


}

#endif