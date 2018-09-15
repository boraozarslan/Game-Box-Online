//
//  Camera.cpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "Camera.hpp"
#include <SFML/Graphics.hpp>
#include "../Game/GameEntities/PlayerEntity.hpp"
#include "Entity.hpp"

using namespace GameEngine;

Camera::Camera(Game::PlayerEntity* player, sf::RenderWindow* window):
  m_player(player), m_window(window)
{}

void Camera::Update()
{
  auto view = m_window->getView();
  auto pos = m_player->GetPos();
  view.setCenter(pos.x, pos.y);
  m_window->setView(view);
}
