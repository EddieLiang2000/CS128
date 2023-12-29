#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <map>
#include "utilities.hpp"

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

  // int GetIndex(const int& uin) const;
  // std::vector<int> GetAdjacencyList(const int& uin) const;
  // std::vector<int> GetAdjacencyList(const int& uin, const std::string& relation) const;
  // std::vector<int> GetAdjacencyList(const int& uin, const std::vector<std::string>& relation) const;
  std::map<int,int> BFS(const int& uin) const;
  std::map<int,int> BFS(const int& uin, const std::string& relation) const;
  std::map<int,int> BFS(const int& uin, const std::map<std::string, int>& relation) const;
  std::map<int,int> BFSGetSteps(const int& uin, const int& n) const;
  // std::vector<std::string>& GetListByUIN(const int& uin) const;
  
  
  
private:
  std::vector<int> uins_;
  std::map<int,int> uins_index_;
  std::map<int, std::vector<std::pair<int,std::string>>> adj_list_;
  
};

// std::ostream& operator<<(std::ostream& os, std::vector<std::vector<std::string>> & adj_matrix);
#endif
