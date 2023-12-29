#include "functions.hpp"

#include <fstream>
#include <iostream>
std::vector<std::vector<std::string>> Process(std::string inputfile) {
  std::vector<std::vector<std::string>> output;
  std::ifstream ifs{inputfile};
  if (!ifs.is_open()) {
    std::cout << "not open" << std::endl;
  }
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> each = utilities::GetSubstrs(line, ',');
    output.push_back(each);
  }
  return output;
}

// std::map<std::string, int> count(std::string inputfile, std::string sequence)
// {
//     std::vector<std::vector<std::string>> converted = process(inputfile);
//     std::map<std::string, int> output;
//     for (unsigned long i = 1; i < converted.at(0).size(); ++i) {
//         output[converted.at(0).at(i)] = 0;
//     }
//     for (unsigned long i = 1; i < converted.at(0).size(); i++) {
//         bool stop = false;
//         int length = converted.at(0).at(i).length();
//         for (size_t j = 0; j < sequence.length(); j++) {
//             // std::cout << j << std::endl;
//             if (((j+length) <= sequence.length()) &&
//             output.contains(sequence.substr(j, length))) {
//                 if (stop == false) {
//                     output[sequence.substr(j, length)] += 1;
//                     j = j + length - 1;
//                 }
//             } else if ((!output.contains(sequence.substr(j, length))) &&
//             (output[converted.at(0).at(i)] > 0)) {
//                 stop = true;
//             }
//         }
//     }
//     return output;
// }

int CountOccurence(std::string segment, std::string sequence) {
  int span = segment.length();
  int count = 0;
  bool stop = false;
  for (unsigned long i = 0; i < sequence.length(); i++) {
    if (((i + span) <= sequence.length()) &&
        (sequence.substr(i, span) == segment)) {
      if (!stop) {
        count++;
        i = i + span - 1;
      }

    } else if ((count > 0) && sequence.substr(i, span) != segment) {
      stop = true;
      int possible =
          CountOccurence(segment, sequence.substr(i, sequence.length() - 1));
      if (possible > count) {
        count = possible;
      }
    }
  }
  return count;
}

std::string Match(std::string inputfile, std::string sequence) {
  std::vector<std::vector<std::string>> converted = Process(inputfile);
  for (unsigned long i = 1; i < converted.size(); ++i) {
    int correct = 0;
    for (unsigned long j = 1; j < converted.at(i).size(); ++j) {
      if (std::stoi(converted.at(i).at(j)) ==
          CountOccurence(converted.at(0).at(j), sequence)) {
        // std::cout << "actual " << converted.at(0).at(j)
        //           << " is: " << std::stoi(converted.at(i).at(j)) <<
        //           std::endl;
        // std::cout << "count " << converted.at(0).at(j)
        //           << " is: " << CountOccurence(converted.at(0).at(j),
        //           sequence)
        //           << std::endl;
        correct += 1;
        // std::cout << "number of correct " << correct << std::endl;
        // std::cout << "size of vec " << (int)converted.at(i).size() <<
        // std::endl;
        if (correct == (int)converted.at(i).size() - 1) {
          return converted.at(i).at(0);
        }
      }
    }
  }
  return "No match";
}