###############################################################################
#
# (c) Copyright IBM Corp. 2015, 2017
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

top_srcdir = ../../..
include $(top_srcdir)/omrmakefiles/configure.mk

MODULE_NAME := ddr-scanner
ARTIFACT_TYPE := archive

MODULE_INCLUDES = \
  $(top_srcdir)/ddr/include \
  $(top_srcdir)/include_core

ifeq (gcc,$(OMR_TOOLCHAIN))
  MODULE_CXXFLAGS += -frtti -D__STDC_LIMIT_MACROS -std=c++0x
endif

ifeq (msvc,$(OMR_TOOLCHAIN))
  MODULE_CXXFLAGS += /EHsc
endif

OBJECTS = Scanner$(OBJEXT)

ifneq (,$(findstring pdb,$(DEBUG_FORMAT)))
  OBJECTS += pdb/PdbScanner$(OBJEXT)
  MODULE_STATIC_LIBS += diaguids.lib
endif

ifneq (,$(findstring dwo,$(DEBUG_FORMAT)))
  OBJECTS += dwarf/DwarfScanner$(OBJEXT)
endif

ifeq (osx,$(OMR_HOST_OS))
  OBJECTS += dwarf/DwarfParser$(OBJEXT) \
    dwarf/DwarfFunctions$(OBJEXT)
endif

ifeq (aix,$(OMR_HOST_OS))
  OBJECTS += dwarf/AixSymbolTableParser$(OBJEXT) \
    dwarf/DwarfFunctions$(OBJEXT)
endif

include $(top_srcdir)/omrmakefiles/rules.mk
