//
// Created by nicolas-constanty on 01/01/17.
//

#ifndef RTYPE_LABELLIST_HPP
#define RTYPE_LABELLIST_HPP

#include "SaltyEngine/SFML/Label.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML
        {
            class LIB_EXPORT LabelList : public GUI::UIBehaviour
            {
            public:
                LabelList(GameObject * const obj);
                virtual ~LabelList();

                void AddLabel(Label * const label);
                void RemoveLabel(size_t index);
                void RemoveAllLabel();

                virtual void OnGui() override;

                size_t GetIndex() const;
                const std::string &GetSelected();

                Component *CloneComponent(GameObject *const obj) override;

            private:
                std::vector<Label *> m_labels;
                long  m_index;
            };
        }
    }
}

#endif //RTYPE_LABELLIST_HPP
