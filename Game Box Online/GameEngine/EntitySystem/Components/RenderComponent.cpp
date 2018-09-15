#include "RenderComponent.hpp"

#include "GameEngine/EntitySystem/Components/CollidableComponent.hpp"
#include "GameEngine/EntitySystem/Entity.hpp"
#include "GameEngine/GameEngineMain.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace GameEngine;

RenderComponent::RenderComponent()
	: m_fillColor(sf::Color::Green)
	, m_zLevel(0)
{

}


RenderComponent::~RenderComponent()
{

}


void RenderComponent::Update()
{

}

void RenderComponent::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		return;
	}

	static bool drawDebug = false;
	//Debug draw of bounding boxes
	if (drawDebug)
	{
		if (CollidableComponent* collidable = GetEntity()->GetComponent<CollidableComponent>())
		{
			sf::RectangleShape rect = sf::RectangleShape();
			AABBRect aabb = collidable->GetWorldAABB();

			rect.setSize(sf::Vector2f(aabb.width, aabb.height));
			rect.setPosition(sf::Vector2f(aabb.left, aabb.top));

			sf::Color col = m_fillColor;
			col.b = 255;
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(2.f);
			if (GameEngineMain::GetInstance()->IsGameOver())
			{
				float seconds = GameEngineMain::GetInstance()->GetGameTime();
				float alphaVal = abs(sin(4 * seconds));
				col.a = (int)(255.f * alphaVal);
			}

			rect.setOutlineColor(col);

			target->draw(rect);
		}


		//Debug draw of entity pos

		sf::RectangleShape shape(sf::Vector2f(5.f, 5.f));
		sf::Vector2f pos = GetEntity()->GetPos();
		pos -= shape.getSize() / 2.f;
		shape.setFillColor(m_fillColor);
		shape.setPosition(pos);

		if (GameEngineMain::GetInstance()->IsGameOver())
		{
			float seconds = GameEngineMain::GetInstance()->GetGameTime();
			float alphaVal = abs(sin(4 * seconds));
			sf::Color gameOverCol = m_fillColor;
			gameOverCol.a = (int)(255.f * alphaVal);
			shape.setFillColor(gameOverCol);
		}

		target->draw(shape);
	}	
}
