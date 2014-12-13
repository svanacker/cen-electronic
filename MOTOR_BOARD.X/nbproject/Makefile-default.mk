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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../common/2d/2d.c ../common/delay/cenDelay.c ../common/eeprom/eeprom.c ../common/error/error.c ../common/i2c/i2cDebug.c ../common/i2c/slave/i2cSlaveLink.c ../common/io/buffer.c ../common/io/inputStream.c ../common/io/outputStream.c ../common/io/printWriter.c ../common/io/filter.c ../common/io/ioUtils.c ../common/io/reader.c ../common/io/streamLink.c ../common/log/logger.c ../common/log/logHandler.c ../common/log/logHandlerList.c ../common/log/logLevel.c ../common/math/cenMath.c ../common/math/hexUtils.c ../common/pwm/30F/pwmPic30F.c ../common/serial/serialLink.c ../common/serial/serialOutputStream.c ../common/serial/30F/serial30F.c ../common/serial/30F/serialInputInterrupt30F.c ../common/timer/cenTimer.c ../common/timer/timerList.c ../device/deviceList.c ../device/deviceDescriptor.c ../device/deviceInterface.c ../device/deviceUsage.c ../device/device.c ../device/dispatcher/deviceDataDispatcher.c ../device/motion/pid/pidDevice.c ../device/motion/pid/pidDeviceInterface.c ../device/motion/position/codersDevice.c ../device/motion/position/codersDeviceInterface.c ../device/motion/position/trajectoryDevice.c ../device/motion/position/trajectoryDeviceInterface.c ../device/motion/simple/motionDevice.c ../device/motion/simple/motionDeviceInterface.c ../device/motor/pwmMotorDevice.c ../device/motor/pwmMotorDeviceInterface.c ../device/motor/pwmMotor.c ../device/system/systemDevice.c ../device/system/systemDeviceInterface.c ../drivers/driverStreamListener.c ../drivers/driver.c ../drivers/driverList.c ../drivers/dispatcher/driverDataDispatcher.c ../drivers/dispatcher/driverDataDispatcherList.c ../main/motorboard/motorboardmain.c ../motion/extended/bspline.c ../motion/extended/bsplineDebug.c ../motion/pid/pid.c ../motion/pid/pidPersistence.c ../motion/pid/pidMotionProfileComputer.c ../motion/pid/motionEndDetection.c ../motion/pid/pidTimer.c ../motion/pid/alphaTheta.c ../motion/position/coderErrorComputer.c ../motion/pid/pidComputer.c ../motion/pid/bSplinePidComputer.c ../motion/position/hctl2032.c ../motion/position/hctlCoders.c ../motion/position/trajectory.c ../motion/simple/motion.c ../motion/simple/motionPersistence.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1544594553/2d.o ${OBJECTDIR}/_ext/1309593678/cenDelay.o ${OBJECTDIR}/_ext/1971462805/eeprom.o ${OBJECTDIR}/_ext/1310910675/error.o ${OBJECTDIR}/_ext/637739483/i2cDebug.o ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o ${OBJECTDIR}/_ext/1544592837/buffer.o ${OBJECTDIR}/_ext/1544592837/inputStream.o ${OBJECTDIR}/_ext/1544592837/outputStream.o ${OBJECTDIR}/_ext/1544592837/printWriter.o ${OBJECTDIR}/_ext/1544592837/filter.o ${OBJECTDIR}/_ext/1544592837/ioUtils.o ${OBJECTDIR}/_ext/1544592837/reader.o ${OBJECTDIR}/_ext/1544592837/streamLink.o ${OBJECTDIR}/_ext/637734705/logger.o ${OBJECTDIR}/_ext/637734705/logHandler.o ${OBJECTDIR}/_ext/637734705/logHandlerList.o ${OBJECTDIR}/_ext/637734705/logLevel.o ${OBJECTDIR}/_ext/1705077469/cenMath.o ${OBJECTDIR}/_ext/1705077469/hexUtils.o ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o ${OBJECTDIR}/_ext/1922645879/serialLink.o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ${OBJECTDIR}/_ext/61306627/serial30F.o ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o ${OBJECTDIR}/_ext/1324490256/cenTimer.o ${OBJECTDIR}/_ext/1324490256/timerList.o ${OBJECTDIR}/_ext/1250819707/deviceList.o ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o ${OBJECTDIR}/_ext/1250819707/deviceInterface.o ${OBJECTDIR}/_ext/1250819707/deviceUsage.o ${OBJECTDIR}/_ext/1250819707/device.o ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o ${OBJECTDIR}/_ext/1422778756/pidDevice.o ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o ${OBJECTDIR}/_ext/435840296/codersDevice.o ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o ${OBJECTDIR}/_ext/1116590881/motionDevice.o ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o ${OBJECTDIR}/_ext/271714155/pwmMotor.o ${OBJECTDIR}/_ext/14189049/systemDevice.o ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o ${OBJECTDIR}/_ext/239857660/driverStreamListener.o ${OBJECTDIR}/_ext/239857660/driver.o ${OBJECTDIR}/_ext/239857660/driverList.o ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o ${OBJECTDIR}/_ext/1594349736/motorboardmain.o ${OBJECTDIR}/_ext/99181277/bspline.o ${OBJECTDIR}/_ext/99181277/bsplineDebug.o ${OBJECTDIR}/_ext/1751824225/pid.o ${OBJECTDIR}/_ext/1751824225/pidPersistence.o ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o ${OBJECTDIR}/_ext/1751824225/pidTimer.o ${OBJECTDIR}/_ext/1751824225/alphaTheta.o ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o ${OBJECTDIR}/_ext/1751824225/pidComputer.o ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o ${OBJECTDIR}/_ext/1825453805/hctl2032.o ${OBJECTDIR}/_ext/1825453805/hctlCoders.o ${OBJECTDIR}/_ext/1825453805/trajectory.o ${OBJECTDIR}/_ext/534139932/motion.o ${OBJECTDIR}/_ext/534139932/motionPersistence.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1544594553/2d.o.d ${OBJECTDIR}/_ext/1309593678/cenDelay.o.d ${OBJECTDIR}/_ext/1971462805/eeprom.o.d ${OBJECTDIR}/_ext/1310910675/error.o.d ${OBJECTDIR}/_ext/637739483/i2cDebug.o.d ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d ${OBJECTDIR}/_ext/1544592837/buffer.o.d ${OBJECTDIR}/_ext/1544592837/inputStream.o.d ${OBJECTDIR}/_ext/1544592837/outputStream.o.d ${OBJECTDIR}/_ext/1544592837/printWriter.o.d ${OBJECTDIR}/_ext/1544592837/filter.o.d ${OBJECTDIR}/_ext/1544592837/ioUtils.o.d ${OBJECTDIR}/_ext/1544592837/reader.o.d ${OBJECTDIR}/_ext/1544592837/streamLink.o.d ${OBJECTDIR}/_ext/637734705/logger.o.d ${OBJECTDIR}/_ext/637734705/logHandler.o.d ${OBJECTDIR}/_ext/637734705/logHandlerList.o.d ${OBJECTDIR}/_ext/637734705/logLevel.o.d ${OBJECTDIR}/_ext/1705077469/cenMath.o.d ${OBJECTDIR}/_ext/1705077469/hexUtils.o.d ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d ${OBJECTDIR}/_ext/1922645879/serialLink.o.d ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d ${OBJECTDIR}/_ext/61306627/serial30F.o.d ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d ${OBJECTDIR}/_ext/1324490256/cenTimer.o.d ${OBJECTDIR}/_ext/1324490256/timerList.o.d ${OBJECTDIR}/_ext/1250819707/deviceList.o.d ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d ${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d ${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d ${OBJECTDIR}/_ext/1250819707/device.o.d ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d ${OBJECTDIR}/_ext/1422778756/pidDevice.o.d ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d ${OBJECTDIR}/_ext/435840296/codersDevice.o.d ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d ${OBJECTDIR}/_ext/1116590881/motionDevice.o.d ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d ${OBJECTDIR}/_ext/271714155/pwmMotor.o.d ${OBJECTDIR}/_ext/14189049/systemDevice.o.d ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d ${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d ${OBJECTDIR}/_ext/239857660/driver.o.d ${OBJECTDIR}/_ext/239857660/driverList.o.d ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d ${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d ${OBJECTDIR}/_ext/99181277/bspline.o.d ${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d ${OBJECTDIR}/_ext/1751824225/pid.o.d ${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d ${OBJECTDIR}/_ext/1751824225/pidTimer.o.d ${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d ${OBJECTDIR}/_ext/1751824225/pidComputer.o.d ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d ${OBJECTDIR}/_ext/1825453805/hctl2032.o.d ${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d ${OBJECTDIR}/_ext/1825453805/trajectory.o.d ${OBJECTDIR}/_ext/534139932/motion.o.d ${OBJECTDIR}/_ext/534139932/motionPersistence.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1544594553/2d.o ${OBJECTDIR}/_ext/1309593678/cenDelay.o ${OBJECTDIR}/_ext/1971462805/eeprom.o ${OBJECTDIR}/_ext/1310910675/error.o ${OBJECTDIR}/_ext/637739483/i2cDebug.o ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o ${OBJECTDIR}/_ext/1544592837/buffer.o ${OBJECTDIR}/_ext/1544592837/inputStream.o ${OBJECTDIR}/_ext/1544592837/outputStream.o ${OBJECTDIR}/_ext/1544592837/printWriter.o ${OBJECTDIR}/_ext/1544592837/filter.o ${OBJECTDIR}/_ext/1544592837/ioUtils.o ${OBJECTDIR}/_ext/1544592837/reader.o ${OBJECTDIR}/_ext/1544592837/streamLink.o ${OBJECTDIR}/_ext/637734705/logger.o ${OBJECTDIR}/_ext/637734705/logHandler.o ${OBJECTDIR}/_ext/637734705/logHandlerList.o ${OBJECTDIR}/_ext/637734705/logLevel.o ${OBJECTDIR}/_ext/1705077469/cenMath.o ${OBJECTDIR}/_ext/1705077469/hexUtils.o ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o ${OBJECTDIR}/_ext/1922645879/serialLink.o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ${OBJECTDIR}/_ext/61306627/serial30F.o ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o ${OBJECTDIR}/_ext/1324490256/cenTimer.o ${OBJECTDIR}/_ext/1324490256/timerList.o ${OBJECTDIR}/_ext/1250819707/deviceList.o ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o ${OBJECTDIR}/_ext/1250819707/deviceInterface.o ${OBJECTDIR}/_ext/1250819707/deviceUsage.o ${OBJECTDIR}/_ext/1250819707/device.o ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o ${OBJECTDIR}/_ext/1422778756/pidDevice.o ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o ${OBJECTDIR}/_ext/435840296/codersDevice.o ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o ${OBJECTDIR}/_ext/1116590881/motionDevice.o ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o ${OBJECTDIR}/_ext/271714155/pwmMotor.o ${OBJECTDIR}/_ext/14189049/systemDevice.o ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o ${OBJECTDIR}/_ext/239857660/driverStreamListener.o ${OBJECTDIR}/_ext/239857660/driver.o ${OBJECTDIR}/_ext/239857660/driverList.o ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o ${OBJECTDIR}/_ext/1594349736/motorboardmain.o ${OBJECTDIR}/_ext/99181277/bspline.o ${OBJECTDIR}/_ext/99181277/bsplineDebug.o ${OBJECTDIR}/_ext/1751824225/pid.o ${OBJECTDIR}/_ext/1751824225/pidPersistence.o ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o ${OBJECTDIR}/_ext/1751824225/pidTimer.o ${OBJECTDIR}/_ext/1751824225/alphaTheta.o ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o ${OBJECTDIR}/_ext/1751824225/pidComputer.o ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o ${OBJECTDIR}/_ext/1825453805/hctl2032.o ${OBJECTDIR}/_ext/1825453805/hctlCoders.o ${OBJECTDIR}/_ext/1825453805/trajectory.o ${OBJECTDIR}/_ext/534139932/motion.o ${OBJECTDIR}/_ext/534139932/motionPersistence.o

# Source Files
SOURCEFILES=../common/2d/2d.c ../common/delay/cenDelay.c ../common/eeprom/eeprom.c ../common/error/error.c ../common/i2c/i2cDebug.c ../common/i2c/slave/i2cSlaveLink.c ../common/io/buffer.c ../common/io/inputStream.c ../common/io/outputStream.c ../common/io/printWriter.c ../common/io/filter.c ../common/io/ioUtils.c ../common/io/reader.c ../common/io/streamLink.c ../common/log/logger.c ../common/log/logHandler.c ../common/log/logHandlerList.c ../common/log/logLevel.c ../common/math/cenMath.c ../common/math/hexUtils.c ../common/pwm/30F/pwmPic30F.c ../common/serial/serialLink.c ../common/serial/serialOutputStream.c ../common/serial/30F/serial30F.c ../common/serial/30F/serialInputInterrupt30F.c ../common/timer/cenTimer.c ../common/timer/timerList.c ../device/deviceList.c ../device/deviceDescriptor.c ../device/deviceInterface.c ../device/deviceUsage.c ../device/device.c ../device/dispatcher/deviceDataDispatcher.c ../device/motion/pid/pidDevice.c ../device/motion/pid/pidDeviceInterface.c ../device/motion/position/codersDevice.c ../device/motion/position/codersDeviceInterface.c ../device/motion/position/trajectoryDevice.c ../device/motion/position/trajectoryDeviceInterface.c ../device/motion/simple/motionDevice.c ../device/motion/simple/motionDeviceInterface.c ../device/motor/pwmMotorDevice.c ../device/motor/pwmMotorDeviceInterface.c ../device/motor/pwmMotor.c ../device/system/systemDevice.c ../device/system/systemDeviceInterface.c ../drivers/driverStreamListener.c ../drivers/driver.c ../drivers/driverList.c ../drivers/dispatcher/driverDataDispatcher.c ../drivers/dispatcher/driverDataDispatcherList.c ../main/motorboard/motorboardmain.c ../motion/extended/bspline.c ../motion/extended/bsplineDebug.c ../motion/pid/pid.c ../motion/pid/pidPersistence.c ../motion/pid/pidMotionProfileComputer.c ../motion/pid/motionEndDetection.c ../motion/pid/pidTimer.c ../motion/pid/alphaTheta.c ../motion/position/coderErrorComputer.c ../motion/pid/pidComputer.c ../motion/pid/bSplinePidComputer.c ../motion/position/hctl2032.c ../motion/position/hctlCoders.c ../motion/position/trajectory.c ../motion/simple/motion.c ../motion/simple/motionPersistence.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4013
MP_LINKER_FILE_OPTION=,--script=p30F4013.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1544594553/2d.o: ../common/2d/2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544594553 
	@${RM} ${OBJECTDIR}/_ext/1544594553/2d.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544594553/2d.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/2d/2d.c  -o ${OBJECTDIR}/_ext/1544594553/2d.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544594553/2d.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544594553/2d.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1309593678/cenDelay.o: ../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1309593678 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/delay/cenDelay.c  -o ${OBJECTDIR}/_ext/1309593678/cenDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1971462805/eeprom.o: ../common/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1971462805 
	@${RM} ${OBJECTDIR}/_ext/1971462805/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1971462805/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/eeprom/eeprom.c  -o ${OBJECTDIR}/_ext/1971462805/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1971462805/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1971462805/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1310910675/error.o: ../common/error/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1310910675 
	@${RM} ${OBJECTDIR}/_ext/1310910675/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1310910675/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/error/error.c  -o ${OBJECTDIR}/_ext/1310910675/error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1310910675/error.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1310910675/error.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637739483/i2cDebug.o: ../common/i2c/i2cDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637739483 
	@${RM} ${OBJECTDIR}/_ext/637739483/i2cDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/637739483/i2cDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/i2c/i2cDebug.c  -o ${OBJECTDIR}/_ext/637739483/i2cDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637739483/i2cDebug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637739483/i2cDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o: ../common/i2c/slave/i2cSlaveLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/274716013 
	@${RM} ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/i2c/slave/i2cSlaveLink.c  -o ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/buffer.o: ../common/io/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/buffer.c  -o ${OBJECTDIR}/_ext/1544592837/buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/inputStream.o: ../common/io/inputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/inputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/inputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/inputStream.c  -o ${OBJECTDIR}/_ext/1544592837/inputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/inputStream.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/inputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/outputStream.o: ../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/outputStream.c  -o ${OBJECTDIR}/_ext/1544592837/outputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/outputStream.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/printWriter.o: ../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/printWriter.c  -o ${OBJECTDIR}/_ext/1544592837/printWriter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/printWriter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/filter.o: ../common/io/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/filter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/filter.c  -o ${OBJECTDIR}/_ext/1544592837/filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/filter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/filter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/ioUtils.o: ../common/io/ioUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/ioUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/ioUtils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/ioUtils.c  -o ${OBJECTDIR}/_ext/1544592837/ioUtils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/ioUtils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/ioUtils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/reader.o: ../common/io/reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/reader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/reader.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/reader.c  -o ${OBJECTDIR}/_ext/1544592837/reader.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/reader.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/reader.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/streamLink.o: ../common/io/streamLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/streamLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/streamLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/streamLink.c  -o ${OBJECTDIR}/_ext/1544592837/streamLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/streamLink.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/streamLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logger.o: ../common/log/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logger.c  -o ${OBJECTDIR}/_ext/637734705/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logHandler.o: ../common/log/logHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logHandler.c  -o ${OBJECTDIR}/_ext/637734705/logHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logHandlerList.o: ../common/log/logHandlerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandlerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandlerList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logHandlerList.c  -o ${OBJECTDIR}/_ext/637734705/logHandlerList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logHandlerList.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logHandlerList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logLevel.o: ../common/log/logLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logLevel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logLevel.c  -o ${OBJECTDIR}/_ext/637734705/logLevel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logLevel.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logLevel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1705077469/cenMath.o: ../common/math/cenMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1705077469 
	@${RM} ${OBJECTDIR}/_ext/1705077469/cenMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705077469/cenMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/math/cenMath.c  -o ${OBJECTDIR}/_ext/1705077469/cenMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1705077469/cenMath.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705077469/cenMath.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1705077469/hexUtils.o: ../common/math/hexUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1705077469 
	@${RM} ${OBJECTDIR}/_ext/1705077469/hexUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705077469/hexUtils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/math/hexUtils.c  -o ${OBJECTDIR}/_ext/1705077469/hexUtils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1705077469/hexUtils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705077469/hexUtils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1626057909/pwmPic30F.o: ../common/pwm/30F/pwmPic30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1626057909 
	@${RM} ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/pwm/30F/pwmPic30F.c  -o ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1922645879/serialLink.o: ../common/serial/serialLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/serialLink.c  -o ${OBJECTDIR}/_ext/1922645879/serialLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialLink.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1922645879/serialOutputStream.o: ../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/serialOutputStream.c  -o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/61306627/serial30F.o: ../common/serial/30F/serial30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/61306627 
	@${RM} ${OBJECTDIR}/_ext/61306627/serial30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/61306627/serial30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/30F/serial30F.c  -o ${OBJECTDIR}/_ext/61306627/serial30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/61306627/serial30F.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/61306627/serial30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o: ../common/serial/30F/serialInputInterrupt30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/61306627 
	@${RM} ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/30F/serialInputInterrupt30F.c  -o ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324490256/cenTimer.o: ../common/timer/cenTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324490256 
	@${RM} ${OBJECTDIR}/_ext/1324490256/cenTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324490256/cenTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/timer/cenTimer.c  -o ${OBJECTDIR}/_ext/1324490256/cenTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324490256/cenTimer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324490256/cenTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324490256/timerList.o: ../common/timer/timerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324490256 
	@${RM} ${OBJECTDIR}/_ext/1324490256/timerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324490256/timerList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/timer/timerList.c  -o ${OBJECTDIR}/_ext/1324490256/timerList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324490256/timerList.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324490256/timerList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceList.o: ../device/deviceList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceList.c  -o ${OBJECTDIR}/_ext/1250819707/deviceList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceList.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o: ../device/deviceDescriptor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceDescriptor.c  -o ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceInterface.o: ../device/deviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceInterface.c  -o ${OBJECTDIR}/_ext/1250819707/deviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceUsage.o: ../device/deviceUsage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceUsage.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceUsage.c  -o ${OBJECTDIR}/_ext/1250819707/deviceUsage.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/device.o: ../device/device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/device.c  -o ${OBJECTDIR}/_ext/1250819707/device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o: ../device/dispatcher/deviceDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1913309839 
	@${RM} ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/dispatcher/deviceDataDispatcher.c  -o ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1422778756/pidDevice.o: ../device/motion/pid/pidDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1422778756 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/pid/pidDevice.c  -o ${OBJECTDIR}/_ext/1422778756/pidDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1422778756/pidDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1422778756/pidDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o: ../device/motion/pid/pidDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1422778756 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/pid/pidDeviceInterface.c  -o ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/codersDevice.o: ../device/motion/position/codersDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/codersDevice.c  -o ${OBJECTDIR}/_ext/435840296/codersDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/codersDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/codersDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o: ../device/motion/position/codersDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/codersDeviceInterface.c  -o ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/trajectoryDevice.o: ../device/motion/position/trajectoryDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/trajectoryDevice.c  -o ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o: ../device/motion/position/trajectoryDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/trajectoryDeviceInterface.c  -o ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1116590881/motionDevice.o: ../device/motion/simple/motionDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1116590881 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/simple/motionDevice.c  -o ${OBJECTDIR}/_ext/1116590881/motionDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1116590881/motionDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1116590881/motionDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o: ../device/motion/simple/motionDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1116590881 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/simple/motionDeviceInterface.c  -o ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o: ../device/motor/pwmMotorDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotorDevice.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o: ../device/motor/pwmMotorDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotorDeviceInterface.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotor.o: ../device/motor/pwmMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotor.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/14189049/systemDevice.o: ../device/system/systemDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/14189049 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/system/systemDevice.c  -o ${OBJECTDIR}/_ext/14189049/systemDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/14189049/systemDevice.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/14189049/systemDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o: ../device/system/systemDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/14189049 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/system/systemDeviceInterface.c  -o ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driverStreamListener.o: ../drivers/driverStreamListener.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverStreamListener.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driverStreamListener.c  -o ${OBJECTDIR}/_ext/239857660/driverStreamListener.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driver.o: ../drivers/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driver.c  -o ${OBJECTDIR}/_ext/239857660/driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driverList.o: ../drivers/driverList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverList.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driverList.c  -o ${OBJECTDIR}/_ext/239857660/driverList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driverList.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driverList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o: ../drivers/dispatcher/driverDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/516843162 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/dispatcher/driverDataDispatcher.c  -o ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o: ../drivers/dispatcher/driverDataDispatcherList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/516843162 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/dispatcher/driverDataDispatcherList.c  -o ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1594349736/motorboardmain.o: ../main/motorboard/motorboardmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1594349736 
	@${RM} ${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1594349736/motorboardmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main/motorboard/motorboardmain.c  -o ${OBJECTDIR}/_ext/1594349736/motorboardmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/99181277/bspline.o: ../motion/extended/bspline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/99181277 
	@${RM} ${OBJECTDIR}/_ext/99181277/bspline.o.d 
	@${RM} ${OBJECTDIR}/_ext/99181277/bspline.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/extended/bspline.c  -o ${OBJECTDIR}/_ext/99181277/bspline.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/99181277/bspline.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/99181277/bspline.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/99181277/bsplineDebug.o: ../motion/extended/bsplineDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/99181277 
	@${RM} ${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/99181277/bsplineDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/extended/bsplineDebug.c  -o ${OBJECTDIR}/_ext/99181277/bsplineDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pid.o: ../motion/pid/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pid.c  -o ${OBJECTDIR}/_ext/1751824225/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidPersistence.o: ../motion/pid/pidPersistence.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidPersistence.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidPersistence.c  -o ${OBJECTDIR}/_ext/1751824225/pidPersistence.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o: ../motion/pid/pidMotionProfileComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidMotionProfileComputer.c  -o ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/motionEndDetection.o: ../motion/pid/motionEndDetection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/motionEndDetection.c  -o ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidTimer.o: ../motion/pid/pidTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidTimer.c  -o ${OBJECTDIR}/_ext/1751824225/pidTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidTimer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/alphaTheta.o: ../motion/pid/alphaTheta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/alphaTheta.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/alphaTheta.c  -o ${OBJECTDIR}/_ext/1751824225/alphaTheta.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o: ../motion/position/coderErrorComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/coderErrorComputer.c  -o ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidComputer.o: ../motion/pid/pidComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidComputer.c  -o ${OBJECTDIR}/_ext/1751824225/pidComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidComputer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o: ../motion/pid/bSplinePidComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/bSplinePidComputer.c  -o ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/hctl2032.o: ../motion/position/hctl2032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctl2032.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctl2032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/hctl2032.c  -o ${OBJECTDIR}/_ext/1825453805/hctl2032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/hctl2032.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/hctl2032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/hctlCoders.o: ../motion/position/hctlCoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctlCoders.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/hctlCoders.c  -o ${OBJECTDIR}/_ext/1825453805/hctlCoders.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/trajectory.o: ../motion/position/trajectory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/trajectory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/trajectory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/trajectory.c  -o ${OBJECTDIR}/_ext/1825453805/trajectory.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/trajectory.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/trajectory.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/534139932/motion.o: ../motion/simple/motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534139932 
	@${RM} ${OBJECTDIR}/_ext/534139932/motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/534139932/motion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/simple/motion.c  -o ${OBJECTDIR}/_ext/534139932/motion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/534139932/motion.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/534139932/motion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/534139932/motionPersistence.o: ../motion/simple/motionPersistence.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534139932 
	@${RM} ${OBJECTDIR}/_ext/534139932/motionPersistence.o.d 
	@${RM} ${OBJECTDIR}/_ext/534139932/motionPersistence.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/simple/motionPersistence.c  -o ${OBJECTDIR}/_ext/534139932/motionPersistence.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/534139932/motionPersistence.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/534139932/motionPersistence.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1544594553/2d.o: ../common/2d/2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544594553 
	@${RM} ${OBJECTDIR}/_ext/1544594553/2d.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544594553/2d.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/2d/2d.c  -o ${OBJECTDIR}/_ext/1544594553/2d.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544594553/2d.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544594553/2d.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1309593678/cenDelay.o: ../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1309593678 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/delay/cenDelay.c  -o ${OBJECTDIR}/_ext/1309593678/cenDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1971462805/eeprom.o: ../common/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1971462805 
	@${RM} ${OBJECTDIR}/_ext/1971462805/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1971462805/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/eeprom/eeprom.c  -o ${OBJECTDIR}/_ext/1971462805/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1971462805/eeprom.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1971462805/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1310910675/error.o: ../common/error/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1310910675 
	@${RM} ${OBJECTDIR}/_ext/1310910675/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1310910675/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/error/error.c  -o ${OBJECTDIR}/_ext/1310910675/error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1310910675/error.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1310910675/error.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637739483/i2cDebug.o: ../common/i2c/i2cDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637739483 
	@${RM} ${OBJECTDIR}/_ext/637739483/i2cDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/637739483/i2cDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/i2c/i2cDebug.c  -o ${OBJECTDIR}/_ext/637739483/i2cDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637739483/i2cDebug.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637739483/i2cDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o: ../common/i2c/slave/i2cSlaveLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/274716013 
	@${RM} ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/i2c/slave/i2cSlaveLink.c  -o ${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/274716013/i2cSlaveLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/buffer.o: ../common/io/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/buffer.c  -o ${OBJECTDIR}/_ext/1544592837/buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/buffer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/inputStream.o: ../common/io/inputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/inputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/inputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/inputStream.c  -o ${OBJECTDIR}/_ext/1544592837/inputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/inputStream.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/inputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/outputStream.o: ../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/outputStream.c  -o ${OBJECTDIR}/_ext/1544592837/outputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/outputStream.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/printWriter.o: ../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/printWriter.c  -o ${OBJECTDIR}/_ext/1544592837/printWriter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/printWriter.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/filter.o: ../common/io/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/filter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/filter.c  -o ${OBJECTDIR}/_ext/1544592837/filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/filter.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/filter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/ioUtils.o: ../common/io/ioUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/ioUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/ioUtils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/ioUtils.c  -o ${OBJECTDIR}/_ext/1544592837/ioUtils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/ioUtils.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/ioUtils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/reader.o: ../common/io/reader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/reader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/reader.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/reader.c  -o ${OBJECTDIR}/_ext/1544592837/reader.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/reader.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/reader.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1544592837/streamLink.o: ../common/io/streamLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/streamLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/streamLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/io/streamLink.c  -o ${OBJECTDIR}/_ext/1544592837/streamLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/streamLink.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/streamLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logger.o: ../common/log/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logger.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logger.c  -o ${OBJECTDIR}/_ext/637734705/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logger.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logHandler.o: ../common/log/logHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logHandler.c  -o ${OBJECTDIR}/_ext/637734705/logHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logHandler.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logHandlerList.o: ../common/log/logHandlerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandlerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logHandlerList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logHandlerList.c  -o ${OBJECTDIR}/_ext/637734705/logHandlerList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logHandlerList.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logHandlerList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/637734705/logLevel.o: ../common/log/logLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/637734705 
	@${RM} ${OBJECTDIR}/_ext/637734705/logLevel.o.d 
	@${RM} ${OBJECTDIR}/_ext/637734705/logLevel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/log/logLevel.c  -o ${OBJECTDIR}/_ext/637734705/logLevel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/637734705/logLevel.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/637734705/logLevel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1705077469/cenMath.o: ../common/math/cenMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1705077469 
	@${RM} ${OBJECTDIR}/_ext/1705077469/cenMath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705077469/cenMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/math/cenMath.c  -o ${OBJECTDIR}/_ext/1705077469/cenMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1705077469/cenMath.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705077469/cenMath.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1705077469/hexUtils.o: ../common/math/hexUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1705077469 
	@${RM} ${OBJECTDIR}/_ext/1705077469/hexUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705077469/hexUtils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/math/hexUtils.c  -o ${OBJECTDIR}/_ext/1705077469/hexUtils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1705077469/hexUtils.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705077469/hexUtils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1626057909/pwmPic30F.o: ../common/pwm/30F/pwmPic30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1626057909 
	@${RM} ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/pwm/30F/pwmPic30F.c  -o ${OBJECTDIR}/_ext/1626057909/pwmPic30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1626057909/pwmPic30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1922645879/serialLink.o: ../common/serial/serialLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/serialLink.c  -o ${OBJECTDIR}/_ext/1922645879/serialLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialLink.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialLink.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1922645879/serialOutputStream.o: ../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/serialOutputStream.c  -o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/61306627/serial30F.o: ../common/serial/30F/serial30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/61306627 
	@${RM} ${OBJECTDIR}/_ext/61306627/serial30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/61306627/serial30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/30F/serial30F.c  -o ${OBJECTDIR}/_ext/61306627/serial30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/61306627/serial30F.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/61306627/serial30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o: ../common/serial/30F/serialInputInterrupt30F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/61306627 
	@${RM} ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d 
	@${RM} ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/serial/30F/serialInputInterrupt30F.c  -o ${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/61306627/serialInputInterrupt30F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324490256/cenTimer.o: ../common/timer/cenTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324490256 
	@${RM} ${OBJECTDIR}/_ext/1324490256/cenTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324490256/cenTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/timer/cenTimer.c  -o ${OBJECTDIR}/_ext/1324490256/cenTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324490256/cenTimer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324490256/cenTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324490256/timerList.o: ../common/timer/timerList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324490256 
	@${RM} ${OBJECTDIR}/_ext/1324490256/timerList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324490256/timerList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../common/timer/timerList.c  -o ${OBJECTDIR}/_ext/1324490256/timerList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324490256/timerList.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324490256/timerList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceList.o: ../device/deviceList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceList.c  -o ${OBJECTDIR}/_ext/1250819707/deviceList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceList.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o: ../device/deviceDescriptor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceDescriptor.c  -o ${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceDescriptor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceInterface.o: ../device/deviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceInterface.c  -o ${OBJECTDIR}/_ext/1250819707/deviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/deviceUsage.o: ../device/deviceUsage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/deviceUsage.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/deviceUsage.c  -o ${OBJECTDIR}/_ext/1250819707/deviceUsage.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/deviceUsage.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1250819707/device.o: ../device/device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1250819707 
	@${RM} ${OBJECTDIR}/_ext/1250819707/device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1250819707/device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/device.c  -o ${OBJECTDIR}/_ext/1250819707/device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1250819707/device.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1250819707/device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o: ../device/dispatcher/deviceDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1913309839 
	@${RM} ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/dispatcher/deviceDataDispatcher.c  -o ${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1913309839/deviceDataDispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1422778756/pidDevice.o: ../device/motion/pid/pidDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1422778756 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/pid/pidDevice.c  -o ${OBJECTDIR}/_ext/1422778756/pidDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1422778756/pidDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1422778756/pidDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o: ../device/motion/pid/pidDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1422778756 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/pid/pidDeviceInterface.c  -o ${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1422778756/pidDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/codersDevice.o: ../device/motion/position/codersDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/codersDevice.c  -o ${OBJECTDIR}/_ext/435840296/codersDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/codersDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/codersDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o: ../device/motion/position/codersDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/codersDeviceInterface.c  -o ${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/codersDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/trajectoryDevice.o: ../device/motion/position/trajectoryDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/trajectoryDevice.c  -o ${OBJECTDIR}/_ext/435840296/trajectoryDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/trajectoryDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o: ../device/motion/position/trajectoryDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/435840296 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/position/trajectoryDeviceInterface.c  -o ${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/435840296/trajectoryDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1116590881/motionDevice.o: ../device/motion/simple/motionDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1116590881 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/simple/motionDevice.c  -o ${OBJECTDIR}/_ext/1116590881/motionDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1116590881/motionDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1116590881/motionDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o: ../device/motion/simple/motionDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1116590881 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motion/simple/motionDeviceInterface.c  -o ${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1116590881/motionDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o: ../device/motor/pwmMotorDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotorDevice.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotorDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o: ../device/motor/pwmMotorDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotorDeviceInterface.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotorDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/271714155/pwmMotor.o: ../device/motor/pwmMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/271714155 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/271714155/pwmMotor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/motor/pwmMotor.c  -o ${OBJECTDIR}/_ext/271714155/pwmMotor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/271714155/pwmMotor.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/271714155/pwmMotor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/14189049/systemDevice.o: ../device/system/systemDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/14189049 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDevice.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/system/systemDevice.c  -o ${OBJECTDIR}/_ext/14189049/systemDevice.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/14189049/systemDevice.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/14189049/systemDevice.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o: ../device/system/systemDeviceInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/14189049 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d 
	@${RM} ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../device/system/systemDeviceInterface.c  -o ${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/14189049/systemDeviceInterface.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driverStreamListener.o: ../drivers/driverStreamListener.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverStreamListener.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driverStreamListener.c  -o ${OBJECTDIR}/_ext/239857660/driverStreamListener.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driverStreamListener.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driver.o: ../drivers/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driver.c  -o ${OBJECTDIR}/_ext/239857660/driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driver.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/239857660/driverList.o: ../drivers/driverList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/239857660 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverList.o.d 
	@${RM} ${OBJECTDIR}/_ext/239857660/driverList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/driverList.c  -o ${OBJECTDIR}/_ext/239857660/driverList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/239857660/driverList.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/239857660/driverList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o: ../drivers/dispatcher/driverDataDispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/516843162 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/dispatcher/driverDataDispatcher.c  -o ${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/516843162/driverDataDispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o: ../drivers/dispatcher/driverDataDispatcherList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/516843162 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d 
	@${RM} ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../drivers/dispatcher/driverDataDispatcherList.c  -o ${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/516843162/driverDataDispatcherList.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1594349736/motorboardmain.o: ../main/motorboard/motorboardmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1594349736 
	@${RM} ${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1594349736/motorboardmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main/motorboard/motorboardmain.c  -o ${OBJECTDIR}/_ext/1594349736/motorboardmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1594349736/motorboardmain.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/99181277/bspline.o: ../motion/extended/bspline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/99181277 
	@${RM} ${OBJECTDIR}/_ext/99181277/bspline.o.d 
	@${RM} ${OBJECTDIR}/_ext/99181277/bspline.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/extended/bspline.c  -o ${OBJECTDIR}/_ext/99181277/bspline.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/99181277/bspline.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/99181277/bspline.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/99181277/bsplineDebug.o: ../motion/extended/bsplineDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/99181277 
	@${RM} ${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/99181277/bsplineDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/extended/bsplineDebug.c  -o ${OBJECTDIR}/_ext/99181277/bsplineDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/99181277/bsplineDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pid.o: ../motion/pid/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pid.c  -o ${OBJECTDIR}/_ext/1751824225/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pid.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidPersistence.o: ../motion/pid/pidPersistence.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidPersistence.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidPersistence.c  -o ${OBJECTDIR}/_ext/1751824225/pidPersistence.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidPersistence.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o: ../motion/pid/pidMotionProfileComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidMotionProfileComputer.c  -o ${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidMotionProfileComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/motionEndDetection.o: ../motion/pid/motionEndDetection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/motionEndDetection.c  -o ${OBJECTDIR}/_ext/1751824225/motionEndDetection.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/motionEndDetection.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidTimer.o: ../motion/pid/pidTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidTimer.c  -o ${OBJECTDIR}/_ext/1751824225/pidTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidTimer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidTimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/alphaTheta.o: ../motion/pid/alphaTheta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/alphaTheta.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/alphaTheta.c  -o ${OBJECTDIR}/_ext/1751824225/alphaTheta.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/alphaTheta.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o: ../motion/position/coderErrorComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/coderErrorComputer.c  -o ${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/coderErrorComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/pidComputer.o: ../motion/pid/pidComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/pidComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/pidComputer.c  -o ${OBJECTDIR}/_ext/1751824225/pidComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/pidComputer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/pidComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o: ../motion/pid/bSplinePidComputer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1751824225 
	@${RM} ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/pid/bSplinePidComputer.c  -o ${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1751824225/bSplinePidComputer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/hctl2032.o: ../motion/position/hctl2032.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctl2032.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctl2032.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/hctl2032.c  -o ${OBJECTDIR}/_ext/1825453805/hctl2032.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/hctl2032.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/hctl2032.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/hctlCoders.o: ../motion/position/hctlCoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/hctlCoders.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/hctlCoders.c  -o ${OBJECTDIR}/_ext/1825453805/hctlCoders.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/hctlCoders.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1825453805/trajectory.o: ../motion/position/trajectory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825453805 
	@${RM} ${OBJECTDIR}/_ext/1825453805/trajectory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825453805/trajectory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/position/trajectory.c  -o ${OBJECTDIR}/_ext/1825453805/trajectory.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1825453805/trajectory.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825453805/trajectory.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/534139932/motion.o: ../motion/simple/motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534139932 
	@${RM} ${OBJECTDIR}/_ext/534139932/motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/534139932/motion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/simple/motion.c  -o ${OBJECTDIR}/_ext/534139932/motion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/534139932/motion.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/534139932/motion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/534139932/motionPersistence.o: ../motion/simple/motionPersistence.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/534139932 
	@${RM} ${OBJECTDIR}/_ext/534139932/motionPersistence.o.d 
	@${RM} ${OBJECTDIR}/_ext/534139932/motionPersistence.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../motion/simple/motionPersistence.c  -o ${OBJECTDIR}/_ext/534139932/motionPersistence.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/534139932/motionPersistence.o.d"        -g -omf=elf -O0 -I"../C:/Program Files (x86)/Microchip/MPLAB C30/include" -I"../common/pwm" -I"../common/serial" -I"../motion/position" -I"../robot" -I"../motion/pid" -I"../common/eeprom" -I"../motion/simple" -I"../device" -I"../common" -I"../common/io" -I"../common/cmd" -I"../common/log" -I"../common/timer" -I"../common/math" -I"../device/dispatcher" -I"../device/motor" -I"../device/system" -I"../common/i2c" -I"../common/i2c/slave" -I"../main/motorboard" -I"../drivers" -I"../drivers/dispatcher" -I"../device/motion/pid" -I"../device/motion/position" -I"../device/motion/simple" -I"../common/2d" -I"../common/error" -I"../motion/extended" -I"../common/delay" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/534139932/motionPersistence.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=480,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../C:/Program Files (x86)/Microchip/MPLAB C30/src/peripheral_30F_24H_33F/libs",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/MOTOR_BOARD.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=480,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../C:/Program Files (x86)/Microchip/MPLAB C30/src/peripheral_30F_24H_33F/libs",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/MOTOR_BOARD.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MOTOR_BOARD.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
