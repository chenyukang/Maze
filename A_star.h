#ifndef A_STAR_H_
#define A_STAR_H_
#include "Algorithm.h"
#include <queue>
using namespace std;


class A_star:public AlgorithmBase
{
    class Node
    {
    public:
        int x,y;
        int wei;
        friend bool operator > (const Node& lhs,const Node& rhs)
            {
                return lhs.wei>rhs.wei;
            }
        Node(int xx,int yy,int w):x(xx),y(yy),wei(w)
            {
            }
    };
private:
    bool search();
    int Di[4][2];
    map<int,int> m_pathmap;
    priority_queue<Node,vector<Node>,greater<Node> > PQ;//优先队列
    int EvalFunc(int x,int y);
    
public:
    void Draw() {}
    A_star(Maze*,int,int);
    ~A_star() {}
    const virtual vector<int>& GetPath();
};

#endif//A_STAR_H_
