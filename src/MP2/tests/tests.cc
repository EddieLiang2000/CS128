// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop disk to board once", "[Disk_Drop]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop same disk to board twice same column", "[Disk_Drop]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop different disks to board different columns", "[Disk_Drop]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop disk out of lower bound", "[Disk_Drop]") {
  Board student;
  InitBoard(student);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -1), 
                    std::runtime_error);
}

TEST_CASE("Drop disk out of upper bound", "[Disk_Drop]") {
  Board student;
  InitBoard(student);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 7),
                    std::runtime_error);
}

TEST_CASE("Drop disk to filled column", "[Disk_Drop]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 3),
                    std::runtime_error);
}

//THE FUNCTION MADE 80 TO 90
TEST_CASE("Search for winner one leftdiag two rightdiag", "[Winner_Search]") {
  Board output;
  InitBoard(output);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer1, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer1, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer1, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer1, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer1, 5);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kLeftDiag) == true);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kRightDiag) == true);
}

//FROM 90 to 100
TEST_CASE("Search for winner but tie", "[Winner_Search]") {
  Board output;
  InitBoard(output);
  DropDiskToBoard(output, DiskType::kPlayer2, 0);
  DropDiskToBoard(output, DiskType::kPlayer1, 0);
  DropDiskToBoard(output, DiskType::kPlayer2, 0);
  DropDiskToBoard(output, DiskType::kPlayer2, 0);
  DropDiskToBoard(output, DiskType::kPlayer2, 0);
  DropDiskToBoard(output, DiskType::kPlayer1, 0);
  DropDiskToBoard(output, DiskType::kPlayer1, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 1);
  DropDiskToBoard(output, DiskType::kPlayer1, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 2);
  DropDiskToBoard(output, DiskType::kPlayer1, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 2);
  DropDiskToBoard(output, DiskType::kPlayer1, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer1, 4);
  DropDiskToBoard(output, DiskType::kPlayer1, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer2, 4);
  DropDiskToBoard(output, DiskType::kPlayer1, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer1, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 5);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer1, 6);
  DropDiskToBoard(output, DiskType::kPlayer2, 6);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
}

//THE FUNCTION WENT FROM 60 TO 80
TEST_CASE("Search for winner both rightdiag", "[Winner_Search]") {
  Board output;
  InitBoard(output);
  DropDiskToBoard(output, DiskType::kPlayer1, 0);
  DropDiskToBoard(output, DiskType::kPlayer1, 1);
  DropDiskToBoard(output, DiskType::kPlayer1, 1);
  DropDiskToBoard(output, DiskType::kPlayer1, 2);
  DropDiskToBoard(output, DiskType::kPlayer1, 2);
  DropDiskToBoard(output, DiskType::kPlayer1, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer1, 3);
  DropDiskToBoard(output, DiskType::kPlayer2, 0);
  DropDiskToBoard(output, DiskType::kPlayer2, 1);
  DropDiskToBoard(output, DiskType::kPlayer2, 2);
  DropDiskToBoard(output, DiskType::kPlayer2, 3);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer1, WinningDirection::kRightDiag) == true);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kRightDiag) == true);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(output, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
}

TEST_CASE("Board location in bounds", "[In_Bound]") {
  REQUIRE(BoardLocationInBounds(0, 0) == true);
  REQUIRE(BoardLocationInBounds(0, 6) == true);
  REQUIRE(BoardLocationInBounds(5, 0) == true);
  REQUIRE(BoardLocationInBounds(5, 6) == true);
  REQUIRE(BoardLocationInBounds(-1, 5) == false);
  REQUIRE(BoardLocationInBounds(0, 7) == false);
  REQUIRE(BoardLocationInBounds(-1, 7) == false);
}