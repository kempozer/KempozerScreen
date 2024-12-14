#pragma once

#include <cstdint>
#include <type_traits>

namespace Kempozer::Screen {
	template<typename EnumT>
	concept commandtype = requires {
		requires std::is_enum_v<EnumT>;
		requires std::is_same_v<std::uint8_t, std::underlying_type_t<EnumT>>
			  || std::is_same_v<std::uint16_t, std::underlying_type_t<EnumT>>
			  || std::is_same_v<std::uint32_t, std::underlying_type_t<EnumT>>
			  || std::is_same_v<std::uint64_t, std::underlying_type_t<EnumT>>;
	};
};
