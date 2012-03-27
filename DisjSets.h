#ifndef DISJ_SETS_H
#define DISJ_SETS_H

#include <vector>
using namespace std;

class Disjsets
{
 public:

  Disjsets(int numElements);

  int find(int x) const;
  void unionSets(int root1,int root2);

 private:
  vector<int> s;
};

#endif

