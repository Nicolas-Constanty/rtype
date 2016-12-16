#pragma once

#ifndef PLAYER_CONTROLLER_HPP_
#define PLAYER_CONTROLLER_HPP_

#include "Rtype/Game/Client/GameManager.hpp"
#include "Prefabs/GenericController.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"

typedef struct InformationPlayerShot {
    int power;
    SaltyEngine::GameObject *laser;
    std::string laserString;
} InformationPlayerShot;

namespace SaltyEngine {
	class PlayerController : public AGenericController
	{
		typedef std::chrono::high_resolution_clock clock;

	public:
		constexpr static const std::chrono::milliseconds    timeoutShot = std::chrono::milliseconds(1000); // 1 second

	public:
		explicit PlayerController(GameObject* const gamObj);
		PlayerController(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
		double speed;


	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			return new PlayerController(obj);
		}

	public:
		void OnBeamAction();
        InformationPlayerShot *OnShotAction();

	public:
		double mticks()
		{
			typedef std::chrono::duration<float, std::milli> duration;

			//static  = clock::now();
			duration elapsed = clock::now() - start;
			return elapsed.count();
		}

	public:
        void Die() const override;


    public:
		void IncIdShot() {
			idShot += 1;
		}

		void SetPlayerID(int id);

		unsigned int GetIDShot() const;
		int GetPlayerID() const;

        void Move() override;

        void Shot() override;

		void Beam();

    public:
		clock::time_point start;

	private:
		double power;

	private:
		unsigned int	idShot;

	public:
        GameObject     *beamShot;
		int				playerID;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !PLAYER_CONTROLLER_HPP_
