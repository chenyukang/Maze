#ifndef DFS_R_H_
#define DFS_R_H_

#include "Algorithm.h"

class DFS_R:public AlgorithmBase
{
private:
    bool search();
    int Turn_AntiClock(int);
    map<int,int> m_pathmap;
    stack<Node> m_stack;
    int Di[4][2];
    int dir_now;
public:
    void Draw();
    DFS_R(Maze*,int,int);
    ~DFS_R() {}
    const virtual vector<int>& GetPath();
    
};

#endif//DFS_R_H_
