//Created and Written by Swaraj Sonavane

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <stack>

#include "operations.h"
#include"Operators.h"
#include"bool_var.h"
#include "expres_elm.h"
#include "brackets.h"
#include "Expression_Tree.h"
#include "grid.h"


bool is_valid_operator(char s,Operators*& f)
{
	for (int i = 0; i < ops.size(); i++)
	{
		if (ops[i]->get_symbol() == s)
		{
			f = ops[i];
			return true;
		}
	}
	return false;
}

bool is_Parenthesis(char s)
{
	Parenthesis temp(s);
	if (temp.is_closing_parenthsis() || temp.is_opening_parenthsis())
	{
		return true;
	}
	return false;
}


bool in(const std::vector<Boolean_Variable*>& variables, char symb,int& pos)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i]->get_symbol() == symb)
		{
			pos = i;
			return true;
		}
	}
	return false;
}



std::vector<Expression_Element*> get_expression(std::string user_input,std::vector<Boolean_Variable*>& variables)
{
	Operators* op = NULL;
	std::vector<Expression_Element*> Expression;
	for (int i = 0; i < user_input.length(); i++)
	{
		if (user_input[i] == ' ')
		{
			continue;
		}
		else if (isalpha(user_input[i]))
		{
			if (Expression.size() > 0 && Expression[Expression.size() - 1]->isBooleanVariable())
			{
				Expression.push_back(And);
			}
			else if (Expression.size() > 0 && Expression[Expression.size() - 1]->isOperetor())
			{
				Operators* o = (Operators*)Expression[Expression.size() - 1];
				if (o->isUnaryOperator())
				{
					Expression.push_back(And);
				}
			}
			else if (Expression.size() > 0 && Expression[Expression.size() - 1]->isParenthesis())
			{
				Parenthesis* p = (Parenthesis*)Expression[Expression.size() - 1];
				if (p->is_closing_parenthsis())
				{
					Expression.push_back(And);
				}
			}
			int pos = -1;
			if (in(variables, user_input[i], pos))
			{
				Expression.push_back(variables[pos]);
			}
			else
			{
				Boolean_Variable* temp = new Boolean_Variable(true, user_input[i]);
				Expression.push_back(temp);
				variables.push_back(temp);
			}
		}
		else if (is_valid_operator(user_input[i], op))
		{
			Expression.push_back(op);
		}
		else if (is_Parenthesis(user_input[i]))
		{
			Parenthesis* temp = new Parenthesis(user_input[i]);
			if (Expression.size() > 0 && Expression[Expression.size() - 1]->isBooleanVariable() && temp->is_opening_parenthsis())
			{
				Expression.push_back(And);
			}
			else if (Expression.size() > 0 && Expression[Expression.size() - 1]->isParenthesis())
			{
				Parenthesis* p = (Parenthesis*)Expression[Expression.size() - 1];
				if (p->is_closing_parenthsis() && temp->is_opening_parenthsis())
				{
					Expression.push_back(And);
				}
			}
			else if (Expression.size() > 0 && Expression[Expression.size() - 1]->isOperetor() && temp->is_opening_parenthsis())
			{
				Operators* o = (Operators*)Expression[Expression.size() - 1];
				if (o->isUnaryOperator())
				{
					Expression.push_back(And);
				}
			}
			
			Expression.push_back(temp);
		}
	}
	return Expression;
}

void arrange(std::vector<Boolean_Variable*>& var)
{
	for (int i = 0; i < var.size(); i++)
	{
		int min_pos = i;
		for (int j = i + 1; j < var.size(); j++)
		{
			if (var[j]->get_symbol() < var[min_pos]->get_symbol())
			{
				min_pos = j;
			}
		}
		if (min_pos != i)
		{
			Boolean_Variable* temp = var[i];
			var[i] = var[min_pos];
			var[min_pos] = temp;
		}
	}
}

