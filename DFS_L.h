#ifndef DFS_L_H_
#define DFS_L_H_
#include "Algorithm.h"

class DFS_L:public AlgorithmBase
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
    DFS_L(Maze*,int,int);
    ~DFS_L() {}
    const virtual vector<int>& GetPath();
    
};


#endif//DFS_L_H_
