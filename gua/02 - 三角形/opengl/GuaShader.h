
#ifndef GuaShader_h
#define GuaShader_h

#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>


unsigned int
GuaShaderProgramCreate(const char* vertexFile, const char* fragmentFile);
#endif /* GuaShader_h */
