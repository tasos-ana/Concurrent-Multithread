#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ListFGSync/listFGSync.o \
	${OBJECTDIR}/ListLazySync/listLazySync.o \
	${OBJECTDIR}/StackCG/stackCG.o \
	${OBJECTDIR}/StackCGWithElim/stackCGWithElim.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/source/client.o \
	${OBJECTDIR}/source/list.o \
	${OBJECTDIR}/source/stack.o \
	${OBJECTDIR}/source/updater.o \
	${OBJECTDIR}/source/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hy486_phasea.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hy486_phasea.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hy486_phasea ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ListFGSync/listFGSync.o: ListFGSync/listFGSync.c
	${MKDIR} -p ${OBJECTDIR}/ListFGSync
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ListFGSync/listFGSync.o ListFGSync/listFGSync.c

${OBJECTDIR}/ListLazySync/listLazySync.o: ListLazySync/listLazySync.c
	${MKDIR} -p ${OBJECTDIR}/ListLazySync
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ListLazySync/listLazySync.o ListLazySync/listLazySync.c

${OBJECTDIR}/StackCG/stackCG.o: StackCG/stackCG.c
	${MKDIR} -p ${OBJECTDIR}/StackCG
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StackCG/stackCG.o StackCG/stackCG.c

${OBJECTDIR}/StackCGWithElim/stackCGWithElim.o: StackCGWithElim/stackCGWithElim.c
	${MKDIR} -p ${OBJECTDIR}/StackCGWithElim
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StackCGWithElim/stackCGWithElim.o StackCGWithElim/stackCGWithElim.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/source/client.o: source/client.c
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/client.o source/client.c

${OBJECTDIR}/source/list.o: source/list.c
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/list.o source/list.c

${OBJECTDIR}/source/stack.o: source/stack.c
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/stack.o source/stack.c

${OBJECTDIR}/source/updater.o: source/updater.c
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/updater.o source/updater.c

${OBJECTDIR}/source/utils.o: source/utils.c
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/utils.o source/utils.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
