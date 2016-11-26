#pragma once

#ifndef EXPORTBUTTON_HPP_
#define EXPORTBUTTON_HPP_

#include <iostream>
#include <fstream>
#include "SpriteEditor/Button.hpp"
#include "SpriteEditor/DialogBox.hpp"

namespace SpriteEditor
{
	class ExportButton : public Button
	{
	public:
		ExportButton(const sf::Texture &texture, const sf::Texture &over, DialogBox &db);
		~ExportButton();

		void Export(const std::string & name, const std::string &content, std::string &f);
		void OnClic(const sf::Event &ev);

	private:
		DialogBox &m_db;
	};
}

#endif // !EXPORTBUTTON_HPP_

