#ifndef ADXL435_REGISTER_H
#define ADXL435_REGISTER_H

// please refer to the sensor datasheet.
//
// EN: http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf

// Register Map
// Order is "Type, Reset Value, Description".
#define REG_DEVID          0x00    // R,     11100101,   Device ID
// The DEVID register holds a fixed device ID code of 0xE5 (345 octal).
#define REG_DEVID_CONST_VALUE 0xE5

// The THRESH_TAP register is eight bits and holds the threshold
// value for tap interrupts. The data format is unsigned, therefore,
// the magnitude of the tap event is compared with the value
// in THRESH_TAP for normal tap detection. The scale factor is
// 62.5 mg/LSB (that is, 0xFF = 16 g). A value of 0 may result in
// undesirable behavior if single tap/double tap interrupts are
// enabled. 
#define REG_THRESH_TAP     0x1D    // R/W,   00000000,   Tap threshold

// The OFSX, OFSY, and OFSZ registers are each eight bits and
// offer user-set offset adjustments in twos complement format
// with a scale factor of 15.6 mg/LSB (that is, 0x7F = 2 g). The
// value stored in the offset registers is automatically added to the
// acceleration data, and the resulting value is stored in the output
// data registers. For additional information regarding offset
// calibration and the use of the offset registers, refer to the Offset
// Calibration section.
#define REG_OFSX           0x1E    // R/W,   00000000,   X-axis offset
#define REG_OFSY           0x1F    // R/W,   00000000,   Y-axis offset
#define REG_OFSZ           0x20    // R/W,   00000000,   Z-axis offset

// The DUR register is eight bits and contains an unsigned time
// value representing the maximum time that an event must be
// above the THRESH_TAP threshold to qualify as a tap event. The
// scale factor is 625 µs/LSB. A value of 0 disables the single tap/
// double tap functions
#define REG_DUR            0x21    // R/W,   00000000,   Tap duration

// The latent register is eight bits and contains an unsigned time
// value representing the wait time from the detection of a tap
// event to the start of the time window (defined by the window
// register) during which a possible second tap event can be detected.
// The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap
// function.
#define REG_LATENT         0x22    // R/W,   00000000,   Tap latency 

// The window register is eight bits and contains an unsigned time
// value representing the amount of time after the expiration of the
// latency time (determined by the latent register) during which a
// second valid tap can begin. The scale factor is 1.25 ms/LSB. A
// value of 0 disables the double tap function. 
#define REG_WINDOW         0x23    // R/W,   00000000,   Tap window

// The THRESH_ACT register is eight bits and holds the threshold
// value for detecting activity. The data format is unsigned, so the
// magnitude of the activity event is compared with the value in
// the THRESH_ACT register. The scale factor is 62.5 mg/LSB.
// A value of 0 may result in undesirable behavior if the activity
// interrupt is enabled. 
#define REG_THRESH_ACT     0x24    // R/W,   00000000,   Activity threshold

// The THRESH_INACT register is eight bits and holds the threshold
// value for detecting inactivity. The data format is unsigned, so
// the magnitude of the inactivity event is compared with the value
// in the THRESH_INACT register. The scale factor is 62.5 mg/LSB.
// A value of 0 may result in undesirable behavior if the inactivity
// interrupt is enabled.
#define REG_THRESH_INACT   0x25    // R/W,   00000000,   Inactivity threshold

// The TIME_INACT register is eight bits and contains an unsigned
// time value representing the amount of time that acceleration
// must be less than the value in the THRESH_INACT register for
// inactivity to be declared. The scale factor is 1 sec/LSB. Unlike
// the other interrupt functions, which use unfiltered data (see the
// Threshold section), the inactivity function uses filtered output
// data. At least one output sample must be generated for the
// inactivity interrupt to be triggered. This results in the function
// appearing unresponsive if the TIME_INACT register is set to a
// value less than the time constant of the output data rate. A value
// of 0 results in an interrupt when the output data is less than the
// value in the THRESH_INACT register. 
#define REG_TIME_INACT     0x26    // R/W,   00000000,   Inactivity time

