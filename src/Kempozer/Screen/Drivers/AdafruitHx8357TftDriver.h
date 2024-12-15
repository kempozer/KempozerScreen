#pragma once

#include "Kempozer/Screen/Driver.h"
#include "Kempozer/Screen/DriverFeatures.h"

#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/Command.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/FrameRate.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/MemoryAccessControl.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/PixelFormat.h"

namespace Kempozer::Screen::Drivers {
	using namespace ::Kempozer::Screen;
	using namespace ::Kempozer::Screen::Drivers::AdafruitHx8357Tft;

	class AdafruitHx8357TftDriver final : public Driver {
	public:
		constexpr static DriverFeatures FEATURES = {
			.hasExplicit16Implementation = true,
			.hasExplicit32Implementation = true,
			.hasExplicit64Implementation = true,
			.hasExplicitArrayImplementation = true,
			.hasExplicitCommandDataSignal = true,
			.hasExplicitReadWriteSignal = true,
			.supportsRotate = true
		};
		const DriverFeatures &features() const {
			return FEATURES;
		}

		/**
		 * 
		 */
		AdafruitHx8357TftDriver(std::uint8_t selectPin, std::uint8_t dataPin, std::uint8_t writePin, std::uint8_t readPin, 
								std::uint8_t resetPin);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver(const AdafruitHx8357TftDriver& other);

		/**
		 * @inheritdoc
		 */
		bool initialize();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *select();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *deselect();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *assertCommand();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *deassertCommand();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *writePixel(std::uint16_t color);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *writePixels(std::size_t count, const std::uint16_t *data);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *writeRepeatedPixel(std::size_t count, const std::uint16_t color);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *write(std::uint8_t u8);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *write16(std::uint16_t u16);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *write32(std::uint32_t u32);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *write64(std::uint64_t u64);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *writeArray(std::size_t count, const std::uint8_t *data);

		/**
		 * @inheritdoc
		 */
		void readPixels(std::size_t count, std::uint16_t *data);

		/**
		 * @inheritdoc
		 */
		std::uint8_t read();

		/**
		 * @inheritdoc
		 */
		std::uint16_t read16();

		/**
		 * @inheritdoc
		 */
		std::uint32_t read32();

		/**
		 * @inheritdoc
		 */
		std::uint64_t read64();

		/**
		 * @inheritdoc
		 */
		void readArray(std::size_t count, std::uint8_t *data);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *reset();

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *displayOff();

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *displayOn();

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *setMemoryAccessControl(MemoryAccessControl memoryAccessControl);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *setPixelFormat(PixelFormat dbiPixelFormat, PixelFormat dpiPixelFormat);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *setFrameRate(FrameRate normalFrameRate, FrameRate idleFrameRate);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *setSync(bool syncOn);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *setSyncScanLine(std::uint16_t scanLine);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *rotate(int rotation);

		/**
		 * @inheritdoc
		 */
		bool rotated();

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *addressWindow(std::uint16_t &x1, std::uint16_t &y1, std::uint16_t &x2, std::uint16_t &y2);

		/**
		 * @inheritdoc
		 */
		AdafruitHx8357TftDriver *setAddressWindow(std::uint16_t x1, std::uint16_t y1, std::uint16_t x2, std::uint16_t y2);

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *sleepOn();

		/**
		 * 
		 */
		AdafruitHx8357TftDriver *sleepOff();
	private:
		std::uint8_t mSelectPin,
					 mDataPin,
					 mWritePin,
					 mReadPin,
					 mResetPin;
		std::uint32_t mLastSleepOff,
					  mLastSleepOn,
					  mLastReset;
		std::uint16_t mX1,
					  mY1,
					  mX2,
					  mY2;
		bool mRotated;
	};
};
