#pragma once
#include "GameEngine/EntitySystem/Component.hpp"
#include "GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "GameEngine/Util/SoundManager.hpp"

namespace Game
{	
	class PlayerSoundComponent;

	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

	private:
		float m_flyTimerDt;
		float m_flyTimerMaxTime;

		GameEngine::AnimationComponent* m_animComponent;
		PlayerSoundComponent*			m_playerSoundComponent;
	};
}


