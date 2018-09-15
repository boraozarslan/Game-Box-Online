//
//  NetworkManager.cpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "NetworkManager.hpp"
#include "../EntitySystem/Components/NetworkedComponent.hpp"

#include <assert.h>

using namespace GameEngine;

NetworkManager* NetworkManager::sm_instance = nullptr;

NetworkManager::NetworkManager()
{
  
}


NetworkManager::~NetworkManager()
{
  
}

void NetworkManager::RegisterNetworked(NetworkedComponent* networked)
{
  auto found = std::find(m_networkeds.begin(), m_networkeds.end(), networked);
  assert(found == m_networkeds.end()); //Drop an assert if we add duplicate;
  if (found == m_networkeds.end())
  {
    m_networkeds.push_back(networked);
  }
}

void NetworkManager::UnRegisterNetworked(NetworkedComponent* networked)
{
  auto found = std::find(m_networkeds.begin(), m_networkeds.end(), networked);
  assert(found != m_networkeds.end()); //Drop an assert if we remove a non existing entity;
  
  if (found != m_networkeds.end())
  {
    m_networkeds.erase(found);
  }
}
