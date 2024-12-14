#pragma once

#include "KempozerScreenConfig.h"

#if defined(ks_enable_struct_packing) && ks_enable_struct_packing

	#define ks_packed_struct struct [[gnu::packed]]

#else

	#define ks_packed_struct struct

#endif//defined(ks_enable_struct_packing) && ks_enable_struct_packing
