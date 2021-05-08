#include "LoadGame.h"
#include "Hooks.h"
#include "DataHandler.h"

namespace MaxSuPowerAttackControl
{

	DireHandler::DireHandler()
	{
		static const std::string PluginName = "Maxsu_PowerAttackControl.esp";

		direGlobal = std::make_unique<FormPair<RE::TESGlobal>>(0xD61, PluginName);

		auto readThld = GetFloatFromINI("GamePad", "LeftStickThreshold", 0.25f);

		if (readThld > 0.f && readThld < 1.0f) {
			padThld = readThld;
			logger::info(FMT_STRING("Set Left Stick ThreShold Value to {}"), padThld);
		}
	}



	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kDataLoaded)
		{
			logger::info("Data Load CallBack Trigger!");

			int enableDebug = GetPrivateProfileIntA("Main", "EnableDebugMessage", 0, SETTINGFILE_PATH);

			if (enableDebug == 1) {
				spdlog::set_level(spdlog::level::debug);
				logger::info("Enable Debug Message!");
			}

			if (MaxSuPowerAttackControl::DireHandler::GetSingleton()->direGlobal->GetForm())
				MaxSuPowerAttackControl::AttackHook::HookPowerAttack();
			else
				logger::error("Fail to Load Direction Control Global Variable!");

		}
	}


}