// A setting of 0 selects dc-coupled operation, and a setting of 1
// enables ac-coupled operation. In dc-coupled operation, the
// current acceleration magnitude is compared directly with
// THRESH_ACT and THRESH_INACT to determine whether
// activity or inactivity is detected.
// In ac-coupled operation for activity detection, the acceleration
// value at the start of activity detection is taken as a reference
// value. New samples of acceleration are then compared to this
// reference value, and if the magnitude of the difference exceeds
// the THRESH_ACT value, the device triggers an activity interrupt.
// Similarly, in ac-coupled operation for inactivity detection, a
// reference value is used for comparison and is updated whenever
// the device exceeds the inactivity threshold. After the reference
// value is selected, the device compares the magnitude of the
// difference between the reference value and the current acceleration
// with THRESH_INACT. If the difference is less than the value in
// THRESH_INACT for the time in TIME_INACT, the device is
// considered inactive and the inactivity interrupt is triggered. 
#define REG_ACT_INACT_CTL  0x27    // R/W,   00000000,   Axis enable control for activity and inactiv ity detection

// BITS for ACT_INACT_CTL
// ACT_x Enable Bits and INACT_x Enable Bits
// A setting of 1 enables x-, y-, or z-axis participation in detecting
// activity or inactivity. A setting of 0 excludes the selected axis from
// participation. If all axes are excluded, the function is disabled.
// For activity detection, all participating axes are logically OR?ed,
// causing the activity function to trigger when any of the participating axes exceeds the threshold. For inactivity detection, all
// participating axes are logically AND?ed, causing the inactivity
// function to trigger only if all participating axes are below the
// threshold for the specified time.
#define ACT_INACT_CTL_ACT_AC_DC                 0b10000000
#define ACT_INACT_CTL_ACT_X_ENABLE              0b01000000
#define ACT_INACT_CTL_ACT_Y_ENABLE              0b00100000
#define ACT_INACT_CTL_ACT_Z_ENABLE              0b00010000
#define ACT_INACT_CTL_ACT_Z_ENABLE              0b00010000
#define ACT_INACT_CTL_INACT_AC_DC               0b00001000
#define ACT_INACT_CTL_INACT_X_ENABLE            0b00000100
#define ACT_INACT_CTL_INACT_Y_ENABLE            0b00000010
#define ACT_INACT_CTL_INACT_Z_ENABLE            0b00000001

// The THRESH_FF register is eight bits and holds the threshold
// value, in unsigned format, for free-fall detection. The acceleration on
// all axes is compared with the value in THRESH_FF to determine if
// a free-fall event occurred. The scale factor is 62.5 mg/LSB. Note
// that a value of 0 mg may result in undesirable behavior if the freefall 
// interrupt is enabled. Values between 300 mg and 600 mg
// (0x05 to 0x09) are recommended. 
#define REG_THRESH_FF      0x28    // R/W,   00000000,   Free-fall threshold

// The TIME_FF register is eight bits and stores an unsigned time
// value representing the minimum time that the value of all axes
// must be less than THRESH_FF to generate a free-fall interrupt.
// The scale factor is 5 ms/LSB. A value of 0 may result in undesirable
// behavior if the free-fall interrupt is enabled. Values between 100 ms
// and 350 ms (0x14 to 0x46) are recommended. 
#define REG_TIME_FF        0x29    // R/W,   00000000,   Free-fall time

#define REG_TAP_AXES       0x2A    // R/W,   00000000,   Axis control for single tap/double tap
// Setting the suppress bit suppresses double tap detection if
// acceleration greater than the value in THRESH_TAP is present
// between taps. See the Tap Detection section for more details. 
#define TAP_AXES_SUPPRESS                       0b00001000
// A setting of 1 in the TAP_X enable, TAP_Y enable, or TAP_Z
// enable bit enables x-, y-, or z-axis participation in tap detection.
// A setting of 0 excludes the selected axis from participation in
// tap detection. 
#define TAP_AXES_ALL_ENABLE                     0b00000111
#define TAP_AXES_X_ENABLE                       0b00000100
#define TAP_AXES_Y_ENABLE                       0b00000010
#define TAP_AXES_Z_ENABLE                       0b00000001


#define REG_ACT_TAP_STATUS 0x2B    // R,     00000000,   Source of single tap/double tap
// These bits indicate the first axis involved in a tap or activity
// event. A setting of 1 corresponds to involvement in the event,
// and a setting of 0 corresponds to no involvement. When new
// data is available, these bits are not cleared but are overwritten by
// the new data. The ACT_TAP_STATUS register should be read
// before clearing the interrupt. Disabling an axis from participation
// clears the corresponding source bit when the next activity or
// single tap/double tap event occurs. 
#define ACT_TAP_STATUS_ACT_X_SOURCE             0b01000000
#define ACT_TAP_STATUS_ACT_Y_SOURCE             0b00100000
#define ACT_TAP_STATUS_ACT_Z_SOURCE             0b00010000
#define ACT_TAP_STATUS_TAP_X_SOURCE             0b00000100
#define ACT_TAP_STATUS_TAP_Y_SOURCE             0b00000010
#define ACT_TAP_STATUS_TAP_Z_SOURCE             0b00000001
// A setting of 1 in the asleep bit indicates that the part is asleep,
// and a setting of 0 indicates that the part is not asleep. This bit
// toggles only if the device is configured for auto sleep. See the
// AUTO_SLEEP Bit section for more information on autosleep
// mode. 
#define ACT_TAP_STATUS_ACT_SLEEP_SOURCE         0b00001000


