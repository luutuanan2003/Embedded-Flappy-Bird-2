#include "bird.h"
#include "uart0.h"
#include "framebf.h"

void initBird(hitboxBird* bird, float width, float height, float x, float y, float speed) {
    bird->width = width;
    bird->height = height;
    bird->x = x;
    bird->y = y;
    bird->speed = speed;
}

void clearBird(hitboxBird* bird){
    float x1 = bird->x;
    float y1 = bird->y;
    float x2 = bird->x + bird->width;
    float y2 = bird->y + bird->height;
    drawRectARGB32(x1, y1, x2, y2, 0x00000000, 1);
}

void drawBird(hitboxBird* bird) {
    float x1 = bird->x;
    float y1 = bird->y;
    float x2 = bird->x + bird->width;
    float y2 = bird->y + bird->height;
    drawRectARGB32(x1, y1, x2, y2, 0x00AA0000, 1);
}

void updateBirdFall(hitboxBird* bird) {
    
    bird->speed += G; // Increase speed by gravity
    bird->y += bird->speed + 0.5 * G; // Update y position based on speed and gravity
    drawBird(bird);
    delay(200); // Delay for 100ms; adjust as needed for desired frame rate
    clearBird(bird);

}

void updateBirdonClick(hitboxBird* bird){

    bird->y += bird->speed + 0.5 * G;
    bird->speed += G;
    if (uart_isReadByteReady()) {
        char c = uart_getc();
        if (c == 'a') {
            clearBird(bird);
            uart_puts("Space bar hit\n");
            bird->speed = SPEEDFLY;
        }
    }
    drawBird(bird);
    delay(200); // Delay for 100ms; adjust as needed for desired frame rate
    clearBird(bird);
}
