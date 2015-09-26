#include <stdio.h>
#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{}

GLWidget::~GLWidget()
{}

void GLWidget::initializeGL()
{
    printf("initilizeGL\n");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    return ;
}

void GLWidget::paintGL()
{
    //printf("paintGL\n");
    glClear(GL_DEPTH_BUFFER_BIT);
    // gluLookAt(1.4, 1.4, 1.4, 0, 0, 0, 0, 1, 0); // exterieur du cube
    gluLookAt(1.6, 1.6, 1.6, 0, 0, 0, 0, 1, 0);    // interieur du cube
    _cubeGenerator(1, 1, 1);
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    //printf("resizeGL\n");
    //   TO   DO
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(70, (double)(800/600), 1, 1000);
    //glMatrixMode(GL_MODELVIEW);
}

void	GLWidget::_cubeGenerator(double x, double y, double z)
{
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 0);
    glVertex3d(x + 1, y, z);
    glVertex3d(x + 1, y + 1, z);
    glVertex3d(x + 1, y + 1, z + 1);
    glVertex3d(x + 1, y, z + 1);
    glColor3ub(0, 255, 0);
    glVertex3d(x, y, z);
    glVertex3d(x + 1, y, z);
    glVertex3d(x + 1, y, z + 1);
    glVertex3d(x, y, z + 1);
    glColor3ub(0, 0, 255);
    glVertex3d(x, y, z + 1);
    glVertex3d(x + 1, y, z + 1);
    glVertex3d(x + 1, y + 1, z + 1);
    glVertex3d(x, y + 1, z + 1);
    glColor3ub(255, 255, 0);
    glVertex3d(x, y, z);
    glVertex3d(x + 1, y, z);
    glVertex3d(x + 1, y + 1, z);
    glVertex3d(x, y + 1, z);
    glColor3ub(255, 0, 255);
    glVertex3d(x, y, z);
    glVertex3d(x, y, z + 1);
    glVertex3d(x, y + 1, z + 1);
    glVertex3d(x, y + 1, z);
    glColor3ub(125, 125, 125);
    glVertex3d(x, y + 1, z);
    glVertex3d(x + 1, y + 1, z);
    glVertex3d(x + 1, y + 1, z + 1);
    glVertex3d(x, y + 1, z + 1);
}
