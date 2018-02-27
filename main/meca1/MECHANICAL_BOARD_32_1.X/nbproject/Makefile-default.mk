#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../common/clock/clock.c ../../../common/delay/cenDelay.c ../../../common/eeprom/eeprom.c ../../../drivers/eeprom/24c512.c ../../../common/error/error.c ../../../common/i2c/i2cDebug.c ../../../common/i2c/i2cCommon.c ../../../common/i2c/i2cBusConnectionList.c ../../../common/i2c/i2cBusList.c ../../../common/i2c/32/i2cCommon32.c ../../../common/i2c/master/i2cMaster.c ../../../common/i2c/master/32/i2cMaster32.c ../../../common/i2c/master/32/i2cMasterSetup32.c ../../../common/i2c/slave/i2cSlaveLink.c ../../../common/i2c/slave/i2cSlave.c ../../../common/i2c/slave/32/i2cSlave32.c ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c ../../../common/i2c/slave/32/i2cSlaveSetup32.c ../../../common/io/buffer.c ../../../common/io/inputStream.c ../../../common/io/outputStream.c ../../../common/io/printWriter.c ../../../common/io/filter.c ../../../common/io/ioUtils.c ../../../common/io/reader.c ../../../common/io/streamLink.c ../../../common/io/pin.c ../../../common/io/binaryPrintWriter.c ../../../common/io/nullOutputStream.c ../../../common/io/printTableWriter.c ../../../common/log/logger.c ../../../common/log/logHandler.c ../../../common/log/logHandlerList.c ../../../common/log/logLevel.c ../../../common/log/loggerDebug.c ../../../common/math/cenMath.c ../../../common/math/hexUtils.c ../../../common/pwm/32/pwmPic32.c ../../../common/pwm/motor/motorPwm.c ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c ../../../common/pwm/motor/32/motorPwm32.c ../../../common/pwm/servo/servoPwm.c ../../../common/pwm/servo/servoPwmDebug.c ../../../common/pwm/servo/32/servoPwm32.c ../../../common/serial/serialLink.c ../../../common/serial/serialOutputStream.c ../../../common/serial/serialLinkDebug.c ../../../common/serial/serialLinkList.c ../../../common/serial/32/serial32.c ../../../common/serial/32/serialInputInterrupt32.c ../../../common/system/system.c ../../../common/timer/cenTimer.c ../../../common/timer/timerList.c ../../../common/timer/timerDebug.c ../../../common/timer/32/timerInterrupt32.c ../../../common/timer/32/timerSetup32.c ../../../device/device.c ../../../device/deviceList.c ../../../device/deviceDescriptor.c ../../../device/deviceInterface.c ../../../device/deviceUsage.c ../../../device/transmitMode.c ../../../device/deviceDebug.c ../../../device/clock/clockDevice.c ../../../device/clock/clockDeviceInterface.c ../../../device/dispatcher/deviceDataDispatcher.c ../../../device/motor/pwmMotorDevice.c ../../../device/motor/pwmMotorDeviceInterface.c ../../../device/motor/pwmMotor.c ../../../device/serial/serialDebugDevice.c ../../../device/serial/serialDebugDeviceInterface.c ../../../device/servo/servoDevice.c ../../../device/servo/servoDeviceInterface.c ../../../device/system/systemDevice.c ../../../device/system/systemDeviceInterface.c ../../../device/test/testDeviceInterface.c ../../../device/test/testDevice.c ../../../device/timer/timerDevice.c ../../../device/timer/timerDeviceInterface.c ../../../drivers/driverStreamListener.c ../../../drivers/driver.c ../../../drivers/driverList.c ../../../drivers/clock/softClock.c ../../../drivers/dispatcher/driverDataDispatcher.c ../../../drivers/dispatcher/driverDataDispatcherList.c ../mechanicalMainBoard32_1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/761317689/clock.o ${OBJECTDIR}/_ext/762029742/cenDelay.o ${OBJECTDIR}/_ext/2118117323/eeprom.o ${OBJECTDIR}/_ext/1245422637/24c512.o ${OBJECTDIR}/_ext/763346739/error.o ${OBJECTDIR}/_ext/358337669/i2cDebug.o ${OBJECTDIR}/_ext/358337669/i2cCommon.o ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o ${OBJECTDIR}/_ext/358337669/i2cBusList.o ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o ${OBJECTDIR}/_ext/466947884/i2cMaster.o ${OBJECTDIR}/_ext/554612702/i2cMaster32.o ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o ${OBJECTDIR}/_ext/1364558899/i2cSlave.o ${OBJECTDIR}/_ext/291343329/i2cSlave32.o ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o ${OBJECTDIR}/_ext/1674127323/buffer.o ${OBJECTDIR}/_ext/1674127323/inputStream.o ${OBJECTDIR}/_ext/1674127323/outputStream.o ${OBJECTDIR}/_ext/1674127323/printWriter.o ${OBJECTDIR}/_ext/1674127323/filter.o ${OBJECTDIR}/_ext/1674127323/ioUtils.o ${OBJECTDIR}/_ext/1674127323/reader.o ${OBJECTDIR}/_ext/1674127323/streamLink.o ${OBJECTDIR}/_ext/1674127323/pin.o ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o ${OBJECTDIR}/_ext/1674127323/printTableWriter.o ${OBJECTDIR}/_ext/358342447/logger.o ${OBJECTDIR}/_ext/358342447/logHandler.o ${OBJECTDIR}/_ext/358342447/logHandlerList.o ${OBJECTDIR}/_ext/358342447/logLevel.o ${OBJECTDIR}/_ext/358342447/loggerDebug.o ${OBJECTDIR}/_ext/1776269187/cenMath.o ${OBJECTDIR}/_ext/1776269187/hexUtils.o ${OBJECTDIR}/_ext/1786728963/pwmPic32.o ${OBJECTDIR}/_ext/857340905/motorPwm.o ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o ${OBJECTDIR}/_ext/1127655255/motorPwm32.o ${OBJECTDIR}/_ext/852099397/servoPwm.o ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o ${OBJECTDIR}/_ext/1636369869/servoPwm32.o ${OBJECTDIR}/_ext/1717258711/serialLink.o ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o ${OBJECTDIR}/_ext/1717258711/serialLinkList.o ${OBJECTDIR}/_ext/1498749947/serial32.o ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o ${OBJECTDIR}/_ext/1698747804/system.o ${OBJECTDIR}/_ext/776926320/cenTimer.o ${OBJECTDIR}/_ext/776926320/timerList.o ${OBJECTDIR}/_ext/776926320/timerDebug.o ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o ${OBJECTDIR}/_ext/166712226/timerSetup32.o ${OBJECTDIR}/_ext/927408101/device.o ${OBJECTDIR}/_ext/927408101/deviceList.o ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o ${OBJECTDIR}/_ext/927408101/deviceInterface.o ${OBJECTDIR}/_ext/927408101/deviceUsage.o ${OBJECTDIR}/_ext/927408101/transmitMode.o ${OBJECTDIR}/_ext/927408101/deviceDebug.o ${OBJECTDIR}/_ext/285179548/clockDevice.o ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o ${OBJECTDIR}/_ext/275849781/pwmMotor.o ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o ${OBJECTDIR}/_ext/270608273/servoDevice.o ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o ${OBJECTDIR}/_ext/219576217/systemDevice.o ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o ${OBJECTDIR}/_ext/1394172804/testDevice.o ${OBJECTDIR}/_ext/269570917/timerDevice.o ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o ${OBJECTDIR}/_ext/954557028/driverStreamListener.o ${OBJECTDIR}/_ext/954557028/driver.o ${OBJECTDIR}/_ext/954557028/driverList.o ${OBJECTDIR}/_ext/1343658459/softClock.o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/761317689/clock.o.d ${OBJECTDIR}/_ext/762029742/cenDelay.o.d ${OBJECTDIR}/_ext/2118117323/eeprom.o.d ${OBJECTDIR}/_ext/1245422637/24c512.o.d ${OBJECTDIR}/_ext/763346739/error.o.d ${OBJECTDIR}/_ext/358337669/i2cDebug.o.d ${OBJECTDIR}/_ext/358337669/i2cCommon.o.d ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d ${OBJECTDIR}/_ext/358337669/i2cBusList.o.d ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d ${OBJECTDIR}/_ext/466947884/i2cMaster.o.d ${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d ${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d ${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d ${OBJECTDIR}/_ext/1674127323/buffer.o.d ${OBJECTDIR}/_ext/1674127323/inputStream.o.d ${OBJECTDIR}/_ext/1674127323/outputStream.o.d ${OBJECTDIR}/_ext/1674127323/printWriter.o.d ${OBJECTDIR}/_ext/1674127323/filter.o.d ${OBJECTDIR}/_ext/1674127323/ioUtils.o.d ${OBJECTDIR}/_ext/1674127323/reader.o.d ${OBJECTDIR}/_ext/1674127323/streamLink.o.d ${OBJECTDIR}/_ext/1674127323/pin.o.d ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d ${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d ${OBJECTDIR}/_ext/358342447/logger.o.d ${OBJECTDIR}/_ext/358342447/logHandler.o.d ${OBJECTDIR}/_ext/358342447/logHandlerList.o.d ${OBJECTDIR}/_ext/358342447/logLevel.o.d ${OBJECTDIR}/_ext/358342447/loggerDebug.o.d ${OBJECTDIR}/_ext/1776269187/cenMath.o.d ${OBJECTDIR}/_ext/1776269187/hexUtils.o.d ${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d ${OBJECTDIR}/_ext/857340905/motorPwm.o.d ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d ${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d ${OBJECTDIR}/_ext/852099397/servoPwm.o.d ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d ${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d ${OBJECTDIR}/_ext/1717258711/serialLink.o.d ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d ${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d ${OBJECTDIR}/_ext/1498749947/serial32.o.d ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d ${OBJECTDIR}/_ext/1698747804/system.o.d ${OBJECTDIR}/_ext/776926320/cenTimer.o.d ${OBJECTDIR}/_ext/776926320/timerList.o.d ${OBJECTDIR}/_ext/776926320/timerDebug.o.d ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d ${OBJECTDIR}/_ext/166712226/timerSetup32.o.d ${OBJECTDIR}/_ext/927408101/device.o.d ${OBJECTDIR}/_ext/927408101/deviceList.o.d ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d ${OBJECTDIR}/_ext/927408101/deviceInterface.o.d ${OBJECTDIR}/_ext/927408101/deviceUsage.o.d ${OBJECTDIR}/_ext/927408101/transmitMode.o.d ${OBJECTDIR}/_ext/927408101/deviceDebug.o.d ${OBJECTDIR}/_ext/285179548/clockDevice.o.d ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d ${OBJECTDIR}/_ext/275849781/pwmMotor.o.d ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d ${OBJECTDIR}/_ext/270608273/servoDevice.o.d ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d ${OBJECTDIR}/_ext/219576217/systemDevice.o.d ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d ${OBJECTDIR}/_ext/1394172804/testDevice.o.d ${OBJECTDIR}/_ext/269570917/timerDevice.o.d ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d ${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d ${OBJECTDIR}/_ext/954557028/driver.o.d ${OBJECTDIR}/_ext/954557028/driverList.o.d ${OBJECTDIR}/_ext/1343658459/softClock.o.d ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/761317689/clock.o ${OBJECTDIR}/_ext/762029742/cenDelay.o ${OBJECTDIR}/_ext/2118117323/eeprom.o ${OBJECTDIR}/_ext/1245422637/24c512.o ${OBJECTDIR}/_ext/763346739/error.o ${OBJECTDIR}/_ext/358337669/i2cDebug.o ${OBJECTDIR}/_ext/358337669/i2cCommon.o ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o ${OBJECTDIR}/_ext/358337669/i2cBusList.o ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o ${OBJECTDIR}/_ext/466947884/i2cMaster.o ${OBJECTDIR}/_ext/554612702/i2cMaster32.o ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o ${OBJECTDIR}/_ext/1364558899/i2cSlave.o ${OBJECTDIR}/_ext/291343329/i2cSlave32.o ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o ${OBJECTDIR}/_ext/1674127323/buffer.o ${OBJECTDIR}/_ext/1674127323/inputStream.o ${OBJECTDIR}/_ext/1674127323/outputStream.o ${OBJECTDIR}/_ext/1674127323/printWriter.o ${OBJECTDIR}/_ext/1674127323/filter.o ${OBJECTDIR}/_ext/1674127323/ioUtils.o ${OBJECTDIR}/_ext/1674127323/reader.o ${OBJECTDIR}/_ext/1674127323/streamLink.o ${OBJECTDIR}/_ext/1674127323/pin.o ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o ${OBJECTDIR}/_ext/1674127323/printTableWriter.o ${OBJECTDIR}/_ext/358342447/logger.o ${OBJECTDIR}/_ext/358342447/logHandler.o ${OBJECTDIR}/_ext/358342447/logHandlerList.o ${OBJECTDIR}/_ext/358342447/logLevel.o ${OBJECTDIR}/_ext/358342447/loggerDebug.o ${OBJECTDIR}/_ext/1776269187/cenMath.o ${OBJECTDIR}/_ext/1776269187/hexUtils.o ${OBJECTDIR}/_ext/1786728963/pwmPic32.o ${OBJECTDIR}/_ext/857340905/motorPwm.o ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o ${OBJECTDIR}/_ext/1127655255/motorPwm32.o ${OBJECTDIR}/_ext/852099397/servoPwm.o ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o ${OBJECTDIR}/_ext/1636369869/servoPwm32.o ${OBJECTDIR}/_ext/1717258711/serialLink.o ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o ${OBJECTDIR}/_ext/1717258711/serialLinkList.o ${OBJECTDIR}/_ext/1498749947/serial32.o ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o ${OBJECTDIR}/_ext/1698747804/system.o ${OBJECTDIR}/_ext/776926320/cenTimer.o ${OBJECTDIR}/_ext/776926320/timerList.o ${OBJECTDIR}/_ext/776926320/timerDebug.o ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o ${OBJECTDIR}/_ext/166712226/timerSetup32.o ${OBJECTDIR}/_ext/927408101/device.o ${OBJECTDIR}/_ext/927408101/deviceList.o ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o ${OBJECTDIR}/_ext/927408101/deviceInterface.o ${OBJECTDIR}/_ext/927408101/deviceUsage.o ${OBJECTDIR}/_ext/927408101/transmitMode.o ${OBJECTDIR}/_ext/927408101/deviceDebug.o ${OBJECTDIR}/_ext/285179548/clockDevice.o ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o ${OBJECTDIR}/_ext/275849781/pwmMotor.o ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o ${OBJECTDIR}/_ext/270608273/servoDevice.o ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o ${OBJECTDIR}/_ext/219576217/systemDevice.o ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o ${OBJECTDIR}/_ext/1394172804/testDevice.o ${OBJECTDIR}/_ext/269570917/timerDevice.o ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o ${OBJECTDIR}/_ext/954557028/driverStreamListener.o ${OBJECTDIR}/_ext/954557028/driver.o ${OBJECTDIR}/_ext/954557028/driverList.o ${OBJECTDIR}/_ext/1343658459/softClock.o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o

