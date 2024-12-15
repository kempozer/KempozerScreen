#pragma once

#include <Arduino.h>
#include <cstdint>
#include <type_traits>
#include "KempozerScreenConcepts.h"
#include "Kempozer/Screen/DriverFeatures.h"

namespace Kempozer::Screen {

	class Driver {
	public:
		/**
		 * Returns a compact struct that defines all of the features of the
		 * implementing driver so that some runtime introspection can be
		 * performed to determine the best way to read from and write to
		 * the screen.
		 */
		virtual const DriverFeatures &features() const = 0;

		/**
		 * Initializes this driver so that it can be used to interact with the
		 * screen. If the driver is successfully initialized, or no verification
		 * of initialization is possible, then true must be returned.
		 */
		virtual bool initialize() = 0;

		/**
		 * Selects this driver. This may either be a no-op if selection isn't
		 * required, driving a line high or low as a chip select, or any other
		 * method of alerting the screen that it will be sending or receiving
		 * data.
		 */
		virtual Driver *select() = 0;

		/**
		 * Deselects this driver. This may either be a no-op if selection isn't
		 * required, driving a line low or high as a chip select, or any other
		 * method of alerting the screen that it will be sending or receiving
		 * data.
		 */
		virtual Driver *deselect() = 0;

		/**
		 * Asserts that a command is being sent by this driver to the screen. This
		 * may either be a no-op if command signaling isn't required, driving a 
		 * line low or high as a signal, or any other method of alerting the screen
		 * that it will be sending or receiving a command.
		 */
		virtual Driver *assertCommand() = 0;

		/**
		 * Deasserts that a command is being sent by this driver to the screen. This
		 * may either be a no-op if command signaling isn't required, driving a 
		 * line low or high as a signal, or any other method of alerting the screen
		 * that it will be sending or receiving a command.
		 */
		virtual Driver *deassertCommand() = 0;

		/**
		 * Sends a command to the screen. This command must be convertible
		 * to an {@link std::uint8_t}, {@link std::uint16_t}, {@link std::uint32_t},
		 * or {@link std::uint64_t}.
		 * 
		 * @tparam E
		 */
		template<commandtype EnumT>
		[[gnu::always_inline]]
		inline Driver *writeCommand(EnumT command) {
			assertCommand();
			if (std::is_same_v<std::uint8_t, std::underlying_type_t<EnumT>>) {
				write(std::uint8_t(command));
			} else if (std::is_same_v<std::uint16_t, std::underlying_type_t<EnumT>>) {
				write16(std::uint16_t(command));
			} else if (std::is_same_v<std::uint32_t, std::underlying_type_t<EnumT>>) {
				write32(std::uint32_t(command));
			} else if (std::is_same_v<std::uint64_t, std::underlying_type_t<EnumT>>) {
				write64(std::uint64_t(command));
			}
			deassertCommand();
			return this;
		}

		/**
		 * 
		 */
		virtual Driver *writePixel(std::uint16_t color) = 0;

		/**
		 * Sends all 16-bit pixels to the screen.
		 * 
		 * @param count
		 * @param data
		 */
		[[gnu::nonnull]]
		virtual Driver *writePixels(std::size_t count, const std::uint16_t *data) = 0;

		/**
		 * Sends the same color of pixel to the screen repeatedly.
		 * 
		 * @param count
		 * @param color
		 */
		virtual Driver *writeRepeatedPixel(std::size_t count, const std::uint16_t color) = 0;

		/**
		 * Sends all 16-bit pixels to the screen.
		 * 
		 * @tparam C
		 * @param data
		 */
		template<std::size_t C>
		[[gnu::always_inline]]
		inline Driver *writePixels(const std::uint16_t (&data)[C]) {
			return writePixels(C, data);
		}

		/**
		 * Sends an 8-bit value to the screen. At minimum, this send method must
		 * be implemented, though the others should be overridden with higher
		 * performance implementations.
		 * 
		 * If any delays are necessary, and the default methods are used, then
		 * this method should have the appropriate delays necessary for sending
		 * each 8-bit value.
		 * 
		 * @param u8
		 */
		virtual Driver *write(std::uint8_t u8) = 0;

		/**
		 * Sends a 16-bit value to the screen.
		 * 
		 * @param u16
		 */
		virtual Driver *write16(std::uint16_t u16);

		/**
		 * Sends a 32-bit value to the screen.
		 * 
		 * @param u32
		 */
		virtual Driver *write32(std::uint32_t u32);

		/**
		 * Sends a 64-bit value to the screen.
		 * 
		 * @param u64
		 */
		virtual Driver *write64(std::uint64_t u64);

