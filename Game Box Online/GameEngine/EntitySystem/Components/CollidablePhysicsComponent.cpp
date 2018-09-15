#include "./CollidablePhysicsComponent.hpp"

#include "../../Util/CollisionManager.hpp"
#include "../../EntitySystem/Entity.hpp"

#include <vector>
#include <iostream>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	Component::OnAddToWorld();
    CollisionManager::GetInstance()->RegisterCollidable(this);

    if (m_useDefaultBox)
        SetupDefaultBoundingBox();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	Component::OnRemoveFromWorld();
    CollisionManager::GetInstance()->UnRegisterCollidable(this);
}


void CollidablePhysicsComponent::Update()
{
    std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
        
        GameEngine::Entity* entity = colComponent->GetEntity();
        
        Game::ProjectileEntity* projectile = dynamic_cast<Game::ProjectileEntity*>(entity);

        if (projectile && projectile->GetSource() != GetEntity() && myBox.intersects(colideBox, intersection))
		{
            handleDamage(projectile);
		}
	}
}

void CollidablePhysicsComponent::handleDamage(Game::ProjectileEntity* projectile) {
    bool wasKilled = static_cast<Game::PlayerEntity*>(GetEntity())->TakeDamage(projectile->GetDamage());
    Game::PlayerEntity* projectileSrc = projectile->GetSource();

    auto currentEngine = GameEngine::GameEngineMain::GetInstance();
    currentEngine->RemoveEntity(projectile);

    if (wasKilled) {
        currentEngine->RemoveEntity(GetEntity());
        projectileSrc->IncreaseScore(1);
        //std::cout << projectileSrc->GetScore() << std::endl << std::flush;
    }
}
