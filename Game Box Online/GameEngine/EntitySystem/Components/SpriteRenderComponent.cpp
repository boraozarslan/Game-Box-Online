#include "SpriteRenderComponent.hpp"

#include "../../GameEngineMain.hpp"

using namespace GameEngine;

SpriteRenderComponent::SpriteRenderComponent()
: m_texture(eTexture::None)
, m_tileIndex(sf::Vector2i(0, 0))
, m_animComponent(nullptr)
{
  
}


SpriteRenderComponent::~SpriteRenderComponent()
{
  
}


void SpriteRenderComponent::OnAddToWorld()
{
  Component::OnAddToWorld();
  UpdateSpriteParams();
  
  m_animComponent = GetEntity()->GetComponent<AnimationComponent>();
}

void SpriteRenderComponent::UpdateSpriteParams()
{
  if (m_texture == eTexture::None)
    return;
  
  sf::Texture* texture = TextureManager::GetInstance()->GetTexture(m_texture);
  m_sprite.setTexture(*texture);
  
  //Set origin to centre
  sf::Vector2f textureSize = sf::Vector2f(texture->getSize());
  if (TextureHelper::GetTextureTileSize(m_texture).x > 0.f)
  {
    textureSize = TextureHelper::GetTextureTileSize(m_texture);
  }
  
  sf::IntRect textureRect((int)textureSize.x * m_tileIndex.x, (int)textureSize.y * m_tileIndex.y, (int)textureSize.x, (int)textureSize.y);
  m_sprite.setTextureRect(textureRect);
  
  m_sprite.setOrigin(sf::Vector2f(textureSize.x / 2.f, textureSize.y / 2.f));
  //If we have specified size, rescale to fit:
  if (GetEntity()->GetSize().x > 0.f && GetEntity()->GetSize().y > 0.f)
  {
    float scaleX = GetEntity()->GetSize().x / textureSize.x;
    float scaleY = GetEntity()->GetSize().y / textureSize.y;
    
    m_sprite.setScale(sf::Vector2f(scaleX, scaleY));
  }
}


void SpriteRenderComponent::UpdateTileRect()
{
  sf::Texture* texture = TextureManager::GetInstance()->GetTexture(m_texture);
  if (!texture)
    return;
  
  //Set origin to centre
  sf::Vector2f textureSize = sf::Vector2f(texture->getSize());
  if (TextureHelper::GetTextureTileSize(m_texture).x > 0.f)
  {
    textureSize = TextureHelper::GetTextureTileSize(m_texture);
  }
  
  sf::IntRect textureRect((int)textureSize.x * m_tileIndex.x, (int)textureSize.y * m_tileIndex.y, (int)textureSize.x, (int)textureSize.y);
  m_sprite.setTextureRect(textureRect);
}


void SpriteRenderComponent::Update()
{
  if (m_animComponent && m_animComponent->IsAnimPlaying())
  {
    SetTileIndex(m_animComponent->GetWantedTileIndex());
  }
  
  UpdateTileRect();
}


void SpriteRenderComponent::SetTexture(eTexture::type texture)
{
  m_texture = texture;
}


void SpriteRenderComponent::Render(sf::RenderTarget* target)
{
  RenderComponent::Render(target);
  
  if (!target)
  {
    return;
  }
  
  m_sprite.setPosition(GetEntity()->GetPos());
  m_sprite.setRotation(GetEntity()->GetRot());
  
  
  target->draw(m_sprite);
}
