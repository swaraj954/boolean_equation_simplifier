#include "grid.h"
#include "operations.h"
#include <iostream>
#include<cassert>
#include<cmath>

void K_Map::get_gray_code_helper(std::vector<std::vector<bool>>& gray_codes, std::vector<bool>& temp,int pos = 0)
{
	if (pos == temp.size())
	{
		gray_codes.push_back(temp);
		return;
	}
	temp[pos] = false;
	get_gray_code_helper(gray_codes, temp, pos + 1);
	for (int i = gray_codes.size() - 1; i >= 0; i--)
	{
		std::vector<bool> temp2 = gray_codes[i];
		temp2[pos] = true;
		gray_codes.push_back(temp2);
	}
}

std::vector<std::vector<bool>> K_Map::get_gray_codes()
{
	int numb = kmap[0].size() > kmap.size() ? kmap[0].size() : kmap.size();
	//std::cout << "numb: "<<numb;
	std::vector<std::vector<bool>> gray_codes;
	std::vector<bool> temp(int(ceil(log(numb)/log(2))));
	//std::cout << int(ceil(log(numb) / log(2))) << "\n";
	get_gray_code_helper(gray_codes, temp);

	//Just for testing
	//for (int i = 0; i < gray_codes.size(); i++)
	//{
		//for (int j = 0; j < gray_codes[0].size(); j++)
		//{
			//if (gray_codes[i][j])
			//{
				//std::cout << "1";
			//}
			//else
			//{
				//std::cout << "0";
			//}
			//std::cout << " ";
		//}
		//std::cout << "\n";
	//}
	return gray_codes; 
}

int floor_twos_power(int x)
{
	int i = 0;
	while (true)
	{
		if (pow(2, i + 1) > x)
		{
			return pow(2, i);
		}
		else
		{
			i = i + 1;
		}
	}
}

bool is_a_power_of_2(int x)
{
	if (x == 1)
	{
		return true;
	}
	if (x % 2 == 0)
	{
		return is_a_power_of_2(x / 2);
	}
	else
	{
		return false;
	}
}

K_Map::K_Map(int height, int width,std::vector<Boolean_Variable*> bv)
{
	for (int i = 0; i < height; i++)
	{
		std::vector<Cell> temp;
		for (int i = 0; i < width; i++)
		{
			Cell new_cell;
			temp.push_back(new_cell);
		}
		kmap.push_back(temp);
	}
	number_of_cells_covered = 0;
	boolean_variables = bv;
}

void K_Map::mark_one(int row_num, int colum_num)
{
	kmap[row_num][colum_num].mark = true;
	int offset = 1;
	number_of_ones++;
	if (colum_num + offset == kmap[0].size())
	{
		offset = -colum_num;
	}
	while (kmap[row_num][colum_num + offset].mark)
	{
		if (offset == 0)
		{
			break;
		}
		kmap[row_num][colum_num].right += 1;
		offset++;
		if (colum_num + offset == kmap[0].size())
		{
			offset = -colum_num;
		}
	}
	offset = -1;
	if (colum_num + offset == -1)
	{
		offset = kmap[row_num].size() - colum_num - 1;
	}
	while (kmap[row_num][colum_num + offset].mark)
	{
		if (offset == 0)
		{
			break;
		}

		int prev_right;
		if (colum_num + offset == kmap[0].size() - 1)
		{
			prev_right = kmap[row_num][0].right;
			kmap[row_num][colum_num + offset].right = (prev_right == kmap[0].size())?prev_right:prev_right+ 1;
		}
		else
		{
			prev_right = kmap[row_num][colum_num + offset + 1].right;
			kmap[row_num][colum_num + offset].right = (prev_right == kmap[0].size()) ? prev_right : prev_right + 1;
		}

		offset--;
		if (colum_num + offset == -1)
		{
			offset = kmap[row_num].size() - colum_num - 1;
		}
	}
	offset = 1;
	if (row_num + offset == kmap.size())
	{
		offset = -row_num;
	}
	while (kmap[row_num + offset][colum_num].mark)
	{
		if (offset == 0)
		{
			break;
		}
		kmap[row_num][colum_num].down++;
		offset++;
		if (offset + row_num == kmap.size())
		{
			offset = -row_num;
		}
	}
	offset = -1;
	if (row_num + offset == -1)
	{
		offset = kmap.size() - 1 - row_num;
	}
	while (kmap[row_num+offset][colum_num].mark)
	{
		if (offset == 0)
		{
			break;
		}
		int prev_down;
		if (row_num + offset != kmap.size() - 1)
		{
			prev_down = kmap[row_num + offset + 1][colum_num].down;
			kmap[row_num + offset][colum_num].down = (prev_down == kmap.size()) ? prev_down : prev_down + 1;
		}
		else
		{
			prev_down = kmap[0][colum_num].down;
			kmap[row_num + offset][colum_num].down = (prev_down == kmap.size()) ? prev_down : prev_down + 1;
		}
		offset--;
		if (row_num + offset == -1)
		{
			offset = kmap.size() - 1 - row_num;
		}
	}
}

