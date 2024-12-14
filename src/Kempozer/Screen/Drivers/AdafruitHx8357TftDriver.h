#pragma once

#include "Kempozer/Screen/Driver.h"

#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/Command.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/FrameRate.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/MemoryAccessControl.h"
#include "Kempozer/Screen/Drivers/AdafruitHx8357Tft/PixelFormat.h"

namespace Kempozer::Screen::Drivers {
	using namespace ::Kempozer::Screen;
	using namespace ::Kempozer::Screen::Drivers::AdafruitHx8357Tft;

	class AdafruitHx8357TftDriver final : public Driver {
	public:
		AdafruitHx8357TftDriver(std::uint8_t selectPin, std::uint8_t dataPin, std::uint8_t writePin, std::uint8_t readPin, 
								std::uint8_t resetPin);
		AdafruitHx8357TftDriver(const AdafruitHx8357TftDriver& other);

		bool initialize();

		void select();

		void deselect();

		void assertCommand();

		void deassertCommand();

		void writePixels(std::size_t count, const std::uint16_t *data);

		void writeRepeatedPixels(std::size_t count, const std::uint16_t color);

		void write(std::uint8_t u8);

		void write16(std::uint16_t u16);

		void write32(std::uint32_t u32);

		void write64(std::uint64_t u64);

		void writeArray(std::size_t count, const std::uint8_t *data);

		void readPixels(std::size_t count, std::uint16_t *data);

		std::uint8_t read();

		std::uint16_t read16();

		std::uint32_t read32();

		std::uint64_t read64();

		void readArray(std::size_t count, std::uint8_t *data);

		void reset();

		void displayOff();

		void displayOn();

		void setMemoryAccessControl(MemoryAccessControl memoryAccessControl);

		void setPixelFormat(PixelFormat dbiPixelFormat, PixelFormat dpiPixelFormat);

		void setFrameRate(FrameRate normalFrameRate, FrameRate idleFrameRate);

		void setSync(bool syncOn);

		void setSyncScanLine(std::uint16_t scanLine);

		void rotate(int rotation);

		bool rotated();

		void addressWindow(std::uint16_t &x1, std::uint16_t &y1, std::uint16_t &x2, std::uint16_t &y2);

		void setAddressWindow(std::uint16_t x1, std::uint16_t y1, std::uint16_t x2, std::uint16_t y2);

		void sleepOn();

		void sleepOff();
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
