#ifndef _MAZE_H__
#define _MAZE_H__
#include "DisjSets.h"
#include "Algorithm.h"
#include <map>
#include <vector>
using namespace std;

class Maze
{
public:
    typedef struct
    {
        int id;
        int neighbor[4];
        bool visited;
    }Cell;
    typedef struct
    {
        int cell_id1;
        int cell_id2;
    }Door;

public:
    typedef Cell** World;
    Maze(int M,int N,float m_pe);
    ~Maze();

    void Draw();
    void Update();
    void InitDoorId();
    void InitPath();
    void InitRoom();
    void MovePerson(int);
    void CreateAlgorithm(AlgorithmType type);

    bool IsCellVisited(int,int);
    bool IsValid(int,int);
    bool IsValidNextPath(int,int,int,int);
    bool TestNeighbor(int id1,int id2);

    int  Getid(int x,int y);
    void SetPerson(int x,int y) {personx=x; persony=y;}
    void SetCellVisited(int x,int y,bool visited);
    void Reset();
    void SetAllCellUnVisited();

    int GetWidth()const {return N;}
    int GetHeight() const {return M;}

    void ChangeMode();
    bool IsFinished() {return finished;}
    void ChangeDrawVisited() { draw_visited=(!draw_visited);}

private:
    Cell* GetFromID(int id);

private:

    Cell** world;
    bool m_buser; // is in user control?
    bool draw_visited;
    int M,N;
    float m_per;
    Disjsets* Ds;
    int personx;
    int persony;
    vector<Door> Doors;
    AlgorithmType Al_type;
    AlgorithmBase* m_pAlgorithm;
    bool finished;
};
#endif
