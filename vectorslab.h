#ifndef _VECTORS_LAB_
#define _VECTORS_LAB_

#include <istream>
#include <vector>

using namespace std;

vector<double> doubles_read_vector(istream & in_stream);
vector<double> doubles_read_one_line(istream & in_stream);
vector<vector<double>> doubles_read_matrix(istream & in_stream);
double magnitude(vector<double> v);
double dotproduct(vector<double> v1, vector<double> v2);
double cosdistance(vector<double> v1, vector<double> v2);
void finalprint(vector<vector<double>> v);
vector<vector<double>> pairwisecos(vector<vector<double>> v);

#endif