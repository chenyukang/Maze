#ifndef _ALGORITHM_H__
#define _ALGORITHM_H__

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

class Maze;

enum AlgorithmType{
  none,
  Dfs,
  Bfs,
  Left,//靠左走 直到没有路径 右转
  Right,//靠右走 直到没有路径 左转
  Astar//A* 算法
};

class AlgorithmBase
{
 protected:
  class Node
  {
  public:
    int x;
    int y;

  Node(int x,int y):x(x),y(y)
    {}

    bool operator==(const Node& node) const
    {
      return (node.x==x&&node.y==y);
    }
  };

  Maze* m_pMaze;
  vector<int> m_path;
  int personx,persony;
  int fromx;
  int fromy;

 public:
  AlgorithmBase(Maze*, int, int);
  virtual ~AlgorithmBase();
  virtual bool search()=0;
  virtual void Draw()=0;
  void MovePerson();
  const virtual vector<int>& GetPath();
};


class DFS:public AlgorithmBase
{
 private:
  stack<Node> m_stack;
  bool search();
  void Draw();
  void ProcessPath(int id);
  map<int,int> m_pathmap;
  int Di[4][2];
 public:
  DFS(Maze*,int,int);
  ~DFS() {}
  const virtual vector<int>& GetPath();

};

class BFS:public AlgorithmBase
{
 private:
  queue<Node> m_queue;
  bool search();
  void Draw();
  void ProcessPath(int id);
  map<int,int> m_pathmap;
  int Di[4][2];

 public:
  BFS(Maze*,int,int);
  ~BFS() {}
  const virtual vector<int>& GetPath();
};


#endif
