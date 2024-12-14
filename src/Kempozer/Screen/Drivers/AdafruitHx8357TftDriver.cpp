#include "Kempozer/Screen/Drivers/AdafruitHx8357TftDriver.h"

#include <Arduino.h>
#include <cassert>

namespace Kempozer::Screen::Drivers {
	using namespace ::Kempozer::Screen;
	using namespace ::Kempozer::Screen::Drivers::AdafruitHx8357Tft;

	constexpr std::uint32_t CORE_PIN19_PIN18_BITMASK = CORE_PIN19_BITMASK
													 | CORE_PIN18_BITMASK,
							CORE_PIN17_PIN16_BITMASK = CORE_PIN17_BITMASK
								  					 | CORE_PIN16_BITMASK;
	constexpr std::uint32_t CORE_DATA_BITMASK = CORE_PIN19_PIN18_BITMASK
											  | CORE_PIN17_PIN16_BITMASK
											  | CORE_PIN15_BITMASK
											  | CORE_PIN14_BITMASK
											  | CORE_PIN41_BITMASK
											  | CORE_PIN40_BITMASK;
	constexpr std::uint32_t CORE_PORT_BITMASK = ~CORE_DATA_BITMASK;

	#define assertRead(driver) digitalWriteFast(driver->mReadPin, LOW)
	#define deassertRead(driver) digitalWriteFast(driver->mReadPin, HIGH)
	#define assertReset(driver) digitalWriteFast(driver->mResetPin, LOW)
	#define deassertReset(driver) digitalWriteFast(driver->mResetPin, HIGH)
	#define assertWrite(driver) digitalWriteFast(driver->mWritePin, LOW)
	#define deassertWrite(driver) digitalWriteFast(driver->mWritePin, HIGH)

	[[gnu::always_inline]]
	inline void setDataDirection(uint8_t direction) {
		pinMode(19, direction);
		pinMode(18, direction);
		pinMode(17, direction);
		pinMode(16, direction);
		pinMode(15, direction);
		pinMode(14, direction);
		pinMode(41, direction);
		pinMode(40, direction);
	}

	[[gnu::always_inline]]
	inline std::uint32_t remap8To32(std::uint8_t u8) {
		std::uint32_t remap = ((u8 & 0b00000011) << (CORE_PIN19_BIT - 0))	// 16  ,  D0
																			// 17  ,  D1
					   		| ((u8 & 0b00001100) << (CORE_PIN17_BIT - 2))	// 22  ,  D2
					   														// 23  ,  D3
					   		| ((u8 & 0b00010000) << (CORE_PIN15_BIT - 4))	// 19  ,  D4
					   		| ((u8 & 0b00100000) << (CORE_PIN14_BIT - 5))	// 18  ,  D5
					   		| ((u8 & 0b01000000) << (CORE_PIN41_BIT - 6))	// 20  ,  D6
					   		| ((u8 & 0b10000000) << (CORE_PIN40_BIT - 7));  // 21  ,  D7
		return remap;
	}

	[[gnu::always_inline]]
	inline std::uint8_t remap32To8(std::uint32_t u32) {
		std::uint8_t remap = ((u32 & CORE_PIN19_PIN18_BITMASK) >> (CORE_PIN19_BIT - 0))
			 			   | ((u32 & CORE_PIN17_PIN16_BITMASK) >> (CORE_PIN17_BIT - 2))
			 			   | ((u32 & CORE_PIN15_BITMASK		 ) >> (CORE_PIN15_BIT - 4))
			 			   | ((u32 & CORE_PIN14_BITMASK		 ) >> (CORE_PIN14_BIT - 5))
			 			   | ((u32 & CORE_PIN41_BITMASK		 ) >> (CORE_PIN41_BIT - 6))
			 			   | ((u32 & CORE_PIN40_BITMASK		 ) >> (CORE_PIN40_BIT - 7));
		return remap;
	}

