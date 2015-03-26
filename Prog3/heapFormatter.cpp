/****** FORMATTING BASED ON http://stackoverflow.com/questions/20922755/print-heap-array-in-tree-format ******/
//              10              
//      ||--------------||      
//       6               8      
//  ||------||      ||------||  
//   2       4       3       6  
//||--||  ||--||  ||--||  ||--||
// 0   1   3   2   2   1   0   2

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<cmath>
#include<iomanip>
#include "heapFormatter.h"
using namespace std;

// http://stackoverflow.com/questions/994593/how-to-do-an-integer-log2-in-c
// will be used to compute height of the heap
size_t heapFormatter::IntegerLogarithm2(size_t arg) {
	size_t logarithm = 0;
	while (arg >>= 1) ++logarithm;
	return logarithm;
}

// will be used to compute number of elements at the level i
size_t heapFormatter::IntegerPower2(size_t arg) {
	if (arg)
		return (size_t) 2 << (arg - 1);
	else
		return 1;
}

// returns total line length for the level
size_t heapFormatter::LineLength(size_t level, size_t item_width, size_t spaces_between) {
	return IntegerPower2(level) * (item_width + spaces_between) - spaces_between;
}

int heapFormatter::formatHeap(int input[], int size)
{
	// The input heap array
	std::vector<int> A(&input[0], &input[size]);
	// The heap array split by level
	std::vector<std::vector<int> > levels;

	// Height of the heap
	size_t levels_number = IntegerLogarithm2(A.size() + 1);
	levels.resize(levels_number);

	// Now fill the levels
	for (size_t i = 0; i < levels.size(); ++i) {
		size_t elements_number = IntegerPower2(i);
		levels[i].resize(elements_number);
		for (size_t j = elements_number - 1, p = 0; p < elements_number; ++j, ++p)
			levels[i][p] = A[j];
	}

	if (levels_number < 1) return 0;

	int magnitude = (abs(A[0]) <= 1 ? 1 : abs(A[0]));
	size_t tab_width = (size_t) floor(log(double(magnitude)) / log(10.0)) + 1;
	// size_t longest_line = LineLength(levels_number - 1, tab_width, tab_width);
	std::vector<std::string> text;
	text.reserve(levels_number * 2 - 1);

	// Do the aligned output to the strings array
	for (size_t i = 0; i < levels_number; ++i) {
		size_t outer_space_width = IntegerPower2(levels_number - 1 - i) - 1;
		size_t inner_space_width = outer_space_width * 2 + 1;
		std::string outer_space(outer_space_width * tab_width, ' ');
		std::string inner_space(inner_space_width * tab_width, ' ');

		std::ostringstream line;
		line << outer_space;

		if (i > 0) {
			std::ostringstream branchline;
			std::string joint(tab_width, '|');
			std::string branch(inner_space_width * tab_width, '-');

			branchline << outer_space;

			if (levels[i].size() > 0) {
				branchline << joint;
			}

			bool isline = true;
			for (size_t j = 1; j < levels[i].size(); ++j, isline = !isline) {
				if (isline)
					branchline << branch << joint;
				else
					branchline << inner_space << std::setfill(' ') <<
					std::setw(tab_width) << joint;
			}

			branchline << outer_space;
			text.push_back(branchline.str());
		}

		if (levels[i].size() > 0) {
			line << std::setfill(' ') << std::setw(tab_width) << levels[i][0];
		}

		for (size_t j = 1; j < levels[i].size(); ++j) {
			line << inner_space << std::setfill(' ') <<
				std::setw(tab_width) << levels[i][j];
		}

		line << outer_space;
		text.push_back(line.str());
	}
	int i;
	// Output the text
	for (auto& i : text)
		std::cout << i << std::endl;

	return 0;
}