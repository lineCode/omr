/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2000, 2017
 *
 *  This program and the accompanying materials are made available
 *  under the terms of the Eclipse Public License v1.0 and
 *  Apache License v2.0 which accompanies this distribution.
 *
 *      The Eclipse Public License is available at
 *      http://www.eclipse.org/legal/epl-v10.html
 *
 *      The Apache License v2.0 is available at
 *      http://www.opensource.org/licenses/apache2.0.php
 *
 * Contributors:
 *    Multiple authors (IBM Corp.) - initial implementation and documentation
 *******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "codegen/FrontEnd.hpp"
#include "codegen/OMRMachine.hpp"
#include "compile/Compilation.hpp"
#include "env/jittypes.h"
#include "infra/Assert.hpp"


/** \brief
  *    Encode a BRC / BRCL at \p locationAddr to branch to \p destinationAddr.
  *
  * \param locationAddr
  *    The location to patch.
  *
  * \param destinationAddr
  *    The destination of the branch target.
  *
  * \param smpFlag
  *    N/A.
  *
  * \note
  *    It is up to the caller to ensure that if a NOP BRC / BRCL does not exist at \p locationAddr then a non-atomic
  *    4 or 6 byte (depending on distance between \p locationAddr and \p destinationAddr) store to the instruction
  *    stream at \p locationAddr is safe.
  */
extern "C" void _patchVirtualGuard(uint8_t* locationAddr, uint8_t* destinationAddr, int32_t smpFlag)
   {
   volatile uint8_t* volatileLocationAddr = locationAddr;

   static bool debugTrace = debug("traceVGNOP") != NULL;

   if (debugTrace)
      {
      printf("####> Patching VGNOP at locationAddr %p (%x), destinationAddr %p (%x), smpFlag: %d\n", volatileLocationAddr, *reinterpret_cast<volatile intptrj_t*>(volatileLocationAddr), destinationAddr, *reinterpret_cast<intptrj_t*>(destinationAddr), smpFlag);
      }

   int64_t displacement = static_cast<int64_t>(destinationAddr - volatileLocationAddr) / 2;

   // If there is a NOP BRC / BRCL at locationAddr the application could be asynchronously executing this branch as
   // we are patching it. Because the caller / codegen ensured this branch will never execute if it is to be patched
   // asynchronously, modifying the displacement first should always be valid. Thus we modify the displacement first,
   // and then activate the branch mask to avoid any potential race conditions.
   if (displacement >= MIN_IMMEDIATE_VAL && displacement <= MAX_IMMEDIATE_VAL)
      {
      // Note the 0 mask value
      volatileLocationAddr[1] = 0x04;

      volatileLocationAddr[0] = 0xA7;
      volatileLocationAddr[2] = (displacement & 0xFF00) >> 8;
      volatileLocationAddr[3] = (displacement & 0x00FF);
      }
   else
      {
      // Note the 0 mask value
      volatileLocationAddr[1] = 0x04;

      volatileLocationAddr[0] = 0xC0;
      volatileLocationAddr[2] = (displacement & 0xFF000000) >> 24;
      volatileLocationAddr[3] = (displacement & 0x00FF0000) >> 16;
      volatileLocationAddr[4] = (displacement & 0x0000FF00) >> 8;
      volatileLocationAddr[5] = (displacement & 0x000000FF);
      }

   // Modify the mask value to an always taken branch (after modifying displacement - order matters; see above)
   volatileLocationAddr[1] = 0xF4;
   }