void K_Map::print()
{
	for (int i = 0; i < kmap.size(); i++)
	{
		for (int j = 0; j < kmap[i].size(); j++)
		{
			std::cout << kmap[i][j].mark << " ";
		}
		std::cout << "\n----------------------------------------\n";
	}
}

void K_Map::test()
{
	for (int i = 0; i < kmap.size(); i++)
	{
		for (int j = 0; j < kmap[i].size(); j++)
		{
			std::cout << "At cell (" << i << "," << j << ")\n";
			std::cout << "Value:" << kmap[i][j].mark<<"\n";
			std::cout << "Right chain:" << kmap[i][j].right << "\n";
			std::cout << "Down chain:" << kmap[i][j].down  << "\n";
			std::cout << "\n----------------------------------------\n";
		}
		
	}
}

void K_Map::make_block(int right, int min_down,int row,int column)
{
	Block* b = new Block;
	for (int i = 0; i < right; i++)
	{
		for (int j = 0; j < min_down; j++)
		{
			b->add_coordinate((row + j)%kmap.size(),(column+i)%kmap[0].size());
			//kmap[(row + j)%kmap.size()][(column + i)%kmap[0].size()].blocks.push_back(b);//Do this in a better waym
		}
	}
	bool is_sub_block = true;
	for (int i = 0; i < b->get_size(); i++)
	{
		if (kmap[b->coordinates[i][0]][b->coordinates[i][1]].max_block_size<=b->get_size())
		{
			is_sub_block = false;
			kmap[b->coordinates[i][0]][b->coordinates[i][1]].add_block(b);
		}
	}
	if (!is_sub_block)
	{
		Blocks.push_back(b);
	}
}


