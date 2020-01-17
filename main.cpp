#include "Maze.h"
#include "Algorithm.h"
#include "DFS_R.h"
#include <GLUT/glut.h>
#include <GL/glui.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int   main_window;
/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Spinner    *width_spinner, *height_spinner;
GLUI_Spinner    *percent_spinner;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;
int width,height;
float percent;

int algorithm_type=1;

Maze* maze;

void update()
{
    if ( glutGetWindow() != main_window )
        glutSetWindow(main_window);

    maze->Update();
    usleep(10000);
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-10.0f,0.0f,0.0f);
    glTranslatef(0.0f,0.0f,-(width/80.0)*10.0f);
    maze->Draw();
    glPopMatrix();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20000.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0f,0.0f,70.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'i':
        maze->MovePerson(0);//up
        break;
    case 'l':
        maze->MovePerson(1);//right
        break;
    case 'k':
        maze->MovePerson(2);//down
        break;
    case 'j':
        maze->MovePerson(3);//left
        break;
    case 'd':
        maze->CreateAlgorithm(Dfs);
        break;
    case 'b':
        maze->CreateAlgorithm(Bfs);
        break;
    case 'v':
        maze->ChangeDrawVisited();
        break;
    case 'r':
        maze->Reset();//reset
        break;
    }
    glutPostRedisplay();
}



/************ myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  glutPostRedisplay();
}


void reset()
{
    maze->Reset();
}

void new_maze()//建立新的迷宫
{
    if(maze!=NULL)
        delete maze;
    if(width%2 != 0)
        width+=1;
    if(height%2!= 0)
        height+=1;
    maze=new Maze(width,height,percent);
}

void depth_func()
{
    maze->CreateAlgorithm(Dfs);
}

void breadth_func()
{
     maze->CreateAlgorithm(Bfs);
}

void dfs_r_func()
{
     maze->CreateAlgorithm(Right);
}

void dfs_l_func()
{
    maze->CreateAlgorithm(Left);
}

void A_star_func()
{
    maze->CreateAlgorithm(Astar);
}


int main(int argc,char* argv[])
{
    maze=new Maze(60,78,0.9);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(100,100);

    main_window=glutCreateWindow ("Maze");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/

    /*** Create the side subwindow ***/
    glui = GLUI_Master.create_glui_subwindow( main_window,
                                              GLUI_SUBWINDOW_RIGHT );

    GLUI_Panel *maze_size = new GLUI_Panel(glui,"Maze Size");
    width_spinner =
        new GLUI_Spinner(maze_size, "Width:", &width);
    width_spinner->set_int_limits( 4, 100 );
    width_spinner->set_alignment( GLUI_ALIGN_RIGHT );

    height_spinner =
        new GLUI_Spinner(maze_size, "Height:", &height);
    height_spinner->set_int_limits( 4, 100 );
    height_spinner->set_alignment( GLUI_ALIGN_RIGHT );

    percent_spinner =
        new GLUI_Spinner(maze_size, "Percent:", &percent);
    percent_spinner->set_float_limits(0.1, 1.0);
    percent_spinner->set_alignment( GLUI_ALIGN_RIGHT );


    new GLUI_Button(maze_size,"New Maze",0,(GLUI_Update_CB)new_maze);

    GLUI_Panel *type_panel = new GLUI_Panel(glui, "Algorithm_Type" );
    new GLUI_Button(type_panel,"Depth first",0,(GLUI_Update_CB)depth_func);
    new GLUI_Button(type_panel,"Breadth first",0,(GLUI_Update_CB)breadth_func);
    new GLUI_Button(type_panel,"Right first DFS",0,(GLUI_Update_CB)dfs_r_func);
    new GLUI_Button(type_panel,"Left first DFS",0,(GLUI_Update_CB)dfs_l_func);
    new GLUI_Button(type_panel,"A star",0,(GLUI_Update_CB)A_star_func);

    new GLUI_Button(glui, "Reset",0,(GLUI_Update_CB)reset);
    new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );


    glui->set_main_gfx_window( main_window );
    GLUI_Master.set_glutIdleFunc( update );

    glutMainLoop();
    return EXIT_SUCCESS;
}
