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



	const std::optional<float> DireHandler::GetGamePadDireValue()
	{
		auto inputMgr = RE::BSInputDeviceManager::GetSingleton();

		std::optional<float> result;
		if (inputMgr && inputMgr->GetGamepad()) {
			auto gamePad = (RE::BSWin32GamepadDevice*)(inputMgr->GetGamepad());

			if (gamePad) {
				logger::debug(FMT_STRING("Current LX is {}, Current LY is {}"), gamePad->curLX, gamePad->curLY);

				float dir_xy[2] = { gamePad->curLX , gamePad->curLY };
				static const float dir_base[2] = { 0, 1.0f };

				float power = sqrt(std::powf(gamePad->curLX, 2) + std::powf(gamePad->curLY, 2));
				logger::debug(FMT_STRING("Current Power is {}"), power);

				float theta = (dir_xy[0] * dir_base[0] + dir_xy[1] * dir_base[1]) / sqrt(dir_xy[0] * dir_xy[0] + dir_xy[1] * dir_xy[1]) / sqrt(dir_base[0] * dir_base[0] + dir_base[1] * dir_base[1]);
				theta = gamePad->curLX >= 0.f ? std::acos(theta) : -std::acos(theta);
				logger::debug(FMT_STRING("theta is {}"), theta);

				if (power > padThld)
					result.emplace(theta);
			}
		}

		return result;
	}



	bool DireHandler::ComputeDirectionValue(float& a_out)
	{
		std::optional<float> dire;

		auto inputMgr = RE::BSInputDeviceManager::GetSingleton();
		if (inputMgr && inputMgr->GetKeyboard() && inputMgr->GetKeyboard()->IsEnabled() && !inputMgr->IsGamepadConnected()) 
			dire = GetKeyboardDireValue();
		else if (inputMgr->IsGamepadConnected()) 
			dire = GetGamePadDireValue();
		
		if (dire.has_value()) {
			a_out = dire.value();
			return true;
		}

		return false;
	}


}