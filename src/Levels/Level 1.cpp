#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/Player.hh"
#include "../Framework/Bullet.hh"
#include "../Framework/EventManager.hh"
#include "../Framework/CollisionManager.hh"
#include "../Framework/Squadron.hh"
/******************************************************************************
filename    Level 1.cc
author      Markel Susial de la fuente
DP email    markel.susial@digipen.edu
course      cs225
assignment  3.2
due date    17/11/2026

Brief Description: level 1 main program
******************************************************************************/
int mode = 0;

bool ShowFrameworkMenu();
/*Pointers to all the specific needed object*/
Bullet* pBullet;
Player* player;
EventManager* PlayerManager;
CollisionManager* ColManager;
Squadron* squadron;
/**
 * Level_1_Load
 * @param context: load all the resources for the scene
 * @return nothing
 */
void Level_1_Load()
{
    //Create all the types of objects
    pBullet = new Bullet(AEVec2(10, 15), BulletType::PlayerBullet, AE_COLORS_AIR_FORCE_BLUE);
    player = new Player(AEVec2(0, -200), AEVec2(30, 20), AE_COLORS_AIR_FORCE_BLUE, pBullet);
    squadron = new Squadron(AEVec2(-130, 250), AEVec2(30, 20), AE_COLORS_AMBER, AEVec2(10, 15));
    PlayerManager = new EventManager();
    ColManager = new CollisionManager(player,pBullet,squadron);
    //Send the pointers of the objects to the types of managers
    Player* p = player;
    Squadron* s = squadron;
    PlayerManager->addHandler([p](GameEvent* event)
        {
            p->OnInputEvent(event);
        });

    ColManager->addHandler([p, s](CollisionEvent* event)
        {
            p->OnColEvent(event);
            s->OnColEvent(event);
        });

}
/**
 * Level_1_Init
 * @param context:restart the objects
 * @return nothing
 */
void Level_1_Init()
{
    player->Restart();
    squadron->RestartSq();
}
/**
 * Level_1_Update
 * @param context: update all the objects on scene
 * @return nothing
 */
void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();

    bool guiActive = ShowFrameworkMenu();
    if (player->Alive == false)
    {
        Level_1_Free();
        return;
    }
    if (AEInputKeyPressed('A'))
    {
        GameEvent direction ;
        direction.PlayerType = Type::MoveLeft;
        PlayerManager->trigger(&direction);
    }
    if (AEInputKeyPressed('D'))
    {
        GameEvent direction;
        direction.PlayerType = Type::MoveRight;
        PlayerManager->trigger(&direction);
    }
    if (AEInputKeyPressed(' '))
    {
        GameEvent shoot;
        shoot.PlayerType = Type::Shoot;
        PlayerManager->trigger(&shoot);
    }

    pBullet->Update();
    squadron->Update();
    ColManager->update();

}
/**
 * Level_1_Render
 * @param context: draw the objects
 * @return nothing
 */
void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
    player->Draw();
    pBullet->Draw();
    squadron->Draw();

}

void Level_1_Free()
{

}
/**
 * Level_1_Unload
 * @param context: just unload everything
 * @return nothing
 */
void Level_1_Unload()
{
    delete pBullet;
    delete player;
    delete squadron;
    delete PlayerManager;
    delete ColManager;
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

