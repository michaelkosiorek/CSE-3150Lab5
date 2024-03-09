#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "expensive_digraph_ep.h"

void expensive_digraph_ep(std::vector<std::vector<int>>& d_min_1,
                         std::vector<std::vector<int>>& d_0,
                         std::vector<std::vector<int>>& d_1)
{
    int n = d_0.size();

    for (int l=2; l <= (3*(n*n) + 1); l++) {
        for (int i=1; i <= n; i++) {
            for (int j=1; j <= n; j++) {
                for (int k=1; k <= n; k++) {
                    int i_k_of_dmin1 = get_val_at_x_y_matrix(d_min_1, i, k);
                    int k_j_of_dmin1 = get_val_at_x_y_matrix(d_min_1, k, j);
                    int k_j_of_d1 = get_val_at_x_y_matrix(d_1, k, j);
                    int i_k_of_d1 = get_val_at_x_y_matrix(d_1, i, k);
                    int k_j_of_d0 = get_val_at_x_y_matrix(d_0, k, j);
                    int i_k_of_d0 = get_val_at_x_y_matrix(d_0, i, k);

                    if (((i_k_of_dmin1 + k_j_of_d1)==0) || ((i_k_of_d1 + k_j_of_dmin1)==0)) d_0[j-1][i-1] = 0;
                    if (((i_k_of_d1 + k_j_of_d0)==1) || ((i_k_of_d0 + k_j_of_d1)==1)) d_1[j-1][i-1] = 1;
                    if (((i_k_of_dmin1 + k_j_of_d0)==-1) || ((i_k_of_d0 + k_j_of_dmin1)==-1)) d_min_1[j-1][i-1] = -1;
                }
            }
        }
    }

}


int get_val_at_x_y_matrix(const std::vector<std::vector<int>>& matrix, int x, int y) {
    if (matrix.size()==0) throw std::string("Error: Empty matrix");
    return matrix[y-1][x-1];
}


void processStream(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        std::cout << "Read from stream: " << line << std::endl;
    }
}