void K_Map::group_the_ones()
{
	for (int i = 0; i < kmap.size(); i++)
	{
		for (int j = 0; j < kmap[0].size(); j++)
		{
			//std::cout <<i<<j<< "\n";/////////////////////////////////////////////
			if (i == 2 && j == 5)////////////
			{
				int lol = 4;
				//stop
			}
			bool same_block = false;
			int min_down_required = 1;
			bool already_covered = false;
			int start = 0;

			if (!kmap[i][j].mark)//OG code (200-203)
			{
				continue;
			}
			if (kmap[i][j].right == kmap[i].size() && j!=0)
			{
				already_covered = true;
				same_block = true;
				bool break_found = false;
				for (int z = 1; z < kmap[i][j].down; z++)
				{
					
					if (kmap[(i + z) % kmap.size()][j].right == kmap[i].size() && !break_found)
					{
						min_down_required++;
					}
					else
					{
						break_found = true;
						if (is_a_power_of_2(z + 1))
						{
							same_block = false;
							break;
						}
					}
				}
			}

			if (same_block)
			{
				continue;
			}

			if (kmap[i][j].down == kmap.size() && i != 0)
			{
				same_block = true;
				bool break_found = false;
				start++;
				for (int z = 1; z < kmap[i][j].right; z++)
				{
					//Update:Bug solved
					//FIND THE BUG HERE
					//std::cout << "Here bro:" << j << "\n";////////
					//std::cout << kmap[j].size() << "\n";
					//std::cout << (j + z) % kmap[0].size() << "\n";////////
					
					if (kmap[i][(j + z) % kmap[0].size()].down == kmap.size() && !break_found)
					{
						start++;
					}
					else
					{
						break_found = true;
						if (is_a_power_of_2(z + 1))
						{
							same_block = false;
							break;
						}
					}
				}
			}
			if (same_block)
			{
				continue;
			}
			
			int min_down = floor_twos_power(kmap[i][j].down);/////////////////////
			//min_down = (min_down == kmap.size()) ? floor_twos_power(kmap.size() - i) : min_down;////////////////
			//int loop_counter = (kmap[i][j].right == kmap[i].size()) ? (kmap[i].size() - j): (kmap[i][j].right);/////////////
			int loop_counter = kmap[i][j].right;

			for (int k = start; k < loop_counter; k++)//for(int k =0;k<loop_counter;k++)<- old code
			{
				if (kmap[i][(j+k)%kmap[i].size()].down <=min_down_required)
				{
					if (!already_covered)
					{
						make_block(floor_twos_power(loop_counter), 1, i, j);
					}
					break;
				}
				else
				{
					if (floor_twos_power(kmap[i][(j + k)%kmap[i].size()].down) < min_down)
					{
						min_down = floor_twos_power(kmap[i][(j + k)%kmap[i].size()].down);
						
					}
					if (is_a_power_of_2(k+1))
					{
						make_block(k+1, min_down, i, j);
					}
				}
				
			}
		}
	}
}

void K_Map::print_blocks()
{
	for (int i = 0; i < Blocks.size(); i++)
	{
		Blocks[i]->print();
	}
}

void K_Map::test_blocks_point_of_view()
{
	for (int i = 0; i < kmap.size(); i++)
	{
		for (int j = 0; j < kmap[0].size(); j++)
		{
			std::cout << "At(" << i << "," << j << ")\n";
			kmap[i][j].print_blocks();
		}
	}
}

void K_Map::categorize_blocks()
{
	for (int i = 0; i < Blocks.size(); i++)
	{
		if (is_essential_prime_implicant(Blocks[i]))
		{
			essential_prime_implicants.push_back(Blocks[i]);
		}
		else if (is_prime_implicant(Blocks[i]))
		{
			prime_implicants.push_back(Blocks[i]);
		}
	}
}

bool K_Map::is_essential_prime_implicant(Block* b)
{
	for (int i = 0; i < b->get_size(); i++)
	{
		if (kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered_by_one_PI_block_only() && b == kmap[b->coordinates[i][0]][b->coordinates[i][1]].blocks[0])
		{
			return true;
		}
	}
	return false;
}

bool K_Map::is_prime_implicant(Block* b)
{
	for (int i = 0; i < b->get_size(); i++)
	{
		if (kmap[b->coordinates[i][0]][b->coordinates[i][1]].max_block_size == b->get_size())
		{
			return true;
		}
	}
	return false;
}

void K_Map::print_PIEI()
{
	std::cout << "---------------------------------------------------------\n";
	std::cout << "ESSENTIAL PRIME IMPLICANTS:\n";
	for (int i = 0; i < essential_prime_implicants.size();i++)
	{
		essential_prime_implicants[i]->print();
	}
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "NON ESSENTIAL PRIME IMPLICANTS:\n";
	for (int i = 0; i < prime_implicants.size(); i++)
	{
		prime_implicants[i]->print();
	}
	std::cout << "-----------------------------------------------------------------------\n";
}

void K_Map::cover_block(Block* b)
{
	for (int i = 0; i < b->get_size(); i++)
	{
		if (!kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered)
		{
			number_of_cells_covered++;
			kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered = true;
		}
		kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered_counter++;
	}
}

