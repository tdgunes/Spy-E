
#include <stdio.h>
#include <GL/glew.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <graphics/Drawer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <physics/Physics.h>
#include "SDL.h"
#include "logic/Timer.h"
#include "world/Scene.h"
#include "graphics/Renderer.h"
#include "input/Input.h"
#include "logic/Game.h"
#include "logic/SystemController.h"
#define TICK_PER_SECOND 1000

Game::Game() {

    controller = new SystemController();
}

bool Game::init(int width, int height, char const *title, bool fullScreen) {
	quit = false;
    this->width = width;
    this->height = height;
    SDL_Init(SDL_INIT_EVERYTHING&(~SDL_INIT_AUDIO));
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ) ;


    mainWindow = SDL_CreateWindow("Spy-E", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, ((fullScreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN) |SDL_WINDOW_OPENGL);
    mainGLContext = SDL_GL_CreateContext(mainWindow);

    if (mainGLContext == 0) {
        printf ("Error while creating OpenGL context: %s\n", SDL_GetError());
        abort();
    }
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    if( TTF_Init() == -1 )
    {
        printf("Failed to init ttf\n");
        return false;
    }

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if (initted&flags != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

    scene = new Scene();
    input = new Input(mainWindow);
    drawer = new Drawer(this);
    physics = new Physics();

    controller->addCoreSystem(input);
    controller->addCoreSystem(scene);
    controller->addCoreSystem(drawer);
    controller->addCoreSystem(physics);


    controller->init();

    timer = new Timer(TICK_PER_SECOND);




    return true;
}

void Game::update() {
    unsigned long lastTime = SDL_GetTicks();
    int tickCount = 0;
    bool isUpdated = false;

    while(!quit) {
        unsigned long currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;


        while (timer->tick()) {
            controller->update(timer->getTickSize());
            tickCount++;
            isUpdated = true;
        }
        timer->endLoop();

		if (isUpdated) {
			controller->draw();
		}

        controller->draw2D();

        isUpdated = false;
        if (deltaTime > 1000) {
            lastTime = currentTime;
            printf("%d tick %d\n", tickCount, SDL_GetTicks());
        }
        SDL_GL_SwapWindow(mainWindow);
    }
}

void Game::end() {
    SDL_GL_DeleteContext(mainGLContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