	[[gnu::always_inline]]
	inline void enableExtensionCommands(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_ENABLE_EXTENSION_COMMANDS);
		driver->writeArray<3>({0xFF, 0xB3, 0x57});
		delay(250);  // TODO: Update this to a more accurate delay.
	}

	[[gnu::always_inline]]
	inline void initializeRgbInterface(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_RGB_INTERFACE);
		driver->writeArray<4>({0b00110000, 0b00000000, 0b00000110, 0b00000110});
	}

	[[gnu::always_inline]]
	inline void initializeVComVoltage(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_VCOM_VOLTAGE_REGISTER);
		driver->write(0x25);
	}

	[[gnu::always_inline]]
	inline void initializePanel(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_PANEL_CHARACTERISTICS);
		driver->write(0b00000101);
	}

	[[gnu::always_inline]]
	inline void initializePowerControl(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_POWER_CONTROL);
		driver->writeArray<6>({0x00, 0x15, 0x1C, 0x1C, 0x83, 0xAA});
	}

	[[gnu::always_inline]]
	inline void initializeStba(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_STBA);
		driver->writeArray<6>({0x50, 0x50, 0x01, 0x3C, 0x1E, 0x08});
	}

	[[gnu::always_inline]]
	inline void initializeDisplayCycle(Driver* driver) {
		reinterpret_cast<AdafruitHx8357TftDriver*>(driver)->writeCommand(Command::WRITE_DISPLAY_CYCLE_REGISTER);
		driver->writeArray<7>({0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78});
	}

	// Main methods
	AdafruitHx8357TftDriver::AdafruitHx8357TftDriver(uint8_t selectPin, uint8_t dataPin, uint8_t writePin, uint8_t readPin,
													 uint8_t resetPin) :
							 Screen::Driver(320, 480) {
		mSelectPin = selectPin;
		mDataPin = dataPin;
		mWritePin = writePin;
		mReadPin = readPin;
		mResetPin = resetPin;

		mLastSleepOn = 0;
		mLastSleepOff = 0;
		mLastReset = 0;

		mX1 = 0;
		mY1 = 0;
		mX2 = 0;
		mY2 = 0;

		mRotated = false;
	}

	AdafruitHx8357TftDriver::AdafruitHx8357TftDriver(const AdafruitHx8357TftDriver& other) :
			   				 AdafruitHx8357TftDriver(other.mSelectPin, other.mDataPin, other.mWritePin, other.mReadPin,
			   				 						 other.mResetPin) {
		mLastSleepOn = other.mLastSleepOn;
		mLastSleepOff = other.mLastSleepOff;
		mLastReset = other.mLastReset;

		mX1 = other.mX1;
		mY1 = other.mY1;
		mX2 = other.mX2;
		mY2 = other.mY2;

		mRotated = other.mRotated;
	}

	bool AdafruitHx8357TftDriver::initialize() {
		deassertCommand();
		deassertWrite(this);
		deassertRead(this);
		deassertReset(this);

		pinMode(mSelectPin, OUTPUT);
		pinMode(mDataPin, OUTPUT);
		pinMode(mWritePin, OUTPUT);
		pinMode(mReadPin, OUTPUT);
		pinMode(mResetPin, OUTPUT);
		setDataDirection(OUTPUT);

		select();
		reset();
		displayOff();
		enableExtensionCommands(this);
		initializeRgbInterface(this);
		initializeVComVoltage(this);
		setFrameRate(FrameRate::FPS_030, FrameRate::FPS_030);
		initializePanel(this);
		initializePowerControl(this);
		initializeStba(this);
		initializeDisplayCycle(this);

		setPixelFormat(PixelFormat::BITS_16, PixelFormat::BITS_16);
		rotate(0);
		setSync(true);
		setSyncScanLine(0x0002);
		sleepOff();
		displayOn();

		return true;
	}

	void AdafruitHx8357TftDriver::select() {
		digitalWriteFast(mSelectPin, LOW);
	}

	void AdafruitHx8357TftDriver::deselect() {
		digitalWriteFast(mSelectPin, HIGH);
	}

	void AdafruitHx8357TftDriver::assertCommand() {
		digitalWriteFast(mDataPin, LOW);
	}

	void AdafruitHx8357TftDriver::deassertCommand() {
		digitalWriteFast(mDataPin, HIGH);
	}

	void AdafruitHx8357TftDriver::writePixels(std::size_t count, const std::uint16_t *data) {
		writeCommand(Command::WRITE_MEMORY);
		for (std::size_t i = 0; i < count; ++i) {
			write(std::uint8_t(data[i] >> 8));
			write(std::uint8_t(data[i] >> 0));
		}
	}

	void AdafruitHx8357TftDriver::writeRepeatedPixels(std::size_t count, const std::uint16_t color) {
		std::uint8_t hi = std::uint8_t(color >> 8);
		std::uint8_t lo = std::uint8_t(color >> 0);

		writeCommand(Command::WRITE_MEMORY);;
		for (std::size_t i = 0; i < count; ++i) {
			write(hi);
			write(lo);
		}
	}

	void AdafruitHx8357TftDriver::write(std::uint8_t u8) {
		*(&GPIO6_DR) = (CORE_PORT_BITMASK & *(&GPIO6_DR)) | remap8To32(u8);
		assertWrite(this);
		deassertWrite(this);
	}

	void AdafruitHx8357TftDriver::write16(std::uint16_t u16) {
		write(std::uint8_t(u16 >> 8));
		write(std::uint8_t(u16 >> 0));
	}

	void AdafruitHx8357TftDriver::write32(std::uint32_t u32) {
		write(std::uint8_t(u32 >> 24));
		write(std::uint8_t(u32 >> 16));
		write(std::uint8_t(u32 >> 8));
		write(std::uint8_t(u32 >> 0));
	}

	void AdafruitHx8357TftDriver::write64(std::uint64_t u64) {
		write(std::uint8_t(u64 >> 56));
		write(std::uint8_t(u64 >> 48));
		write(std::uint8_t(u64 >> 40));
		write(std::uint8_t(u64 >> 32));
		write(std::uint8_t(u64 >> 24));
		write(std::uint8_t(u64 >> 16));
		write(std::uint8_t(u64 >> 8));
		write(std::uint8_t(u64 >> 0));
	}

	void AdafruitHx8357TftDriver::writeArray(std::size_t count, const std::uint8_t *data) {
		for (std::size_t i = 0; i < count; ++i) {
			write(data[i]);
		}
	}

	void AdafruitHx8357TftDriver::readPixels(std::size_t count, std::uint16_t *data) {
		writeCommand(Command::READ_MEMORY);
		// Dummy read - required by the controller.
		read();
		for (std::size_t i = 0; i < count; ++i) {
			data[i] = read() | (read() << 8);
		}
	}

	std::uint8_t AdafruitHx8357TftDriver::read() {
		setDataDirection(INPUT);
		assertRead(this);
		delayNanoseconds(475);
		std::uint8_t u8 = remap32To8(*(&GPIO6_DR));
		deassertRead(this);
		setDataDirection(OUTPUT);
		return u8;
	}

	std::uint16_t AdafruitHx8357TftDriver::read16() {
		setDataDirection(INPUT);
		std::uint16_t u16 = 0;
		#pragma unroll 2
		for (std::size_t i = 0; i < 2; ++i) {
			assertRead(this);
			delayNanoseconds(475);
			u16 = (u16 << 8) | remap32To8(*(&GPIO6_DR));
			deassertRead(this);
		}
		setDataDirection(OUTPUT);
		return u16;
	}

	std::uint32_t AdafruitHx8357TftDriver::read32() {
		setDataDirection(INPUT);
		std::uint32_t u32 = 0;
		#pragma unroll 4
		for (std::size_t i = 0; i < 4; ++i) {
			assertRead(this);
			delayNanoseconds(475);
			u32 = (u32 << 8) | remap32To8(*(&GPIO6_DR));
			deassertRead(this);
		}
		setDataDirection(OUTPUT);
		return u32;
	}

	std::uint64_t AdafruitHx8357TftDriver::read64() {
		setDataDirection(INPUT);
		std::uint64_t u64 = 0;
		#pragma unroll 8
		for (std::size_t i = 0; i < 8; ++i) {
			assertRead(this);
			delayNanoseconds(475);
			u64 = (u64 << 8) | remap32To8(*(&GPIO6_DR));
			deassertRead(this);
		}
		setDataDirection(OUTPUT);
		return u64;
	}

	void AdafruitHx8357TftDriver::readArray(std::size_t count, std::uint8_t *data) {
		assert(count);
		assert(nullptr != data);
		setDataDirection(INPUT);
		for (std::size_t i = 0; i < count; ++i) {
			assertRead(this);
			delayNanoseconds(475);
			data[i] = remap32To8(*(&GPIO6_DR));
			deassertRead(this);
		}
		setDataDirection(OUTPUT);
	}

	void AdafruitHx8357TftDriver::reset() {
		std::uint32_t timeSinceLastSleepOff = millis() - mLastSleepOff;
		if (timeSinceLastSleepOff < 120) {
			delay(timeSinceLastSleepOff);
		}
		
		writeCommand(Command::RESET);
		mLastReset = millis();
		delay(5);
	}

	void AdafruitHx8357TftDriver::displayOn() {
		writeCommand(Command::DISPLAY_ON);
	}

	void AdafruitHx8357TftDriver::displayOff() {
		writeCommand(Command::DISPLAY_OFF);
	}

	void AdafruitHx8357TftDriver::setMemoryAccessControl(MemoryAccessControl memoryAccessControl) {
		writeCommand(Command::WRITE_MEMORY_ACCESS_CONTROL);
		write(std::uint8_t(memoryAccessControl));
	}

	void AdafruitHx8357TftDriver::setPixelFormat(PixelFormat dbiPixelFormat, PixelFormat dpiPixelFormat) {
		writeCommand(Command::WRITE_INTERFACE_PIXEL_FORMAT);
		write((std::uint8_t(dpiPixelFormat) << 4) | std::uint8_t(dbiPixelFormat));
	}

	void AdafruitHx8357TftDriver::setFrameRate(FrameRate normalFrameRate, FrameRate idleFrameRate) {
		writeCommand(Command::WRITE_OSCILLATOR);
		write((std::uint8_t(idleFrameRate) << 4) | std::uint8_t(normalFrameRate));
		write(0x01);
	}

	void AdafruitHx8357TftDriver::setSync(bool syncOn) {
		writeCommand(syncOn ? Command::SYNC_SIGNAL_ON : Command::SYNC_SIGNAL_OFF);
	}

	void AdafruitHx8357TftDriver::setSyncScanLine(uint16_t scanLine) {
		writeCommand(Command::WRITE_SYNC_SCAN_LINE);
		write16(scanLine);
	}

	void AdafruitHx8357TftDriver::sleepOn() {
		std::uint32_t timeSinceLastSleepOff = millis() - mLastSleepOff;
		if (timeSinceLastSleepOff < 120) {
			delay(timeSinceLastSleepOff);
		}

		writeCommand(Command::SLEEP_ON);
		mLastSleepOn = millis();
	}

	void AdafruitHx8357TftDriver::sleepOff() {
		std::uint32_t timeSinceLastSleepOn = millis() - mLastSleepOn;
		if (timeSinceLastSleepOn < 120) {
			delay(timeSinceLastSleepOn);
		}

		std::uint32_t timeSinceLastReset = millis() - mLastReset;
		if (timeSinceLastReset < 120) {
			delay(timeSinceLastReset);
		}

		writeCommand(Command::SLEEP_OFF);
		mLastSleepOff = millis();
		delay(5);
	}

	void AdafruitHx8357TftDriver::rotate(int rotation) {
		MemoryAccessControl memoryAccessControl = MemoryAccessControl::BGR_FILTER;

		switch (rotation) {
		case 0:
			memoryAccessControl |= MemoryAccessControl::Y_REVERSED;
			break;
		case 1:
			memoryAccessControl |= MemoryAccessControl::ROTATED
								|  MemoryAccessControl::X_REVERSED
								|  MemoryAccessControl::Y_REVERSED;
			break;
		case 2:
			memoryAccessControl |= MemoryAccessControl::X_REVERSED;
			break;
		default:
			memoryAccessControl |= MemoryAccessControl::ROTATED;
			break;
		}

		mRotated = MemoryAccessControl::ROTATED == (MemoryAccessControl::ROTATED & memoryAccessControl);

		setMemoryAccessControl(memoryAccessControl);
	}

	bool AdafruitHx8357TftDriver::rotated() {
		return mRotated;
	}

	void AdafruitHx8357TftDriver::addressWindow(uint16_t &x1, uint16_t &y1, uint16_t &x2, uint16_t &y2) {
		x1 = mX1;
		y1 = mY1;
		x2 = mX2;
		y2 = mY2;
	}

	void AdafruitHx8357TftDriver::setAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
		mX1 = x1;
		mY1 = y1;
		mX2 = x2;
		mY2 = y2;

		writeCommand(Command::WRITE_COLUMN_ADDRESS);
		write16(x1);
		write16(x2);
		writeCommand(Command::WRITE_PAGE_ADDRESS);
		write16(y1);
		write16(y2);
	}
};
