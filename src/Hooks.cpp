#include "Hooks.h"

namespace MaxSuPowerAttackControl
{
	 bool AttackHook::ProcessAttackHook(RE::AttackBlockHandler* handler, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data)
	{
		if (handler->IsInputEventHandlingEnabled() && RE::ControlMap::GetSingleton()->IsFightingControlsEnabled() && a_event && a_event->QUserEvent() == RE::UserEvents::GetSingleton()->rightAttack) {
			logger::debug("Process Attack Hook Start!");
			if (DireHandler::GetSingleton()->UpdateDirectionValue())
				logger::debug("Update Direction Value Successfully!");
			else
				logger::debug("Update Direction Value Fail!");
		}

		return _ProcessAttackHook(handler, a_event, a_data);
	}

}