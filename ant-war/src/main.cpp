

#ifdef _WIN32
#include <SDL.h>

#define not !

#else

#include <SDL2/SDL.h>
//#include <SDL2/SDL2_gfxPrimitives.h>

#endif

#include "config.h"
#include "boidsystem.h"
using namespace std;
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include "../../SDL2_gfx/src/SDL2_gfxPrimitives.h"


int const WIDTH = Config::WIDTH;
int const HEIGHT = Config::HEIGHT;
float Config::TARGET_X = 100.0f;
float Config::TARGET_Y = 100.0f;
float const PI = 3.1415927;

struct global_t {
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	// random
	std::random_device rd;
	std::default_random_engine eng;
	std::uniform_real_distribution<float> rand;

	BSystem<float> boidSystem;
};

global_t g;


void init_boids() {
	g.boidSystem.add_boid({ 100,100 }, { 1,0 });
	g.boidSystem.add_boid({ 200,100 }, { -1,0 });
	g.boidSystem.add_boid({ 150,200 }, { 0,1 });
	g.boidSystem.add_boid({ 300,300 }, { 1,-1 });
}

// init boids with random positions and velocities
void init_boids_random(int count) {
	uniform_real_distribution<float> pos_dist_x(0, WIDTH);
	uniform_real_distribution<float> pos_dist_y(0, HEIGHT);
	uniform_real_distribution<float> vel_dist(-1, 1);

	for (int i = 0; i < count; ++i) {
		vector2<float> position{ pos_dist_x(g.eng), pos_dist_y(g.eng) };
		vector2<float> velocity{ vel_dist(g.eng), vel_dist(g.eng) };
		g.boidSystem.add_boid(position, velocity);
	}
}

void draw_boid(SDL_Renderer* renderer, vector2<float> pos, vector2<float> vel, float size = Config::BOID_SIZE) {
	float angle = atan2(vel.y, vel.x);
	float halfSize = size / 2.0f;  // size: size of the boid

	// 1. define the 3 points of the triangle(bird
	vector2<float> p1{ size, 0 };
	vector2<float> p2{ -halfSize, halfSize };
	vector2<float> p3{ -halfSize, -halfSize };

	auto rotate = [&](vector2<float> v) -> vector2<float> {
		return { v.x * cos(angle) - v.y * sin(angle),
				 v.x * sin(angle) + v.y * cos(angle) };
		};

	vector2<float> tp1 = rotate(p1) + pos;
	vector2<float> tp2 = rotate(p2) + pos;
	vector2<float> tp3 = rotate(p3) + pos;

	// fill the polygen 
	filledTrigonRGBA(renderer,
		(Sint16)tp1.x, (Sint16)tp1.y,
		(Sint16)tp2.x, (Sint16)tp2.y,
		(Sint16)tp3.x, (Sint16)tp3.y,
		0, 255, 255, 128);

	//  draw outlines 
	trigonRGBA(renderer,
		(Sint16)tp1.x, (Sint16)tp1.y,
		(Sint16)tp2.x, (Sint16)tp2.y,
		(Sint16)tp3.x, (Sint16)tp3.y,
		0, 0, 128, 255);
}


void draw_nid(SDL_Renderer* renderer,  float size = Config::NID_SIZE) {
	float r = size / 2.0f;

	vector2<float> pos{ Config::TARGET_X, Config::TARGET_Y };
	float cx = (Sint16)pos.x;
	float cy = (Sint16)pos.y;

	// visualisation of nid
	filledCircleRGBA(renderer, cx, cy, r, 50, 100, 200, 40);
	filledCircleRGBA(renderer, cx, cy, r/20, 80, 130, 255, 255);
}

bool point_in_nid(vector2<float> point, float size = Config::NID_SIZE) {
	float r = size / 2.0f;
	vector2<float> nid_pos{ Config::TARGET_X, Config::TARGET_Y };
	vector2<float> diff = point - nid_pos;
	return (diff.length() <= r);
}


// tp
void do_render() {
	/*SDL_SetRenderDrawBlendMode(g.renderer, SDL_BLENDMODE_BLEND);*/

	SDL_SetRenderDrawColor(g.renderer, 255u, 255u, 255u, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g.renderer);

	//paint_it_s_work(0, 0, 20);

	// drow boids
	SDL_SetRenderDrawColor(g.renderer, 0, 255, 255, 255);
	for (auto& b : g.boidSystem.boids) {
		draw_boid(g.renderer, b.position, b.velocity);
		cout << "Boid at (" << b.position.x << ", " << b.position.y << ") with velocity (" << b.velocity.x << ", " << b.velocity.y << ")\n";
	}

	if (Config::cible_MODE)   draw_nid(g.renderer);  
	SDL_RenderPresent(g.renderer);
}


void do_update() {
	g.boidSystem.do_update();
}

int main(int argc, char** argv)
{
    int status;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        return 1;
    }

    g.window = SDL_CreateWindow(
        "Ant War",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!g.window) {
        return 1;
    }

    // initialize boids
    int const NUM_BOIDS = Config::NUM_BOIDS;
    init_boids_random(NUM_BOIDS);

    // get the default renderer
    g.renderer = SDL_CreateRenderer(g.window, -1, 0);
    SDL_SetRenderDrawBlendMode(g.renderer, SDL_BLENDMODE_BLEND);
    if (!g.renderer) {
        return 1;
    }

    bool end = false;
    bool dragging_nid = false;

    while (!end) {

        SDL_Event event;

        if (SDL_WaitEventTimeout(&event, 20)) {

            switch (event.type) {

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    end = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    end = true;
                break;

                // ============================
				// 1. Button down ¡ú  Add boid or start dragging nid
                // ============================
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {

                    float mx = event.button.x;
                    float my = event.button.y;

                    if (point_in_nid({ mx, my }) && Config::DRAG_NID) {
                        dragging_nid = true;
                        printf("Start dragging nid at (%.2f, %.2f)\n", mx, my);
                    }
                    else {
                        vector2<float> pos{ mx, my };
                        vector2<float> vel{
                            (float)(rand() % 100 - 50) / 50.0f,
                            (float)(rand() % 100 - 50) / 50.0f
                        };
                        g.boidSystem.add_boid(pos, vel);
                        printf("Added boid at (%.2f, %.2f)\n", mx, my);
                    }
                }
                break;

                // ============================
				// 2. Button motion ¡ú  Dragging nid
                // ============================
            case SDL_MOUSEMOTION:
                if (dragging_nid) {
                    Config::TARGET_X = (float)event.motion.x;
                    Config::TARGET_Y = (float)event.motion.y;

                    printf("Dragging nid to (%.2f, %.2f)\n",
                        Config::TARGET_X, Config::TARGET_Y);
                }
                break;

                // ============================
				// 3. Button up ¡ú  Stop dragging nid
                // ============================
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && dragging_nid) {
                    dragging_nid = false;
                    printf("Stopped dragging nid\n");
                }
                break;
            } // switch end

        }
        else {
            char const* e = SDL_GetError();
            if (e != NULL && strlen(e) != 0) return 1;

            do_update();
            do_render();
        }

    } // end while

    SDL_DestroyRenderer(g.renderer);
    SDL_DestroyWindow(g.window);
    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
