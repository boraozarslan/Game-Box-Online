//
//  DumbAIComponent.cpp
//  Game Box Online
//
//  Created by Ben Zhang on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "DumbAIComponent.hpp"
#include "PlayerEntity.hpp"

using namespace GameEngine;

DumbAIComponent::DumbAIComponent()
{
    
}


DumbAIComponent::~DumbAIComponent()
{
    
}


void DumbAIComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}


void DumbAIComponent::OnRemoveFromWorld()
{
    Component::OnRemoveFromWorld();
}


void DumbAIComponent::Update()
{
    Component::Update();
    
    auto game_instance = GameEngine::GameEngineMain::GetInstance();
    
    if (game_instance->IsGameOver())
    {
        return;
    }
    
    Game::GameBoard* game_board = game_instance->GetGameBoard();
    
    Game::PlayerEntity* player = game_board->GetPlayer();
    auto entity = GetEntity();

    sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);
    static float entityVel = 80.f; //Pixels/s
    float dt = GameEngine::GameEngineMain::GetTimeDelta();

    auto entity_pos = entity->GetPos();
    auto player_pos = player->GetPos();
    
    if (entity_pos.x > player_pos.x) {
        wantedVel.x -= entityVel * dt;
    } else if (entity_pos.x < player_pos.x) {
        wantedVel.x += entityVel * dt;
    }
    
    if (entity_pos.y > player_pos.y) {
        wantedVel.y -= entityVel * dt;
    } else if (entity_pos.y < player_pos.y) {
        wantedVel.y += entityVel * dt;
    }
    
    entity->SetPos(entity_pos + wantedVel);
    
    
    static float rotationVel = 50.f; //Deg/s
    static float maxRotation = 20.f; //Deg
    
    float currentRotation = GetEntity()->GetRot();
    float wantedRot = 0.f;
    bool  reseting = false;
    
    if (wantedVel.y > 0.f)
        wantedRot = rotationVel;
    else if (wantedVel.y < 0.f)
        wantedRot = -rotationVel;
    else
    {
        if (currentRotation > 0.f)
            wantedRot = -rotationVel;
        else if (currentRotation < 0.f)
            wantedRot = rotationVel;
    }
    
    float frameRot = wantedRot * dt;
    float totalRot = currentRotation + frameRot;
    
    if (!reseting)
    {
        if (totalRot > maxRotation)
            totalRot = maxRotation;
        else if (totalRot < -maxRotation)
            totalRot = -maxRotation;
    }
    else
    {
        if (currentRotation > 0.f && totalRot < 0.f)
            totalRot = 0.f;
        if (currentRotation < 0.f && totalRot > 0.f)
            totalRot = 0.f;
    }
    
    entity->SetRotation(totalRot);
}
