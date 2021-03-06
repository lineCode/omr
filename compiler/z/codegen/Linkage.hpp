/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2000, 2016
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

#ifndef TR_LINKAGE_INCL
#define TR_LINKAGE_INCL

#include "codegen/OMRLinkage.hpp"

#include "codegen/LinkageConventionsEnum.hpp"  // for TR_LinkageConventions
#include "infra/Annotations.hpp"               // for OMR_EXTENSIBLE

namespace TR { class CodeGenerator; }

namespace TR
{

class OMR_EXTENSIBLE Linkage : public OMR::LinkageConnector
   {
   public:

   Linkage(TR::CodeGenerator *cg, TR_S390LinkageConventions elc, TR_LinkageConventions le)
      : OMR::LinkageConnector(cg, elc, le) {}
   };
}

#endif
