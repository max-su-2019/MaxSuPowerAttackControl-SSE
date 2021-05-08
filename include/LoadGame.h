#pragma once

namespace MaxSuPowerAttackControl
{
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\MaxsuPowerAttackControl.ini"


	void EventCallback(SKSE::MessagingInterface::Message* msg);


	static inline std::string ReturnStringValueFromINI(std::string file_path, std::string section_name, std::string key_name, std::string default_value)
	{
		char return_string[255];

		std::int32_t len = GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), default_value.c_str(), return_string, sizeof(return_string), file_path.c_str());

		logger::debug(FMT_STRING("String length is {}"), len);

		if (len <= 0)
		{
			logger::debug("Key Value is Error, return default value");
			return default_value;
		}
		else
		{
			logger::debug(FMT_STRING("Get Result String Value is {}"), return_string);
			return return_string;
		}

	}

	static inline const float GetFloatFromINI(std::string section_name, std::string key_name, const float default_value)
	{
		logger::debug("Start Getting Float From INI File");

		const std::string file_path = SETTINGFILE_PATH;

		auto result_string = ReturnStringValueFromINI(file_path, section_name, key_name, "");

		if (result_string.empty())
		{
			logger::debug("Get Error Float Value, return default float value");
			return default_value;
		}

		auto result_value = std::stof(result_string);

		logger::debug(FMT_STRING("Get Result Float Value is {}"), result_value);

		return result_value;

	}

}