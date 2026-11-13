#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/Player.hh"
#include "../Framework/Bullet.hh"
#include "../Framework/EventManager.hh"
#include "../Framework/CollisionManager.hh"

int mode = 0;

bool ShowFrameworkMenu();
Bullet playerBullet(10, 15, BulletType::PlayerBullet, AE_COLORS_AIR_FORCE_BLUE);
Player player(AEVec2(0,-200), AEVec2(50,30),AE_COLORS_AIR_FORCE_BLUE, &playerBullet);
EventManager PlayerManager;
CollisionManager ColManager;
void Level_1_Load()
{
    Player* p = &player;
    PlayerManager.addHandler([p](GameEvent* event)
        {
            p->OnInputEvent(event);
        });
    
}

void Level_1_Init()
{
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();
    if (AEInputKeyPressed('A'))
    {
        GameEvent direction ;
        direction.PlayerType = Type::MoveLeft;
        PlayerManager.trigger(&direction);
    }
    if (AEInputKeyPressed('D'))
    {
        GameEvent direction;
        direction.PlayerType = Type::MoveRight;
        PlayerManager.trigger(&direction);
    }
    if (AEInputKeyPressed(' '))
    {
        GameEvent shoot;
        shoot.PlayerType = Type::Shoot;
        PlayerManager.trigger(&shoot);
    }

    playerBullet.Update();
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
    player.Draw();
    playerBullet.Draw();
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
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

