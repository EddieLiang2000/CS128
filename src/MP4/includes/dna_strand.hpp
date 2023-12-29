#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const char* pattern);
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void PushBack(char data);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void FindSpliceRange(Node * find_start, const char* pattern, Node *& seq_start, Node *& seq_end);
  unsigned int Strlen(const char *s);
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
private:
  
  
};

#endif