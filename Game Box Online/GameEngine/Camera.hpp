//
//  Camera.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

namespace Game {
  class PlayerEntity;
}

namespace sf {
  class RenderWindow;
}

namespace GameEngine
{
  class Camera
  {
  public:
    Camera(Game::PlayerEntity* player, sf::RenderWindow* window);
    void Update();
  private:
    Game::PlayerEntity* m_player;
    sf::RenderWindow* m_window;
  };
}
