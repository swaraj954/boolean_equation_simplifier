#include <iostream>

#include "Expression_Tree.h"

Expression_Tree::Expression_Tree(Expression_Element* exp_elm)
{
	this->exp_elm = exp_elm;
	left_node = NULL;
	right_node = NULL;
}

void Expression_Tree::set_left_node(Expression_Tree* node)
{
	left_node = node;
}

void Expression_Tree::set_right_node(Expression_Tree* node)
{
	right_node = node;
}

Expression_Tree* Expression_Tree::get_left_node()
{
	return left_node;
}

Expression_Tree* Expression_Tree::get_right_node()
{
	return right_node;
}

Expression_Element* Expression_Tree::get_data()
{
	return exp_elm;
}