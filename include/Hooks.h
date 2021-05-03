#pragma once
#include "DataHandler.h"

namespace MaxSuPowerAttackControl
{
	class AttackHook
	{
	public:

		static void HookPowerAttack()
		{
			REL::Relocation<std::uintptr_t> AttackBlockHandlerVtbl{ RE::Offset::AttackBlockHandler::Vtbl };
			_ProcessAttackHook = AttackBlockHandlerVtbl.write_vfunc(0x4, ProcessAttackHook);
			logger::info("Hook Power Attack Control!");
		}

	private:

		static bool		ProcessAttackHook(RE::AttackBlockHandler* handler, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);

		static inline REL::Relocation<decltype(ProcessAttackHook)> _ProcessAttackHook;
	};



}