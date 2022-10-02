#pragma once
#include <vector>

class Block
{
public:
	std::vector<std::vector<int>> coordinates;
	void add_coordinate(int row, int column);
	void print();
	int get_size();
};
