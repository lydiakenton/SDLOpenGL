#include <iostream>
#include "SDLOpenGL.h"
#include "Shader.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>

void initializeGL();
void renderGL();

int main(int argc, char *argv[])
{
  SDLOpenGL window("test",0,0,1024,720);
  window.makeCurrent();
  initializeGL();
  bool quit=false;
  while(!quit)
  {
    SDL_Event event;
    window.pollEvent(event);
    switch(event.type)
    {
      case SDL_QUIT : quit=true; break;
      case SDL_KEYDOWN :
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE : quit=true; break;
          case SDLK_w : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
          case SDLK_s : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
        }
      }
    }

    renderGL();
    window.swapWindow();
    SDL_Delay(10);
  }
}

void initializeGL()
{
  ngl::NGLInit::instance();
  glClearColor(0.8,0.8,0.8,1.0);
  Shader colour("shaders/ColourVertex.glsl",
                "shaders/ColourFragment.glsl");
}

void renderGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ngl::VAOPrimitives::instance()->draw("teapot");
}
