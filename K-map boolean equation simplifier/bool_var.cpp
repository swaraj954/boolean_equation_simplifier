#include "bool_var.h"

Boolean_Variable::Boolean_Variable(bool val, char symb)
	:Expression_Element(symb)
{
	value = val;
}

Boolean_Variable::Boolean_Variable(bool val)
	:Expression_Element('\0')
{
	value = val;
}

Boolean_Variable Boolean_Variable::operator+(Boolean_Variable b)
{
	Boolean_Variable res ( (value || b.value),'\0');
	return res;
}

Boolean_Variable Boolean_Variable::operator*(Boolean_Variable b)
{
	Boolean_Variable res((value && b.value), '\0');
	return res;
}

Boolean_Variable Boolean_Variable::operator!()
{
	Boolean_Variable res(!value, '\0');
	return res;
}

bool Boolean_Variable::isBooleanVariable()
{
	return true;
}

Boolean_Variable::operator bool()
{
	return value;
}

void Boolean_Variable::set_value(bool val)
{
	value = val;
}
