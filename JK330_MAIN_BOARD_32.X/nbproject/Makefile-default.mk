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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../common/delay/cenDelay.c ../common/io/outputStream.c ../common/io/printWriter.c ../common/serial/serialOutputStream.c ../drivers/lcd/lcd24064.c ../drivers/lcd/lcdOutputStream.c ../drivers/lcd/lcdProvider_24064.c ../main/JK330/MainJK330.c ../menu/menu.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1309593678/cenDelay.o ${OBJECTDIR}/_ext/1544592837/outputStream.o ${OBJECTDIR}/_ext/1544592837/printWriter.o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ${OBJECTDIR}/_ext/649236794/lcd24064.o ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o ${OBJECTDIR}/_ext/1868118216/MainJK330.o ${OBJECTDIR}/_ext/760809394/menu.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1309593678/cenDelay.o.d ${OBJECTDIR}/_ext/1544592837/outputStream.o.d ${OBJECTDIR}/_ext/1544592837/printWriter.o.d ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d ${OBJECTDIR}/_ext/649236794/lcd24064.o.d ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d ${OBJECTDIR}/_ext/1868118216/MainJK330.o.d ${OBJECTDIR}/_ext/760809394/menu.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1309593678/cenDelay.o ${OBJECTDIR}/_ext/1544592837/outputStream.o ${OBJECTDIR}/_ext/1544592837/printWriter.o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ${OBJECTDIR}/_ext/649236794/lcd24064.o ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o ${OBJECTDIR}/_ext/1868118216/MainJK330.o ${OBJECTDIR}/_ext/760809394/menu.o

# Source Files
SOURCEFILES=../common/delay/cenDelay.c ../common/io/outputStream.c ../common/io/printWriter.c ../common/serial/serialOutputStream.c ../drivers/lcd/lcd24064.c ../drivers/lcd/lcdOutputStream.c ../drivers/lcd/lcdProvider_24064.c ../main/JK330/MainJK330.c ../menu/menu.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1309593678/cenDelay.o: ../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1309593678 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" -o ${OBJECTDIR}/_ext/1309593678/cenDelay.o ../common/delay/cenDelay.c   
	
${OBJECTDIR}/_ext/1544592837/outputStream.o: ../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" -o ${OBJECTDIR}/_ext/1544592837/outputStream.o ../common/io/outputStream.c   
	
${OBJECTDIR}/_ext/1544592837/printWriter.o: ../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" -o ${OBJECTDIR}/_ext/1544592837/printWriter.o ../common/io/printWriter.c   
	
${OBJECTDIR}/_ext/1922645879/serialOutputStream.o: ../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" -o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ../common/serial/serialOutputStream.c   
	
${OBJECTDIR}/_ext/649236794/lcd24064.o: ../drivers/lcd/lcd24064.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcd24064.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcd24064.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcd24064.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcd24064.o.d" -o ${OBJECTDIR}/_ext/649236794/lcd24064.o ../drivers/lcd/lcd24064.c   
	
${OBJECTDIR}/_ext/649236794/lcdOutputStream.o: ../drivers/lcd/lcdOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d" -o ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o ../drivers/lcd/lcdOutputStream.c   
	
${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o: ../drivers/lcd/lcdProvider_24064.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d" -o ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o ../drivers/lcd/lcdProvider_24064.c   
	
${OBJECTDIR}/_ext/1868118216/MainJK330.o: ../main/JK330/MainJK330.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1868118216 
	@${RM} ${OBJECTDIR}/_ext/1868118216/MainJK330.o.d 
	@${RM} ${OBJECTDIR}/_ext/1868118216/MainJK330.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1868118216/MainJK330.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1868118216/MainJK330.o.d" -o ${OBJECTDIR}/_ext/1868118216/MainJK330.o ../main/JK330/MainJK330.c   
	
${OBJECTDIR}/_ext/760809394/menu.o: ../menu/menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760809394 
	@${RM} ${OBJECTDIR}/_ext/760809394/menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/760809394/menu.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760809394/menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/760809394/menu.o.d" -o ${OBJECTDIR}/_ext/760809394/menu.o ../menu/menu.c   
	
else
${OBJECTDIR}/_ext/1309593678/cenDelay.o: ../common/delay/cenDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1309593678 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1309593678/cenDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1309593678/cenDelay.o.d" -o ${OBJECTDIR}/_ext/1309593678/cenDelay.o ../common/delay/cenDelay.c   
	
${OBJECTDIR}/_ext/1544592837/outputStream.o: ../common/io/outputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/outputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/outputStream.o.d" -o ${OBJECTDIR}/_ext/1544592837/outputStream.o ../common/io/outputStream.c   
	
${OBJECTDIR}/_ext/1544592837/printWriter.o: ../common/io/printWriter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1544592837 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1544592837/printWriter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1544592837/printWriter.o.d" -o ${OBJECTDIR}/_ext/1544592837/printWriter.o ../common/io/printWriter.c   
	
${OBJECTDIR}/_ext/1922645879/serialOutputStream.o: ../common/serial/serialOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1922645879 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1922645879/serialOutputStream.o.d" -o ${OBJECTDIR}/_ext/1922645879/serialOutputStream.o ../common/serial/serialOutputStream.c   
	
${OBJECTDIR}/_ext/649236794/lcd24064.o: ../drivers/lcd/lcd24064.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcd24064.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcd24064.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcd24064.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcd24064.o.d" -o ${OBJECTDIR}/_ext/649236794/lcd24064.o ../drivers/lcd/lcd24064.c   
	
${OBJECTDIR}/_ext/649236794/lcdOutputStream.o: ../drivers/lcd/lcdOutputStream.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcdOutputStream.o.d" -o ${OBJECTDIR}/_ext/649236794/lcdOutputStream.o ../drivers/lcd/lcdOutputStream.c   
	
${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o: ../drivers/lcd/lcdProvider_24064.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/649236794 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d 
	@${RM} ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o.d" -o ${OBJECTDIR}/_ext/649236794/lcdProvider_24064.o ../drivers/lcd/lcdProvider_24064.c   
	
${OBJECTDIR}/_ext/1868118216/MainJK330.o: ../main/JK330/MainJK330.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1868118216 
	@${RM} ${OBJECTDIR}/_ext/1868118216/MainJK330.o.d 
	@${RM} ${OBJECTDIR}/_ext/1868118216/MainJK330.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1868118216/MainJK330.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1868118216/MainJK330.o.d" -o ${OBJECTDIR}/_ext/1868118216/MainJK330.o ../main/JK330/MainJK330.c   
	
${OBJECTDIR}/_ext/760809394/menu.o: ../menu/menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760809394 
	@${RM} ${OBJECTDIR}/_ext/760809394/menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/760809394/menu.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760809394/menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/760809394/menu.o.d" -o ${OBJECTDIR}/_ext/760809394/menu.o ../menu/menu.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/JK330_MAIN_BOARD_32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
