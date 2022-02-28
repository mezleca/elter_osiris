#pragma once

#include "Inconstructible.h"
#include "VirtualMethod.h"

class Entity;
class MoveData;

class GameMovement {
public:
	INCONSTRUCTIBLE(GameMovement)

		VIRTUAL_METHOD_V(void, processMovement, 1, (Entity* localPlayer, MoveData* moveData), (this, localPlayer, moveData))

		constexpr void FinishTrackPredictionErrors(Entity* localPlayer) noexcept
	{
		return VirtualMethod::callVirtualMethod<void, Entity*>(this, 4, localPlayer);
	}
};
