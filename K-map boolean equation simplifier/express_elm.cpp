#include <iostream>
#include "expres_elm.h"

Expression_Element::Expression_Element(char s)
{
	symbol = s;
}

char Expression_Element::get_symbol()
{
	return symbol;
}

void Expression_Element::print_symbol()
{
	std::cout << symbol;
}

bool Expression_Element::isBooleanVariable()
{
	return false;
}

bool Expression_Element::isOperetor()
{
	return false;
}

bool Expression_Element::isParenthesis()
{
	return false;
}