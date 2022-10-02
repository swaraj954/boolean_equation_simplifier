#pragma once
#include <iostream>
#include "expres_elm.h"

class Boolean_Variable : public Expression_Element
{
public:
	bool isBooleanVariable();
	Boolean_Variable operator +(Boolean_Variable bool_var);
	Boolean_Variable operator *(Boolean_Variable bool_var);
	Boolean_Variable operator !();
	Boolean_Variable(bool, char);
	Boolean_Variable(bool);
	operator bool();
	void set_value(bool val);
private:
	bool value;
};