void K_Map::sort_EPI_blocks()
{
	for (int i = 0; i < essential_prime_implicants.size()-1; i++)
	{
		int min_size_block_pos = i;
		for (int j = i+1; j < essential_prime_implicants.size(); j++)
		{
			if (essential_prime_implicants[j]->get_size()<essential_prime_implicants[min_size_block_pos]->get_size())
			{
				min_size_block_pos = j;
			}
		}
		Block* temp = essential_prime_implicants[i];
		essential_prime_implicants[i] = essential_prime_implicants[min_size_block_pos];
		essential_prime_implicants[min_size_block_pos] = temp;
	}
}

void K_Map::uncover_block(Block* b)
{
	for (int i = 0; i < b->get_size(); i++)
	{
		assert(kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered && "Trying to uncover an uncovered cell");
		if (kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered_counter == 1)
		{
			kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered = false;
			number_of_cells_covered--;
		}
		kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered_counter--;
	}
}

//This function is most likely redundant and unnecessary
int K_Map::uncovered_cells(Block* b)
{
	int number_of_uncovered_cells = 0;
	for (int i = 0; i < b->get_size(); i++)
	{
		if (!kmap[b->coordinates[i][0]][b->coordinates[i][1]].covered)
		{
			number_of_uncovered_cells++;
		}
	}
	return number_of_uncovered_cells;
}

//Remove blocks that are redundant but eemed like essential prime implicants
void K_Map::clean(std::vector<Block*>& covered_blocks)
{
	for (int i = 0; i < covered_blocks.size(); i++)
	{
		bool is_redundant = true;
		for (int j = 0; j < covered_blocks[i]->coordinates.size(); j++)
		{
			if (kmap[covered_blocks[i]->coordinates[j][0]][covered_blocks[i]->coordinates[j][1]].covered_counter== 1)
			{
				is_redundant = false;
				break;
			}
		}
		if (is_redundant)
		{
			covered_blocks[i] = covered_blocks[covered_blocks.size() - 1];
			covered_blocks.pop_back();
			i = i - 1;
		}
	}
}

//Check this thorughly when you come back
void K_Map::get_all_PI_groupings(std::vector<bool>& mark, std::vector<std::vector<Block*>>& grp, int pos )
{
	if (pos == prime_implicants.size())
	{
		if (number_of_cells_covered != number_of_ones)
		{
			return;
		}
		std::vector<Block*> temp;
		for (int i = 0; i < mark.size(); i++)
		{
			if (mark[i])
			{
				temp.push_back(prime_implicants[i]);
			}
		}
		grp.push_back(temp);
		return;
	}
	int cells_covered_prior = number_of_cells_covered;
	cover_block(prime_implicants[pos]);
	int cells_covered_after = number_of_cells_covered;
	if (cells_covered_after == cells_covered_prior)
	{
		uncover_block(prime_implicants[pos]);//Unecessary?
		get_all_PI_groupings(mark, grp, pos + 1);
		return;

	}
	mark[pos] = true;
	if (number_of_cells_covered == number_of_ones)
	{
		get_all_PI_groupings(mark, grp, prime_implicants.size());
	}
	else
	{
		get_all_PI_groupings(mark, grp, pos + 1);
	}
	uncover_block(prime_implicants[pos]);
	mark[pos] = false;
	get_all_PI_groupings(mark, grp, pos + 1);
}

