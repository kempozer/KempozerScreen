#pragma once

#include <cstdint>

namespace Kempozer::Screen::Drivers::AdafruitHx8357Tft {
	enum class FrameRate : std::uint8_t {
		FPS_030 = 0b0000,
		FPS_035 = 0b0001,
		FPS_040 = 0b0010,
		FPS_045 = 0b0011,
		FPS_050 = 0b0100,
		FPS_055 = 0b0101,
		FPS_060 = 0b0110,
		FPS_065 = 0b0111,
		FPS_070 = 0b1000,
		FPS_075 = 0b1001,
		FPS_080 = 0b1010,
		FPS_085 = 0b1011,
		FPS_090 = 0b1100,
		FPS_095 = 0b1101,
		FPS_100 = 0b1110,
		FPS_105 = 0b1111
	};
};
