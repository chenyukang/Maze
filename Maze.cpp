#include "Maze.h"
#include "DisjSets.h"
#include "DFS_R.h"
#include "DFS_L.h"
#include "A_star.h"
//#include <GL/glut.h>
#include <GLUT/glut.h>
#include <iostream>
#include <assert.h>
using namespace std;


Maze::Maze(int m,int n,float per):M(m),N(n),personx(0),persony(0),m_per(per),m_buser(false)
{
    Ds=new Disjsets(m*n);
    world=(Cell**)malloc(sizeof(Cell*)*m);
    for(int i=0;i<m;i++)
        world[i]=(Cell*)malloc(sizeof(Cell)*n);
    InitDoorId();
    InitPath();
    InitRoom();

    Al_type=none;
	m_pAlgorithm=NULL;
    finished=false;
    draw_visited=false;
}

void Maze::InitDoorId()
{
    int index=0;
    int size=(M-1)*N+(N-1)*M;
    cout<<size<<endl;
    Doors.clear();
    Doors.resize(size);
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            world[i][j].id=index++;
            world[i][j].visited=false;
            for(int k=0;k<4;k++)
                world[i][j].neighbor[k]=-1;
        }

    index=0;
    int door_id=0;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N-1;j++)
        {
            world[i][j].neighbor[1]=index+1;
            world[i][j+1].neighbor[3]=index;
            Doors[door_id].cell_id1=index;
            Doors[door_id].cell_id2=(++index);
            door_id++;

        }
        ++index;
    }

    for(int i=0;i<M-1;i++)
        for(int j=0;j<N;j++)
        {
            world[i][j].neighbor[2]=(i+1)*N+j;
            world[i+1][j].neighbor[0]=i*N+j;
            Doors[door_id].cell_id1=(i*N+j);
            Doors[door_id].cell_id2=((i+1)*N+j);
            door_id++;
        }
    cout<<"Init right"<<endl;
}

void Maze::InitPath()
{
    int size=Doors.size();
    int max=M*N-1;
    time_t t;
    srand((unsigned)time(&t));
    while(Ds->find(0)!= Ds->find(max))//union sets until 0 and M*N-1 are in the same set
    {
        int size=Doors.size()-1;
        int rand_door=rand()%size;
        vector<Door>::iterator iter=Doors.begin();
        iter+=rand_door;
        int roota=Ds->find(iter->cell_id1);
        int rootb=Ds->find(iter->cell_id2);

        if(roota!= rootb)
        {
            Ds->unionSets(roota,rootb);
            Doors.erase(iter);
        }
    }
    while(Doors.size()*1.0f/size > m_per)
    {
        vector<Door>::iterator iter=Doors.begin();
        int rand_door=rand()%Doors.size();
        iter+=rand_door;
        Doors.erase(iter);
    }
}

Maze::~Maze()
{
    for(int i=0;i<M;i++)
        delete world[i];
    delete world;//attension
}

void Maze::InitRoom()
{
    vector<Door>::iterator iter=Doors.begin();
    while(iter!=Doors.end())
    {
        int id1=iter->cell_id1;
        int id2=iter->cell_id2;
        Cell* Cell1=GetFromID(id1);
        Cell* Cell2=GetFromID(id2);

        if(id1==(id2-1))
        {
            Cell1->neighbor[1]=-1;
            Cell2->neighbor[3]=-1;
        }
        else
        {
            Cell1->neighbor[2]=-1;
            Cell2->neighbor[0]=-1;
        }
        iter++;
    }
}



void Maze::Draw()
{
    glRotatef(-90,0.0f,0.0f,1.0f);
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-M/2,N/2);
    glVertex2f(-M/2,-N/2);
    glVertex2f(M/2,-N/2);
    glVertex2f(M/2,N/2);
    glEnd();

    glTranslatef(-M/2,-N/2,0.0f);
    for(int i=0;i<M;i++)
        for(int j=0;j<N-1;j++)
        {
            if(world[i][j].neighbor[1]==-1)
            {
                glBegin(GL_LINES);
                glVertex2f(i,j+1);
                glVertex2f(i+1,j+1);
                glEnd();

            }
        }
    for(int i=0;i<M-1;i++)
        for(int j=0;j<N;j++)
        {
            if(world[i][j].neighbor[2]==-1)
            {
                glBegin(GL_LINES);
                glVertex2f(i+1,j);
                glVertex2f(i+1,j+1);
                glEnd();
            }
        }

    glColor3f(1.0f,1.0f,1.0f);//draw the person
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f(personx+0.5f,persony+0.5f);
    glVertex2f(personx+0.5f,persony+0.5f);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(M-1,N);
    glVertex2f(M,N);
    glEnd();

    if(finished) {
        vector<int> path=m_pAlgorithm->GetPath();
        if(path.size()==0)
            return;
        vector<int> xindex;
        vector<int> yindex;
        for(vector<int>::iterator iter=path.begin();iter!=path.end();iter++)
        {
            int id=*iter;
            int x=id/N;
            int y=id%N;
            xindex.push_back(x);
            yindex.push_back(y);
        }

        for(int i=0;i<xindex.size()-1;i++)
        {
            int x1=xindex[i];
            int y1=yindex[i];
            int x2=xindex[i+1];
            int y2=yindex[i+1];

            glColor3f(1.0f,1.0f,1.0f);
            glBegin(GL_LINE);
            glVertex2f(x1+0.5f,y1+0.5f);
            glVertex2f(x2+0.5f,y2+0.5f);
            glEnd();
        }
    }

    if(true)
    {
        glColor3f(1.0f,1.0f,1.0f);
        glPointSize(0.8);
        glBegin(GL_POINTS);
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
            {
                if(world[i][j].visited)
                {
                    glVertex2f(i+0.5f,j+0.5f);
                }
            }
        glEnd();
    }


}


