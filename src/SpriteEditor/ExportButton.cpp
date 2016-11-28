#include "SpriteEditor/ExportButton.hpp"

#define EXPORT_DIRECTORY "../../../Assets/Sprites/"

namespace SpriteEditor
{
	ExportButton::ExportButton(const sf::Texture &texture, const sf::Texture &over, DialogBox &db) : Button(texture, over), m_db(db) {}

	ExportButton::~ExportButton() {}

	void ExportButton::Export(const std::string & name, const std::string &content, std::string &f)
	{
		std::ofstream myfile;
		std::replace(f.begin(), f.end(), '\\', '/');
		myfile.open(EXPORT_DIRECTORY + name);
		myfile << "{" << std::endl;
		myfile << "\t" << "\"name\" : " << "\"" << f  << "\"," << std::endl;
		myfile << content;
		myfile << "}" << std::endl;
		myfile.close();
	}

	void ExportButton::OnClic(const sf::Event & ev)
	{
		sf::FloatRect rect = m_sprite.getGlobalBounds();
		if (ev.mouseButton.x > rect.left && ev.mouseButton.y > rect.top &&
			ev.mouseButton.x < rect.left + rect.width && ev.mouseButton.y < rect.top + rect.height)
		{
			m_db.Open();
		}
	}
}