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

#ifndef __Kempozer_Screen_Drivers_AdafruitHx8357Tft_FrameRate_h__
#define __Kempozer_Screen_Drivers_AdafruitHx8357Tft_FrameRate_h__

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

#endif//__Kempozer_Screen_Drivers_AdafruitHx8357Tft_FrameRate_h__
