#ifndef Borders_hpp
#define Borders_hpp

class Borders : public sf::Drawable, public sf::Transformable {
public:
	sf::Vector2i coords;

	sf::VertexArray outlines;

	std::vector < short > tiles;

	Borders() {

	}


	void generate(Terrain* terrain, Terrain* topTerrain, Terrain* bottomTerrain, Terrain* leftTerrain, Terrain* rightTerrain) {

		outlines.clear();
		outlines.setPrimitiveType(sf::Quads);

		//cout << "coords " << terrain->coords.x / 16 << " " << terrain->coords.y / 16 << "\n";

		short x, y;
		int coord_x, coord_y;
		float lineThickness = 2.0f; // Grubość linii

		for (short i = 0; i < terrain->tiles.size(); i++) {

			x = i % 16;
			y = i / 16;

			coord_x = (terrain->coords.x + x) * tileSide;
			coord_y = (terrain->coords.y + y) * tileSide;

			short tileValue;

			// GÓRNA KRAWĘDŹ

			if (y == 0) {
				(topTerrain != nullptr) ? tileValue = topTerrain->tiles[15 * 16 + x] : tileValue = -1;
			}
			else
				tileValue = terrain->tiles[i - 16];

			if (terrain->tiles[i] != tileValue) {
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + lineThickness / 2), sf::Color::Black));
			}

			// DOLNA KRAWĘDŹ

			if (y == 15) {
				(bottomTerrain != nullptr) ? tileValue = bottomTerrain->tiles[x] : tileValue = -1;
			}
			else
				tileValue = terrain->tiles[i + 16];

			if (terrain->tiles[i] != tileValue) {
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + tileSide - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + tileSide - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + tileSide + lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + tileSide + lineThickness / 2), sf::Color::Black));
			}

			// LEWA KRAWĘDŹ

			if (x == 0) {
				(leftTerrain != nullptr) ? tileValue = leftTerrain->tiles[i + 16 - 1] : tileValue = -1;
			}
			else
				tileValue = terrain->tiles[i - 1];

			if (terrain->tiles[i] != tileValue) {
				outlines.append(sf::Vertex(sf::Vector2f(coord_x - lineThickness / 2, coord_y), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + lineThickness / 2, coord_y), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + lineThickness / 2, coord_y + tileSide), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x - lineThickness / 2, coord_y + tileSide), sf::Color::Black));
			}

			// PRAWA KRAWĘDŹ

			if (x == 15) {
				(rightTerrain != nullptr) ? tileValue = rightTerrain->tiles[i - 16 + 1] : tileValue = -1;
			}
			else
				tileValue = terrain->tiles[i + 1];

			if (terrain->tiles[i] != tileValue) {
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide - lineThickness / 2, coord_y), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide + lineThickness / 2, coord_y), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide + lineThickness / 2, coord_y + tileSide), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide - lineThickness / 2, coord_y + tileSide), sf::Color::Black));
			}

		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(outlines, states);
	}
};

#endif