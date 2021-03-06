/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2015, 2017
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

#ifndef UDT_HPP
#define UDT_HPP

#include "ddr/config.hpp"

#include <vector>

#include "ddr/ir/Members.hpp"
#include "ddr/ir/Macro.hpp"
#include "ddr/ir/Type.hpp"

class UDT : public Type
{
public:
	NamespaceUDT *_outerNamespace;
	unsigned int _lineNumber;

	UDT(size_t size, unsigned int lineNumber = 0);
	virtual ~UDT();

	virtual string getFullName();
	virtual void checkDuplicate(Symbol_IR *ir);
	virtual NamespaceUDT * getNamespace();

	bool operator==(Type const & rhs) const;
	virtual bool compareToUDT(UDT const &) const;
};

#endif /* UDT_HPP */