void print_expression(std::vector<Expression_Element*> exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] != And)
		{
			std::cout << exp[i]->get_symbol();
		}
	}
}

std::vector<Expression_Element*> get_sub_expression(std::vector<Expression_Element*> Expression, int start, int end)
{
	std::vector<Expression_Element*> sub_exprsn;
	for (int i = start; i <= end; i++)
	{
		sub_exprsn.push_back(Expression[i]);
	}
	return sub_exprsn;
}

int priorty(Operators* op)
{
	for (int i = 0; i < ops.size(); i++)
	{
		if (ops[i] == op)
		{
			return i;
		}
	}
	return -1;
}


Expression_Tree* get_expression_tree(std::vector<Expression_Element*> Expression)
{
	if (Expression.size() == 0)
	{
		return NULL;
	}
	if (Expression.size() == 1)
	{
		if (Expression[0]->isBooleanVariable())
		{
			Expression_Tree* ext = new Expression_Tree(Expression[0]);
			return ext;
		}
		else
		{
			return NULL;
		}
	}
	bool whole_expression_in_bracket = false;
	if (Expression[0]->isParenthesis())
	{
		bool encountered_closing_bracket = false;
		std::stack<Parenthesis*> st;
		Parenthesis* p = (Parenthesis*)Expression[0];
		st.push(p);
		for (int i = 1; i < Expression.size(); i++)
		{
			if (Expression[i]->isParenthesis())
			{
				p = (Parenthesis*)Expression[i];
				if (p->is_closing_parenthsis())
				{
					if (st.size() == 0)
					{
						return NULL;
					}
					if (i == Expression.size() - 1 && !encountered_closing_bracket)
					{
						whole_expression_in_bracket = true;
					}
					else
					{
						if (st.size() == 1)
						{
							encountered_closing_bracket = true;
						}
					}
					st.pop();
				}
				else
				{
					st.push(p);
				}
			}
		}
		if (st.size() != 0)
		{
			return NULL;
		}
	}
	if (whole_expression_in_bracket)
	{
		for (int i = 0; i < Expression.size() - 1; i++)
		{
			Expression[i] = Expression[i + 1];
		}
		Expression.pop_back();
		Expression.pop_back();
		return get_expression_tree(Expression);
	}

	int least_priorty_operator_pos = -1;
	int least_priorty;
	std::stack<Parenthesis*> stck;
	for (int i = 0; i < Expression.size(); i++)
	{
		if (Expression[i]->isParenthesis())
		{
			Parenthesis* p = (Parenthesis*)Expression[i];
			if (p->is_opening_parenthsis())
			{
				stck.push(p);
			}
			else if (p->is_closing_parenthsis())
			{
				if (stck.empty())
				{
					return NULL;
				}
				stck.pop();
			}
		}
		if (!stck.empty())
		{
			continue;
		}
		else if (Expression[i]->isOperetor())
		{
			if (least_priorty_operator_pos == -1)
			{
				least_priorty_operator_pos = i;
				least_priorty = priorty((Operators*)(Expression[i]));
			}
			else
			{
				int current_op_priorty = priorty((Operators*)(Expression[i]));
				if (current_op_priorty < least_priorty)
				{
					least_priorty_operator_pos = i;
					least_priorty = current_op_priorty;
				}
			}
		}
	}
	if (!stck.empty())
	{
		return NULL;
	}
	if (least_priorty_operator_pos == -1)
	{
		return NULL;
	}
	Operators* current_op = (Operators*) Expression[least_priorty_operator_pos];
	Expression_Tree* Root = new Expression_Tree(current_op);
	Expression_Tree* left_subtree = get_expression_tree(get_sub_expression(Expression, 0, least_priorty_operator_pos - 1));
	Expression_Tree* right_subtree = NULL;
	if (left_subtree == NULL)
	{
		return NULL;
	}
	Root->set_left_node(left_subtree);
	
	if(!current_op->isUnaryOperator())
	{
		right_subtree = get_expression_tree(get_sub_expression(Expression, least_priorty_operator_pos + 1, Expression.size() - 1));
		if (right_subtree == NULL)
		{
			return NULL;
		}
		Root->set_right_node(right_subtree);
	}
	return Root;	
}

