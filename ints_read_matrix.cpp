#include <istream>
#include <sstream>
#include <vector>

#include "ints_read_vector.h"
#include "ints_read_matrix.h"

using namespace std;

vector<vector<int>> ints_read_matrix(istream & in_stream) {
    vector<vector<int>> matrix;
    string line;
    
    int row = 0;
    while (! in_stream.eof() ) {
        vector<int> line = ints_read_one_line(in_stream);
        matrix.push_back(line);
    }

    return matrix;
}