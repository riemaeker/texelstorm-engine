#include "Engine.h"
#include "OpenGLDisplay.h"
#include "VulkanDisplay.h"
#include "SoftwareRenderer.h"

#include <iostream>
#include <SDL2/SDL.h>

bool Engine::Setup()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Error initializing SDL.";
    return false;
  }

  // Display setup.
  //display = new OpenGLDisplay(800, 600);
  display = new VulkanDisplay(1280, 720);
  if (display == nullptr)
  {
    std::cerr << "Error creating display.";
    return false;
  }

  // Renderer setup.
  //renderer = new SoftwareRenderer(display);

  return true;
}

int Engine::Run()
{
  SDL_Event event;
  bool done = false;

  while (!done)
  {
    Uint32 startTime = SDL_GetTicks();

    SDL_PumpEvents();
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SDL_QUIT");
        done = true;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          done = true;
        }
        break;
      }
    }

    Update();

    lastFrameTime = SDL_GetTicks() - startTime;
  }

  return 0;
}

void Engine::Quit()
{
  free(renderer);
  free(display);

  SDL_Quit();
}

void Engine::Update()
{
  //renderer->Refresh();
  display->Present();
}