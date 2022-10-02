#pragma once
#include <vector>
#include "Group.h";


class Cell
{
public:
	Cell();
	int right;
	int down;
	bool mark;
	int max_block_size;
	bool covered;
	int covered_counter;
	void add_block(Block* b);
	void print_blocks();
	bool covered_by_one_PI_block_only();
	std::vector<Block*> blocks;
};