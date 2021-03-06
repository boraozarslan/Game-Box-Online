#include "ObstacleEntity.hpp"

#include "GameEngine/EntitySystem/Components/CollidableComponent.hpp"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity()	
{
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Tileset);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	AddComponent<GameEngine::CollidableComponent>();
}


ObstacleEntity::~ObstacleEntity()
{

}


void ObstacleEntity::OnAddToWorld()
{
	GameEngine::Entity::OnAddToWorld();
}


void ObstacleEntity::OnRemoveFromWorld()
{
	GameEngine::Entity::OnRemoveFromWorld();
}
