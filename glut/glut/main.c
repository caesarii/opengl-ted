//
//  main.c
//  glut
//
//  Created by qinghe on 2020/5/11.
//  Copyright © 2020 qinghe. All rights reserved.
//

#include <glut/glut.h>

void guaRender(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5, -0.5, 0.5, 0.5);
    glFlush();
}
int main(int argc, char *argv[]) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(400, 400);
 glutCreateWindow("my first opengl");
 glutDisplayFunc(&guaRender);
 glutMainLoop();
 return 0;
}
