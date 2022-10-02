#pragma once

class Expression_Element
{
public:
	virtual bool isOperetor();
	virtual bool isBooleanVariable();
	virtual bool isParenthesis();
	Expression_Element(char s);
	char get_symbol();
	void print_symbol();
private:
	char symbol;
};

