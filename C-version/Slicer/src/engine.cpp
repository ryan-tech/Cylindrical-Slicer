
#include "engine.h"
#include "SDL.h"
/*
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>

// includes for imgui
#if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#endif*/

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

// updated constructor to include the shader files
Engine::Engine(string name, int width, int height, std::string vShader, std::string fShader)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
	m_Vertex_Shader = vShader;
	m_Fragment_Shader = fShader;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize(std::string vShader, std::string fShader)
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

	// assign shaders
	m_Vertex_Shader = vShader;
	m_Fragment_Shader = fShader;	

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_Vertex_Shader, m_Fragment_Shader))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

		// check for keyboard input
		while(SDL_PollEvent(&m_event) != 0)
		{
		  Keyboard();
		}

    // Update and render the graphics
		// Using the keydown events, send the key stroke to the Update() method with a switch statement inside it
    m_graphics->Update(m_DT);
		m_keyValue = 0;
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
	int moon = 0;
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
		if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
		// handle moon controls here
		if (m_event.key.keysym.sym == SDLK_LALT || m_event.key.keysym.sym == SDLK_RALT)
		{
			if (SDL_PollEvent(&m_event) != 0)
			{
						if (m_event.key.keysym.sym == SDLK_q)
							std::cout << "deez nuts\n";
					
			}
		}
		
	}
		/*
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
		else if (m_event.key.keysym.sym == SDLK_q || m_event.button.button == SDL_BUTTON_LEFT)
    {
      m_keyValue = 1;
    }
		else if (m_event.key.keysym.sym == SDLK_w || m_event.button.button == SDL_BUTTON_RIGHT)
    {
      m_keyValue = 2;
    }
		else if (m_event.key.keysym.sym == SDLK_e)
    {
      m_keyValue = 3;
    }
		else if (m_event.key.keysym.sym == SDLK_r)
    {
      m_keyValue = 4;
    }
		else if (m_event.key.keysym.sym == SDLK_z)	// resets orbit speed
    {
      m_keyValue = 7;
    }
		else if (m_event.wheel.y > 0)	// mouse wheel up
		{
			m_keyValue = 5;
		}		
		else if (m_event.wheel.y < 0)	// mouse wheel down
		{
			m_keyValue = 6;
		}
		// moon controls	
  }
	else if (m_event.type == SDL_MOUSEBUTTONDOWN)
	{

	}
	else if (m_event.type == SDL_MOUSEWHEEL)
	{

	}*/
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
