#pragma once
#include "expres_elm.h"


class Expression_Tree
{
public:
	Expression_Tree(Expression_Element* exp_elm);
	void set_left_node(Expression_Tree* node);
	void set_right_node(Expression_Tree* node);
	Expression_Tree* get_left_node();
	Expression_Tree* get_right_node();
	Expression_Element* get_data();
private:
	Expression_Tree* left_node;
	Expression_Tree* right_node;
	Expression_Element* exp_elm;
};