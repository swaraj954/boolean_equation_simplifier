#include <iostream>


#include "brackets.h"

Parenthesis::Parenthesis(char s)
	:Expression_Element(s)
{

}

bool Parenthesis::isParenthesis()
{
	return true;
}

bool Parenthesis::is_closing_parenthsis()
{
	char brkt = get_symbol();
	if (brkt == ')' || brkt == '}' || brkt == ']')
	{
		return true;
	}
	return false;
}

bool Parenthesis::is_opening_parenthsis()
{
	char brkt = get_symbol();
	if (brkt == '(' || brkt == '{' || brkt == '[')
	{
		return true;
	}
	return false;
}