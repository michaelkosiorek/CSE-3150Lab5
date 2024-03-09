#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "ints_read_matrix.h"
#include "expensive_digraph_ep.h"

std::ostream &operator<<(std::ostream &os, const std::vector<int> &input)
{
    for (auto const & i: input) {
        os << i << " ";
    }
    return os;
}

int main() {

    std::ifstream d_min_1_stream;
    d_min_1_stream.open("graph_m1.txt");

    std::ifstream d_0_stream;
    d_0_stream.open("graph_0.txt");

    std::ifstream d_1_stream;
    d_1_stream.open("graph_1.txt");

    std::vector<std::vector<int>> d_min_1 = ints_read_matrix(d_min_1_stream);
    std::vector<std::vector<int>> d_0 = ints_read_matrix(d_0_stream);
    std::vector<std::vector<int>> d_1 = ints_read_matrix(d_1_stream);

    // compute_n_matrix(d_0);
    
    int x = get_val_at_x_y_matrix(d_1, 2, 2);
    std::cout << x << std::endl;
    


    expensive_digraph_ep(d_min_1, d_0, d_1);
    
    for (vector<int> i : d_min_1) std::cout << i << std::endl;
    for (vector<int> i : d_0) std::cout << i << std::endl;
    for (vector<int> i : d_1) std::cout << i << std::endl;
    

    return 0;
}