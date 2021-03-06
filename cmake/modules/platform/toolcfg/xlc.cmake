###############################################################################
#
# (c) Copyright IBM Corp. 2017, 2017
#
#  This program and the accompanying materials are made available
#  under the terms of the Eclipse Public License v1.0 and
#  Apache License v2.0 which accompanies this distribution.
#
#      The Eclipse Public License is available at
#      http://www.eclipse.org/legal/epl-v10.html
#
#      The Apache License v2.0 is available at
#      http://www.opensource.org/licenses/apache2.0.php
#
# Contributors:
#    Multiple authors (IBM Corp.) - initial implementation and documentation
###############################################################################

set(OMR_WARNING_AS_ERROR_FLAG -qhalt=w)

list(APPEND OMR_PLATFORM_COMPILE_OPTIONS
	-qalias=noansi
	-qxflag=LTOL:LTOL0
)

if(OMR_ENV_DATA64)
	list(APPEND OMR_PLATFORM_COMPILE_OPTIONS
		-q64
	)
else()
	#-qarch should be there for 32 and 64 C/CXX flags but the C compiler is used for the assembler and it has trouble with some assembly files if it is specified
	list(APPEND OMR_PLATFORM_COMPILE_OPTIONS
		-q32
		-qarch=ppc
	)
endif()


if(OMR_HOST_OS STREQUAL "aix")
	list(APPEND OMR_PLATFORM_COMPILE_OPTIONS
		-qlanglvl=extended
		-qinfo=pro
	)
	
	set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lm -liconv -ldl -lperfstat")
	
	if(OMR_ENV_DATA64)
	set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -q64")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -q64")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -q64")
	
	set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> -X64 cr <TARGET> <LINK_FLAGS> <OBJECTS>")
	set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> -X64 cr <TARGET> <LINK_FLAGS> <OBJECTS>")
	set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> -X64 <TARGET>")
	
elseif(OMR_HOST_OS STREQUAL "linux")
	list(APPEND OMR_PLATFORM_COMPILE_OPTIONS
		-qxflag=selinux
	)
endif()

# Testarossa build variables. Longer term the distinction between TR and the rest 
# of the OMR code should be heavily reduced. In the mean time, we keep
# the distinction

# TR_COMPILE_OPTIONS are variables appended to CMAKE_{C,CXX}_FLAGS, and so 
# apply to both C and C++ compilations. 
list(APPEND TR_COMPILE_OPTIONS
	-qarch=pwr7
	-qtls 
	-qnotempinc 
	-qenum=small 
	-qmbcs 
	-qfuncsect 
	-qsuppress=1540-1087:1540-1088:1540-1090:1540-029:1500-029
	-qdebug=nscrep
)

# TR_CXX_COMPILE_OPTIONS are appended to CMAKE_CXX_FLAGS, and so apply only to
# C++ file compilation
list(APPEND TR_CXX_COMPILE_OPTIONS
	-qlanglvl=extended0x 
)

# TR_C_COMPILE_OPTIONS are appended to CMAKE_C_FLAGS, and so apply only to
# C file compilation
list(APPEND TR_C_COMPILE_OPTIONS 
)

set(SPP_CMD ${CMAKE_C_COMPILER}) 
set(SPP_FLAGS -E -P) 
