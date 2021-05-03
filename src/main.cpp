#include "version.h"
#include "Hooks.h"

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= "MaxSuPowerAttackControl.log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::trace);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

	logger::info(FMT_STRING("MaxSuPowerAttackControl v{}"), MYFP_VERSION_VERSTRING);

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "MaxSuPowerAttackControl";
	a_info->version = MYFP_VERSION_MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}



void EventCallback(SKSE::MessagingInterface::Message* msg)
{
	if (msg->type == SKSE::MessagingInterface::kDataLoaded)
	{
		logger::info("Data Load CallBack Trigger!");

		if (MaxSuPowerAttackControl::DireHandler::GetSingleton()->direGlobal->GetForm())
			MaxSuPowerAttackControl::AttackHook::HookPowerAttack();
		else
			logger::error("Fail to Load Direction Control Global Variable!");

	}
}


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	logger::info("MaxSuPowerAttackControl loaded");

	SKSE::Init(a_skse);
	auto g_message = SKSE::GetMessagingInterface();

	if (!g_message)
	{
		logger::error("Messaging Interface Not Found!");
		return false;
	}

	SKSE::AllocTrampoline(1 << 4);

	if (g_message->RegisterListener(EventCallback))
	{
		logger::info("Register Event Call Back!");
		return true;
	}

	return false;
}
