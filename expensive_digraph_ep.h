#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>


void expensive_digraph_ep(std::vector<std::vector<int>>& d_min_1,
                         std::vector<std::vector<int>>& d_0,
                         std::vector<std::vector<int>>& d_1);
int get_val_at_x_y_matrix(const std::vector<std::vector<int>>& matrix, int x, int y);