#include <istream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "vectorslab.h"

using namespace std;

vector<double> doubles_read_vector(istream & in_stream) { // given
    vector<double> res;
    for(double i; in_stream >> i; ) {
        res.push_back(i);
    }

    return res;
}

vector<double> doubles_read_one_line(istream & in_stream) { // given
    vector<double> res;
    string line;
    
    getline(in_stream, line);
    istringstream is(line);
    string next;
    while (is >> next) {
        res.push_back(stod(next));
    }

    return res;
}

vector<vector<double>> doubles_read_matrix(istream & in_stream) { // given function
    vector<vector<double>> matrix;
    string line;

    while (getline(in_stream, line)) { // modifying to try to fix an error
        istringstream is_line(line);
        vector<double> row = doubles_read_vector(is_line);
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }

    return matrix;
}

double magnitude(vector<double> v) { // squre root of the sum of the square of all the numbers
    double sum = 0.0;

    for(double elem : v) {
        sum = sum + (elem * elem);
    }

    return sqrt(sum);
}
double dotproduct(vector<double> v1, vector<double> v2) {
    double sum = 0.0;
    for (int i = 0; i < v1.size(); i++) {
        sum = sum + (v1[i] * v2[i]);
    }
    return sum;
}
double cosdistance(vector<double> v1, vector<double> v2) {
    double mag1 = magnitude(v1);
    double mag2 = magnitude(v2);

    double dp = dotproduct(v1, v2);
    double send = mag1 * mag2;
    send = dp / send;

    double final = acos(send);
    
    return final;
}

void finalprint(vector<vector<double>> v) {
    for (int x = 0; x < v.size(); x++) {
        printf("%d %d cos dist = %f \n", int(v[x][1]), int(v[x][2]), v[x][0]);
    }
}

vector<vector<double>> pairwisecos(vector<vector<double>> v) {
    vector<vector<double>> dis;
    int disindex = 0;
    for (int x = 0; x < v.size(); x++) { 
        for (int i = 0; i < v.size(); i++) {
            if (i != x) {
                double tempdist = cosdistance(v[x], v[i]);
                dis.push_back({tempdist, double(x), double(i)}); // put tempdist 1st to make sorting easier - cast to double to fit format
                disindex++;
            }
        }
    }

    // SORT THE VECTOR BASED ON THE LAST VAL IN THE VECTOR - do not need to remove duplicates
    sort(dis.begin(), dis.end());

    finalprint(dis); // prints everything in order

    return dis;

}
