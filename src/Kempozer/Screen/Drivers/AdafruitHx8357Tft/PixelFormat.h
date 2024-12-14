#pragma once

#include <cstdint>

namespace Kempozer::Screen::Drivers::AdafruitHx8357Tft {
	enum class PixelFormat : std::uint8_t {
		BITS_12	= 0b0011,
		BITS_16 = 0b0101,
		BITS_18 = 0b0110,
		BITS_24 = 0b0111
	};
};
