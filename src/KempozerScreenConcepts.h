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

#ifndef __KempozerScreenConcepts_h__
#define __KempozerScreenConcepts_h__

#ifdef  __cpp_concepts

#include <cstdint>
#include <type_traits>

template<typename EnumT>
concept commandtype = requires {
    requires std::is_enum_v<EnumT>;
    requires std::is_same_v<std::uint8_t, std::underlying_type_t<EnumT>>
          || std::is_same_v<std::uint16_t, std::underlying_type_t<EnumT>>
          || std::is_same_v<std::uint32_t, std::underlying_type_t<EnumT>>
          || std::is_same_v<std::uint64_t, std::underlying_type_t<EnumT>>;
};

#else

#define commandtype typename

#endif//__cpp_concepts

#endif//__KempozerScreenConcepts_h__
