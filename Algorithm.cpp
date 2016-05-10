#include "Maze.h"
#include <iostream>
#include <iomanip>
using namespace std;


AlgorithmBase::AlgorithmBase(Maze* maze,int x,int y):m_pMaze(maze),personx(x),persony(y)
{
    fromx=x;
    fromy=y;
}

AlgorithmBase::~AlgorithmBase() {
  delete m_pMaze;
}

void AlgorithmBase::MovePerson()
{
  search();
  m_pMaze->SetPerson(personx,persony);

}

const vector<int>& AlgorithmBase::GetPath()
{
    return m_path;
}

DFS::DFS(Maze* maze,int x,int y):AlgorithmBase(maze,x,y)
{
    Di[0][0]=-1;Di[0][1]=0;
    Di[1][0]=0;Di[1][1]=-1;
    Di[2][0]=0;Di[2][1]=1;
    Di[3][0]=1;Di[3][1]=0;
  m_stack.push(Node(x,y));
    cout<<"DFS constructed"<<endl;
}

bool DFS::search()
{
    if(!m_stack.empty())
    {
        Node step=m_stack.top();
        m_stack.pop();
        m_pMaze->SetCellVisited(step.x,step.y,true);//set this node visited
        for(int i=0;i<4;i++)
        {
            int nx=step.x+Di[i][0];
            int ny=step.y+Di[i][1];
            if(m_pMaze->IsValid(nx,ny)&&
               m_pMaze->IsValidNextPath(step.x,step.y,nx,ny))
            {
                Node node(nx,ny);
                m_stack.push(node);
                m_pathmap[m_pMaze->Getid(nx,ny)]=m_pMaze->Getid(step.x,step.y);
            }
        }

        personx=step.x;
        persony=step.y;

    }
    return false;
}


const vector<int>& DFS::GetPath()
{
    if(m_path.size()==0)
    {
        cout<<"constructor result path"<<endl;
        int target=m_pMaze->Getid(m_pMaze->GetHeight()-1,m_pMaze->GetWidth()-1); // get the target id
        int id_now=m_pathmap[target];
        int from=m_pMaze->Getid(fromx,fromy);
        while(id_now!=from)
        {
            m_path.insert(m_path.begin(),id_now);
            id_now=m_pathmap[id_now];
        }
    }
    return m_path;
}

void DFS::Draw()
{
    return;
}



BFS::BFS(Maze* maze,int x,int y):AlgorithmBase(maze,x,y)
{
    m_queue.push(Node(x,y));
    Di[0][0]=-1;Di[0][1]=0;
    Di[1][0]=0;Di[1][1]=-1;
    Di[2][0]=0;Di[2][1]=1;
    Di[3][0]=1;Di[3][1]=0;
    m_pMaze->SetCellVisited(x,y,true);
    cout<<"BFS constructed"<<endl;
}

bool BFS::search()
{
    if(!m_queue.empty())
    {
        Node step=m_queue.front();
        m_queue.pop();
        int id_now=m_pMaze->Getid(step.x,step.y);

        for(int i=0;i<4;i++)
        {
            int nx=step.x+Di[i][0];
            int ny=step.y+Di[i][1];
            if(m_pMaze->IsValid(nx,ny)&&
               m_pMaze->IsValidNextPath(step.x,step.y,nx,ny))
            {
                Node node(nx,ny);
                m_queue.push(node);
                m_pathmap[m_pMaze->Getid(nx,ny)]=m_pMaze->Getid(step.x,step.y);
                m_pMaze->SetCellVisited(nx,ny,true);
            }
        }

        personx=step.x;
        persony=step.y;
    }
    return false;
}

const vector<int>& BFS::GetPath()//return the path from source to target
{
    if(m_path.size()==0)
    {
        cout<<"constructor result path"<<endl;
        int target=m_pMaze->Getid(m_pMaze->GetHeight()-1,m_pMaze->GetWidth()-1); // get the target id
        int id_now=m_pathmap[target];
        int from=m_pMaze->Getid(fromx,fromy);
        while(id_now!=from)
        {
            m_path.insert(m_path.begin(),id_now);
            id_now=m_pathmap[id_now];
        }
    }
    return m_path;

}

void BFS::Draw()
{
    return ;
}
