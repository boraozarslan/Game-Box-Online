#include "PlayerEntity.hpp"

#include "Game/GameComponents/PlayerSoundComponent.hpp"
#include "Game/GameComponents/PlayerCameraComponent.hpp"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.hpp"
#include "GameEngine/EntitySystem/Components/ParticleEmitterComponent.hpp"
#include "GameEngine/EntitySystem/Components/SoundComponent.hpp"
#include "GameEngine/EntitySystem/Components/DumbAIComponent.hpp"
#include "GameEngine/Util/AnimationManager.hpp"

using namespace Game;

PlayerEntity::PlayerEntity(bool isEnemy): health(100.f)
{
    if (!isEnemy) {
        //Movement
        m_playerMovementComponent = static_cast<PlayerMovementComponent*>(AddComponent<PlayerMovementComponent>());
    } else {
        AddComponent<GameEngine::DumbAIComponent>();
    }

	//Render 
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
    AddComponent<GameEngine::CollidablePhysicsComponent>();
	m_renderComponent->SetTexture(GameEngine::eTexture::Player);
	m_renderComponent->SetZLevel(2);

	//Animation
	m_animComponent = static_cast<GameEngine::AnimationComponent*>(AddComponent<GameEngine::AnimationComponent>());
		
    
	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();
	
	//Particles
	GameEngine::ParticleEmitterComponent* emitterComponent = static_cast<GameEngine::ParticleEmitterComponent*>(AddComponent<GameEngine::ParticleEmitterComponent>());
	GameEngine::SParticleDefinition particleDef = GameEngine::SParticleDefinition(GameEngine::eTexture::Particles, 1, sf::Vector2f(32.f, 32.f), GameEngine::EAnimationId::Smoke, 1.f);
	emitterComponent->SetParticleDefinition(particleDef);


	//Sound
	GameEngine::SoundComponent* const soundComponent = static_cast<GameEngine::SoundComponent*>(AddComponent<GameEngine::SoundComponent>());
	soundComponent->SetNumSimultaneousSounds(2); // Hard coded 5 simultaneous sounds for the player
												 
	AddComponent<PlayerSoundComponent>();

	//Camera control
	AddComponent<PlayerCameraComponent>();
    
    AddComponent<Game::ProjectileEmitterComponent>();

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
