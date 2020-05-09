
#include "GuaShader.h"


char *
_GuaShaderReadWholeFile(const char * fileName) {
    FILE *file;
    long int length;
    char *buffer;
    
    file = fopen (fileName, "rb" );
    if (file == NULL) {
        fprintf(stderr, "open file error: %s\n", fileName);
        return NULL;
    }
 
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    buffer = malloc(sizeof(char) * length + 1);
    buffer[length] = '\0';
 
    fread(buffer, 1, length, file);
    fclose(file);
    
    return buffer;
}

unsigned int
GuaShaderProgramCreate(const char* vertexFile, const char* fragmentFile) {
    const char *vertexShaderSource = _GuaShaderReadWholeFile(vertexFile);
    if (vertexShaderSource == NULL) {
        fprintf(stderr, "Read vertexFile error\n");
        return -1;
    }
    
    const char *fragmentShaderSource = _GuaShaderReadWholeFile(fragmentFile);
    if (fragmentShaderSource == NULL) {
        fprintf(stderr, "Read fragmentFile error\n");
        return -1;
    }

    
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "vertexShader compile error: %s\n", infoLog);
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "fragmentShader compile error: %s\n", infoLog);
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 检查链接错
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "shader link error: %s\n", infoLog);
    }
    // 链接完成后可以删除 shader
    free((void *)vertexShaderSource);
    free((void *)fragmentShaderSource);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}
