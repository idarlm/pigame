#include <stdio.h>
#include "SDL.h"
#include "GL/gl.h"

typedef struct {
  SDL_Window     *window;
  SDL_GLContext glContext;
} AppContext;

typedef struct {
  float x, y;
} vec2;

typedef struct {
  float x, y, z;
} vec3;

typedef struct {
  float x, y, z, w;
} vec4;

vec3 add(vec3 a, vec3 b) {
  vec3 new = {a.x+b.x, a.y+b.y, a.z+b.z};
  return new;
}

float dot(vec3 a, vec3 b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

void immediate_begin() {
  glBegin(GL_TRIANGLES);
}

void immediate_end() {
  glEnd();
}

void draw_triangle(vec3 pos, vec3 col) {
  immediate_begin();
  vec3 a = {-0.5f, -0.5f, 0.f};
  vec3 b = { 0.5f, -0.5f, 0.f};
  vec3 c = { 0.0f,  0.5f, 0.f};
  glVertex3f(pos.x + a.x, pos.y + a.y, pos.z + a.z);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(pos.x + b.x, pos.y + b.y, pos.z + b.z);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(pos.x + c.x, pos.y + c.y, pos.z + c.z);
  glColor3f(0.0f, 0.0f, 1.0f);
  immediate_end();
}

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

	vec3 pos = {0.f, 0.f, 0.f};
	vec3 col = {0.5f, 0.5f, 0.8f};
	draw_triangle(pos, col);

	SDL_GL_SwapWindow(context.window);
    }
}

int main(int argc, char** argv) {
    // print info
    SDL_version ver = {0,0,0};
    SDL_GetVersion(&ver);
    printf("SDL VERSION: %d.%d.%d\n", ver.major, ver.minor, ver.patch);
  
    // init sdl subsystems
    AppContext appCtx;
    checkSDLError(SDL_Init(SDL_INIT_VIDEO));

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    appCtx.window = SDL_CreateWindow("pigame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, SDL_WINDOW_OPENGL);

    if (appCtx.window == NULL) {
      printf("Failed to create window: %s\n", SDL_GetError());
      return 1;
    }
    appCtx.glContext = SDL_GL_CreateContext(appCtx.window);
    checkSDLError(SDL_GL_MakeCurrent(appCtx.window, appCtx.glContext));

    // game loop
    startGameLoop(appCtx);

    // sdl cleanup
    SDL_GL_DeleteContext(appCtx.glContext);
    SDL_DestroyWindow(appCtx.window);
    SDL_Quit();
}
