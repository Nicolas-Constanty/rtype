#pragma once

#ifndef PLAYER_CONTROLLER_HPP_
#define PLAYER_CONTROLLER_HPP_

#include "Rtype/Game/Client/GameManager.hpp"
#include "Prefabs/GenericController.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"

class PodController;

typedef struct InformationPlayerShot {
    int power;
    SaltyEngine::GameObject *laser;
    std::string laserString;
} InformationPlayerShot;

//todo add method to check if a pod is already attached to it
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
		void OnCollisionEnter(ICollider *collider);
		void SetColor(unsigned char color);
        void SetHighScore(int highScore);
		int GetHighScore() const;
		bool IsUpdateHighScore() const;
		void SetUpdateHighScore(bool update);
		double speed;


	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			return new PlayerController(obj);
		}

	public:
		void	OnBeamAction();
        int 	OnShotAction();

	public:
		PodController	*FindFirstAvailablePod();

	public:
		double mticks()
		{
			typedef std::chrono::duration<float, std::milli> duration;

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
		bool Attach(PodController *toattach);
		bool Launch();
		bool Call();
		bool HasPod() const;

    public:
		clock::time_point start;

	private:
		double power;

	private:
		unsigned int	idShot;

	public:
        GameObject     *beamShot;
		int				beamServerID = 0;
		GameObject		*m_beamSFX = nullptr;

	private:
		int				playerID;
		PodController	*pod;
        int             highScore;
		bool			updateHighScore = true;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !PLAYER_CONTROLLER_HPP_
