#include "BattlePlayer.h"
#include <bInput.h>
#include <bTime.h>
#include "AniRender.h"

Status a;
Status* Status::BattleStatus[3] = { new Status(a),new Status(a),new Status(a) } ;
int BattlePlayer::Skills[3] = {-1,-1,-1};
bool BattlePlayer::PowerUp = false;
bool BattlePlayer::SkillOn = false;
int BattlePlayer::CharIndex = 0;
int BattlePlayer::DMG = 0;
int BattlePlayer::PlTarget[3] = { -1, -1, -1 };

BattlePlayer::BattlePlayer() : SkillCount(0.0f), Victory(false), SkillEnd(false), Damage(false), Die(false)
{
}


BattlePlayer::~BattlePlayer()
{
}
