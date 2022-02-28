#pragma once

#include "../JsonForward.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <mutex>
#include <numbers>
#include <numeric>
#include <windows.h>
#include <sstream>
#include <random>

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_stdlib.h"

#include "../ConfigStructs.h"
#include "../InputUtil.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../ProtobufReader.h"
#include "../SDK/Prediction.h"
#include "../d3drender.h"
#include "EnginePrediction.h"
#include "Misc.h"
#include "../render.h"
#include "../SDK/ClassId.h"
#include "../SDK/Client.h"
#include "../SDK/ClientClass.h"
#include "../SDK/ClientMode.h"
#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/Engine.h"
#include "../SDK/EngineTrace.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/ItemSchema.h"
#include "../SDK/Localize.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/Panorama.h"
#include "../SDK/Platform.h"
#include "../SDK/UserCmd.h"
#include "../SDK/UtlVector.h"
#include "../SDK/Vector.h"
#include "../SDK/WeaponData.h"
#include "../SDK/WeaponId.h"
#include "../SDK/WeaponSystem.h"

#include "../GUI.h"
#include "../Helpers.h"
#include "../Hooks.h"
#include "../GameData.h"

#include "../imguiCustom.h"

#include <vector>
#include <deque>

enum class FrameStage;
class GameEvent;
struct ImDrawList;
struct UserCmd;

#define M_PI 3.14159265358979323846
#define PI_F	((float)(M_PI)) 

namespace Misc
{
    inline float unpredicted_velocity;
    inline int iFlags = 0;

    void RegionChanger();
    void setup_steam();
    bool shouldRevealMoney() noexcept;
    bool shouldRevealSuspect() noexcept;
    bool shouldDisableModelOcclusion() noexcept;
    bool shouldFixBoneMatrix() noexcept;
    bool isRadarHackOn() noexcept;
    bool isMenuKeyPressed() noexcept;
    float maxAngleDelta() noexcept;
    float aspectRatio() noexcept;
    void Camera();
    void DamageIndicator(GameEvent* event);
    void watermark2() noexcept;
    void EdgebugDetect(UserCmd* cmd) noexcept;
    void Keystrokes();
    void Jumpstats();
    void BlockBot(UserCmd* cmd);
    void edgejump(UserCmd* cmd) noexcept;
    void PostPred(UserCmd* cmd);
    void StrafeOpt(UserCmd* cmd);
    void TeamDamage(GameEvent* event) noexcept;
    void DrawDamage();
    void autoStrafe(UserCmd* cmd) noexcept;
    void StaminaIndicator();
    void longjump(UserCmd* cmd);
    void ladderlj(UserCmd* cmd);
    void VelocityIndicator();
    void Spotify();
    void smartedgebug(UserCmd* pCmd);
    void VelocityGraph();
    void StaminaGraph();
    void NullStrafe(UserCmd* cmd);
    void indicator();
    void Oldedgebug(UserCmd* cmd);
    void jumpbug(UserCmd* cmd) noexcept;
    void slowwalk(UserCmd* cmd) noexcept;
    void updateClanTag(bool = false) noexcept;
    void spectatorList() noexcept;
    void noscopeCrosshair(ImDrawList* drawlist) noexcept;
    void recoilCrosshair(ImDrawList* drawList) noexcept;
    void watermark() noexcept;
    void prepareRevolver(UserCmd*) noexcept;
    void fastPlant(UserCmd*) noexcept;
    void fastStop(UserCmd*) noexcept;
    void drawBombTimer() noexcept;
    void stealNames() noexcept;
    void disablePanoramablur() noexcept;
    void quickReload(UserCmd*) noexcept;
    bool changeName(bool, const char*, float) noexcept;
    void bunnyHop(UserCmd*) noexcept;
    void fakeBan(bool = false) noexcept;
    void nadePredict() noexcept;
    void fixTabletSignal() noexcept;
    void killMessage(GameEvent& event) noexcept;
    void fixMovement(UserCmd* cmd, float yaw) noexcept;
    void antiAfkKick(UserCmd* cmd) noexcept;
    void fixAnimationLOD(FrameStage stage) noexcept;
    void autoPistol(UserCmd* cmd) noexcept;
    void chokePackets(bool& sendPacket) noexcept;
    void autoReload(UserCmd* cmd) noexcept;
    void revealRanks(UserCmd* cmd) noexcept;
    void removeCrouchCooldown(UserCmd* cmd) noexcept;
    void moonwalk(UserCmd* cmd) noexcept;
    void playHitSound(GameEvent& event) noexcept;
    void killSound(GameEvent& event) noexcept;
    void purchaseList(GameEvent* event = nullptr) noexcept;
    void oppositeHandKnife(FrameStage stage) noexcept;
    void runReportbot() noexcept;
    void resetReportbot() noexcept;
    void preserveKillfeed(bool roundStart = false) noexcept;
    void voteRevealer(GameEvent& event) noexcept;
    void onVoteStart(const void* data, int size) noexcept;
    void onVotePass() noexcept;
    void onVoteFailed() noexcept;
    void drawOffscreenEnemies(ImDrawList* drawList) noexcept;
    void Spectatorlist();
    void autoAccept(const char* soundEntry) noexcept;

    void updateEventListeners(bool forceRemove = false) noexcept;
    void updateInput() noexcept;

    // GUI
    void menuBarItem() noexcept;
    void tabItem() noexcept;
    void tabItem2() noexcept;
    void drawGUI(bool contentOnly) noexcept;

    void drawGUI2(bool contentOnly) noexcept;

    // Config
    json toJson() noexcept;
    void fromJson(const json& j) noexcept;
    void resetConfig() noexcept;
    inline int teamDamage = 0;
    inline int teamKills = 0;
}