		/**
		 * Sends count 8-bit values to the screen.
		 * 
		 * @param count
		 * @param data
		 */
		[[gnu::nonnull]]
		virtual Driver *writeArray(std::size_t count, const std::uint8_t *data);

		/**
		 * Sends count 8-bit values to the screen.
		 * 
		 * @tparam C
		 * @param data
		 */
		template<std::size_t C>
		[[gnu::always_inline]]
		inline Driver *writeArray(const std::uint8_t (&data)[C]) {
			return writeArray(C, data);
		}

		/**
		 * 
		 */
		[[gnu::always_inline]]
		inline std::uint16_t readPixel() {
			std::uint16_t pixel;
			readPixels(1, &pixel);
			return pixel;
		}

		/**
		 * Reads all 16-bit pixels from the screen.
		 * 
		 * @param count
		 * @param data
		 */
		[[gnu::nonnull]]
		virtual void readPixels(std::size_t count, std::uint16_t *data) = 0;

		template<std::size_t C>
		[[gnu::always_inline]]
		inline void readPixels(std::uint16_t (&data)[C]) {
			readPixels(C, data);
		}

		/**
		 * Receives an 8-bit value from the screen.
		 * 
		 * @return
		 */
		virtual std::uint8_t read() = 0;

		/**
		 * Receives a 16-bit value from the screen.
		 * 
		 * @return
		 */
		virtual std::uint16_t read16();

		/**
		 * Receives a 32-bit value from the screen.
		 * 
		 * @return
		 */
		virtual std::uint32_t read32();

		/**
		 * Receives a 64-bit value from the screen.
		 * 
		 * @return
		 */
		virtual std::uint64_t read64();

		/**
		 * Recieves count 8-bit values from the screen.
		 * 
		 * @param count
		 * @param data
		 */
		[[gnu::nonnull]]
		virtual void readArray(std::size_t count, std::uint8_t *data);

		/**
		 * Recieves count 8-bit values from the screen.
		 * 
		 * @tparam C
		 * @param data
		 */
		template<std::size_t C>
		[[gnu::always_inline]]
		inline void readArray(std::uint8_t (&data)[C]) {
			readArray(C, data);
		}

		/**
		 * Gets the write or read graphics RAM address window.
		 * 
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 */
		virtual Driver *addressWindow(std::uint16_t &x1, std::uint16_t &y1,
								   	  std::uint16_t &x2, std::uint16_t &y2) = 0;

		/**
		 * Gets the write or read graphics RAM address window.
		 * 
		 * This is an alias of {@link addressWindow(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t)}.
		 * 
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 */
		[[gnu::always_inline]]
		[[gnu::nonnull]]
		inline Driver *addressWindow(std::uint16_t *x1, std::uint16_t *y1,
								 	 std::uint16_t *x2, std::uint16_t *y2) {
			return addressWindow(*x1, *y1, *x2, *y2);
		}

		/**
		 * Sets the write or read graphics RAM address window.
		 * 
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 */
		virtual Driver *setAddressWindow(std::uint16_t x1, std::uint16_t y1,
									  	 std::uint16_t x2, std::uint16_t y2) = 0;

		/**
		 * Rotates the screen to the given rotation. The values of rotation
		 * are defined by the individual driver. If the driver does not
		 * support rotation, then this method is a no-op. 
		 * 
		 * @param rotation
		 */
		virtual Driver *rotate(int rotation);

		/**
		 * Gets whether or not the screen has been rotated.
		 * 
		 * @return
		 */
		virtual bool rotated() = 0;

		/**
		 * Queries the screen resolution and places its width and height into the
		 * given references. If {@link rotated()} returns true, then width and
		 * height must be flipped.
		 * 
		 * This method may be overridden by drivers that are able to query the
		 * screen's resolution.
		 * 
		 * @param width
		 * @param height
		 */
		virtual Driver *resolution(std::uint16_t &width, std::uint16_t &height);

		/**
		 * Queries the screen resolution and places its width and height into the
		 * given pointers. If {@link rotated()} returns true, then width and
		 * height must be flipped.
		 * 
		 * This method is an alias of {@link resolution(std::uint16_t, std::uint16_t)}.
		 * 
		 * @param width
		 * @param height
		 */
		[[gnu::always_inline]]
		[[gnu::nonnull]]
		inline Driver *resolution(std::uint16_t *width, std::uint16_t *height) {
			return resolution(*width, *height);
		}
	protected:
		/**
		 * Initializes the width and height of the driver.
		 */
		[[gnu::always_inline]]
		inline Driver(std::uint16_t width, std::uint16_t height) {
			mHeight = height;
			mWidth = width;
		}

		std::uint16_t mHeight,
					  mWidth;
	};
};
