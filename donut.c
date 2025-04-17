#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void getCoordinates(double R1, double R2, double theta, double *x, double *y, double *z){
    *x = R2 + R1 * cos(theta);
    *y = R1 * sin(theta);
    *z = 0.0;
}

int main(void){
    
    // Connessione con il display
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Impossibile aprire il display\n");
        return 1;
    }

    // Recupera lo schermo corrente
    int screen = DefaultScreen(display);

    // Crea la finestra
    Window window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        10, 10,                 // posizione
        400, 400,               // larghezza, altezza
        1,                      // bordo
        BlackPixel(display, screen), // colore bordo
        WhitePixel(display, screen)  // colore sfondo
    );

    // Mostra la finestra
    XMapWindow(display, window);
    XFlush(display);

    // Esegui il calcolo delle coordinate
    double R1 = 1.0, R2 = 2.0, theta = M_PI / 4;
    double x, y, z;
    getCoordinates(R1, R2, theta, &x, &y, &z);
    printf("x = %f, y = %f, z = %f\n", x, y, z);

    // Ciclo di eventi per mantenere la finestra aperta
    XEvent event;
    while (1) {
        XNextEvent(display, &event);  // Attende un evento
        if (event.type == DestroyNotify) {
            break;  // Esce quando la finestra è chiusa
        }
    }

    // Chiudi la connessione con il display
    XCloseDisplay(display);
    return 0;
}
