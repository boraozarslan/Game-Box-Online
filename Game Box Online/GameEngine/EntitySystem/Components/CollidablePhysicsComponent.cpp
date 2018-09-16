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
        
        if (!myBox.intersects(colideBox, intersection)) {
            continue; // no collision with the entity
        }
        
        if (Game::ProjectileEntity* projectile = dynamic_cast<Game::ProjectileEntity*>(entity)) {
            std::cout << "Projectile collision detected!" << std::endl;

            if (projectile->GetSource() != GetEntity())
            {
                handleDamage(projectile);
            }
        } else if (Game::PlayerEntity* player = dynamic_cast<Game::PlayerEntity*>(entity)) {
            std::cout << "Player collision detected!" << std::endl;
            
            sf::Vector2f pos = entity->GetPos();
            if (intersection.width < intersection.height)
            {
                if (myBox.left < colideBox.left)
                    pos.x += intersection.width / 2;
                else
                    pos.x -= intersection.width / 2;
            } else {
                if (myBox.top < colideBox.top)
                    pos.y += intersection.height / 2;
                else
                    pos.y -= intersection.height / 2;
            }
            
            entity->SetPos(pos);
        } else if (entity != nullptr) {
            std::cout << "Wall collision detected!" << std::endl;
            
            sf::Vector2f pos = GetEntity()->GetPos();
            if (intersection.width < intersection.height)
            {
                if (myBox.left < colideBox.left)
                    pos.x -= intersection.width;
                else
                    pos.x += intersection.width;
            }
            else
            {
                if (myBox.top < colideBox.top)
                    pos.y -= intersection.height;
                else
                    pos.y += intersection.height;
            }

            GetEntity()->SetPos(pos);
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
