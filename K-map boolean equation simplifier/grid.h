#pragma once
#include <vector>
#include <iostream>
#include "Squares.h"
#include "expres_elm.h"
#include "bool_var.h"

class K_Map
{
public:
	K_Map(int height, int width,std::vector<Boolean_Variable*> bv);
	void mark_one(int row_num, int colum_num);
	void print();
	void test();
	void group_the_ones();
	void make_block(int right, int min_down,int x,int y);
	void print_blocks();
	void test_blocks_point_of_view();
	void categorize_blocks();
	bool is_essential_prime_implicant(Block*);
	bool is_prime_implicant(Block*);
	void print_PIEI();
	std::vector<std::vector<Expression_Element*>> get_expressions();
	void sort_EPI_blocks();
	void cover_block(Block* b);
	int uncovered_cells(Block* b);
	std::vector<std::vector<Block*>> get_final_groupings(std::vector<Block*>& Common_Block);
	void clean(std::vector<Block*>& covered_blocks);
	void uncover_block(Block* b);
	void get_all_PI_groupings(std::vector<bool>& mark,std::vector<std::vector<Block*>>& grp,int pos = 0);
	std::vector<std::vector<bool>> get_gray_codes();
	std::vector<Expression_Element*> extract_expression(std::vector<Block*> b,std::vector<std::vector<bool>>&);
private:
	void get_gray_code_helper(std::vector<std::vector<bool>>& gray_codes,std::vector<bool>& temp,int numb);
	std::vector<Boolean_Variable*> boolean_variables;
	std::vector<std::vector<Cell>> kmap;
	std::vector<Block*> essential_prime_implicants;
	std::vector<Block*> prime_implicants;
	std::vector<Block*> Blocks;
	int number_of_cells_covered;
	int number_of_ones;
};
