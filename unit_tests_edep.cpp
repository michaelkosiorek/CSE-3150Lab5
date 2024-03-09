#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "expensive_digraph_ep.h"
#include "ints_read_matrix.h"

#include <iostream>
#include <fstream>
#include <sstream>

TEST_CASE("expensive digraph exact paths tests") {

    SUBCASE("test x_y func") {
        std::vector<std::vector<int>> matrix_1 = {{1, 0, 0},
                                                  {3, -1, 0},
                                                  {0, 1, 9}};
        int matrix_1_at_1_1 = 1;
        int matrix_1_at_2_2 = -1;
        int matrix_1_at_3_3 = 9;
        CHECK_EQ(get_val_at_x_y_matrix(matrix_1, 1, 1), matrix_1_at_1_1);
        CHECK_EQ(get_val_at_x_y_matrix(matrix_1, 2, 2), matrix_1_at_2_2); 
        CHECK_EQ(get_val_at_x_y_matrix(matrix_1, 3, 3), matrix_1_at_3_3); 
    };

    SUBCASE("test x_y func 1 elem") {
        std::vector<std::vector<int>> matrix_2 = {{0}};
        int matrix_2_at_1_1 = 0;
        CHECK_EQ(get_val_at_x_y_matrix(matrix_2, 1, 1), matrix_2_at_1_1);
    };

    SUBCASE("test x_y func 1 empty") {
        std::vector<std::vector<int>> matrix_empty = {};
        REQUIRE_THROWS_AS(get_val_at_x_y_matrix(matrix_empty, 0, 0), std::string);
    };

    SUBCASE("empty matrix edep crash test") {
        std::vector<std::vector<int>> vec_1;
        std::vector<std::vector<int>> vec_2;
        std::vector<std::vector<int>> vec_3;

        expensive_digraph_ep(vec_1, vec_2, vec_3);

        CHECK_EQ(vec_1.size(), 0);
        CHECK_EQ(vec_2.size(), 0);
        CHECK_EQ(vec_3.size(), 0);
    };

    SUBCASE("test edep normal") {
        // replicating the IO function idea referenced in the assignment preamble,
        // our IO functions can take both ifstream and istringstreams.

        // to show this concept, i'll take the file input matrices in
        // using an ifstream, and create the "expected" matrices using
        // an istringstream.

        std::ifstream d_min_1s("graph_m1.txt");
        std::ifstream d_0s("graph_0.txt");
        std::ifstream d_1s("graph_1.txt");

        std::vector<std::vector<int>> d_min_1 = ints_read_matrix(d_min_1s);
        std::vector<std::vector<int>> d_0 = ints_read_matrix(d_0s);
        std::vector<std::vector<int>> d_1 = ints_read_matrix(d_1s);

        std::string d_min_1_expectedstr = "-1 -1 -1 -1 -1 -1\n-1 -1 -1 -1 -1 -1\n-1 -1 -1 -1 -1 -1\n-1 -1 -1 -1 -1 -1\n-1 -1 -1 -1 -1 -1\n -1 -1 -1 -1 -1 -1\n";
        std::string d_0_expectedstr = "0 0 0 0 0 0\n0 0 0 0 0 0\n0 0 0 0 0 0\n0 0 0 0 0 0\n0 0 0 0 0 0\n0 0 0 0 0 0\n";
        std::string d_1_expectedstr = "1 1 1 1 1 1\n1 1 1 1 1 1\n1 1 1 1 1 1\n1 1 1 1 1 1\n1 1 1 1 1 1\n1 1 1 1 1 1\n";

        std::istringstream d_min_1_expected_ss(d_min_1_expectedstr);
        std::istringstream d_0_expected_ss(d_0_expectedstr);
        std::istringstream d_1_expected_ss(d_1_expectedstr);

        std::vector<std::vector<int>> d_min_1_expected = ints_read_matrix(d_min_1_expected_ss);
        std::vector<std::vector<int>> d_0_expected = ints_read_matrix(d_0_expected_ss);
        std::vector<std::vector<int>> d_1_expected = ints_read_matrix(d_1_expected_ss);

        expensive_digraph_ep(d_min_1, d_0, d_1);

        bool all_vals_are_equal_d_m1=true;
        bool all_vals_are_equal_d1=true;
        bool all_vals_are_equal_d0=true;
        for (int row_idx=1; row_idx <= 6; row_idx++) {
            for (int column_idx=1; column_idx <= 6; column_idx++) {
                if (get_val_at_x_y_matrix(d_min_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_min_1, row_idx, column_idx)) {
                    all_vals_are_equal_d_m1=false;
                }
                if (get_val_at_x_y_matrix(d_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_1, row_idx, column_idx)) {
                    all_vals_are_equal_d1=false;
                }
                if (get_val_at_x_y_matrix(d_0_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_0, row_idx, column_idx)) {
                    all_vals_are_equal_d0=false;
                }
            }
        }
        CHECK(all_vals_are_equal_d_m1);
        CHECK(all_vals_are_equal_d1);
        CHECK(all_vals_are_equal_d0);
    };

    SUBCASE("test edep only negative paths aval") {
        // this is a case in which you only have -1 paths
        // all around a 4 node path.
        // we would expect there to be NO 0 cost or
        // 1 cost paths from one node to any other node.
        // there should also only be -1 cost paths from one
        // node to the node directly behind it.
        // therefore, the edep algorithm should NOT CHANGE
        // the any of the matrices whatsoever, as there
        // are no complex paths to be discovered.
        
        std::ifstream d_min_1s("graphN_m1.txt");
        std::ifstream d_0s("graphN_0.txt");
        std::ifstream d_1s("graphN_1.txt");

        std::vector<std::vector<int>> d_min_1 = ints_read_matrix(d_min_1s);
        std::vector<std::vector<int>> d_0 = ints_read_matrix(d_0s);
        std::vector<std::vector<int>> d_1 = ints_read_matrix(d_1s);

        std::ifstream d_min_1se("graphN_m1.txt");
        std::ifstream d_0se("graphN_0.txt");
        std::ifstream d_1se("graphN_1.txt");

        std::vector<std::vector<int>> d_min_1_expected = ints_read_matrix(d_min_1se);
        std::vector<std::vector<int>> d_0_expected = ints_read_matrix(d_0se);
        std::vector<std::vector<int>> d_1_expected = ints_read_matrix(d_1se);

        expensive_digraph_ep(d_min_1, d_0, d_1);

        bool all_vals_are_equal_d_m1=true;
        bool all_vals_are_equal_d1=true;
        bool all_vals_are_equal_d0=true;
        for (int row_idx=1; row_idx <= 4; row_idx++) {
            for (int column_idx=1; column_idx <= 4; column_idx++) {
                if (get_val_at_x_y_matrix(d_min_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_min_1, row_idx, column_idx)) {
                    all_vals_are_equal_d_m1=false;
                }
                if (get_val_at_x_y_matrix(d_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_1, row_idx, column_idx)) {
                    all_vals_are_equal_d1=false;
                }
                if (get_val_at_x_y_matrix(d_0_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_0, row_idx, column_idx)) {
                    all_vals_are_equal_d0=false;
                }
            }
        }

        CHECK(all_vals_are_equal_d_m1);
        CHECK(all_vals_are_equal_d1);
        CHECK(all_vals_are_equal_d0);
    };

    SUBCASE("barbell_10_ex") {

        std::ifstream d_min_1s("barbell_graph10_m1.txt");
        std::ifstream d_0s("barbell_graph10_0.txt");
        std::ifstream d_1s("barbell_graph10_1.txt");

        std::vector<std::vector<int>> d_min_1 = ints_read_matrix(d_min_1s);
        std::vector<std::vector<int>> d_0 = ints_read_matrix(d_0s);
        std::vector<std::vector<int>> d_1 = ints_read_matrix(d_1s);

        std::ifstream d_min_1se("barbell_graph10_m1_expected.txt");
        std::ifstream d_0se("barbell_graph10_0_expected.txt");
        std::ifstream d_1se("barbell_graph10_1_expected.txt");

        std::vector<std::vector<int>> d_min_1_expected = ints_read_matrix(d_min_1se);
        std::vector<std::vector<int>> d_0_expected = ints_read_matrix(d_0se);
        std::vector<std::vector<int>> d_1_expected = ints_read_matrix(d_1se);

        expensive_digraph_ep(d_min_1, d_0, d_1);

        bool all_vals_are_equal_d_m1=true;
        bool all_vals_are_equal_d1=true;
        bool all_vals_are_equal_d0=true;
        for (int row_idx=1; row_idx <= 10; row_idx++) {
            for (int column_idx=1; column_idx <= 10; column_idx++) {
                if (get_val_at_x_y_matrix(d_min_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_min_1, row_idx, column_idx)) {
                    all_vals_are_equal_d_m1=false;
                }
                if (get_val_at_x_y_matrix(d_1_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_1, row_idx, column_idx)) {
                    all_vals_are_equal_d1=false;
                }
                if (get_val_at_x_y_matrix(d_0_expected, row_idx, column_idx) != get_val_at_x_y_matrix(d_0, row_idx, column_idx)) {
                    all_vals_are_equal_d0=false;
                }
            }
        }
        CHECK(all_vals_are_equal_d_m1);
        CHECK(all_vals_are_equal_d1);
        CHECK(all_vals_are_equal_d0);
    };
}
