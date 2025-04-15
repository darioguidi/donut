#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void getCoordinates(double R1, double R2, double theta, double *x, double *y, double *z){
    *x = R2 + R1 * cos(theta);
    *y = R1 * sin(theta);
    *z = 0.0;
}

int main(void){

    // Connessione con il Server X
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Impossibile connettersi al display\n");
        return 1;
    }

    // Creazione dello screen - schermo
    int screen = DefaultScreen(display);

    // Creazione della finestra
    Window window = XCreateSimpleWindow(
        display, RootWindow(display, screen),
        10, 10,               // Posizione (x, y)
        100, 100,             // Dimensioni (larghezza, altezza)
        1,                    // Spessore bordo
        BlackPixel(display, screen),   // Colore bordo
        WhitePixel(display, screen)    // Colore sfondo
    );

    // Mostra la finestra
    XMapWindow(display, window);

    // Calcoli per le coordinate
    double R1 = 1.0;
    double R2 = 2.0;
    double theta = M_PI / 4;  // 45 gradi

    double x, y, z;
    getCoordinates(R1, R2, theta, &x, &y, &z);

    printf("x = %f, y = %f, z = %f\n", x, y, z);

    // Attendi qualche secondo o eventi per visualizzare la finestra (facoltativo)
    XFlush(display);  // Forza l'invio dei comandi grafici

    // Chiusura della connessione
    XCloseDisplay(display);
    return 0;
}
