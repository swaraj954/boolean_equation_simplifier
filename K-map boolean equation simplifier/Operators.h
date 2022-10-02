#pragma once
#include "bool_var.h"
#include "expres_elm.h"

class Operators:public Expression_Element
{
public:
	bool isOperetor();
	virtual Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false,'\0')) = 0;
	virtual bool isUnaryOperator() = 0;
	Operators(char s);
};


class OR :public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	OR();
};

class AND :public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	AND();
};

class COMPLEMENT :public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	COMPLEMENT();
};

class NAND : public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	NAND();
};

class NOR : public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	NOR();
};

class EXOR : public Operators
{
public:
	Boolean_Variable operate(Boolean_Variable b1, Boolean_Variable b2 = Boolean_Variable(false, '\0'));
	bool isUnaryOperator();
	EXOR();
};





