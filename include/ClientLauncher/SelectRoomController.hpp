//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_LOGGERCONTROLLER_HPP
#define RTYPE_LOGGERCONTROLLER_HPP

#include "Common/DLLexport.hpp"
#include "SaltyEngine/SFML/TextBox.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/GameObject.hpp"

class LIB_EXPORT SelectRoomController : public SaltyEngine::SaltyBehaviour
{
public:
    explicit SelectRoomController(SaltyEngine::GameObject *obj);

    virtual ~SelectRoomController();
    void Start() override;

    void OnMouseEnter() override;

    void OnMouseOver() override;

    void OnMouseExit() override;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj);

private:
    SaltyEngine::GameObject *m_textBox = nullptr;
    SaltyEngine::GameObject *m_buttonSubmit = nullptr;
    SaltyEngine::GUI::SFML::Button *m_submit = nullptr;
    SaltyEngine::GUI::SFML::TextBox *m_text = nullptr;
};

#endif //RTYPE_LOGGERCONTROLLER_HPP
