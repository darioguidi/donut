#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

void drawPoints(Display *display, Window window, GC gc) {
    float i, j;

    XClearWindow(display, window);

    for (j = 0; j < 6.28; j += 0.07) {
        for (i = 0; i < 6.28; i += 0.02) {
            float x3d = j * i + cos(i);
            float y3d = i * sin(i);

            // Trasforma coordinate "matematiche" in pixel
            int x_screen = (int)(WIDTH / 2 + x3d * 30);
            int y_screen = (int)(HEIGHT / 2 - y3d * 30); // asse y invertito

            // Disegna punto
            if (x_screen >= 0 && x_screen < WIDTH && y_screen >= 0 && y_screen < HEIGHT) {
                XDrawPoint(display, window, gc, x_screen, y_screen);
            }
        }
    }

    XFlush(display);
}

int main(void) {
    
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Impossibile aprire il display\n");
        return 1;
    }

    int screen = DefaultScreen(display);

    Window window = XCreateSimpleWindow(display,
                                        RootWindow(display, screen),
                                        10, 10,
                                        WIDTH, HEIGHT,
                                        1,
                                        BlackPixel(display, screen),
                                        WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, NULL);

    XEvent event;
    int running = 1;

    while (running) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            drawPoints(display, window, gc);
        } else if (event.type == KeyPress) {
            running = 0; // Esce alla pressione di un tasto
        }
    }

    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
