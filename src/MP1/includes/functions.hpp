#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
std::vector<std::vector<std::string>> Process(std::string inputfile);
// std::map<std::string, int> count(std::string inputfile, std::string
// sequence);
std::string Match(std::string inputfile, std::string sequence);
int CountOccurence(std::string segment, std::string sequence);
#endif