#pragma once

#include <cstdint>

namespace Kempozer::Screen::Drivers::AdafruitHx8357Tft {
	/**
	 * The documentation on the members of this enum are based off of the
	 * HX8357-D's (seemingly incomplete) documentation, along with testing.
	 */
	enum class Command : std::uint8_t {
		/**
		 * As the name implies, this command is a no-op. Nothing is modified
		 * when executed. This command can be used to end a
		 * [write](#WRITE_MEMORY), [read](#READ_MEMORY),
		 * [continue write](#WRITE_MEMORY_CONTINUE), or
		 * [continue read](#READ_MEMORY_CONTINUE) command without executing
		 * another command.
		 * 
		 * Command Results
		 * ===============
		 * None
		 * 
		 * @see #WRITE_MEMORY
		 * @see #READ_MEMORY
		 * @see #WRITE_MEMORY_CONTINUE
		 * @see #READ_MEMORY_CONTINUE
		 */
		NO_OP 											= 0x00,
		/**
		 * Resets the driver IC and display to its initial state. All settings
		 * are reset to factory default, but the RAM of the screen module is
		 * left untouched.
		 * A delay of 5 milliseconds is required after performing a reset and
		 * sending any other commands. Duing this time, the panel is restoring
		 * factory settings.
		 * A delay of 120 milliseconds is required between reseting and sending
		 * the [sleep off](#SLEEP_OFF) command.
		 * 
		 * Command Results
		 * ===============
		 * None
		 * 
		 * @see #SLEEP_OFF
		 */
		RESET 											= 0x01,
		/**
		 * Reads the identification information of the panel.
		 * 
		 * Command Results
		 * ===============
		 * 
		 * - 0: Dummy read
		 * - 1: Panel manufacturer ID
		 * - 2: Panel/driver version ID
		 * - 3: Panel/driver ID
		 * 
		 * @see #READ_PANEL_MANUFACTURER_ID
		 * @see #READ_PANEL_DRIVER_VERSION_ID
		 * @see #READ_PANEL_DRIVER_ID
		 */
		READ_DISPLAY_IDENTIFICATION_INFORMATION 		= 0x04,
		/**
		 * Reads the number of DSI errors on the panel.
		 * 
		 * Command Results
		 * ===============
		 * 
		 * - 0: Dummy read
		 * - 1: A byte with the flags
		 *   - D7: Overflow status
		 * 	   - 0: No overflow
		 * 	   - 1: Overflow
		 * 	 -D6..D0: Total number of errors
		 */
		READ_NUMBER_OF_ERRORS_ON_DSI 					= 0x05,
		/**
		 * Not used (currently)
		 */
		READ_RED_COLOR 									= 0x06,
		/**
		 * Not used (currently)
		 */
		READ_GREEN_COLOR 								= 0x07,
		/**
		 * Not used (currently)
		 */
		READ_BLUE_COLOR 								= 0x08,
		/**
		 * Reads the panel's power configuration.
		 * 
		 * Command Results
		 * ===============
		 * 
		 * - 0: Dummy read
		 * - 1: A byte with the flags
		 *   - D7: Booster status
		 *     - 0: booster off/faulted
		 * 	   - 1: booster on
		 * 	 - D6: Idle mode
		 *     - 0: Idle mode off
		 * 	   - 1: Idle mode on
		 * 	 - D5: Partial update mode
		 *     - 0: Partial update mode off
		 * 	   - 1: Partial update mode on
		 * 	 - D4: Sleep mode
		 *     - 0: Sleep mode on
		 * 	   - 1: Sleep mode off
		 * 	 - D3: Normal mode
		 *     - 0: Normal mode off
		 * 	   - 1: Normal mode on
		 * 	 - D2: Display
		 *     - 0: Display off
		 * 	   - 1: Display on
		 * 	 - D1..D0: Always 0
		 * 
		 * @see #IDLE_ON
		 * @see #IDLE_OFF
		 * @see #PARTIAL_UPDATE_ON
		 * @see #SLEEP_ON
		 * @see #SLEEP_OFF
		 * @see #NORMAL_ON
		 * @see #DISPLAY_OFF
		 * @see #DISPLAY_ON
		 */
		READ_DISPLAY_POWER_MODE							= 0x0A,
		/**
		 * Reads the panel's memory address control configuration.
		 * 
		 * Command Results
		 * ===============
		 * - 0: Dummy read
		 * - 1: A byte with the following flags
		 * - D7: Y address direction
		 * - 0: Top to bottom
		 * - 1: Bottom to top
		 *   - D6: X address direction
		 * 	   - 0: Left to right
		 * 	   - 1: Right to left
		 *   - D5: Rotation
		 * 	   - 0: Increment X then Y
		 * 	   - 1: Increment Y then X)
		 *   - D4: Refresh direction
		 * 	   - 0: Top to bottom
		 * 	   - 1: Bottom to top)
		 *   - D3: RGB order
		 * 	   - 0: RGB
		 * 	   - 1: BGR
		 *   - D2: Display data latch order
		 * 	   - 0: Left to right
		 * 	   - 1: Right to left
		 *   - D1..D0: Always 0
		 */
		READ_DISPLAY_MEMORY_ADDRESS_CONTROL				= 0x0B,
		/**
		 * Reads the panel's pixel format configuration.
		 * 
		 * Command Results
		 * ===============
		 * - 0: Dummy read
		 * - 1: A byte with the following flags:
		 *   - D7: Always 0
		 * 	 - D6..D4: Bits of the DPI pixel format
		 * 	 - D3: Always 0
		 * 	 - D2..D0: Bits of the DBI pixel format
		 * 
		 * @see #WRITE_DISPLAY_PIXEL_FORMAT
		 */
		READ_DISPLAY_PIXEL_FORMAT						= 0x0C,
		/**
		 * Reads the panel's display configuration.
		 * 
		 * Command Results
		 * ===============
		 * - 0: Dummy read
		 * - 1: A byte with the following flags:
		 *   - D7: Vertical scrolling mode
		 * 	   - 0: Vertical scrolling mode off
		 * 	   - 1: Vertical scrolling mode on
		 * 	 - D6: Always 0
		 * 	 - D5: Color inversion mode
		 * 	   - 0: Color inversion mode off
		 * 	   - 1: Color inversion mode on
		 * 	 - D4..D3: Always 0
		 *   - D2..D0: Gamma curve selection
		 * 	   - 0b000: Gamma curve 1
		 * 	   - 0b001: Gamma curve 2
		 * 	   - 0b010: Gamma curve 3
		 * 	   - 0b011: Gamma curve 4
		 * 
		 * @see #WRITE_GAMMA
		 */
		READ_DISPLAY_IMAGE_MODE							= 0x0D,
		/**
		 * Reads the panel's signaling configuration.
		 * 
		 * Command Results
		 * ===============
		 * - 0: Dummy read
		 * - 1: A byte with the following flags:
		 * 	 - D7: Sync signal
		 * 	   - 0: Sync signal off
		 * 	   - 1: Sync signal on
		 * 	 - D6: Sync signal mode
		 * 	   - 0: Sync signal mode 1
		 * 	   - 1: Sync signal mode 2
		 * 	 - D5..D1: - Always 0
		 * 	 - D0: DSI error
		 * 	   - 0: No DSI errors
		 * 	   - 1: DSI errors
		 */
		READ_DISPLAY_SIGNAL_MDOE						= 0x0E,
		/**
		 * Reads the panel's self-diagnostic report.
		 * 
		 * Command Results
		 * ===============
		 * - 0: Dummy read
		 * - 1: A byte with the following flags:
		 * 	 - D7: Register loading direction (TODO: Investigate the use of this flag)
		 * 	 - D6: Functionality detection (TODO: Investigate the use of this flag)
		 * 	 - D5..D1: Always 0
		 * 	 - D0: Checksum status
		 * 	   - 0: Checksum passed
		 * 	   - 1: Checksum failed
		 */
		READ_DISPLAY_SELF_DIAGNOSTIC_RESULT				= 0x0F,
		/**
		 * Enters the panel into sleep mode. While in sleep mode mode, the
		 * panel's DC/DC converter and internal oscillator are disabled, and the
		 * panel will stop updating. If the panel is already in sleep mode, this
		 * command has no effect.
		 * A delay of 5 milliseconds is required between entering sleep mode and
		 * sending any  other commands.
		 * A delay of 120 milliseconds is required between entering sleep mode
		 * and sending the {@link Command#SLEEP_OFF} command.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		SLEEP_ON										= 0x10,
		/**
		 * Disables the panel sleep mode. The panel's DC/DC converter and
		 * internal oscillator are enabled, and the panel will resume updating.
		 * If the panel is already out of sleep mode, this command has no
		 * effect.
		 * A delay of 5 milliseconds is required between exiting sleep mode and
		 * sending any other commands. During this time, the panel is restoring
		 * factory settings and performing diagnostics.
		 * A delay of 120 milliseconds is required between exiting sleep mode
		 * and sending the {@link Command#SLEEP_ON} command.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		SLEEP_OFF										= 0x11,
		/**
		 * Enters the panel into partial update mode. The partial update screen
		 * area is defined by the {@link Command#WRITE_PARTIAL_AREA} command.
		 * @return None
		 */
		PARTIAL_UPDATE_ON								= 0x12,
		/**
		 * Exits the panel from partial update, vertical scrolling, all pixels
		 * off, and all pixels on modes.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		NORMAL_ON										= 0x13,
		/**
		 * Exits the panel from color inversion mode.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		DISPLAY_INVERSION_OFF							= 0x20,
		/**
		 * Enters the panel into color inversion mode. Color inversion mode
		 * makes no changes to the panel's RAM.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		DISPLAY_INVERSION_ON							= 0x21,
		/**
		 * Disables the panel's access to its RAM, displaying all black. Pixels
		 * off mode makes no changes to the panel's RAM.
		 * The {@link Command#ALL_PIXELS_ON}, {@link Command#NORMAL_MODE_ON},
		 * and {@link Command#PARTIAL_UPDATE_MODE_ON} commands can be used to
		 * exit pixels off mode.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		ALL_PIXELS_OFF									= 0x22,
		/**
		 * Disables the panel's access to its RAM, displaying all white. Pixels
		 * on mode makes no changes to the panel's RAM.
		 * The {@link Command#ALL_PIXELS_OFF}, {@link Command#NORMAL_MODE_ON},
		 * and {@link Command#PARTIAL_UPDATE_MODE_ON} commands can be used to
		 * exit pixels on mode.
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		ALL_PIXELS_ON									= 0x23,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_GAMMA										= 0x26,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		DISPLAY_OFF 									= 0x28,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		DISPLAY_ON 										= 0x29,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_COLUMN_ADDRESS							= 0x2A,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_PAGE_ADDRESS								= 0x2B,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_MEMORY									= 0x2C,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * 0 - Dummy read
		 */
		READ_MEMORY 									= 0x2E,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * 0 - Dummy read
		 */
		WRITE_PARTIAL_AREA								= 0x30,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_VERTICAL_SCROLLING_DEFINITION				= 0x33,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		SYNC_SIGNAL_OFF									= 0x34,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		SYNC_SIGNAL_ON									= 0x35,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_MEMORY_ACCESS_CONTROL						= 0x36,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_VERTICAL_SCROLLING_START_ADDRESS			= 0x37,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		IDLE_OFF										= 0x38,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		IDLE_ON											= 0x39,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_INTERFACE_PIXEL_FORMAT					= 0x3A,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_MEMORY_CONTINUE							= 0x3C,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * 0 - Dummy read
		 */
		READ_MEMORY_CONTINUE							= 0x3E,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_SYNC_SCAN_LINE							= 0x44,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_SCAN_LINE									= 0x45,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DISPLAY_BRIGHTNESS						= 0x51,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_DISPLAY_BRIGHTNESS							= 0x52,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DISPLAY_CONTROL_VALUE						= 0x53,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_DISPLAY_CONTROL_VALUE						= 0x54,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_ADAPTIVE_BRIGHTNESS_CONTROL_VALUE			= 0x55,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		READ_ADAPTIVE_BRIGHTNESS_CONTROL_VALUE			= 0x56,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_ADAPTIVE_BRIGHTNESS_MINIMUM_VALUE			= 0x5E,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_ADAPTIVE_BRIGHTNESS_MINIMUM_VALUE			= 0x5F,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_ADAPTIVE_BRIGHTNESS_SELF_DIAGNOSTIC_RESULT	= 0x68,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLACK_WHITE_LOW_BITS						= 0x70,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLACK_X									= 0x71,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLACK_Y									= 0x72,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_WHITE_X									= 0x73,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_WHITE_Y									= 0x74,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_RED_GREEN_LOW_BITS							= 0x75,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_RED_X										= 0x76,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_RED_Y										= 0x77,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_GREEN_X									= 0x78,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_GREEN_Y									= 0x79,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLUE_A_LOW_BITS							= 0x7A,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLUE_X										= 0x7B,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_BLUE_Y										= 0x7C,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_A_X 										= 0x7D,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_A_Y 										= 0x7E,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_DDB 										= 0xA1,
		/**
		 * TODO: Document these commands
		 * 
		 * Command Results
		 * ===============
		 * Unknown
		 */
		READ_DDB_CONTINUE								= 0xA8,
		/**
		 * 
		 */
		READ_CHECKSUM									= 0xAA,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_CHECKSUM_CONTINUE							= 0xAF,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_IC_ID										= 0xD0,  // Identifies the driver chip - should always return 0x99
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_PANEL_MANUFACTURER_ID						= 0xDA,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_PANEL_DRIVER_VERSION_ID					= 0xDB,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 */
		READ_PANEL_DRIVER_ID							= 0xDC,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_OSCILLATOR								= 0xB0,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_POWER_CONTROL								= 0xB1,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DISPLAY_REGISTER							= 0xB2,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_RGB_INTERFACE								= 0xB3,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DISPLAY_CYCLE_REGISTER					= 0xB4,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_BGP										= 0xB5,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_VCOM_VOLTAGE_REGISTER						= 0xB6,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_OTP										= 0xB7,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_ENABLE_EXTENSION_COMMANDS					= 0xB9,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_STBA										= 0xC0,  // Something to do with power control
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DCG 										= 0xC1,  // Also something to do with power control
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_ID 										= 0xC3,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_DDB 										= 0xC4,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_ADAPTIVE_BRIGHTNESS_CONTROL_SETTING		= 0xC9,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_PANEL_CHARACTERISTICS						= 0xCC,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_GAMMA_CURVE 								= 0xE0,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_IMAGE_FUNCTION							= 0xE9,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_SPI_COMMAND_TYPE							= 0xEA,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_SPI_COLOR									= 0xEB,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		WRITE_SPI_READ_INDEX							= 0xFE,
		/**
		 * 
		 * 
		 * Command Results
		 * ===============
		 * None
		 */
		READ_SPI_COMMAND_TYPE							= 0xFF
	};
};