std::vector<std::vector<Block*>> K_Map::get_final_groupings(std::vector<Block*>& Common_Block)
{
	//bool all_covered = false;
	//int outer_int = 0;
	std::vector<Block*> covered_blocks;
	std::vector<std::vector<Block*>> final_groupings;

	//Wrong Approach
	/*
	while (true)
	{
		std::vector<Block*> copy;
		if (outer_int == essential_prime_implicants.size() - 1)
		{
			copy.push_back(essential_prime_implicants[essential_prime_implicants.size() - 1]);
		}
		while (outer_int < essential_prime_implicants.size() - 1 && essential_prime_implicants[outer_int]->get_size() == essential_prime_implicants[outer_int + 1]->get_size())
		{
			copy.push_back(essential_prime_implicants[outer_int]);
			outer_int = outer_int + 1;
		}

		copy.push_back(essential_prime_implicants[outer_int]);
		outer_int = outer_int + 1;

		while (copy.size() != 0)
		{
			int max_uncovered_pos = 0;
			
			for (int i = 0; i < copy.size(); i++)
			{
				if (uncovered_cells(copy[i]) == copy[i]->get_size())
				{
					max_uncovered_pos = i;
					break;
				}
				if (uncovered_cells(copy[i]) > uncovered_cells(copy[max_uncovered_pos]))
				{
					max_uncovered_pos = i;
				}
			}
			cover_block(copy[max_uncovered_pos]);
			covered_blocks.push_back(copy[max_uncovered_pos]);
			copy[max_uncovered_pos] = copy[copy.size() - 1];
			copy.pop_back();
			if (number_of_cells_covered == number_of_ones)
			{
				all_covered = true;
				break;
			}
		}
		if (outer_int == essential_prime_implicants.size() - 1)
		{
			break;
		}
	}

	if (all_covered)
	{
		final_groupings.push_back(covered_blocks);
	}
	*///Wrong Approach

	for (int i = 0; i < essential_prime_implicants.size(); i++)
	{
		cover_block(essential_prime_implicants[i]);
		covered_blocks.push_back(essential_prime_implicants[i]);
		if (number_of_cells_covered == number_of_ones)
		{
			//all_covered = true;
			clean(covered_blocks);
			Common_Block = covered_blocks;
			//final_groupings.push_back(covered_blocks);
			return final_groupings;
		}
	}
	Common_Block = covered_blocks;

	std::vector<bool> mark;
	for (int i = 0; i < prime_implicants.size(); i++)
	{
		mark.push_back(false);
	}

	std::vector<std::vector<Block*>> all_PI_Combinations;
	get_all_PI_groupings(mark, all_PI_Combinations);
	return all_PI_Combinations;
	//Space Consuming Approach
	/*
	for (int i = 0; i < all_PI_Combinations.size(); i++)
	{
		std::vector<Block*> copy_of_covered_blocks = covered_blocks;
		for (int j = 0; j < all_PI_Combinations[i].size(); j++)
		{
			copy_of_covered_blocks.push_back(all_PI_Combinations[i][j]);
		}
		final_groupings.push_back(copy_of_covered_blocks);
	}
	*/
	
}

