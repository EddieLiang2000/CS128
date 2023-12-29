// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

bool helper(std::vector<std::vector<int>> test, std::vector<std::vector<int>> actual) {
    for (unsigned int row = 0; row < test.size(); row++) {
        for (unsigned int col = 0; col < test.at(row).size(); col++) {
            if (test.at(row).at(col) != actual.at(row).at(col)) {
                return false;
            }
        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("ElevationDataset constructor 2w3h", "[2w3h]") { 
    ElevationDataset actual("./example-data/ex_input_data/2w3h.dat",2,3);
    std::vector<std::vector<int>> testdata = {{9,10},
                                              {8,10},
                                              {7,10}};
    REQUIRE(helper(testdata, actual.GetData()) == true);
    REQUIRE(actual.MaxEle() == 10);
    REQUIRE(actual.MinEle() == 7); 
    REQUIRE(actual.Height() == 3);
    REQUIRE(actual.Width() == 2);
}

TEST_CASE("ElevationDataset constructor 5w2h", "[5w2h]") { 
    ElevationDataset actual("./example-data/ex_input_data/5w2h.dat",5,2);
    std::vector<std::vector<int>> testdata = {{10,20,30,40,35},
                                              {25,20,15,18,20}};
    REQUIRE(helper(testdata, actual.GetData()) == true);
    REQUIRE(actual.MaxEle() == 40);
    REQUIRE(actual.MinEle() == 10); 
    REQUIRE(actual.Height() == 2);
    REQUIRE(actual.Width() == 5);
}

/////////////////////////////////////////////////////////////////////////////////////////////