#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (unsigned row = 0; row < Board::kBoardHeight; row++) {
    for (unsigned col = 0; col < Board::kBoardWidth; col++) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("Column Out of Bound");
  }
  for (int currentrow = 0; currentrow <= Board::kBoardHeight; currentrow++) {
    if (currentrow == Board::kBoardHeight) {
      throw std::runtime_error("Column Filled");
    } else if (b.board[currentrow][col] == DiskType::kEmpty) {
      b.board[currentrow][col] = disk;
      break;
    }
  }
  CheckForWinner(b, disk);
}

bool CheckForWinner(Board& b, DiskType disk) {
  if (disk == DiskType::kEmpty) {
    return false;
  }
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal &&
      SearchForWinnerHorizontal(b, disk)) {
    return true;
  }
  if (to_check == WinningDirection::kVertical &&
      SearchForWinnerVertical(b, disk)) {
    return true;
  }
  if (to_check == WinningDirection::kLeftDiag &&
      SearchForWinnerLeftDiag(b, disk)) {
    return true;
  }
  if (to_check == WinningDirection::kRightDiag &&
      SearchForWinnerRightDiag(b, disk)) {
    return true;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  bool check = false;
  if (row < 0 || row > Board::kBoardHeight - 1 || col < 0 ||
      col > Board::kBoardWidth - 1) {
    check = false;
  }
  if (row >= 0 && row <= Board::kBoardHeight - 1 && col >= 0 &&
      col <= Board::kBoardWidth - 1) {
    check = true;
  }
  return check;
}

bool SearchForWinnerHorizontal(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; row++) {
    int count = 0;
    for (int col = 0; col < Board::kBoardWidth; col++) {
      if (b.board[row][col] == disk) {
        count += 1;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}

bool SearchForWinnerVertical(Board& b, DiskType disk) {
  for (int col = 0; col < Board::kBoardWidth; col++) {
    int count = 0;
    for (int row = 0; row < Board::kBoardHeight; row++) {
      if (b.board[row][col] == disk) {
        count += 1;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}

bool SearchForWinnerLeftDiag(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight - 3; row++) {
    for (int col = 3; col < Board::kBoardWidth; col++) {
      if (b.board[row][col] == disk && b.board[row + 1][col - 1] == disk &&
          b.board[row + 2][col - 2] == disk &&
          b.board[row + 3][col - 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool SearchForWinnerRightDiag(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight - 3; row++) {
    for (int col = 0; col < Board::kBoardWidth - 3; col++) {
      if (b.board[row][col] == disk && b.board[row + 1][col + 1] == disk &&
          b.board[row + 2][col + 2] == disk &&
          b.board[row + 3][col + 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}