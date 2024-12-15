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
