#include <iostream>

#include "Operators.h"

Operators::Operators(char s)
	:Expression_Element(s)
{

}

bool Operators::isOperetor()
{
	return true;
}

OR::OR()
	:Operators('+')
{

}

bool OR::isUnaryOperator()
{
	return false;
}

Boolean_Variable OR::operate(Boolean_Variable b1,Boolean_Variable b2)
{
	return b1 + b2;
}

AND::AND()
	:Operators('*')
{

}

bool AND::isUnaryOperator()
{
	return false;
}

Boolean_Variable AND::operate(Boolean_Variable b1, Boolean_Variable b2)
{
	return b1 * b2;
}

COMPLEMENT::COMPLEMENT()
	:Operators('\'')
{

}

bool COMPLEMENT::isUnaryOperator()
{
	return true;
}

Boolean_Variable COMPLEMENT::operate(Boolean_Variable b1,Boolean_Variable b2)
{
	return !b1;
}

NAND::NAND()
	:Operators('^')
{

}

bool NAND::isUnaryOperator()
{
	return false;
}

Boolean_Variable NAND::operate(Boolean_Variable b1,Boolean_Variable b2)
{
	return !(b1 * b2);
}

NOR::NOR()
	:Operators('#')
{

}

bool NOR::isUnaryOperator()
{
	return false;
}

Boolean_Variable NOR::operate(Boolean_Variable b1, Boolean_Variable b2)
{
	return !(b1 + b2);
}

EXOR::EXOR()
	:Operators('@')
{

}

bool EXOR::isUnaryOperator()
{
	return false;
}

Boolean_Variable EXOR::operate(Boolean_Variable a, Boolean_Variable b)
{
	return a * (!b) + (!a) * b;
}









