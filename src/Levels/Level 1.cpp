#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/Player.hh"
#include "../Framework/Bullet.hh"
#include "../Framework/EventManager.hh"
#include "../Framework/CollisionManager.hh"
#include "../Framework/Squadron.hh"
#include "time.h"
int mode = 0;

bool ShowFrameworkMenu();
Bullet* pBullet;
Player* player;
EventManager* PlayerManager;
CollisionManager* ColManager;
Squadron* squadron;
void Level_1_Load()
{
    pBullet = new Bullet(AEVec2(10, 15), BulletType::PlayerBullet, AE_COLORS_AIR_FORCE_BLUE);
    player = new Player(AEVec2(0, -200), AEVec2(30, 20), AE_COLORS_AIR_FORCE_BLUE, pBullet);
    squadron = new Squadron(AEVec2(-130, 250), AEVec2(30, 20), AE_COLORS_AMBER, AEVec2(10, 15));
    PlayerManager = new EventManager();
    ColManager = new CollisionManager();
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
    ColManager->bplayer = pBullet;
    ColManager->p = p;
    ColManager->squad = s;
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
    if (player->Alive == false)
    {
        Level_1_Free();
    }
    //eBullet->Update();
    pBullet->Update();
    ColManager->update();
    //enemy->Update();
    squadron->Update();
}

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
    delete pBullet;
    delete player;

    delete PlayerManager;
    delete ColManager;
    Level_1_Load();
}

void Level_1_Unload()
{
    delete pBullet;
    delete player;

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

