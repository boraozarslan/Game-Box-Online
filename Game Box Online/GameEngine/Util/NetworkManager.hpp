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
#include "NetworkDefs.hpp"

namespace GameEngine
{
  class NetworkedComponent;
  
  class NetworkManager
  {
  public:
    ~NetworkManager();
    
    static NetworkManager* GetInstance(bool host = false) { if (!sm_instance) sm_instance = new NetworkManager(host); return sm_instance; }
    
    void RegisterNetworked(NetworkedComponent* networked);
    void UnRegisterNetworked(NetworkedComponent* networked);
    void PreUpdate();
    void PostUpdate();
    
  private:
    NetworkManager(bool host);
    static NetworkManager* sm_instance;
    
    sf::TcpSocket tcpConnections[MAX_PLAYERS];
    sf::TcpListener* m_listener;
    bool m_host;
  };
}
