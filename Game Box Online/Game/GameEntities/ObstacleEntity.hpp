#pragma once
#include "GameEngine/EntitySystem/Entity.hpp"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"

namespace Game
{

	class ObstacleEntity : public GameEngine::Entity
	{
	public:
		ObstacleEntity();
		~ObstacleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
	};
}

