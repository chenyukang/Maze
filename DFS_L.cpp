#include "DFS_L.h"
#include "Maze.h"

DFS_L::DFS_L(Maze* maze,int x,int y):AlgorithmBase(maze,x,y)
{
    Di[0][0]=0;Di[0][1]=1;
    Di[1][0]=1;Di[1][1]=0;
    Di[2][0]=0;Di[2][1]=-1;
    Di[3][0]=-1;Di[3][1]=0;
    m_stack.push(Node(x,y));
    dir_now=0;
    cout<<"DFS_L constructed"<<endl;
}

int DFS_L::Turn_AntiClock(int now)
{
    int re=now-1;
    if(re>=0)
        return re;
    else return 3;
}

bool DFS_L::search()
{
    int dir=Turn_AntiClock(dir_now);
    int nx=personx+Di[dir][0];
    int ny=persony+Di[dir][1];
    if(m_pMaze->IsValid(nx,ny)&&
       m_pMaze->IsValidNextPath(personx,persony,nx,ny))
    {
        dir_now=dir;
        m_path.push_back(m_pMaze->Getid(nx,ny));
        personx=nx;
        persony=ny;
        return true;
    }
    while(1){
        nx=personx+Di[dir_now][0];
        ny=persony+Di[dir_now][1];

        if(m_pMaze->IsValid(nx,ny)&&
           m_pMaze->IsValidNextPath(personx,persony,nx,ny))
        {
            personx=nx;
            persony=ny;
            m_path.push_back(m_pMaze->Getid(nx,ny));

            return true;
        }
        dir_now=(dir_now+1)%4;
    }

}

const vector<int>& DFS_L::GetPath()
{
    return m_path;
}

void DFS_L::Draw()
{
    return;
}