std::vector<Expression_Element*> K_Map::extract_expression(std::vector<Block*> given_blocks,std::vector<std::vector<bool>>& gray_codes)
{
	std::vector<Expression_Element*> extracted_expression;
	for (int i = 0; i < given_blocks.size(); i++)
	{
		int offset = kmap.size() < kmap[0].size() ? 1 : 0;
		if (given_blocks[i]->get_size() == 1)
		{
			std::vector<bool> row_gray_code = gray_codes[given_blocks[i]->coordinates[i][0]];
			std::vector<bool> column_gray_code = gray_codes[given_blocks[i]->coordinates[i][1]];
			for (int x = offset; x < row_gray_code.size(); x++)
			{
				extracted_expression.push_back(boolean_variables[x - offset]);
				if (!row_gray_code[x])
				{
					extracted_expression.push_back(complement);
				}

				extracted_expression.push_back(And);

			}
			for (int x = 0; x < column_gray_code.size(); x++)
			{
				extracted_expression.push_back(boolean_variables[x + boolean_variables.size() / 2]);
				if (!column_gray_code[x])
				{
					extracted_expression.push_back(complement);
				}
				if (x != column_gray_code.size() - 1)
				{
					extracted_expression.push_back(And);
				}
			}
			continue;
		}

		int number_of_rows = 1;
		int x = 1;
		std::vector<bool> previous_row_gray_code = gray_codes[given_blocks[i]->coordinates[0][0]];
		std::vector<int> frequency_counter;

		for (int z = 0; z < previous_row_gray_code.size(); z++)
		{
			frequency_counter.push_back(1);
		}

		if (offset == 1)
		{
			frequency_counter[0] = 0;
		}

		while (x < given_blocks[i]->get_size() && given_blocks[i]->coordinates[x - 1][1] == given_blocks[i]->coordinates[x][1])
		{
			number_of_rows++;
			std::vector<bool> current_row_gray_code = gray_codes[given_blocks[i]->coordinates[x][0]];
			for (int y = 0; y < current_row_gray_code.size(); y++)
			{
				if (frequency_counter[y] == 0)
				{
					continue;
				}
				if (current_row_gray_code[y] == previous_row_gray_code[y])
				{
					frequency_counter[y]++;
				}
				else
				{
					frequency_counter[y] = 0;
				}
			}
			previous_row_gray_code = current_row_gray_code;
			x++;
		}

		for (int z = offset; z < frequency_counter.size(); z++)
		{
			if (frequency_counter[z] == number_of_rows)
			{
				extracted_expression.push_back(boolean_variables[z - offset]);
				if (!previous_row_gray_code[z])
				{
					extracted_expression.push_back(complement);
				}
				extracted_expression.push_back(And);
			}
		}
		x = 0;
		int number_of_columns = 1;
		std::vector<bool> previous_column_gray_code = gray_codes[given_blocks[i]->coordinates[x][1]];
		for (int i = 0; i < frequency_counter.size(); i++)
		{
			frequency_counter[i] = 1;
		}
		x = x + number_of_rows;
		while (x < given_blocks[i]->get_size())
		{
			number_of_columns++;
			std::vector<bool> current_column_gray_code = gray_codes[given_blocks[i]->coordinates[x][1]];
			for (int y = 0; y < current_column_gray_code.size(); y++)
			{
				if (frequency_counter[y] == 0)
				{
					continue;
				}
				if (current_column_gray_code[y] == previous_column_gray_code[y])
				{
					frequency_counter[y]++;
				}
				else
				{
					frequency_counter[y] = 0;
				}


			}
			previous_column_gray_code = current_column_gray_code;
			x = x + number_of_rows;
		}

		for (int z = 0; z < frequency_counter.size(); z++)
		{
			if (frequency_counter[z] == number_of_columns)
			{
				extracted_expression.push_back(boolean_variables[z + boolean_variables.size() / 2]);
				if (!previous_column_gray_code[z])
				{
					extracted_expression.push_back(complement);
				}
				extracted_expression.push_back(And);
			}

		}
		while (extracted_expression[extracted_expression.size() - 1] == And)
		{
			extracted_expression.pop_back();
		}
		if (i != given_blocks.size() - 1)
		{
			extracted_expression.push_back(Or);
		}
	}
	return extracted_expression;
}

std::vector<std::vector<Expression_Element*>> K_Map::get_expressions()
{
	std::vector<std::vector<Expression_Element*>> final_res;
	std::vector<Block*> common_blocks;
	std::vector<std::vector<Block*>> PI_combos = get_final_groupings(common_blocks);
	std::vector<std::vector<bool>> gray_codes = get_gray_codes();
	std::vector<Expression_Element*> essential_part_of_expression;
	essential_part_of_expression = extract_expression(common_blocks,gray_codes);
	if (PI_combos.size() == 0)
	{
		final_res.push_back(essential_part_of_expression);
		return final_res;
	}
	std::vector<Expression_Element*> temp;
	for (int i = 0; i < PI_combos.size(); i++)
	{
		temp = extract_expression(PI_combos[i], gray_codes);
		std::vector<Expression_Element*> epoe_copy = essential_part_of_expression;
		epoe_copy.push_back(Or);
		for (int x = 0; x < temp.size(); x++)
		{
			epoe_copy.push_back(temp[x]);
		}

		final_res.push_back(epoe_copy);
		
	}

	return final_res;
}







