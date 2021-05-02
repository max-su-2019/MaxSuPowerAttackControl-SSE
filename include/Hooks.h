#pragma once
#include "DataHandler.h"

namespace MaxSuPowerAttackControl
{
	class MovDirHook
	{
	public:
		static void HookGetMoveDir()
		{
			logger::debug("Hook Get Player Movement Direction!");
			REL::Relocation<std::uintptr_t> GetMoveDirBase{ REL::ID(21236) };
			auto& trampoline = SKSE::GetTrampoline();
			_GetMoveDir = trampoline.write_call<5>(GetMoveDirBase.address() + 0x4F, GetMoveDir);
		}

		static void HookIsMoving()
		{
			logger::debug("Hook IsMoving!");
			REL::Relocation<std::uintptr_t> GetMoveDirBase{ REL::ID(21236) };
			auto& trampoline = SKSE::GetTrampoline();
			_IsMoving = trampoline.write_call<5>(GetMoveDirBase.address() + 0x2D, IsMoving);
		}


	private:

		static float	GetMoveDir(RE::Actor* pc);
		static bool		IsMoving(RE::Actor* pc);


		static inline REL::Relocation<decltype(GetMoveDir)>		 _GetMoveDir;
		static inline REL::Relocation<decltype(IsMoving)>		 _IsMoving;
	};



}