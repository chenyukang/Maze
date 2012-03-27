#include "A_star.h"
#include "Maze.h"
#include <math.h>

int abs ( int v ) 
{
 	if( v >= 0 )
	return v;
	else return -v;
}

A_star::A_star(Maze* maze,int x,int y):AlgorithmBase(maze,x,y)
{
    Di[0][0]=-1;Di[0][1]=0;
    Di[1][0]=0;Di[1][1]=-1;
    Di[2][0]=0;Di[2][1]=1;
    Di[3][0]=1;Di[3][1]=0;
    m_pMaze->SetCellVisited(x,y,true);
    int v=this->EvalFunc(x,y);
    PQ.push(Node(x,y,v));
    cout<<"A_star constructed"<<endl;
}


int A_star::EvalFunc(int x,int y)
{
    int xdiff=abs(x-m_pMaze->GetHeight()-1);
    int ydiff=abs(y-m_pMaze->GetWidth()-1);
    return xdiff+ydiff;
//     if(xdiff>ydiff)
//         return ydiff;
//     else
//         return xdiff;
}

bool A_star::search()
{
    if(!PQ.empty())
    {
        Node now=PQ.top();
        PQ.pop();
        int now_id=m_pMaze->Getid(now.x,now.y);
        for(int i=0;i<4;i++)
        {
            int nx=now.x+Di[i][0];
            int ny=now.y+Di[i][1];
            if(m_pMaze->IsValid(nx,ny)&&
               m_pMaze->IsValidNextPath(now.x,now.y,nx,ny))
            {
                int v=this->EvalFunc(nx,ny);
                PQ.push(Node(nx,ny,v));
                m_pathmap[m_pMaze->Getid(nx,ny)]=now_id;
                m_pMaze->SetCellVisited(nx,ny,true);
            }
        }
        personx=now.x;
        persony=now.y;
    }
    return false;
}

const vector<int>& A_star::GetPath()//return the path from source to target
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
