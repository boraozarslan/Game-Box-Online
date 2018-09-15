#pragma once
#include "./CollidableComponent.hpp"
#include "../../../Game/GameEntities/ProjectileEntity.hpp"
#include "../../../Game/GameEntities/PlayerEntity.hpp"

namespace GameEngine
{
	//This one allows for movement and obstacle detection, 
	class CollidablePhysicsComponent : public CollidableComponent
	{
	public:
		CollidablePhysicsComponent();
		virtual ~CollidablePhysicsComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;

    private:
        void handleDamage(Game::ProjectileEntity* projectile);
	};
}

