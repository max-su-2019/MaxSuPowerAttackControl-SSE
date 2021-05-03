#pragma once

namespace MaxSuPowerAttackControl
{
	template <class T>
	struct FormPair
	{
	public:

		FormPair(const RE::FormID thisID, const RE::BSFixedString thisName) :
			formID(thisID), pluginName(thisName) {};

		const RE::FormID			formID;
		const RE::BSFixedString		pluginName;

		T* GetForm()
		{
			if (pluginName.empty())
				return RE::TESForm::LookupByID<T>(formID);
			else
				return RE::TESDataHandler::GetSingleton()->LookupForm<T>(formID, pluginName);
		}
	};


	struct MovDires
	{
		enum MovDire : std::uint32_t
		{
			kNone = 0,
			kForward,
			kBackward,
			kLeft,
			kRight
		};
	};
	using MovDire = MovDires::MovDire;


	using DirePair = std::pair<MovDire, std::string_view>;
	class DireHandler
	{

	public:

		static DireHandler* GetSingleton()
		{
			static DireHandler singleton;
			return &singleton;
		}


		bool UpdateDirectionValue();


		std::unique_ptr<FormPair<RE::TESGlobal>>	direGlobal;

	private:

		DireHandler();

		~DireHandler() = default;

		DireHandler(const DireHandler&) = delete;

		DireHandler(DireHandler&&) = delete;

		DireHandler& operator= (const DireHandler&) = delete;

		DireHandler& operator= (DireHandler&&) = delete;


	//---------------------------------- For Keyboard---------------------------------------------------------------

		MovDire							PickKeyDirection();															//	Pick the PowerAttack direction based on key pressed.
		bool							GetKeyHeldDuration(const std::uint32_t a_index, float& result) const;		//	Get the held duration of a key
		const float						GetKeyboardDireValue();

	//--------------------------------------------------------------------------------------------------------------

	
	//---------------------------------- For GamePad---------------------------------------------------------------

		const float		GetGamePadDireValue();

	//--------------------------------------------------------------------------------------------------------------


		const std::vector<DirePair> Directions
		{
			DirePair(MovDire::kForward, "Forward"),
			DirePair(MovDire::kBackward,"Back"),
			DirePair(MovDire::kLeft,"Strafe Left"), 
			DirePair(MovDire::kRight,"Strafe Right")
		};

		const float	padThld = 0.25f;

	};

}