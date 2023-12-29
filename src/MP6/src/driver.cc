#include "illini_book.hpp"

// check for includes!!
#include <iostream>
int main() {
  IlliniBook test("example/persons.csv", "example/relations.csv");

  // std::cout << test.GetRelated(1,6,"124") << std::endl;
  
  // for (unsigned int i = 0; i < adj.size(); i++) {
  //   std::cout << adj.at(i) << std::endl;
  // }
  // std::cout << test.CountGroups({"124", "173", "128"}) << std::endl;
  std::map<int,int> m = test.BFS(9);
  
  for (auto it = m.cbegin(); it != m.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }
  std::cout << test.CountGroups({"124","128","173"}) <<std::endl;
  // std::cout << std::to_string(test.AreRelated(1,6, "124")) << std::endl;
  // std::cout << test.GetRelated(1,6,"128") << std::endl;
  // std::vector<int> steps = test.GetSteps(1, 2);
  // for (auto ele:steps) {
  //   std::cout << ele << std::endl;
  // }
  // std::cout << test.relations_.size() << std::endl;
  // std::cout << test.CountGroups(std::vector<std::string>{ "128", "173","124" }) << std::endl;
  return 0;
}
