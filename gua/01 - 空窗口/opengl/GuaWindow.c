
#include "GuaWindow.h"


struct _Window {
    int width;
    int height;
    const char *title;

    SDL_Window *window;
    SDL_GLContext *glContext;
    
    bool running;
    int frame;
    unsigned int lastTick, curTick;
    float fps;
};

static void
_GuaWindowQuit(GuaWindow *window) {
    window->running = false;
}

static void
_GuaWindowHandleEvent(GuaWindow *window, const SDL_Event *event) {
    unsigned int eventType = event->type;
    
    if (eventType == SDL_QUIT) {
        _GuaWindowQuit(window);
    }
}

static void
_GuaWindowUpdateInput(GuaWindow *window) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        _GuaWindowHandleEvent(window, &event);
    }
}

static void
_GuaWindowClear(GuaWindow *window) {
    // 清空颜色缓存信息
    glClear(GL_COLOR_BUFFER_BIT);
}

static void
_GuaWindowUpdate(GuaWindow *window) {
    SDL_GL_SwapWindow(window->window);
}

static void
_GuaWindowCalFps(GuaWindow *window) {
    window->frame += 1;
    window->curTick = SDL_GetTicks();
    window->fps = 1000.0 / (window->curTick - window->lastTick);
    window->lastTick = window->curTick;
//    fprintf(stdout, "FPS: %f\n", window->fps);
}

static void
_GuaWindowRender(GuaWindow *window) {
}

void
GuaWindowRun(GuaWindow *window) {
    while(window->running) {
        _GuaWindowCalFps(window);
        _GuaWindowUpdateInput(window);
        _GuaWindowClear(window);
        _GuaWindowRender(window);
        _GuaWindowUpdate(window);
    }
}

static int
_GuaWindowInit(GuaWindow *window) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
        return -1;
    }

    // 设定 opengl 版本号为 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // 创建窗口
    window->window = SDL_CreateWindow(
        window->title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window->width,
        window->height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window->window) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        return -1;
    }
    
    window->glContext = SDL_GL_CreateContext(window->window);
    if (!window->glContext) {
        fprintf(stderr, "SDL_GL_CreateContext error: %s\n", SDL_GetError());
        return -1;
    }
    
    if (SDL_GL_SetSwapInterval(1) < 0) {
        fprintf(stderr, "SDL_GL_SetSwapInterval error: %s\n", SDL_GetError());
        return -1;
    }
    
    // 设定渲染窗口参数 前两个参数控制窗口左下角的位置 后两个参数是窗口宽度和高度
    glViewport(0, 0, window->width, window->height);
    // 设定背景色
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if (error != GL_NO_ERROR){
        fprintf(stderr, "Could not initialize OpenGL %s\n", glGetString(error));
        return -1;
    }
    
    fprintf(stdout, "OpenGL version: %s\n", glGetString(GL_VERSION));
    // 顶点属性上限， 不同硬件不一样，至少是 16
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    fprintf(stdout, "Maximum nr of vertex attributes supported: %d\n", nrAttributes);
    
    return 0;
}

GuaWindow *
GuaWindowNew(int width, int height, const char *title) {
    GuaWindow *window = malloc(sizeof(GuaWindow));
    memset(window, 0, sizeof(GuaWindow));
    
    window->width = width;
    window->height = height;
    window->title = title;
    window->running = true;

    _GuaWindowInit(window);
    
    return window;
}

