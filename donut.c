#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define WIDTH  1050
#define HEIGHT 1050

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Variabili globali per l'animazione
float A = 0.0f, B = 0.0f;

void drawTorus(SDL_Renderer* renderer, float R1, float R2, float K1, float K2) {
    float cosA = cosf(A), sinA = sinf(A);
    float cosB = cosf(B), sinB = sinf(B);

    for (float theta = 0; theta < 2 * M_PI; theta += 0.07f) {
        float cost = cosf(theta), sint = sinf(theta);
        for (float phi = 0; phi < 2 * M_PI; phi += 0.02f) {
            float cosp = cosf(phi), sinp = sinf(phi);

            // Coordinate del punto sulla superficie del torus
            float circleX = R2 + R1 * cosp;
            float circleY = R1 * sinp;

            // Rotazioni 3D
            float x = circleX * (cosB * cost + sinA * sinB * sint) - circleY * cosA * sinB;
            float y = circleX * (sinB * cost - sinA * cosB * sint) + circleY * cosA * cosB;
            float z = cosA * circleX * sint + circleY * sinA;

            // Proiezione prospettica in 2D
            float ooz = 1.0f / (K2 + z); // One over Z
            int xp = (int)(WIDTH  / 2 + K1 * ooz * x);
            int yp = (int)(HEIGHT / 2 - K1 * ooz * y); // Y è invertito

            // Disegna il punto
            if (xp >= 0 && xp < WIDTH && yp >= 0 && yp < HEIGHT)
                SDL_RenderDrawPoint(renderer, xp, yp);
        }
    }
}

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Errore inizializzazione SDL: %s\n", SDL_GetError());
        return 1;
    }

    float R1, R2;
    printf("Inserisci il raggio del tubo (R1): ");
    scanf("%f", &R1);
    printf("Inserisci il raggio grande (R2): ");
    scanf("%f", &R2);

    float K2 = (R1 + R2) * 2.0f;
    float K1 = WIDTH * K2 / (8.0f * (R1 + R2));

    SDL_Window* window = SDL_CreateWindow(
        "Torus 3D - Donut SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Errore creazione finestra: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Errore creazione renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
                running = 0;
        }

        // Aggiorna angoli per la rotazione
        A += 0.07f;
        B += 0.03f;

        // Pulisce lo schermo
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // bianco
        SDL_RenderClear(renderer);

        // Imposta colore del torus (nero)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Disegna il torus
        drawTorus(renderer, R1, R2, K1, K2);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
