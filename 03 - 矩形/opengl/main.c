
#include "GuaWindow.h"


int main(int argc, const char * argv[]) {
    int w = 800;
    int h = 600;
    const char *t = "Gua OpenGL";
    
    GuaWindow * window = GuaWindowNew(w, h, t);
    GuaWindowRun(window);
    return 0;
}
