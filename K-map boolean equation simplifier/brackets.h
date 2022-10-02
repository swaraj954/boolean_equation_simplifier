#pragma once
#include "expres_elm.h"

class Parenthesis :public Expression_Element
{
public:
	bool isParenthesis();
	Parenthesis(char s);
	bool is_opening_parenthsis();
	bool is_closing_parenthsis();
};