void inorder(Expression_Tree* expression)
{
  if (expression == NULL)
  {
	  return;
  }
  inorder(expression->get_left_node());
  expression->get_data()->print_symbol();
  inorder(expression->get_right_node());
}

void preorder(Expression_Tree* expression)
{
	if (expression == NULL)
	{
		return;
	}
	expression->get_data()->print_symbol();
	preorder(expression->get_left_node());
	preorder(expression->get_right_node());
}

bool evaluate_expression(Expression_Tree* Root)
{
	if (Root->get_left_node() && Root->get_right_node())
	{
		Operators* op = (Operators*)Root->get_data();
		return op->operate(evaluate_expression(Root->get_left_node()), evaluate_expression(Root->get_right_node()));
	}
	else if (Root->get_left_node())
	{
		Operators* op = (Operators*)Root->get_data();
		return op->operate(evaluate_expression(Root->get_left_node()));
	}
	else
	{
		 return *((Boolean_Variable*)Root->get_data());
	}
}

void test(Expression_Tree* Root, std::vector<Boolean_Variable*> var,int i = 0)
{
	if (i == var.size())
	{
		for (int i = 0; i < var.size(); i++)
		{
			std::cout << (bool)*(var[i]) << " ";
		}
		std::cout << "--->";
		std::cout << evaluate_expression(Root);
		std::cout << "\n";
		return;
	}
	var[i]->set_value(false);
	test(Root, var, i+1);
	var[i]->set_value(true);
	test(Root, var, i+1);
}

void evaluate_every_possibility(Expression_Tree* Root, std::vector<Boolean_Variable*> var,std::vector<std::vector<bool>>& truth_table, int i = 0)
{
	if (i == var.size())
	{
		std::vector<bool> temp;
		for (int i = 0; i < var.size(); i++)
		{
			temp.push_back(*var[i]);
		}
		temp.push_back(evaluate_expression(Root));
		truth_table.push_back(temp);
		return;
	}
	var[i]->set_value(false);
	evaluate_every_possibility(Root, var,truth_table, i + 1);
	var[i]->set_value(true);
	evaluate_every_possibility(Root, var,truth_table, i + 1);
}


int get_decimal_equivalent(std::vector<bool> row, int start_index, int end_index)
{
	int decimal_equivalent = 0;
	bool prev_val = row[start_index];
	decimal_equivalent = decimal_equivalent + (prev_val ? pow(2, end_index - start_index) : 0);
	for (int i = start_index + 1; i <= end_index; i++)
	{
		bool current_val = row[i];
		decimal_equivalent = decimal_equivalent + (Xor->operate(prev_val, current_val) ? pow(2, end_index - i) : 0);
		prev_val = Xor->operate(current_val, prev_val);
	}

	return decimal_equivalent;

}

void print_2d_vector(std::vector<std::vector<bool>> vec)
{
	std::cout << "--------------------------------------------------\n";
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size() - 1; j++)
		{
			std::cout << vec[i][j] << " ";
		}
		std::cout << "|" << vec[i][vec[i].size() - 1]<<"\n";
	}
	std::cout << "-------------------------------------------------\n";
}

