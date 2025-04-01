#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

#include "vectorslab.h"

TEST_CASE("doubles_read_matrix") { // this test case was given - just modified it for doubles instead of ints
  
    SUBCASE("doubles_read_matrix : edge cases - istringstream") {
      istringstream istr_0("");
      vector<vector<double>> matrix_0 = doubles_read_matrix(istr_0);
      CHECK(0 == matrix_0.size());
    
      istringstream istr_99("-99");
      vector<vector<double>> matrix_99 = doubles_read_matrix(istr_99);
      CHECK(-99 == matrix_99[0][0]);
      CHECK(1 == matrix_99.size());
      CHECK(1 == matrix_99[0].size());
    };
    
    SUBCASE("doubles_read_matrix : small cases") {
  
      istringstream istr("0 1 2\n4 5 6\n7 8 9");
      vector<vector<double>> matrix = doubles_read_matrix(istr);
      CHECK(0 == matrix[0][0]);
      CHECK(1 == matrix[0][1]);
      CHECK(2 == matrix[0][2]);
      CHECK(3 == matrix.size());
      CHECK(3 == matrix[0].size());
      CHECK(3 == matrix[2].size());
  
    };
}

TEST_CASE("magnitude") {
    vector<double> v1 = {1, 1, 1};
    vector<double> v2 = {1, 1, 0};
    CHECK(magnitude(v1) == sqrt(3));
    CHECK(magnitude(v2) == sqrt(2));
}

TEST_CASE("dotproduct") {
    vector<double> v1 = {1, 1, 1};
    vector<double> v2 = {1, 1, 0};
    CHECK(dotproduct(v1, v2) == 2);

}

TEST_CASE("cosdistance") {
    vector<double> v1 = {1, 1, 1};
    vector<double> v2 = {1, 1, 0};
    CHECK(cosdistance(v1, v2) == doctest::Approx(0.61548).epsilon(0.0001));

    vector<double> v3 = {1, 2.5, 0.5}; // 0
    vector<double> v4 = {1, 3.6, 1.9}; // 1
    vector<double> v5 = {1, 4.5, 3.2}; // 2
    vector<double> v6 = {2.7, 7, 6}; // 3
    vector<double> v7 = {9, 11.5, 22.99}; // 4
    CHECK(cosdistance(v3, v4) == doctest::Approx(0.304862).epsilon(0.0001)); // 0 1 - for comparison to given answers
    CHECK(cosdistance(v3, v5) == doctest::Approx(0.44821).epsilon(0.0001)); // 0 2
    CHECK(cosdistance(v3, v6) == doctest::Approx(0.491088).epsilon(0.0001)); // 0 3
    CHECK(cosdistance(v3, v7) == doctest::Approx(0.84968).epsilon(0.0001)); // 0 4
    CHECK(cosdistance(v4, v5) == doctest::Approx(0.143536).epsilon(0.0001)); // 1 2
    CHECK(cosdistance(v4, v6) == doctest::Approx(0.219741).epsilon(0.0001)); // 1 3
    CHECK(cosdistance(v4, v7) == doctest::Approx(0.6022).epsilon(0.0001)); // 1 4
    CHECK(cosdistance(v5, v6) == doctest::Approx(0.137566).epsilon(0.0001)); // 2 3
    CHECK(cosdistance(v5, v7) == doctest::Approx(0.497381).epsilon(0.0001)); // 2 4
    CHECK(cosdistance(v6, v7) == doctest::Approx(0.382501).epsilon(0.0001)); // 3 4

}

TEST_CASE("pairwisecos") {
    vector<vector<double>> input = {
        {1, 2.5, 0.5}, // 0
        {1, 3.6, 1.9}, // 1
        {1, 4.5, 3.2}, // 2
        {2.7, 7, 6},   // 3
        {9, 11.5, 22.99} // 4
    };

    vector<vector<double>> expected = {
        {0.137566, 2, 3},
        {0.137566, 3, 2},
        {0.143536, 1, 2},
        {0.143536, 2, 1},
        {0.219741, 1, 3},
        {0.219741, 3, 1},
        {0.304862, 0, 1},
        {0.304862, 1, 0},
        {0.382501, 3, 4},
        {0.382501, 4, 3},
        {0.44821, 0, 2},
        {0.44821, 2, 0},
        {0.491088, 0, 3},
        {0.491088, 3, 0},
        {0.497381, 2, 4},
        {0.497381, 4, 2},
        {0.6022, 1, 4},
        {0.6022, 4, 1},
        {0.84968, 0, 4},
        {0.84968, 4, 0}
    };

    vector<vector<double>> result = pairwisecos(input);

    for (size_t i = 0; i < expected.size(); i++) {
        CHECK(doctest::Approx(result[i][0]).epsilon(0.0001) == expected[i][0]); 
        CHECK((result[i][1] == expected[i][1] && result[i][2] == expected[i][2]));
    }
}

TEST_CASE("Test Pairwise Cosine Distances with File Input") {
    printf("\n"); // separating output from output of previous test
    const string file = "testfile.txt";

    std::ifstream file2(file);
    vector<vector<double>> v = doubles_read_matrix(file2);

    CHECK(v.size() > 0);

    vector<vector<double>> expected = {
        {0.604261, 0, 2},
        {0.604261, 2, 0},
        {0.605516, 1, 3},
        {0.605516, 3, 1},
        {1.03285, 0, 3},
        {1.03285, 3, 0},
        {1.25817, 0, 1},
        {1.25817, 1, 0},
        {1.4635, 2, 3},
        {1.4635, 3, 2},
        {1.72212, 1, 2},
        {1.72212, 2, 1}
    };

    vector<vector<double>> result = pairwisecos(v);
    CHECK(result.size() == expected.size());

    for (size_t i = 0; i < expected.size(); i++) {
        CHECK(doctest::Approx(result[i][0]).epsilon(0.0001) == expected[i][0]); 
        CHECK((result[i][1] == expected[i][1] && result[i][2] == expected[i][2]));
    }

    CHECK(result.size() > 0);
}