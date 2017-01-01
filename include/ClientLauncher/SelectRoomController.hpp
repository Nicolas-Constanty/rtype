//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_LOGGERCONTROLLER_HPP
#define RTYPE_LOGGERCONTROLLER_HPP

#include "Common/DLLexport.hpp"
#include "SaltyEngine/SFML/TextBox.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "RoomNetworkSaltyEngine/ITransitionNetworkManager.hpp"

class LIB_EXPORT SelectRoomController : public SaltyEngine::SaltyBehaviour, public ITransitionNetworkManager
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

    /**
 * @brief Implement ITransitionNetworkManager
 */
    void onGetAUTHENTICATE(AUTHENTICATEPackageRoom const& room) override;
    void onGetCREATE(CREATEPackageRoom const& room) override;
    void onGetJOIN(JOINPackageRoom const& room) override;
    void onGetQUIT(QUITPackageRoom const& room) override;
    void onGetPLUGGED(PLUGGEDPackageRoom const& room) override;
    void onGetSWAP(SWAPPackageRoom const& room) override;
    void onGetGET(GETPackageRoom const& room) override;
    void onGetFAILURE(FAILUREPackageRoom const& room) override;
    void onGetLAUNCH(LAUNCHPackageRoom const& room) override;
    void onGetDELETE(DELETEPackageRoom const& room) override;
    void onGetCHAT(CHATPackageRoom const& room) override;

private:
    SaltyEngine::GameObject *m_textBox = nullptr;
    SaltyEngine::GameObject *m_buttonSubmit = nullptr;
    SaltyEngine::GUI::SFML::Button *m_submit = nullptr;
    SaltyEngine::GUI::SFML::TextBox *m_text = nullptr;
    SaltyEngine::GameObject *m_roomNetworkManager = nullptr;
};

#endif //RTYPE_LOGGERCONTROLLER_HPP
