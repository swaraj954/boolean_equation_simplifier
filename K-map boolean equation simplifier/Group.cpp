#include "Group.h"

#include <iostream>

void Block::add_coordinate(int row_num, int colum_num)
{
	std::vector<int> cord;
	cord.push_back(row_num);
	cord.push_back(colum_num);
	coordinates.push_back(cord);
}

void Block::print()
{
	std::cout << "---------------------\n";
	for (int i = 0; i < coordinates.size(); i++)
	{
		std::cout << coordinates[i][0] << "," << coordinates[i][1] << "\n";
	}
	std::cout << "----------------------------\n";
}

int Block::get_size()
{
	return coordinates.size();
}