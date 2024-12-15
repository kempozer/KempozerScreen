#include "Kempozer/Screen/Driver.h"

namespace Kempozer::Screen {
	Driver *Driver::resolution(std::uint16_t& width, std::uint16_t& height) {
		if (rotated()) {
			width = mHeight;
			height = mWidth;
		} else {
			width = mWidth;
			height = mHeight;
		}
		return this;
	}

	Driver *Driver::write16(std::uint16_t u16) {
		write(std::uint8_t(u16));
		return write(std::uint8_t(u16 >> 8));
	}

	Driver *Driver::write32(std::uint32_t u32) {
		write16(std::uint16_t(u32));
		return write16(std::uint16_t(u32 >> 16));
	}

	Driver *Driver::write64(std::uint64_t u64) {
		write32(std::uint32_t(u64));
		return write32(std::uint32_t(u64 >> 32));
	}

	Driver *Driver::writeArray(std::size_t count, const std::uint8_t *data) {
		for (std::size_t i = 0; i < count; ++i) {
			write(data[i]);
		}
		return this;
	}

	std::uint16_t Driver::read16() {
		return std::uint16_t(read()) | (std::uint16_t(read()) << 8);
	}

	std::uint32_t Driver::read32() {
		return std::uint32_t(read16()) | (std::uint32_t(read16()) << 16);
	}

	std::uint64_t Driver::read64() {
		return std::uint64_t(read32()) | (std::uint64_t(read32()) << 32);
	}

	void Driver::readArray(std::size_t count, std::uint8_t *data) {
		for (std::size_t i = 0; i < count; ++i) {
			data[i] = read();
		}
	}

	Driver *Driver::rotate(int rotation) {
		return this;
	}
}