# Source Files
SOURCEFILES=../../../common/clock/clock.c ../../../common/delay/cenDelay.c ../../../common/eeprom/eeprom.c ../../../drivers/eeprom/24c512.c ../../../common/error/error.c ../../../common/i2c/i2cDebug.c ../../../common/i2c/i2cCommon.c ../../../common/i2c/i2cBusConnectionList.c ../../../common/i2c/i2cBusList.c ../../../common/i2c/32/i2cCommon32.c ../../../common/i2c/master/i2cMaster.c ../../../common/i2c/master/32/i2cMaster32.c ../../../common/i2c/master/32/i2cMasterSetup32.c ../../../common/i2c/slave/i2cSlaveLink.c ../../../common/i2c/slave/i2cSlave.c ../../../common/i2c/slave/32/i2cSlave32.c ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c ../../../common/i2c/slave/32/i2cSlaveSetup32.c ../../../common/io/buffer.c ../../../common/io/inputStream.c ../../../common/io/outputStream.c ../../../common/io/printWriter.c ../../../common/io/filter.c ../../../common/io/ioUtils.c ../../../common/io/reader.c ../../../common/io/streamLink.c ../../../common/io/pin.c ../../../common/io/binaryPrintWriter.c ../../../common/io/nullOutputStream.c ../../../common/io/printTableWriter.c ../../../common/log/logger.c ../../../common/log/logHandler.c ../../../common/log/logHandlerList.c ../../../common/log/logLevel.c ../../../common/log/loggerDebug.c ../../../common/math/cenMath.c ../../../common/math/hexUtils.c ../../../common/pwm/32/pwmPic32.c ../../../common/pwm/motor/motorPwm.c ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c ../../../common/pwm/motor/32/motorPwm32.c ../../../common/pwm/servo/servoPwm.c ../../../common/pwm/servo/servoPwmDebug.c ../../../common/pwm/servo/32/servoPwm32.c ../../../common/serial/serialLink.c ../../../common/serial/serialOutputStream.c ../../../common/serial/serialLinkDebug.c ../../../common/serial/serialLinkList.c ../../../common/serial/32/serial32.c ../../../common/serial/32/serialInputInterrupt32.c ../../../common/system/system.c ../../../common/timer/cenTimer.c ../../../common/timer/timerList.c ../../../common/timer/timerDebug.c ../../../common/timer/32/timerInterrupt32.c ../../../common/timer/32/timerSetup32.c ../../../device/device.c ../../../device/deviceList.c ../../../device/deviceDescriptor.c ../../../device/deviceInterface.c ../../../device/deviceUsage.c ../../../device/transmitMode.c ../../../device/deviceDebug.c ../../../device/clock/clockDevice.c ../../../device/clock/clockDeviceInterface.c ../../../device/dispatcher/deviceDataDispatcher.c ../../../device/motor/pwmMotorDevice.c ../../../device/motor/pwmMotorDeviceInterface.c ../../../device/motor/pwmMotor.c ../../../device/serial/serialDebugDevice.c ../../../device/serial/serialDebugDeviceInterface.c ../../../device/servo/servoDevice.c ../../../device/servo/servoDeviceInterface.c ../../../device/system/systemDevice.c ../../../device/system/systemDeviceInterface.c ../../../device/test/testDeviceInterface.c ../../../device/test/testDevice.c ../../../device/timer/timerDevice.c ../../../device/timer/timerDeviceInterface.c ../../../drivers/driverStreamListener.c ../../../drivers/driver.c ../../../drivers/driverList.c ../../../drivers/clock/softClock.c ../../../drivers/dispatcher/driverDataDispatcher.c ../../../drivers/dispatcher/driverDataDispatcherList.c ../mechanicalMainBoard32_1.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/761317689/clock.o: ../../../common/clock/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761317689" 
	@${RM} ${OBJECTDIR}/_ext/761317689/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/761317689/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761317689/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761317689/clock.o.d" -o ${OBJECTDIR}/_ext/761317689/clock.o ../../../common/clock/clock.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/762029742/cenDelay.o: ../../../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/762029742" 
	@${RM} ${OBJECTDIR}/_ext/762029742/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/762029742/cenDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/762029742/cenDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/762029742/cenDelay.o.d" -o ${OBJECTDIR}/_ext/762029742/cenDelay.o ../../../common/delay/cenDelay.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118117323/eeprom.o: ../../../common/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118117323" 
	@${RM} ${OBJECTDIR}/_ext/2118117323/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118117323/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118117323/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2118117323/eeprom.o.d" -o ${OBJECTDIR}/_ext/2118117323/eeprom.o ../../../common/eeprom/eeprom.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1245422637/24c512.o: ../../../drivers/eeprom/24c512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1245422637" 
	@${RM} ${OBJECTDIR}/_ext/1245422637/24c512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1245422637/24c512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1245422637/24c512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1245422637/24c512.o.d" -o ${OBJECTDIR}/_ext/1245422637/24c512.o ../../../drivers/eeprom/24c512.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/763346739/error.o: ../../../common/error/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/763346739" 
	@${RM} ${OBJECTDIR}/_ext/763346739/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/763346739/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/763346739/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/763346739/error.o.d" -o ${OBJECTDIR}/_ext/763346739/error.o ../../../common/error/error.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cDebug.o: ../../../common/i2c/i2cDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cDebug.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cDebug.o ../../../common/i2c/i2cDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cCommon.o: ../../../common/i2c/i2cCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cCommon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cCommon.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cCommon.o ../../../common/i2c/i2cCommon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o: ../../../common/i2c/i2cBusConnectionList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o ../../../common/i2c/i2cBusConnectionList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cBusList.o: ../../../common/i2c/i2cBusList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cBusList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cBusList.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cBusList.o ../../../common/i2c/i2cBusList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2051153879/i2cCommon32.o: ../../../common/i2c/32/i2cCommon32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2051153879" 
	@${RM} ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d" -o ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o ../../../common/i2c/32/i2cCommon32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466947884/i2cMaster.o: ../../../common/i2c/master/i2cMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466947884" 
	@${RM} ${OBJECTDIR}/_ext/466947884/i2cMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/466947884/i2cMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466947884/i2cMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/466947884/i2cMaster.o.d" -o ${OBJECTDIR}/_ext/466947884/i2cMaster.o ../../../common/i2c/master/i2cMaster.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/554612702/i2cMaster32.o: ../../../common/i2c/master/32/i2cMaster32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/554612702" 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMaster32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d" -o ${OBJECTDIR}/_ext/554612702/i2cMaster32.o ../../../common/i2c/master/32/i2cMaster32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o: ../../../common/i2c/master/32/i2cMasterSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/554612702" 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d" -o ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o ../../../common/i2c/master/32/i2cMasterSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o: ../../../common/i2c/slave/i2cSlaveLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1364558899" 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d" -o ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o ../../../common/i2c/slave/i2cSlaveLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1364558899/i2cSlave.o: ../../../common/i2c/slave/i2cSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1364558899" 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlave.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d" -o ${OBJECTDIR}/_ext/1364558899/i2cSlave.o ../../../common/i2c/slave/i2cSlave.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlave32.o: ../../../common/i2c/slave/32/i2cSlave32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlave32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlave32.o ../../../common/i2c/slave/32/i2cSlave32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o: ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o: ../../../common/i2c/slave/32/i2cSlaveSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o ../../../common/i2c/slave/32/i2cSlaveSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/buffer.o: ../../../common/io/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/buffer.o.d" -o ${OBJECTDIR}/_ext/1674127323/buffer.o ../../../common/io/buffer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/inputStream.o: ../../../common/io/inputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/inputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/inputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/inputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/inputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/inputStream.o ../../../common/io/inputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/outputStream.o: ../../../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/outputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/outputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/outputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/outputStream.o ../../../common/io/outputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/printWriter.o: ../../../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/printWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/printWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/printWriter.o ../../../common/io/printWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/filter.o: ../../../common/io/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/filter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/filter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/filter.o.d" -o ${OBJECTDIR}/_ext/1674127323/filter.o ../../../common/io/filter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/ioUtils.o: ../../../common/io/ioUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/ioUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/ioUtils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/ioUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/ioUtils.o.d" -o ${OBJECTDIR}/_ext/1674127323/ioUtils.o ../../../common/io/ioUtils.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/reader.o: ../../../common/io/reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/reader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/reader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/reader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/reader.o.d" -o ${OBJECTDIR}/_ext/1674127323/reader.o ../../../common/io/reader.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/streamLink.o: ../../../common/io/streamLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/streamLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/streamLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/streamLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/streamLink.o.d" -o ${OBJECTDIR}/_ext/1674127323/streamLink.o ../../../common/io/streamLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/pin.o: ../../../common/io/pin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/pin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/pin.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/pin.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/pin.o.d" -o ${OBJECTDIR}/_ext/1674127323/pin.o ../../../common/io/pin.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o: ../../../common/io/binaryPrintWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o ../../../common/io/binaryPrintWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/nullOutputStream.o: ../../../common/io/nullOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o ../../../common/io/nullOutputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/printTableWriter.o: ../../../common/io/printTableWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printTableWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/printTableWriter.o ../../../common/io/printTableWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logger.o: ../../../common/log/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logger.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logger.o.d" -o ${OBJECTDIR}/_ext/358342447/logger.o ../../../common/log/logger.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logHandler.o: ../../../common/log/logHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logHandler.o.d" -o ${OBJECTDIR}/_ext/358342447/logHandler.o ../../../common/log/logHandler.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logHandlerList.o: ../../../common/log/logHandlerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandlerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandlerList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logHandlerList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logHandlerList.o.d" -o ${OBJECTDIR}/_ext/358342447/logHandlerList.o ../../../common/log/logHandlerList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logLevel.o: ../../../common/log/logLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logLevel.o.d" -o ${OBJECTDIR}/_ext/358342447/logLevel.o ../../../common/log/logLevel.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/loggerDebug.o: ../../../common/log/loggerDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/loggerDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/loggerDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/loggerDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/loggerDebug.o.d" -o ${OBJECTDIR}/_ext/358342447/loggerDebug.o ../../../common/log/loggerDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1776269187/cenMath.o: ../../../common/math/cenMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1776269187" 
	@${RM} ${OBJECTDIR}/_ext/1776269187/cenMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1776269187/cenMath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1776269187/cenMath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1776269187/cenMath.o.d" -o ${OBJECTDIR}/_ext/1776269187/cenMath.o ../../../common/math/cenMath.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1776269187/hexUtils.o: ../../../common/math/hexUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1776269187" 
	@${RM} ${OBJECTDIR}/_ext/1776269187/hexUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1776269187/hexUtils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1776269187/hexUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1776269187/hexUtils.o.d" -o ${OBJECTDIR}/_ext/1776269187/hexUtils.o ../../../common/math/hexUtils.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1786728963/pwmPic32.o: ../../../common/pwm/32/pwmPic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1786728963" 
	@${RM} ${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1786728963/pwmPic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d" -o ${OBJECTDIR}/_ext/1786728963/pwmPic32.o ../../../common/pwm/32/pwmPic32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/857340905/motorPwm.o: ../../../common/pwm/motor/motorPwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/857340905" 
	@${RM} ${OBJECTDIR}/_ext/857340905/motorPwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/857340905/motorPwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/857340905/motorPwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/857340905/motorPwm.o.d" -o ${OBJECTDIR}/_ext/857340905/motorPwm.o ../../../common/pwm/motor/motorPwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o: ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127655255" 
	@${RM} ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d" -o ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127655255/motorPwm32.o: ../../../common/pwm/motor/32/motorPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127655255" 
	@${RM} ${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127655255/motorPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d" -o ${OBJECTDIR}/_ext/1127655255/motorPwm32.o ../../../common/pwm/motor/32/motorPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/852099397/servoPwm.o: ../../../common/pwm/servo/servoPwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/852099397" 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/852099397/servoPwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/852099397/servoPwm.o.d" -o ${OBJECTDIR}/_ext/852099397/servoPwm.o ../../../common/pwm/servo/servoPwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/852099397/servoPwmDebug.o: ../../../common/pwm/servo/servoPwmDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/852099397" 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d" -o ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o ../../../common/pwm/servo/servoPwmDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1636369869/servoPwm32.o: ../../../common/pwm/servo/32/servoPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1636369869" 
	@${RM} ${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1636369869/servoPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d" -o ${OBJECTDIR}/_ext/1636369869/servoPwm32.o ../../../common/pwm/servo/32/servoPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLink.o: ../../../common/serial/serialLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLink.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLink.o ../../../common/serial/serialLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialOutputStream.o: ../../../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o ../../../common/serial/serialOutputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o: ../../../common/serial/serialLinkDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o ../../../common/serial/serialLinkDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLinkList.o: ../../../common/serial/serialLinkList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLinkList.o ../../../common/serial/serialLinkList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1498749947/serial32.o: ../../../common/serial/32/serial32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1498749947" 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serial32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serial32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498749947/serial32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498749947/serial32.o.d" -o ${OBJECTDIR}/_ext/1498749947/serial32.o ../../../common/serial/32/serial32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o: ../../../common/serial/32/serialInputInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1498749947" 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d" -o ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o ../../../common/serial/32/serialInputInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698747804/system.o: ../../../common/system/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698747804" 
	@${RM} ${OBJECTDIR}/_ext/1698747804/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698747804/system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698747804/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1698747804/system.o.d" -o ${OBJECTDIR}/_ext/1698747804/system.o ../../../common/system/system.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/cenTimer.o: ../../../common/timer/cenTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/cenTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/cenTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/cenTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/cenTimer.o.d" -o ${OBJECTDIR}/_ext/776926320/cenTimer.o ../../../common/timer/cenTimer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/timerList.o: ../../../common/timer/timerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/timerList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/timerList.o.d" -o ${OBJECTDIR}/_ext/776926320/timerList.o ../../../common/timer/timerList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/timerDebug.o: ../../../common/timer/timerDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/timerDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/timerDebug.o.d" -o ${OBJECTDIR}/_ext/776926320/timerDebug.o ../../../common/timer/timerDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/166712226/timerInterrupt32.o: ../../../common/timer/32/timerInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/166712226" 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d" -o ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o ../../../common/timer/32/timerInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/166712226/timerSetup32.o: ../../../common/timer/32/timerSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/166712226" 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/166712226/timerSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/166712226/timerSetup32.o.d" -o ${OBJECTDIR}/_ext/166712226/timerSetup32.o ../../../common/timer/32/timerSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/device.o: ../../../device/device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/device.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/device.o.d" -o ${OBJECTDIR}/_ext/927408101/device.o ../../../device/device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceList.o: ../../../device/deviceList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceList.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceList.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceList.o ../../../device/deviceList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceDescriptor.o: ../../../device/deviceDescriptor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o ../../../device/deviceDescriptor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceInterface.o: ../../../device/deviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceInterface.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceInterface.o ../../../device/deviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceUsage.o: ../../../device/deviceUsage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceUsage.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceUsage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceUsage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceUsage.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceUsage.o ../../../device/deviceUsage.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/transmitMode.o: ../../../device/transmitMode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/transmitMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/transmitMode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/transmitMode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/transmitMode.o.d" -o ${OBJECTDIR}/_ext/927408101/transmitMode.o ../../../device/transmitMode.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceDebug.o: ../../../device/deviceDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceDebug.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceDebug.o ../../../device/deviceDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/285179548/clockDevice.o: ../../../device/clock/clockDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/285179548" 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/285179548/clockDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/285179548/clockDevice.o.d" -o ${OBJECTDIR}/_ext/285179548/clockDevice.o ../../../device/clock/clockDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o: ../../../device/clock/clockDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/285179548" 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o ../../../device/clock/clockDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o: ../../../device/dispatcher/deviceDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1191224559" 
	@${RM} ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d" -o ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o ../../../device/dispatcher/deviceDataDispatcher.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o: ../../../device/motor/pwmMotorDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o ../../../device/motor/pwmMotorDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o: ../../../device/motor/pwmMotorDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o ../../../device/motor/pwmMotorDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotor.o: ../../../device/motor/pwmMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotor.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotor.o ../../../device/motor/pwmMotor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/201065310/serialDebugDevice.o: ../../../device/serial/serialDebugDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/201065310" 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d" -o ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o ../../../device/serial/serialDebugDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o: ../../../device/serial/serialDebugDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/201065310" 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o ../../../device/serial/serialDebugDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/270608273/servoDevice.o: ../../../device/servo/servoDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270608273" 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270608273/servoDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/270608273/servoDevice.o.d" -o ${OBJECTDIR}/_ext/270608273/servoDevice.o ../../../device/servo/servoDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o: ../../../device/servo/servoDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270608273" 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o ../../../device/servo/servoDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/219576217/systemDevice.o: ../../../device/system/systemDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/219576217" 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/219576217/systemDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/219576217/systemDevice.o.d" -o ${OBJECTDIR}/_ext/219576217/systemDevice.o ../../../device/system/systemDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o: ../../../device/system/systemDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/219576217" 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o ../../../device/system/systemDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o: ../../../device/test/testDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1394172804" 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o ../../../device/test/testDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1394172804/testDevice.o: ../../../device/test/testDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1394172804" 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1394172804/testDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1394172804/testDevice.o.d" -o ${OBJECTDIR}/_ext/1394172804/testDevice.o ../../../device/test/testDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/269570917/timerDevice.o: ../../../device/timer/timerDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/269570917" 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/269570917/timerDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/269570917/timerDevice.o.d" -o ${OBJECTDIR}/_ext/269570917/timerDevice.o ../../../device/timer/timerDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o: ../../../device/timer/timerDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/269570917" 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o ../../../device/timer/timerDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driverStreamListener.o: ../../../drivers/driverStreamListener.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverStreamListener.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d" -o ${OBJECTDIR}/_ext/954557028/driverStreamListener.o ../../../drivers/driverStreamListener.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driver.o: ../../../drivers/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driver.o.d" -o ${OBJECTDIR}/_ext/954557028/driver.o ../../../drivers/driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driverList.o: ../../../drivers/driverList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverList.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driverList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driverList.o.d" -o ${OBJECTDIR}/_ext/954557028/driverList.o ../../../drivers/driverList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1343658459/softClock.o: ../../../drivers/clock/softClock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343658459" 
	@${RM} ${OBJECTDIR}/_ext/1343658459/softClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343658459/softClock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343658459/softClock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343658459/softClock.o.d" -o ${OBJECTDIR}/_ext/1343658459/softClock.o ../../../drivers/clock/softClock.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o: ../../../drivers/dispatcher/driverDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1426650362" 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d" -o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o ../../../drivers/dispatcher/driverDataDispatcher.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o: ../../../drivers/dispatcher/driverDataDispatcherList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1426650362" 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d" -o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o ../../../drivers/dispatcher/driverDataDispatcherList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o: ../mechanicalMainBoard32_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d" -o ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o ../mechanicalMainBoard32_1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/761317689/clock.o: ../../../common/clock/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761317689" 
	@${RM} ${OBJECTDIR}/_ext/761317689/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/761317689/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761317689/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761317689/clock.o.d" -o ${OBJECTDIR}/_ext/761317689/clock.o ../../../common/clock/clock.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/762029742/cenDelay.o: ../../../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/762029742" 
	@${RM} ${OBJECTDIR}/_ext/762029742/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/762029742/cenDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/762029742/cenDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/762029742/cenDelay.o.d" -o ${OBJECTDIR}/_ext/762029742/cenDelay.o ../../../common/delay/cenDelay.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118117323/eeprom.o: ../../../common/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118117323" 
	@${RM} ${OBJECTDIR}/_ext/2118117323/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118117323/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118117323/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2118117323/eeprom.o.d" -o ${OBJECTDIR}/_ext/2118117323/eeprom.o ../../../common/eeprom/eeprom.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1245422637/24c512.o: ../../../drivers/eeprom/24c512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1245422637" 
	@${RM} ${OBJECTDIR}/_ext/1245422637/24c512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1245422637/24c512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1245422637/24c512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1245422637/24c512.o.d" -o ${OBJECTDIR}/_ext/1245422637/24c512.o ../../../drivers/eeprom/24c512.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/763346739/error.o: ../../../common/error/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/763346739" 
	@${RM} ${OBJECTDIR}/_ext/763346739/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/763346739/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/763346739/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/763346739/error.o.d" -o ${OBJECTDIR}/_ext/763346739/error.o ../../../common/error/error.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cDebug.o: ../../../common/i2c/i2cDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cDebug.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cDebug.o ../../../common/i2c/i2cDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cCommon.o: ../../../common/i2c/i2cCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cCommon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cCommon.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cCommon.o ../../../common/i2c/i2cCommon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o: ../../../common/i2c/i2cBusConnectionList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cBusConnectionList.o ../../../common/i2c/i2cBusConnectionList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358337669/i2cBusList.o: ../../../common/i2c/i2cBusList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358337669" 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358337669/i2cBusList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358337669/i2cBusList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358337669/i2cBusList.o.d" -o ${OBJECTDIR}/_ext/358337669/i2cBusList.o ../../../common/i2c/i2cBusList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2051153879/i2cCommon32.o: ../../../common/i2c/32/i2cCommon32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2051153879" 
	@${RM} ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2051153879/i2cCommon32.o.d" -o ${OBJECTDIR}/_ext/2051153879/i2cCommon32.o ../../../common/i2c/32/i2cCommon32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466947884/i2cMaster.o: ../../../common/i2c/master/i2cMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466947884" 
	@${RM} ${OBJECTDIR}/_ext/466947884/i2cMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/466947884/i2cMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466947884/i2cMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/466947884/i2cMaster.o.d" -o ${OBJECTDIR}/_ext/466947884/i2cMaster.o ../../../common/i2c/master/i2cMaster.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/554612702/i2cMaster32.o: ../../../common/i2c/master/32/i2cMaster32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/554612702" 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMaster32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554612702/i2cMaster32.o.d" -o ${OBJECTDIR}/_ext/554612702/i2cMaster32.o ../../../common/i2c/master/32/i2cMaster32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o: ../../../common/i2c/master/32/i2cMasterSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/554612702" 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o.d" -o ${OBJECTDIR}/_ext/554612702/i2cMasterSetup32.o ../../../common/i2c/master/32/i2cMasterSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o: ../../../common/i2c/slave/i2cSlaveLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1364558899" 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o.d" -o ${OBJECTDIR}/_ext/1364558899/i2cSlaveLink.o ../../../common/i2c/slave/i2cSlaveLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1364558899/i2cSlave.o: ../../../common/i2c/slave/i2cSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1364558899" 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1364558899/i2cSlave.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1364558899/i2cSlave.o.d" -o ${OBJECTDIR}/_ext/1364558899/i2cSlave.o ../../../common/i2c/slave/i2cSlave.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlave32.o: ../../../common/i2c/slave/32/i2cSlave32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlave32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlave32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlave32.o ../../../common/i2c/slave/32/i2cSlave32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o: ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlaveInterrupt32.o ../../../common/i2c/slave/32/i2cSlaveInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o: ../../../common/i2c/slave/32/i2cSlaveSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/291343329" 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o.d" -o ${OBJECTDIR}/_ext/291343329/i2cSlaveSetup32.o ../../../common/i2c/slave/32/i2cSlaveSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/buffer.o: ../../../common/io/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/buffer.o.d" -o ${OBJECTDIR}/_ext/1674127323/buffer.o ../../../common/io/buffer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/inputStream.o: ../../../common/io/inputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/inputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/inputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/inputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/inputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/inputStream.o ../../../common/io/inputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/outputStream.o: ../../../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/outputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/outputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/outputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/outputStream.o ../../../common/io/outputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/printWriter.o: ../../../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/printWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/printWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/printWriter.o ../../../common/io/printWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/filter.o: ../../../common/io/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/filter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/filter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/filter.o.d" -o ${OBJECTDIR}/_ext/1674127323/filter.o ../../../common/io/filter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/ioUtils.o: ../../../common/io/ioUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/ioUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/ioUtils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/ioUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/ioUtils.o.d" -o ${OBJECTDIR}/_ext/1674127323/ioUtils.o ../../../common/io/ioUtils.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/reader.o: ../../../common/io/reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/reader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/reader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/reader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/reader.o.d" -o ${OBJECTDIR}/_ext/1674127323/reader.o ../../../common/io/reader.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/streamLink.o: ../../../common/io/streamLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/streamLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/streamLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/streamLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/streamLink.o.d" -o ${OBJECTDIR}/_ext/1674127323/streamLink.o ../../../common/io/streamLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/pin.o: ../../../common/io/pin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/pin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/pin.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/pin.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/pin.o.d" -o ${OBJECTDIR}/_ext/1674127323/pin.o ../../../common/io/pin.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o: ../../../common/io/binaryPrintWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/binaryPrintWriter.o ../../../common/io/binaryPrintWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/nullOutputStream.o: ../../../common/io/nullOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/nullOutputStream.o.d" -o ${OBJECTDIR}/_ext/1674127323/nullOutputStream.o ../../../common/io/nullOutputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1674127323/printTableWriter.o: ../../../common/io/printTableWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1674127323" 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1674127323/printTableWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1674127323/printTableWriter.o.d" -o ${OBJECTDIR}/_ext/1674127323/printTableWriter.o ../../../common/io/printTableWriter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logger.o: ../../../common/log/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logger.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logger.o.d" -o ${OBJECTDIR}/_ext/358342447/logger.o ../../../common/log/logger.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logHandler.o: ../../../common/log/logHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logHandler.o.d" -o ${OBJECTDIR}/_ext/358342447/logHandler.o ../../../common/log/logHandler.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logHandlerList.o: ../../../common/log/logHandlerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandlerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logHandlerList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logHandlerList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logHandlerList.o.d" -o ${OBJECTDIR}/_ext/358342447/logHandlerList.o ../../../common/log/logHandlerList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/logLevel.o: ../../../common/log/logLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/logLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/logLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/logLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/logLevel.o.d" -o ${OBJECTDIR}/_ext/358342447/logLevel.o ../../../common/log/logLevel.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/358342447/loggerDebug.o: ../../../common/log/loggerDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/358342447" 
	@${RM} ${OBJECTDIR}/_ext/358342447/loggerDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/358342447/loggerDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/358342447/loggerDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/358342447/loggerDebug.o.d" -o ${OBJECTDIR}/_ext/358342447/loggerDebug.o ../../../common/log/loggerDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1776269187/cenMath.o: ../../../common/math/cenMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1776269187" 
	@${RM} ${OBJECTDIR}/_ext/1776269187/cenMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1776269187/cenMath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1776269187/cenMath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1776269187/cenMath.o.d" -o ${OBJECTDIR}/_ext/1776269187/cenMath.o ../../../common/math/cenMath.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1776269187/hexUtils.o: ../../../common/math/hexUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1776269187" 
	@${RM} ${OBJECTDIR}/_ext/1776269187/hexUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1776269187/hexUtils.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1776269187/hexUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1776269187/hexUtils.o.d" -o ${OBJECTDIR}/_ext/1776269187/hexUtils.o ../../../common/math/hexUtils.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1786728963/pwmPic32.o: ../../../common/pwm/32/pwmPic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1786728963" 
	@${RM} ${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1786728963/pwmPic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1786728963/pwmPic32.o.d" -o ${OBJECTDIR}/_ext/1786728963/pwmPic32.o ../../../common/pwm/32/pwmPic32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/857340905/motorPwm.o: ../../../common/pwm/motor/motorPwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/857340905" 
	@${RM} ${OBJECTDIR}/_ext/857340905/motorPwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/857340905/motorPwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/857340905/motorPwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/857340905/motorPwm.o.d" -o ${OBJECTDIR}/_ext/857340905/motorPwm.o ../../../common/pwm/motor/motorPwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o: ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127655255" 
	@${RM} ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o.d" -o ${OBJECTDIR}/_ext/1127655255/dualHBridgeMotorPwm32.o ../../../common/pwm/motor/32/dualHBridgeMotorPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127655255/motorPwm32.o: ../../../common/pwm/motor/32/motorPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127655255" 
	@${RM} ${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127655255/motorPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1127655255/motorPwm32.o.d" -o ${OBJECTDIR}/_ext/1127655255/motorPwm32.o ../../../common/pwm/motor/32/motorPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/852099397/servoPwm.o: ../../../common/pwm/servo/servoPwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/852099397" 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/852099397/servoPwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/852099397/servoPwm.o.d" -o ${OBJECTDIR}/_ext/852099397/servoPwm.o ../../../common/pwm/servo/servoPwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/852099397/servoPwmDebug.o: ../../../common/pwm/servo/servoPwmDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/852099397" 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/852099397/servoPwmDebug.o.d" -o ${OBJECTDIR}/_ext/852099397/servoPwmDebug.o ../../../common/pwm/servo/servoPwmDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1636369869/servoPwm32.o: ../../../common/pwm/servo/32/servoPwm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1636369869" 
	@${RM} ${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1636369869/servoPwm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1636369869/servoPwm32.o.d" -o ${OBJECTDIR}/_ext/1636369869/servoPwm32.o ../../../common/pwm/servo/32/servoPwm32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLink.o: ../../../common/serial/serialLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLink.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLink.o ../../../common/serial/serialLink.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialOutputStream.o: ../../../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialOutputStream.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialOutputStream.o ../../../common/serial/serialOutputStream.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o: ../../../common/serial/serialLinkDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLinkDebug.o ../../../common/serial/serialLinkDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1717258711/serialLinkList.o: ../../../common/serial/serialLinkList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717258711" 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717258711/serialLinkList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1717258711/serialLinkList.o.d" -o ${OBJECTDIR}/_ext/1717258711/serialLinkList.o ../../../common/serial/serialLinkList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1498749947/serial32.o: ../../../common/serial/32/serial32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1498749947" 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serial32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serial32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498749947/serial32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498749947/serial32.o.d" -o ${OBJECTDIR}/_ext/1498749947/serial32.o ../../../common/serial/32/serial32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o: ../../../common/serial/32/serialInputInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1498749947" 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o.d" -o ${OBJECTDIR}/_ext/1498749947/serialInputInterrupt32.o ../../../common/serial/32/serialInputInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698747804/system.o: ../../../common/system/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698747804" 
	@${RM} ${OBJECTDIR}/_ext/1698747804/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698747804/system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698747804/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1698747804/system.o.d" -o ${OBJECTDIR}/_ext/1698747804/system.o ../../../common/system/system.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/cenTimer.o: ../../../common/timer/cenTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/cenTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/cenTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/cenTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/cenTimer.o.d" -o ${OBJECTDIR}/_ext/776926320/cenTimer.o ../../../common/timer/cenTimer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/timerList.o: ../../../common/timer/timerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/timerList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/timerList.o.d" -o ${OBJECTDIR}/_ext/776926320/timerList.o ../../../common/timer/timerList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/776926320/timerDebug.o: ../../../common/timer/timerDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/776926320" 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/776926320/timerDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/776926320/timerDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/776926320/timerDebug.o.d" -o ${OBJECTDIR}/_ext/776926320/timerDebug.o ../../../common/timer/timerDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/166712226/timerInterrupt32.o: ../../../common/timer/32/timerInterrupt32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/166712226" 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/166712226/timerInterrupt32.o.d" -o ${OBJECTDIR}/_ext/166712226/timerInterrupt32.o ../../../common/timer/32/timerInterrupt32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/166712226/timerSetup32.o: ../../../common/timer/32/timerSetup32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/166712226" 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerSetup32.o.d 
	@${RM} ${OBJECTDIR}/_ext/166712226/timerSetup32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/166712226/timerSetup32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/166712226/timerSetup32.o.d" -o ${OBJECTDIR}/_ext/166712226/timerSetup32.o ../../../common/timer/32/timerSetup32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/device.o: ../../../device/device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/device.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/device.o.d" -o ${OBJECTDIR}/_ext/927408101/device.o ../../../device/device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceList.o: ../../../device/deviceList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceList.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceList.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceList.o ../../../device/deviceList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceDescriptor.o: ../../../device/deviceDescriptor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceDescriptor.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceDescriptor.o ../../../device/deviceDescriptor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceInterface.o: ../../../device/deviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceInterface.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceInterface.o ../../../device/deviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceUsage.o: ../../../device/deviceUsage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceUsage.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceUsage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceUsage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceUsage.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceUsage.o ../../../device/deviceUsage.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/transmitMode.o: ../../../device/transmitMode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/transmitMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/transmitMode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/transmitMode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/transmitMode.o.d" -o ${OBJECTDIR}/_ext/927408101/transmitMode.o ../../../device/transmitMode.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/927408101/deviceDebug.o: ../../../device/deviceDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/927408101" 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/927408101/deviceDebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/927408101/deviceDebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/927408101/deviceDebug.o.d" -o ${OBJECTDIR}/_ext/927408101/deviceDebug.o ../../../device/deviceDebug.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/285179548/clockDevice.o: ../../../device/clock/clockDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/285179548" 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/285179548/clockDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/285179548/clockDevice.o.d" -o ${OBJECTDIR}/_ext/285179548/clockDevice.o ../../../device/clock/clockDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o: ../../../device/clock/clockDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/285179548" 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/285179548/clockDeviceInterface.o ../../../device/clock/clockDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o: ../../../device/dispatcher/deviceDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1191224559" 
	@${RM} ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o.d" -o ${OBJECTDIR}/_ext/1191224559/deviceDataDispatcher.o ../../../device/dispatcher/deviceDataDispatcher.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o: ../../../device/motor/pwmMotorDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotorDevice.o ../../../device/motor/pwmMotorDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o: ../../../device/motor/pwmMotorDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotorDeviceInterface.o ../../../device/motor/pwmMotorDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/275849781/pwmMotor.o: ../../../device/motor/pwmMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/275849781" 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/275849781/pwmMotor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/275849781/pwmMotor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/275849781/pwmMotor.o.d" -o ${OBJECTDIR}/_ext/275849781/pwmMotor.o ../../../device/motor/pwmMotor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/201065310/serialDebugDevice.o: ../../../device/serial/serialDebugDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/201065310" 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/201065310/serialDebugDevice.o.d" -o ${OBJECTDIR}/_ext/201065310/serialDebugDevice.o ../../../device/serial/serialDebugDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o: ../../../device/serial/serialDebugDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/201065310" 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/201065310/serialDebugDeviceInterface.o ../../../device/serial/serialDebugDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/270608273/servoDevice.o: ../../../device/servo/servoDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270608273" 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270608273/servoDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/270608273/servoDevice.o.d" -o ${OBJECTDIR}/_ext/270608273/servoDevice.o ../../../device/servo/servoDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o: ../../../device/servo/servoDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270608273" 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/270608273/servoDeviceInterface.o ../../../device/servo/servoDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/219576217/systemDevice.o: ../../../device/system/systemDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/219576217" 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/219576217/systemDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/219576217/systemDevice.o.d" -o ${OBJECTDIR}/_ext/219576217/systemDevice.o ../../../device/system/systemDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o: ../../../device/system/systemDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/219576217" 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/219576217/systemDeviceInterface.o ../../../device/system/systemDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o: ../../../device/test/testDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1394172804" 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/1394172804/testDeviceInterface.o ../../../device/test/testDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1394172804/testDevice.o: ../../../device/test/testDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1394172804" 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1394172804/testDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1394172804/testDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1394172804/testDevice.o.d" -o ${OBJECTDIR}/_ext/1394172804/testDevice.o ../../../device/test/testDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/269570917/timerDevice.o: ../../../device/timer/timerDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/269570917" 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/269570917/timerDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/269570917/timerDevice.o.d" -o ${OBJECTDIR}/_ext/269570917/timerDevice.o ../../../device/timer/timerDevice.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o: ../../../device/timer/timerDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/269570917" 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o.d" -o ${OBJECTDIR}/_ext/269570917/timerDeviceInterface.o ../../../device/timer/timerDeviceInterface.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driverStreamListener.o: ../../../drivers/driverStreamListener.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverStreamListener.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driverStreamListener.o.d" -o ${OBJECTDIR}/_ext/954557028/driverStreamListener.o ../../../drivers/driverStreamListener.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driver.o: ../../../drivers/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driver.o.d" -o ${OBJECTDIR}/_ext/954557028/driver.o ../../../drivers/driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/954557028/driverList.o: ../../../drivers/driverList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/954557028" 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverList.o.d 
	@${RM} ${OBJECTDIR}/_ext/954557028/driverList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/954557028/driverList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/954557028/driverList.o.d" -o ${OBJECTDIR}/_ext/954557028/driverList.o ../../../drivers/driverList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1343658459/softClock.o: ../../../drivers/clock/softClock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343658459" 
	@${RM} ${OBJECTDIR}/_ext/1343658459/softClock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343658459/softClock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343658459/softClock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343658459/softClock.o.d" -o ${OBJECTDIR}/_ext/1343658459/softClock.o ../../../drivers/clock/softClock.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o: ../../../drivers/dispatcher/driverDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1426650362" 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o.d" -o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcher.o ../../../drivers/dispatcher/driverDataDispatcher.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o: ../../../drivers/dispatcher/driverDataDispatcherList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1426650362" 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o.d" -o ${OBJECTDIR}/_ext/1426650362/driverDataDispatcherList.o ../../../drivers/dispatcher/driverDataDispatcherList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o: ../mechanicalMainBoard32_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o.d" -o ${OBJECTDIR}/_ext/1472/mechanicalMainBoard32_1.o ../mechanicalMainBoard32_1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DICD3PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=ICD3PlatformTool=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MECHANICAL_BOARD_32_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
