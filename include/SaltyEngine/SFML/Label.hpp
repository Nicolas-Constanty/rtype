//
// Created by nicolas-constanty on 20/12/16.
//

#ifndef RTYPE_LABEL_HPP
#define RTYPE_LABEL_HPP

#include "SaltyEngine/GUI/UIBehaviour.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML {

            class Label : public GUI::UIBehaviour, public sf::Text
            {
            public:
                Label(GameObject *gameObj, const std::string &text, unsigned int size, const sf::Font *fnt, const sf::Color &col = sf::Color::White);

            private:
                std::string m_data;

            public:
                void SetText(const std::string &txt);

                const std::string &GetText() const;

                const Label &operator+=(const std::string &);

                void Clear();
            };
        }
    }
}

#endif //RTYPE_LABEL_HPP
