//
// Created by gaspar_q on 12/15/16.
//

#ifndef RTYPE_APREFAB_HPP
#define RTYPE_APREFAB_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Rtype/Game/Client/GameManager.hpp>

/**
 * @brief Basic rtype prefab that other prefabs has to inherit from. Allow the prefab to send package through the network.
 */
class PREF_EXPORT RtypePrefab : public SaltyEngine::SaltyBehaviour
{
public:
    RtypePrefab(std::string const &name, SaltyEngine::GameObject *gameObject);
    ~RtypePrefab();

protected:
    void LoadManager();
    bool isServerSide() const;
    GameManager *getManager();

protected:
    /**
     * @brief Allow prefab to Broadcast reliable packages
     * @tparam Pack The packet type to send
     * @tparam Args Types of arguments to pass at <pack> construction
     * @param args The arguments to pass at <pack> construction
     */
    template <typename Pack, typename ... Args>
    void BroadCastReliable(Args ... args)
    {
        _BroadcastPackage<Pack>(&Network::UDP::AUDPConnection::SendReliable<Pack>, args...);
    }

    /**
     * @brief Allow prefab to Broadcast a package in non reliable mode
     * @tparam Pack Pack The packet type to send
     * @tparam Args Args Types of arguments to pass at <pack> construction
     * @param args args The arguments to pass at <pack> construction
     */
    template <typename Pack, typename ... Args>
    void BroadcastPackage(Args ... args)
    {
        _BroadcastPackage<Pack>(&Network::Core::BasicConnection::SendData<Pack>, args...);
    }

    /**
     * @brief Allow prefab to send a reliable package
     * @tparam Pack Pack The packet type to send
     * @tparam Args Args Types of arguments to pass at <pack> construction
     * @param args args The arguments to pass at <pack> construction
     */
    template <typename Pack, typename ... Args>
    void SendPackageReliable(Args ... args)
    {
        _SendPackage<Pack>(&Network::UDP::AUDPConnection::SendReliable<Pack>, args...);
    }

    /**
     * @brief Allow prefab to send a package in non reliable mode
     * @tparam Pack Pack The packet type to send
     * @tparam Args Args Types of arguments to pass at <pack> construction
     * @param args args The arguments to pass at <pack> construction
     */
    template <typename Pack, typename ... Args>
    void SendPackage(Args ... args)
    {
        _SendPackage<Pack>(&Network::Core::BasicConnection::SendData<Pack>, args...);
    }

private:
    /**
     * @brief Internal method for sending packages
     * @tparam Pack Pack The packet type to send
     * @tparam Send The type of method pointer to call
     * @tparam Args Args Types of arguments to pass at <pack> construction
     * @param sender The member pointer to call
     * @param args args The arguments to pass at <pack> construction
     * @internal
     */
    template <typename Pack, typename Send, typename ... Args>
    void _SendPackage(Send sender, Args ... args)
    {
        getManager()->SendPackage<Pack>(sender, args...);
    }

    /**
     * @brief Internal method for broadcasting package
     * @tparam Pack Pack The packet type to send
     * @tparam Send The type of method pointer to call
     * @tparam Args Args Types of arguments to pass at <pack> construction
     * @param sender The member pointer to call
     * @param args args The arguments to pass at <pack> construction
     * @internal
     */
    template <typename Pack, typename Send, typename ... Args>
    void _BroadcastPackage(Send sender, Args ... args)
    {
        getManager()->BroadCastPackage<Pack>(sender, args...);
    }

private:
    GameManager *m_manager;
};


#endif //RTYPE_APREFAB_HPP
