#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/Player.hh"
#include "../Framework/PlayerEventManager.hh"

int mode = 0;

bool ShowFrameworkMenu();
Player player(AEVec2(0,-200), AEVec2(100,50),AE_COLORS_AIR_FORCE_BLUE);
PlayerEventManager PlayerManager;
void Level_1_Load()
{
    Player* p = &player;
    PlayerManager.addHandler([p](MoveEvent* event)
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
        MoveEvent direction ;
        direction.MoveType = Type::MoveLeft;
        PlayerManager.trigger(&direction);
    }
    if (AEInputKeyPressed('D'))
    {
        MoveEvent direction;
        direction.MoveType = Type::MoveRight;
        PlayerManager.trigger(&direction);
    }
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
    player.Draw();
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

