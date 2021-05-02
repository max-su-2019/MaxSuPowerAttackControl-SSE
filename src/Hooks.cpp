#include "Hooks.h"

namespace MaxSuPowerAttackControl
{
	
	static float curDir = 0.f;


	bool MovDirHook::IsMoving(RE::Actor* pc)
	{
		if (pc && pc->IsPlayerRef() && RE::ControlMap::GetSingleton()->IsMovementControlsEnabled() && pc->IsAttacking()){
			logger::debug("Player Power Attack Hook Start(Is Moving)!");
			float dir;

			if (!DireHandler::GetSingleton()->ComputeDirectionValue(dir)) {
				logger::debug("Player is standing still");
				return false;
			}
			else {
				logger::debug("Directional Power Attack Start!");
				curDir = dir;
				return true;
			}
		}
		
		return _IsMoving(pc);
	}


	float MovDirHook::GetMoveDir(RE::Actor* pc)
	{

		if (pc && pc->IsPlayerRef() && RE::ControlMap::GetSingleton()->IsMovementControlsEnabled() && pc->IsAttacking()) {
			logger::debug(FMT_STRING("Reset Movement Direction Value to {}"), curDir);
			return curDir;
		}

		return _GetMoveDir(pc);
	}
}