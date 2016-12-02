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
			class Button : public ::SaltyEngine::GUI::Button
			{
			public:
				explicit Button(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite)
					: GUI::Button("SMFLButton", gameObj), m_normal(sprite), m_over(sprite)
				{
					m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
				}

				Button(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite)
					: GUI::Button(name, gameObj), m_normal(sprite), m_over(sprite)
				{
					m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
				}

				virtual ~Button() {};

			public:
				void OnPointerClick() override {}; //	Registered IPointerClickHandler callback.
				void OnSubmit() override {}; //
				void SetOver(::SaltyEngine::SFML::Sprite* const sprite)
				{
					m_over = sprite;
				}
				void SetNormal(::SaltyEngine::SFML::Sprite* const sprite)
				{
					m_normal = sprite;
				}

				::SaltyEngine::SFML::Sprite* GetOver(void) const
				{
					return (m_over);
				}
				::SaltyEngine::SFML::Sprite* GetNormal(void) const
				{
					return (m_normal);
				}

			public:
				Event onClick;

			private:
				::SaltyEngine::SFML::Sprite			*m_normal;
				::SaltyEngine::SFML::Sprite			*m_over;
				::SaltyEngine::SFML::SpriteRenderer *m_sprr;

			public:
				virtual Component *CloneComponent(GameObject* const obj) {
					return new Button(obj, m_over);
				}
			};
		}
	}
}

#endif // !IBUTTONHANDLER_HPP_
