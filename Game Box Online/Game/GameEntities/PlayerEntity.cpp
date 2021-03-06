#include "PlayerEntity.hpp"

#include "Game/GameComponents/PlayerSoundComponent.hpp"
#include "Game/GameComponents/PlayerCameraComponent.hpp"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.hpp"
#include "GameEngine/EntitySystem/Components/ParticleEmitterComponent.hpp"
#include "GameEngine/EntitySystem/Components/SoundComponent.hpp"
#include "GameEngine/EntitySystem/Components/DumbAIComponent.hpp"
#include "GameEngine/EntitySystem/Components/DumbProjectileComponent.hpp"
#include "GameEngine/Util/AnimationManager.hpp"
#include "../ResourcePath.hpp"
#include <string>
#include <iostream>

using namespace Game;

PlayerEntity::PlayerEntity(bool isEnemy): m_health(100.f), m_score(0), GameEngine::Entity(Types::Player)
{
  bool isHost = GameEngine::GameEngineMain::GetInstance()->IsHost();
  if(!isHost)
  {
    static bool firstplayer = true;
    m_isEnemy = isEnemy || !firstplayer;
    firstplayer = false;
 
	//Render 
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_renderComponent->SetTexture(GameEngine::eTexture::Player);
	m_renderComponent->SetZLevel(2);
    
    if(!isEnemy) {
        AddComponent<Game::PlayerCameraComponent>();
    }

    AddComponent<Game::HealthStatusComponent>();
    
	//Animation
	m_animComponent = static_cast<GameEngine::AnimationComponent*>(AddComponent<GameEngine::AnimationComponent>());
    
    if (!isEnemy) {
        //Movement
        m_playerMovementComponent = static_cast<PlayerMovementComponent*>(AddComponent<PlayerMovementComponent>());

        // Projectile Emitter
        AddComponent<Game::ProjectileEmitterComponent>();
        AddComponent<Game::BombEmitterComponent>();
    } else {
        AddComponent<GameEngine::DumbAIComponent>();
//        GameEngine::DumbProjectileComponent* dumbProjectile = static_cast<GameEngine::DumbProjectileComponent*>(AddComponent<GameEngine::DumbProjectileComponent>());
    }

	//Particles
	GameEngine::ParticleEmitterComponent* emitterComponent = static_cast<GameEngine::ParticleEmitterComponent*>(AddComponent<GameEngine::ParticleEmitterComponent>());
	GameEngine::SParticleDefinition particleDef = GameEngine::SParticleDefinition(GameEngine::eTexture::Particles, 1, sf::Vector2f(32.f, 32.f), GameEngine::EAnimationId::Smoke, 1.f);
	emitterComponent->SetParticleDefinition(particleDef);

    
    
    //Health Bar Component
    m_healthStatus = static_cast<Game::HealthStatusComponent*>(AddComponent<Game::HealthStatusComponent>());

	//Sound
	GameEngine::SoundComponent* const soundComponent = static_cast<GameEngine::SoundComponent*>(AddComponent<GameEngine::SoundComponent>());
	soundComponent->SetNumSimultaneousSounds(2); // Hard coded 5 simultaneous sounds for the player
												 
	AddComponent<PlayerSoundComponent>();
  }
  //Collisions
  if(isHost || !GameEngine::GameEngineMain::GetInstance()->IsInNetworkMode())
    AddComponent<GameEngine::CollidablePhysicsComponent>();
}

 
PlayerEntity::~PlayerEntity()
{

}


void PlayerEntity::OnAddToWorld()
{
	GameEngine::Entity::OnAddToWorld();

	if (m_animComponent)
	{
		m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
	}
}


void PlayerEntity::OnRemoveFromWorld()
{
	GameEngine::Entity::OnRemoveFromWorld();
}

bool PlayerEntity::TakeDamage(float damage) {
    m_health -= damage;
 
    return m_health <= 0;
}

void PlayerEntity::IncreaseScore(int score) {
    m_score += score;
    //return m_score;
}

int PlayerEntity::GetScore() {
    return m_score;
}
