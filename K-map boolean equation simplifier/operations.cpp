#include <vector>
#include <iostream>
#include "Operators.h"


 COMPLEMENT* complement = new COMPLEMENT;
 OR* Or = new OR;
 AND* And = new AND;
 NOR* Nor = new NOR;
 NAND* Nand = new NAND;
 EXOR* Xor = new EXOR;

std::vector<Operators*> ops;
void initialize()
{
	ops.push_back(Or);//+
	ops.push_back(And);//*
	ops.push_back(Nor);//#
	ops.push_back(Nand);//^
	ops.push_back(Xor);//@
	ops.push_back(complement);//!
}