#define REG_BW_RATE        0x2C    // R/W,   00001010,   Data rate and power mode control
// BITS FOR BW_RATE
// A setting of 0 in the LOW_POWER bit selects normal operation,
// and a setting of 1 selects reduced power operation, which has
// somewhat higher noise (see the Power Modes section for details). 
#define BW_RATE_LOW_POWER                       0b00010000
// These bits select the device bandwidth and output data rate (see
// Table 7 and Table 8 for details). The default value is 0x0A, which
// translates to a 100 Hz output data rate. An output data rate should
// be selected that is appropriate for the communication protocol
// and frequency selected. Selecting too high of an output data rate with
// a low communication speed results in samples being discarded. 
#define BW_RATE_RATE_MASK                       0b00001111


#define REG_POWER_CTL      0x2D    // R/W,   00000000,   Power-saving features control

// BITS for POWER_CTL REGISTER
// A setting of 1 in the link bit with both the activity and inactivity
// functions enabled delays the start of the activity function until
// inactivity is detected. After activity is detected, inactivity detection
// begins, preventing the detection of activity. This bit serially links
// the activity and inactivity functions. When this bit is set to 0,
// the inactivity and activity functions are concurrent. Additional
// information can be found in the Link Mode section.
// When clearing the link bit, it is recommended that the part be
// placed into standby mode and then set back to measurement
// mode with a subsequent write. This is done to ensure that the
// device is properly biased if sleep mode is manually disabled;
// otherwise, the first few samples of data after the link bit is cleared
// may have additional noise, especially if the device was asleep
// when the bit was cleared.
#define POWER_CTL_LINK                          0b00100000

// If the link bit is set, a setting of 1 in the AUTO_SLEEP bit enables
// the auto-sleep functionality. In this mode, the ADXL345 automatically 
// switches to sleep mode if the inactivity function is
// enabled and inactivity is detected (that is, when acceleration is
// below the THRESH_INACT value for at least the time indicated
// by TIME_INACT). If activity is also enabled, the ADXL345
// automatically wakes up from sleep after detecting activity and
// returns to operation at the output data rate set in the BW_RATE
// register. A setting of 0 in the AUTO_SLEEP bit disables automatic
// switching to sleep mode. See the description of the Sleep Bit in
// this section for more information on sleep mode. 
// If the link bit is not set, the AUTO_SLEEP feature is disabled
// and setting the AUTO_SLEEP bit does not have an impact on
// device operation. Refer to the Link Bit section or the Link Mode
// section for more information on utilization of the link feature.
// When clearing the AUTO_SLEEP bit, it is recommended that the
// part be placed into standby mode and then set back to measurement mode 
// with a subsequent write. This is done to ensure that
// the device is properly biased if sleep mode is manually disabled;
// otherwise, the first few samples of data after the AUTO_SLEEP
// bit is cleared may have additional noise, especially if the device
// was asleep when the bit was cleared. 
#define POWER_CTL_AUTO_SLEEP                    0b00010000

// A setting of 0 in the measure bit places the part into standby mode,
// and a setting of 1 places the part into measurement mode. The
// ADXL345 powers up in standby mode with minimum power
// consumption. 
#define POWER_CTL_MEASURE                       0b00001000

// A setting of 0 in the sleep bit puts the part into the normal mode
// of operation, and a setting of 1 places the part into sleep mode.
// Sleep mode suppresses DATA_READY, stops transmission of data
// to FIFO, and switches the sampling rate to one specified by the
// wakeup bits. In sleep mode, only the activity function can be used.
// When the DATA_READY interrupt is suppressed, the output
// data registers (Register 0x32 to Register 0x37) are still updated
// at the sampling rate set by the wakeup bits (D1:D0).
// When clearing the sleep bit, it is recommended that the part be
// placed into standby mode and then set back to measurement
// mode with a subsequent write. This is done to ensure that the
// device is properly biased if sleep mode is manually disabled;
// otherwise, the first few samples of data after the sleep bit is
// cleared may have additional noise, especially if the device was
// asleep when the bit was cleared. 
#define POWER_CTL_SLEEP                         0b00000100
// These bits control the frequency of readings in sleep mode as
// described in Table 20. 
#define POWER_CTL_WAKEUP_FREQ_8HZ               0b00000000
#define POWER_CTL_WAKEUP_FREQ_4HZ               0b00000001
#define POWER_CTL_WAKEUP_FREQ_2HZ               0b00000010
#define POWER_CTL_WAKEUP_FREQ_1HZ               0b00000001

