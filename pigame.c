#include <stdio.h>
#include "SDL.h"

typedef void(*glClear)(unsigned);
typedef void(*glClearColor)(float red, float green, float blue, float alpha);

typedef struct {
  SDL_Window     *window;
  SDL_GLContext glContext;
} AppContext;

glClear test_glClear;
glClearColor test_glClearColor;

void checkSDLError(int error) {
    if (error != 0) {
        printf("SDL ERROR: %s\n", SDL_GetError());
    }
}

void startGameLoop(AppContext context) {
    while(1) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
	    if (e.type == SDL_QUIT) return;
        }

	test_glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	test_glClear(0xffffffff);
        SDL_GL_SwapWindow(context.window);
    }
}

int main(int* argc, char** argv) {
    // print info
    SDL_version ver = {0,0,0};
    SDL_GetVersion(&ver);
    printf("SDL VERSION: %d.%d.%d\n", ver.major, ver.minor, ver.patch);    
  
    // init sdl subsystems
    AppContext appCtx;
    checkSDLError(SDL_Init(SDL_INIT_VIDEO));

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    appCtx.window = SDL_CreateWindow("pigame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 400, SDL_WINDOW_OPENGL);
    if (appCtx.window == NULL) {
      printf("Failed to create window: %s\n", SDL_GetError());
      return 1;
    }
    appCtx.glContext = SDL_GL_CreateContext(appCtx.window);
    checkSDLError(SDL_GL_MakeCurrent(appCtx.window, appCtx.glContext));

    test_glClear = (glClear)SDL_GL_GetProcAddress("glClear");
    test_glClearColor = (glClearColor)SDL_GL_GetProcAddress("glClearColor");
    if(test_glClear == NULL || test_glClearColor == NULL) {
        printf("gl proc null\n");
        goto stop;
    }

    // game loop
    startGameLoop(appCtx);

    // sdl cleanup
    stop:
    SDL_GL_DeleteContext(appCtx.glContext);
    SDL_DestroyWindow(appCtx.window);
    SDL_Quit();
}
