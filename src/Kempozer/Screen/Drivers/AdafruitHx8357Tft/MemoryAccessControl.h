/*
BSD 2-Clause License

Copyright (c) 2024, Bryan

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __Kempozer_Screen_Drivers_AdafruitHx8357Tft_MemoryAccessControl_h__
#define __Kempozer_Screen_Drivers_AdafruitHx8357Tft_MemoryAccessControl_h__

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

#endif//__Kempozer_Screen_Drivers_AdafruitHx8357Tft_MemoryAccessControl_h__