void Maze::CreateAlgorithm(AlgorithmType type)
{
    if(this->IsFinished())
        this->Reset();
    if(m_buser)
        m_buser=false;
    switch(type)
    {
    case Dfs:
        ChangeMode();
        m_pAlgorithm=new DFS(this,personx,persony);
        break;
    case Bfs:
        ChangeMode();
        m_pAlgorithm=new BFS(this,personx,persony);
        break;
    case Right:
        ChangeMode();
        m_pAlgorithm=new DFS_R(this,personx,persony);
        break;
    case Left:
        ChangeMode();
        m_pAlgorithm=new DFS_L(this,personx,persony);
        break;
    case Astar:
        ChangeMode();
        m_pAlgorithm=new A_star(this,personx,persony);
        break;
    default:
        break;
    }
}

void Maze::Update()
{
    if(m_pAlgorithm!=NULL&&!finished&&!m_buser)
        m_pAlgorithm->MovePerson();
    if(personx==(M-1)&&(persony==(N-1)))
        finished=true;
    else
        finished=false;
}

Maze::Cell* Maze::GetFromID(int id)
{
    int i=id/N;
    int j=id%N;
    return &world[i][j];
}

void Maze::MovePerson(int to)
{
    if(!m_buser)
        m_buser=true;
    switch(to)
    {
    case 0://up =i
        if(world[personx][persony].neighbor[0]!=-1)
            --personx;
        break;
    case 1://right =l
        if(world[personx][persony].neighbor[1]!=-1)
            ++persony;
        break;
    case 2://down =k
        if(world[personx][persony].neighbor[2]!=-1)
            ++personx;
        break;
    case 3://left =j
        if(world[personx][persony].neighbor[3]!=-1)
            --persony;
        break;
    }

    if(personx==(M-1)&&persony==(N-1))
        cout<<"Yes,You finished!"<<endl;
}

bool Maze::IsCellVisited(int x,int y)
{
    return world[x][y].visited;
}

bool Maze::IsValid(int x,int y)
{
    if(x>=M||x<0||
       y>=N||y<0)
        return false;
    return true;
}

bool Maze::IsValidNextPath(int x1,int y1,int x2,int y2)
{
    if(world[x2][y2].visited)//如果节点x2,y2 已经被访问 则返回false
        return false;
    int xdiff=x1-x2;
    int ydiff=y1-y2;
    if(abs(xdiff)==1)
    {
        if(x1>x2&&world[x1][y1].neighbor[0]==Getid(x2,y2))
            return true;
        if(x1<x2&&world[x1][y1].neighbor[2]==Getid(x2,y2))
            return true;
    }
    if(abs(ydiff)==1)
    {
        if(y1>y2&&world[x1][y1].neighbor[3]==Getid(x2,y2))
            return true;
        if(y1<y2&&world[x1][y1].neighbor[1]==Getid(x2,y2))
            return true;
    }
    return false;
}

void Maze::SetAllCellUnVisited()
{
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            world[i][j].visited=false;
}

void Maze::Reset()
{
    delete m_pAlgorithm;
    m_pAlgorithm=NULL;
    personx=0;
    persony=0;
    finished=false;
    this->SetAllCellUnVisited();
}

void Maze::ChangeMode()
{
    if(m_pAlgorithm!=NULL)
        delete m_pAlgorithm;
    m_pAlgorithm=NULL;
    finished=false;
    this->SetAllCellUnVisited();
}

int Maze::Getid(int x,int y)
{
    return x*N+y;
}


void Maze::SetCellVisited(int x,int y,bool visited)
{
    world[x][y].visited=visited;
}

bool Maze::TestNeighbor(int id1,int id2)
{
    int x1=id1/N;
    int y1=id1%N;
    int x2=id2/N;
    int y2=id2%N;
    int xdist=x1-x2;
    int ydist=y1-y2;
    if(abs(xdist)==1)
    {
        if(world[x1][y1].neighbor[0]==id2||world[x1][y1].neighbor[2]==id2)
            return true;
    }
    if(abs(ydist)==1)
    {
        if(world[x1][y1].neighbor[1]==id2||world[x1][y1].neighbor[3]==id2)
            return true;
    }
    return false;
}