// Setting bits in this register to a value of 1 enables their respective
// functions to generate interrupts, whereas a value of 0 prevents
// the functions from generating interrupts. The DATA_READY,
// watermark, and overrun bits enable only the interrupt output;
// the functions are always enabled. It is recommended that interrupts
// be configured before enabling their outputs. 
#define REG_INT_ENABLE     0x2E    // R/W,   00000000,   Interrupt enable control
#define INT_ENABLE_DATA_READY                   0b10000000
#define INT_ENABLE_SINGLE_TAP                   0b01000000
#define INT_ENABLE_DOUBLE_TAP                   0b00100000
#define INT_ENABLE_ACTIVITY                     0b00010000
#define INT_ENABLE_INACTIVITY                   0b00001000
#define INT_ENABLE_FREE_FALL                    0b00000100
#define INT_ENABLE_WATERMARK                    0b00000010
#define INT_ENABLE_OVERRUN                      0b00000001

// Any bits set to 0 in this register send their respective interrupts to
// the INT1 pin, whereas bits set to 1 send their respective interrupts
// to the INT2 pin. All selected interrupts for a given pin are OR?ed. 
#define REG_INT_MAP        0x2F    // R/W,   00000000,   Interrupt mapping control
#define INT_MAP_DATA_READY                      0b10000000
#define INT_MAP_SINGLE_TAP                      0b01000000
#define INT_MAP_DOUBLE_TAP                      0b00100000
#define INT_MAP_ACTIVITY                        0b00010000
#define INT_MAP_INACTIVITY                      0b00001000
#define INT_MAP_FREE_FALL                       0b00000100
#define INT_MAP_WATERMARK                       0b00000010
#define INT_MAP_OVERRUN                         0b00000001

// Bits set to 1 in this register indicate that their respective functions
// have triggered an event, whereas a value of 0 indicates that the
// corresponding event has not occurred. The DATA_READY,
// watermark, and overrun bits are always set if the corresponding
// events occur, regardless of the INT_ENABLE register settings,
// and are cleared by reading data from the DATAX, DATAY, and
// DATAZ registers. The DATA_READY and watermark bits may
// require multiple reads, as indicated in the FIFO mode descriptions
// in the FIFO section. Other bits, and the corresponding interrupts,
// are cleared by reading the INT_SOURCE register. 
#define REG_INT_SOURCE     0x30    // R,     00000010,   Source of interrupts

#define INT_SOURCE_DATA_READY                   0b10000000
#define INT_SOURCE_SINGLE_TAP                   0b01000000
#define INT_SOURCE_DOUBLE_TAP                   0b00100000
#define INT_SOURCE_ACTIVITY                     0b00010000
#define INT_SOURCE_INACTIVITY                   0b00001000
#define INT_SOURCE_FREE_FALL                    0b00000100
#define INT_SOURCE_WATERMARK                    0b00000010
#define INT_SOURCE_OVERRUN                      0b00000001

// The DATA_FORMAT register controls the presentation of data
// to Register 0x32 through Register 0x37. All data, except that for
// the ±16 g range, must be clipped to avoid rollover. 
#define REG_DATA_FORMAT    0x31    // R/W,   00000000,   Data format control
// A setting of 1 in the SELF_TEST bit applies a self-test force to
// the sensor, causing a shift in the output data. A value of 0 disables
// the self-test force. 
#define DATA_FORMAT_SELF_TEST                   0b10000000
// A value of 1 in the SPI bit sets the device to 3-wire SPI mode,
// and a value of 0 sets the device to 4-wire SPI mode. 
#define DATA_FORMAT_SPI                         0b01000000
// A value of 0 in the INT_INVERT bit sets the interrupts to active
// high, and a value of 1 sets the interrupts to active low
#define DATA_FORMAT_INT_INVERT                  0b00100000
// When this bit is set to a value of 1, the device is in full resolution
// mode, where the output resolution increases with the g range
// set by the range bits to maintain a 4 mg/LSB scale factor. When
// the FULL_RES bit is set to 0, the device is in 10-bit mode, and
// the range bits determine the maximum g range and scale factor. 
#define DATA_FORMAT_FULL_RES                    0b00001000
// A setting of 1 in the justify bit selects left-justified (MSB) mode,
// and a setting of 0 selects right-justified mode with sign extension. 
#define DATA_FORMAT_JUSTIFY                     0b00000100
// These bits set the g range as described
#define DATA_FORMAT_RANGE_MASK                  0b00000011
#define DATA_FORMAT_RANGE_16_G                  0b00000011
#define DATA_FORMAT_RANGE_8_G                   0b00000010
#define DATA_FORMAT_RANGE_4_G                   0b00000001
#define DATA_FORMAT_RANGE_2_G                   0b00000000

