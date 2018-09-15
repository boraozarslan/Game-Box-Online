#pragma once
#include "GameEngine/EntitySystem/Component.hpp"

#include "GameEngine/EntitySystem/Entity.hpp"
#include "GameEngine/GameEngineMain.hpp"

namespace GameEngine
{
	class ParticleComponent : public Component
	{
	public:
		ParticleComponent();
		virtual ~ParticleComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		void SetLifeTime(float time) { m_lifeTimer = time; }

	protected:
		virtual void Update() override;

		float m_lifeTimer;
	};
}

