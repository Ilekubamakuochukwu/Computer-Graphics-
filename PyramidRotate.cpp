#include "Renderer3D.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath> // For sin() function

// Define the structure for 3D points and edges if not already defined
struct Point3D {
    float x, y, z;
};

struct Edge {
    int start, end;
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Check if Renderer is created successfully
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Instantiate Renderer3D
    Renderer3D render3D(renderer);

    // Define the pyramid geometry
    std::vector<Point3D> points = {
        {0, 1, 0}, {-1, 0, -1}, {-1, 0, 1}, {1, 0, -1}, {1, 0, 1}
    };
    std::vector<Edge> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {2, 4}, {4, 3}, {3, 1}
    };

    render3D.setPointsAndEdges(points, edges);

    bool running = true;
    SDL_Event e;
    float scale = 0.0f;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        // Animation - scaling the pyramid
        scale = 0.5f * sin(SDL_GetTicks() / 1000.0f) + 1.0f;
        for (auto& point : points) {
            point.y *= scale; // Scale height of the pyramid
        }
        render3D.setPointsAndEdges(points, edges); // Update points in Renderer3D

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Clear with black
        SDL_RenderClear(renderer);

        render3D.render(); // Render the updated pyramid

        SDL_RenderPresent(renderer); // Update screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
