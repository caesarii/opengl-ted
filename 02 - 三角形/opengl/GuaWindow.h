
#ifndef GuaWindow_h
#define GuaWindow_h


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

#include "SDL.h"
#include "SDL_opengl.h"


struct _Window;
typedef struct _Window GuaWindow;


void
GuaWindowRun(GuaWindow * window);

GuaWindow *
GuaWindowNew(int width, int height, const char *title);

#endif /* GuaWindow_h */

