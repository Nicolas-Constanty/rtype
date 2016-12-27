#pragma once

#ifndef IBUTTONHANDLER_HPP_
#define IBUTTONHANDLER_HPP_

#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/GUI/Button.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		namespace SFML
		{
			class LIB_EXPORT Button : public ::SaltyEngine::GUI::Button
			{
			public:
				explicit Button(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);


				Button(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const norm, ::SaltyEngine::SFML::Sprite * const over);


				Button(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);

				virtual ~Button() {};

			public:
				void OnPointerClick() override {}; //	Registered IPointerClickHandler callback.
				void OnSubmit() override {}; //
				void SetOver(::SaltyEngine::SFML::Sprite* const sprite);
				void SetNormal(::SaltyEngine::SFML::Sprite* const sprite);

				::SaltyEngine::SFML::Sprite* GetOver(void) const;
				::SaltyEngine::SFML::Sprite* GetNormal(void) const;

			public:
				Event onClick;

			private:
				::SaltyEngine::SFML::Sprite			*m_normal;
				::SaltyEngine::SFML::Sprite			*m_over;
				::SaltyEngine::SFML::SpriteRenderer *m_sprr;

			public:
				virtual Component *CloneComponent(GameObject* const obj);
			};
		}
	}
}

#endif // !IBUTTONHANDLER_HPP_
