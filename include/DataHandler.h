#pragma once

namespace MaxSuPowerAttackControl
{
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


		bool ComputeDirectionValue(float& a_out);

	private:

		DireHandler() = default;

		~DireHandler() = default;

		DireHandler(const DireHandler&) = delete;

		DireHandler(DireHandler&&) = delete;

		DireHandler& operator= (const DireHandler&) = delete;

		DireHandler& operator= (DireHandler&&) = delete;


		MovDire							PickKeyDirection();															//	Pick the PowerAttack direction based on key pressed.
		bool							GetKeyHeldDuration(const std::uint32_t a_index, float& result) const;		//	Get the held duration of a key
		const std::optional<float>		GetKeyboardDireValue();


		const std::vector<DirePair> Directions
		{
			DirePair(MovDire::kForward, "Forward"),
			DirePair(MovDire::kBackward,"Back"),
			DirePair(MovDire::kLeft,"Strafe Left"), 
			DirePair(MovDire::kRight,"Strafe Right")
		};

	};



}