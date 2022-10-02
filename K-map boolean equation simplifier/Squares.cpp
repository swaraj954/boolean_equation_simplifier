#include "Squares.h"
#include <iostream>

Cell::Cell()
{
	down = 1;
	right = 1;
	mark = false;
	max_block_size = 1;
	covered = false;
	covered_counter = 0;
}

void Cell::add_block(Block* b)//Needs Change
{
	if (b->get_size() == max_block_size)
	{
		blocks.push_back(b);
	}
	else
	{
		blocks = std::vector<Block*>();//Potential point of error
		blocks.push_back(b);
		max_block_size = b->get_size();
	}

}

void Cell::print_blocks()
{	
	for (int i = 0; i < blocks.size(); i++)
	{
		std::cout << "Block Address:" << blocks[i] << "\n";
		blocks[i]->print();
	}
}

bool Cell::covered_by_one_PI_block_only()//Needs Change
{
	return blocks.size() == 1;
}