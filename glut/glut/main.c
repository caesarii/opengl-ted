//
//  main.c
//  glut
//
//  Created by qinghe on 2020/5/11.
//  Copyright © 2020 qinghe. All rights reserved.
//

#include <glut/glut.h>

# define drawOnePoint(x1, y1) glBegin(GL_POINTS); \
    glVertex2f((x1), (y1)); glEnd();

# define drawOneLine(x1, y1, x2, y2) glBegin(GL_LINES); \
    glVertex2f((x1), (y1)); glVertex2f((x2), (y2)); glEnd();

void
init(void) {
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT);
}

void
guaRender(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    
    glPointSize(100);
   
    drawOnePoint(200, 200);
    
    glFlush();
}

void
reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
               
}
int
main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("my first opengl");
    init();
    glutDisplayFunc(&guaRender);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
