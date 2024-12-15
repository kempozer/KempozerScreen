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

#pragma once

#include "Kempozer/Screen/Types.h"

namespace Kempozer::Screen {


	/**
	 * An interface that can be used to interrogate a driver's features programatically.
	 * 
	 * If a driver specifies that a feature is supported, then it *must* provide an
	 * explicit implementation of that feature.
	 */
	ks_packed_struct DriverFeatures {
		/**
		 * Declares that the driver has an explicit implementation for its write16 and
		 * read16 methods.
		 * If this is false, then the driver falls back to the less efficient default
		 * implementation of write16 and read16 that relies on virtual method calls.
		 */
		const bool hasExplicit16Implementation : 1;
		
		/**
		 * Declares that the driver has an explicit implementation for its write32 and
		 * read32 methods.
		 * If this is false, then the driver falls back to the less efficient default
		 * implementation of write16 and read16 that relies on virtual method calls.
		 */
		const bool hasExplicit32Implementation : 1;

		/**
		 * Declares that the driver has an explicit implementation for its write64 and
		 * read64 methods.
		 * If this is false, then the driver falls back to the less efficient default
		 * implementation of write16 and read16 that relies on virtual method calls.
		 */
		const bool hasExplicit64Implementation : 1;

		/**
		 * Declares that the driver has an explicit implementation for its writeArray and
		 * readArray methods.
		 * If this is false, then the driver falls back to the less efficient default
		 * implementation of write16 and read16 that relies on virtual method calls.
		 */
		const bool hasExplicitArrayImplementation : 1;

		/**
		 * Declares that the driver has an explicit command/data signal.
		 */
		const bool hasExplicitCommandDataSignal : 1;

		/**
		 * Declares that the driver has an explicit read/write signal.
		 */
		const bool hasExplicitReadWriteSignal : 1;

		/**
		 * Declares that the driver supports screen rotation.
		 */
		const bool supportsRotate : 1;
	};
};
