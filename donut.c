#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 800
#define HEIGHT 800

void drawTorus(SDL_Renderer* renderer, float R1, float R2) {
    float x, y;
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    for (float theta = 0.0f; theta < 2 * M_PI; theta += 0.05f) {
        for (float phi = 0.0f; phi < 2 * M_PI; phi += 0.05f) {
            // Formula toroidale 2D
            x = (R2 + R1 * cos(phi)) * cos(theta);
            y = (R2 + R1 * cos(phi)) * sin(theta);

            // Traslazione al centro della finestra
            SDL_RenderDrawPoint(renderer, centerX + (int)x, centerY + (int)y);
        }
    }
}

int main(void) {
<<<<<<< HEAD
    float R1, R2;

    // Inizializza SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Errore inizializzazione SDL: %s\n", SDL_GetError());
=======
    
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Impossibile aprire il display\n");
>>>>>>> 163ee7c2392177481cefefc61518515140564a8f
        return 1;
    }

    printf("Uqanto vuoi il Raggio della ciambella? \n");
    scanf("%f", &R1);

    printf("Uqanto vuoi il Raggio dello spessore ciambella? \n");
    scanf("%f", &R2);

    SDL_Window* window = SDL_CreateWindow(
        "Ciambella 2D",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );    

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // Colore sfondo: bianco
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Colore ciambella: nero
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawTorus(renderer, R1, R2);

    // Mostra il rendering
    SDL_RenderPresent(renderer);

    // Aspetta chiusura finestra o tasto
    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN) {
                running = 0;
            }
        }
        SDL_Delay(10); // evita ciclo troppo veloce
    }

    // Chiusura programma
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


