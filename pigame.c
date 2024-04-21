#include <stdio.h>
#include "SDL.h"
#include "GL/gl.h"

typedef struct {
  SDL_Window     *window;
  SDL_GLContext glContext;
} AppContext;

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
	    if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Q) return;
        }

	glClearColor(.5f, .2f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

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

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    appCtx.window = SDL_CreateWindow("pigame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 400, SDL_WINDOW_OPENGL);
    if (appCtx.window == NULL) {
      printf("Failed to create window: %s\n", SDL_GetError());
      return 1;
    }
    appCtx.glContext = SDL_GL_CreateContext(appCtx.window);
    //checkSDLError(SDL_GL_MakeCurrent(appCtx.window, appCtx.glContext));

    // game loop
    startGameLoop(appCtx);

    // sdl cleanup
    SDL_GL_DeleteContext(appCtx.glContext);
    SDL_DestroyWindow(appCtx.window);
    SDL_Quit();
}
