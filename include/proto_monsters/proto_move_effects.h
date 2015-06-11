#pragma once

#include "proto_move.h"
#include "../proto_battle/proto_battle.h"

//Handle Move Effect Logic
bool protoUpdateMoveEffect(ushort moveID, ProtoBattle &battle, bool enemyTurn);

//Handle Move Effect Animation
bool protoDrawMoveEffect(ushort moveID, ProtoBattle &battle, bool enemyTurn);
