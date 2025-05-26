#ifndef ProgressBar_hpp
#define ProgressBar_hpp

std::string shader_source = R"(
    uniform sampler2D texture;
    uniform float progress;
    void main()
    {
		vec4 tex_color = texture2D(texture, gl_TexCoord[0].xy);
		vec3 progress_color = vec3(65.0/255.0, 65.0/255.0, 65.0/255.0); 
		if (tex_color.rgb == progress_color && gl_TexCoord[0].x < progress) {
            //tex_color = vec4(0.75, 0.0, 0.0, 1.0); // Zmiana koloru na czerwony
			tex_color = vec4( 1.0-abs(gl_TexCoord[0].y - 0.5), 0.0, 0.0, 1.0);
        }
        gl_FragColor = tex_color;
    }
)";


class ProgressBar {
public:

	sf::Texture bar_texture;
	sf::Shader shader;
	sf::Sprite bar;
	sf::Vector2f position;

	ProgressBar() {
		bar_texture.loadFromFile("assets\\GUI\\progress_bar.png");

		shader.loadFromMemory(shader_source, sf::Shader::Fragment);

		position.x = float(window->getSize().x) / 2.0f;
		position.y = float(window->getSize().y) * 4.0f / 5.0f;

		bar.setTexture(bar_texture);
		bar.setOrigin(bar_texture.getSize().x / 2, bar_texture.getSize().y / 2);
		bar.setPosition(position);
	}

	~ProgressBar() { }

	void draw(float progress) {

		shader.setUniform("texture", bar_texture);
		shader.setUniform("progress", progress);

		window->clear();
		window->draw(bar, &shader);
		window->display();
	}
};

#endif