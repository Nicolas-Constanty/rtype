#pragma once

#ifndef PLAYER_CONTROLLER_HPP_
#define PLAYER_CONTROLLER_HPP_

#include <Prefabs/CommonPlayer/CommonPlayerController.hpp>
#include "Rtype/Game/Client/GameManager.hpp"
#include "Prefabs/GenericController.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"

class PodController;

typedef struct InformationPlayerShot {
    int power;
    SaltyEngine::GameObject *laser;
    std::string laserString;
} InformationPlayerShot;

class PodHandler;

//todo add method to check if a pod is already attached to it
namespace SaltyEngine {
	class LIB_EXPORT PlayerController : public AGenericController
	{
		typedef std::chrono::high_resolution_clock clock;

	public:
		constexpr static const std::chrono::milliseconds    timeoutShot = std::chrono::milliseconds(1000); // 1 second
		static const float    timeoutDeath;
		static const float    timeoutInvicible;

	public:
		explicit PlayerController(GameObject* const gamObj);
		PlayerController(const std::string &name, GameObject* const gamObj);

	public:
		void Start();
		void FixedUpdate();

	public:
		void SetColor(unsigned char color);
        void SetHighScore(int highScore);
		int GetHighScore() const;
		bool IsUpdateHighScore() const;
		void SetUpdateHighScore(bool update);

	public:
		float speed;


	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			return new PlayerController(obj);
		}

	public:
		void	OnBeamAction();
        int 	OnShotAction();

	public:
		double mticks()
		{
			typedef std::chrono::duration<float, std::milli> duration;

			duration elapsed = clock::now() - start;
			return elapsed.count();
		}

	public:
        void Die() { common->Die(); };

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
        void TakeDamage(int amount) override;

        void OnEnable() override;

        void SetHealth(int health) override;

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
        PodHandler      *handler;
        int             highScore;
		bool			updateHighScore = true;
		SaltyEngine::GameObject *objGUIBeam = NULL;
		Vector2			m_min;
		Vector2			m_max;
		SaltyEngine::SFML::SpriteRenderer *m_renderer = nullptr;
		SaltyEngine::SFML::Animation *m_anim = nullptr;

	private:
		CommonPlayerController	*common;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !PLAYER_CONTROLLER_HPP_
