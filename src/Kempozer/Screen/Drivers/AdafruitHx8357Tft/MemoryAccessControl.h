#pragma once

#include <cstdint>

namespace Kempozer::Screen::Drivers::AdafruitHx8357Tft {
	enum class MemoryAccessControl : std::uint8_t {
		RIGHT_TO_LEFT	= 1 << 2,
		BGR_FILTER		= 1 << 3,
		BOTTOM_TO_TOP	= 1 << 4,
		ROTATED			= 1 << 5,
		X_REVERSED		= 1 << 6,
		Y_REVERSED		= 1 << 7
	};

	inline MemoryAccessControl operator|=(MemoryAccessControl &left, MemoryAccessControl right) {
		return left = MemoryAccessControl(std::uint8_t(left) | std::uint8_t(right));
	}
	inline MemoryAccessControl operator|(MemoryAccessControl left, MemoryAccessControl right) {
		return MemoryAccessControl(std::uint8_t(left) | std::uint8_t(right));
	}

	inline MemoryAccessControl operator&=(MemoryAccessControl &left, MemoryAccessControl right) {
		return left = MemoryAccessControl(std::uint8_t(left) & std::uint8_t(right));
	}
	inline MemoryAccessControl operator&(MemoryAccessControl left, MemoryAccessControl right) {
		return MemoryAccessControl(std::uint8_t(left) & std::uint8_t(right));
	}

	inline MemoryAccessControl operator^=(MemoryAccessControl &left, MemoryAccessControl right) {
		return left = MemoryAccessControl(std::uint8_t(left) ^ std::uint8_t(right));
	}
	inline MemoryAccessControl operator^(MemoryAccessControl left, MemoryAccessControl right) {
		return MemoryAccessControl(std::uint8_t(left) ^ std::uint8_t(right));
	}
};