K_Map get_K_Map(std::vector<std::vector<bool>> truth_table,std::vector<Boolean_Variable*> bv)
{
	int first_half = ((truth_table[0].size() - 1) / 2) - 1;
	//std::cout << "first half:" << first_half << "\n";
	int height = pow(2,first_half + 1);
	//std::cout << "height:" << height << "\n";
	int width = (((truth_table[0].size() - 1) % 2) == 0) ? height : height * 2;
	//std::cout << "width:" << width << "\n";
	K_Map K_map(height, width,bv);
	for (int i = 0; i < truth_table.size(); i++)
	{
		if (truth_table[i][truth_table[i].size() - 1] == 1)
		{
			K_map.mark_one(get_decimal_equivalent(truth_table[i], 0, first_half), get_decimal_equivalent(truth_table[i], first_half + 1, truth_table[i].size() - 2));
		}
	}
	return K_map;
}



//                              TO DO:
//                              complete allocation of down chains      Think about how will you group the ones!               Implement the algorithm          How to not form the same block multiple times        What if a subset of essential prime implicants covers all cells?           
//                              |---------------------------------|    |----------------------------------------|             |------------------------|       |---------------------------------------------|       |--------------------------------------------------------------|
//                                         (completed)                    Few thoughts about this:                             Note:                                          (Completed)                             Example:a'bc'+a'cd+ac'd+abc
//                                                                      1) Do we really need right chains?                     1)Use Blocks* instead of                                                               Thought: Can we sort Essential prime implicants in increasing 
//                                                                      2) Remeber to check if the particluar one               block to save space																	           order then consider the first EPI(s) that cover all 
//                                                                         is already covered by a block bigger then           2)Cell needs to know its																           squares?
//                                                                         its local block size.                                 the size of the biggest
//                                                                      3) Remeber to update max only when counter is            block that covers it
//                                                                         a power of 2
//                                                                                  (Completed)                                      (Completed)
int main()
{
	//Chapter 1
	initialize();
	std::string lolo;
	std::getline(std::cin, lolo);
	std::vector<Boolean_Variable*> bv;
	std::vector<Expression_Element*> exp = (get_expression(lolo,bv));
	arrange(bv);
	//test(get_expression_tree(exp), bv);
	std::vector<std::vector<bool>> truth_table;
	evaluate_every_possibility(get_expression_tree(exp), bv, truth_table);
	
	//print_2d_vector(truth_table);
	

	//Chapter 2 begins!
	std::cout << "KMap:\n\n";
	K_Map k = get_K_Map(truth_table,bv);
	k.print();
	std::cout << "\n\n";
	//std::cout << "Blocks:\n";
	k.group_the_ones();
//	k.print_blocks();
	//std::cout << "Now testing squares point of view\n\n\n\n\n\n";
	//k.test_blocks_point_of_view();
	k.categorize_blocks();
	k.sort_EPI_blocks();
	//k.print_PIEI();

	//std::cout << "FINAL GROUPINGS....\n\n\n";
	//std::vector<std::vector<Block*>> fg = k.get_final_groupings();

	//for (int j = 0; j < fg.size(); j++)
	//{
		//for (int i = 0; i < fg[j].size(); i++)
		//{
			//fg[j][i]->print();
		//}
		//std::cout << "--------------------\n\n";
	//}

	//Code to test get_all_PI
	/*
	std::cout << "All PI Groupings:\n\n\n";
	std::vector<bool> temp_mark;
	for (int i = 0; i < 4; i++)
	{
		temp_mark.push_back(false);
	}
	std::vector<std::vector<Block*>> temp_PI_Groupings;
	k.get_all_PI_groupings(temp_mark, temp_PI_Groupings, 0);
	for (int i = 0; i < temp_PI_Groupings.size(); i++)
	{
		for (int j = 0; j < temp_PI_Groupings[0].size(); j++)
		{
			temp_PI_Groupings[i][j]->print();
		}
		std::cout << "-------------------------------------\n\n";
	}
	*/
	k.get_gray_codes();

	std::cout << "Presenting the final simplified expressions:\n\n";
	std::vector<std::vector<Expression_Element*>> finally = k.get_expressions();
	for (int i = 0; i < finally.size(); i++)
	{
		print_expression(finally[i]);
		std::cout << "\n";
	}
}