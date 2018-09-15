//
//  NetworkManager.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include <vector>

namespace GameEngine
{
  class NetworkedComponent;
  
  class NetworkManager
  {
  public:
    ~NetworkManager();
    
    static NetworkManager* GetInstance() { if (!sm_instance) sm_instance = new NetworkManager(); return sm_instance; }
    
    void RegisterNetworked(NetworkedComponent* networked);
    void UnRegisterNetworked(NetworkedComponent* networked);
    //TODO - optimisation - instead of getcollidables, provide get near collidables so that we do not check collisions with all entities, just the ones that could potentially collide
    std::vector<NetworkedComponent*>& GetNetworkeds() { return m_networkeds; }
    
  private:
    NetworkManager();
    static NetworkManager* sm_instance;
    
    std::vector<NetworkedComponent*> m_networkeds;
  };
}
