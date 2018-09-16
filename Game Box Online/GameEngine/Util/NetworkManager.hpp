//
//  NetworkManager.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include <vector>
#include <SFML/Network.hpp>

namespace GameEngine
{ 
  class NetworkManager
  {
  public:
    ~NetworkManager();
    
    static NetworkManager* GetInstance(bool host = false) { if (!sm_instance) sm_instance = new NetworkManager(host); return sm_instance; }
    
    void PreUpdate();
    void PostUpdate();
    
  private:
    NetworkManager(bool host);
    static NetworkManager* sm_instance;
    
    sf::TcpSocket tcpConnections[16];
    sf::TcpListener* m_listener;
    bool m_host;
  };
}
