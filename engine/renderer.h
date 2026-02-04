#ifndef RENDERER_H
#define RENDERER_H

struct canvas {
    /* We are in VGA text mode (80x25), so the size of the x and y in the canvas is: 80x25 */
    int canvas_x; /* 80 */
    int canvas_y; /* 25 */

    struct sphere* sphere;

    struct viewport* viewport;

};

struct scene {
    int camera[2]; /* X | Y | Z COORDINATES */
};

struct viewport {
    int Vw;
    int Vh;
    int Cw;
    int Ch;
};

struct sphere {
    int radius;



};

void canvasPutPixel();

#endif
