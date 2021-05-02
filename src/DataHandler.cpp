#include "DataHandler.h"

namespace MaxSuPowerAttackControl
{

	bool DireHandler::GetKeyHeldDuration(const std::uint32_t a_index, float& result) const
	{
		auto inputMgr = RE::BSInputDeviceManager::GetSingleton();

		if (inputMgr && inputMgr->GetKeyboard()->IsPressed(a_index) && inputMgr->GetKeyboard()->deviceButtons.find(a_index)->second) {
			result = inputMgr->GetKeyboard()->deviceButtons.find(a_index)->second->heldDownSecs;
			return true;
		}

		return false;
	}


	MovDire DireHandler::PickKeyDirection()
	{
		auto ctrlMap = RE::ControlMap::GetSingleton();

		std::optional<MovDire> pickedDir;
		float recordDur = 0.f;

		for (auto dir : Directions) {
			auto key = ctrlMap->GetMappedKey(dir.second, RE::INPUT_DEVICE::kKeyboard);

			float heldDur;
			if (GetKeyHeldDuration(key, heldDur) && (!pickedDir.has_value() || heldDur <= recordDur)) {
				pickedDir.emplace(dir.first);
				recordDur = heldDur;
				logger::debug(FMT_STRING("Get a Held Direction Key Index {:x}, Duration {}"), key, recordDur);
			}
		}

		return pickedDir.has_value() ? pickedDir.value() : MovDire::kNone;
	}


	const std::optional<float> DireHandler::GetKeyboardDireValue()
	{
		static const float PI = 3.1415927f;

		const std::optional<float> null;
		switch (PickKeyDirection()){
		case MovDire::kForward:
			return 0.f;

		case MovDire::kBackward:
			return PI;

		case MovDire::kLeft:
			return -(PI / 2.0f);

		case MovDire::kRight:
			return PI / 2.0f;

		default:
			return null;
		}
	}




	bool DireHandler::ComputeDirectionValue(float& a_out)
	{
		auto inputMgr = RE::BSInputDeviceManager::GetSingleton();
		if (inputMgr && inputMgr->GetKeyboard() && inputMgr->GetKeyboard()->IsEnabled() && !inputMgr->IsGamepadConnected()) {
			auto dire = GetKeyboardDireValue();
			if (dire.has_value()) {
				a_out = dire.value();
				return true;
			}
		}

		return false;
	}


}