// These six bytes (Register 0x32 to Register 0x37) are eight bits
// each and hold the output data for each axis. Register 0x32 and
// Register 0x33 hold the output data for the x-axis, Register 0x34 and
// Register 0x35 hold the output data for the y-axis, and Register 0x36
// and Register 0x37 hold the output data for the z-axis. The output
// data is twos complement, with DATAx0 as the least significant
// byte and DATAx1 as the most significant byte, where x represent X,
// Y, or Z. The DATA_FORMAT register (Address 0x31) controls
// the format of the data. It is recommended that a multiple-byte
// read of all registers be performed to prevent a change in data
// between reads of sequential registers. 
#define REG_DATAX0         0x32    // R,     00000000,   X-Axis Data 0
#define REG_DATAX1         0x33    // R,     00000000,   X-Axis Data 1
#define REG_DATAY0         0x34    // R,     00000000,   Y-Axis Data 0
#define REG_DATAY1         0x35    // R,     00000000,   Y-Axis Data 1
#define REG_DATAZ0         0x36    // R,     00000000,   Z-Axis Data 0
#define REG_DATAZ1         0x37    // R,     00000000,   Z-Axis Data 1

#define REG_FIFO_CTL       0x38    // R/W,   00000000,   FIFO control
// These bits set the FIFO mode, as described in Table 22.
// When triggered by the trigger bit, FIFO holds the last data samples before
// the trigger event and then continues to collect data until full. New data 
// is collected only when FIFO is not full.
#define FIFO_CTL_FIFO_MODE_TRIGGER              0b11000000
// FIFO holds the last 32 data values. When
// FIFO is full, the oldest data is overwritten with newer data. 
#define FIFO_CTL_FIFO_MODE_STREAM               0b10000000
// FIFO collects up to 32 values and then stops collecting data, 
// collecting new data only when FIFO is not full. 
#define FIFO_CTL_FIFO_MODE_FIFO                 0b01000000
// FIFO is bypassed. 
#define FIFO_CTL_FIFO_MODE_BYPASS               0b00000000
// A value of 0 in the trigger bit links the trigger event of trigger mode
// to INT1, and a value of 1 links the trigger event to INT2. 
#define FIFO_CTL_FIFO_MODE_INT1_OR_INT2         0b00100000
// The function of these bits depends on the FIFO mode selected
// (see Table 23). Entering a value of 0 in the samples bits immediately
// sets the watermark status bit in the INT_SOURCE register,
// regardless of which FIFO mode is selected. Undesirable operation
// may occur if a value of 0 is used for the samples bits when trigger
// mode is used. 
// Bypass    None
// FIFO      Specifies how many FIFO entries are needed to trigger a watermark 
//           interrupt.
// Stream    Specifies how many FIFO entries are needed to trigger a 
//           watermark interrupt.
// Trigger   Specifies how many FIFO samples are retained in
//           the FIFO buffer before a trigger event.
#define FIFO_CTL_FIFO_SAMPLES_COUNT_MASK        0b00011111


#define REG_FIFO_STATUS    0x39    // R,     00000000,   FIFO status
// A 1 in the FIFO_TRIG bit corresponds to a trigger event occurring,
// and a 0 means that a FIFO trigger event has not occurred. 
#define FIFO_STATUS_FIFO_TRIG                   0b10000000

// These bits report how many data values are stored in FIFO.
// Access to collect the data from FIFO is provided through the
// DATAX, DATAY, and DATAZ registers. FIFO reads must be
// done in burst or multiple-byte mode because each FIFO level is
// cleared after any read (single- or multiple-byte) of FIFO. FIFO
// stores a maximum of 32 entries, which equates to a maximum
// of 33 entries available at any given time because an additional
// entry is available at the output filter of the device. 
#define FIFO_STATUS_ENTRIES_MASK                0b00111111


#endif
