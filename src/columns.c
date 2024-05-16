#include "columns.h"
#include "framebf.h"


#define COLUMNWIDTH 40
#define COLUMNHEIGHT 400
#define BLANK 160
#define DISTANCE 400
#define COLUMNSPEED 5
#define WINDOWHEIGHT 600
#define INITIAL_OFFSET 500


// Global variable for RNG state
unsigned long seed = 123456789; // This seed can be set to any value
// Function to generate a random number using RNG
unsigned int RNG_random() {
    seed = (A * seed + C) % M;
    return (unsigned int)seed;
}


// Function to initialize columns
void initColumns(Columns *col) {
    col->width = COLUMNWIDTH;
    col->height = COLUMNHEIGHT;
    col->blank = BLANK;
    col->distance = DISTANCE;
    col->speed = COLUMNSPEED;

    // if (run){
    //     for (int i = 0; i < 3; i++) {
    //     col->ls[i][0] = i * col->distance ;
    //     int range = (WINDOWHEIGHT - col->blank - 120) / 20 + 1;
    //     col->ls[i][1] = (RNG_random() % range + 3) * 20 + 60;
    //     }
    // } else if (!run){
    //     for (int i = 0; i < 3; i++) {
    //     col->ls[i][0] = i * col->distance ;
    //     int range = (WINDOWHEIGHT - col->blank - 120) / 20 + 1;
    //     col->ls[i][1] = (RNG_random() % range + 3) * 20 + 60;
    //     }
    // }

    //original code
    for (int i = 0; i < 3; i++) {
        col->ls[i][0] = i * col->distance + INITIAL_OFFSET;
        int range = (WINDOWHEIGHT - col->blank - 120) / 20 + 1;
        col->ls[i][1] = (RNG_random() % range + 3) * 20 + 60;
    }

}


void clearColumns(int x1, int y1, int x2, int y2){
    drawRectARGB32(x1, y1, x2, y2, 0x00000000, 1);
}

// Function to update and redraw columns
void updateColumns(Columns* col) {
    
    // Clear the previous positions of the columns
    for (int i = 0; i < 3; i++) {
        int x1 = col->ls[i][0];
        int y1 = 0; // Start from the top of the screen
        int x2 = x1 + col->width;
        int y2 = WINDOWHEIGHT; // Clear the entire column height
        clearColumns(x1, y1, x2, y2);
    }

    // Update the position of each column
    for (int i = 0; i < 3; i++) {
        col->ls[i][0] -= col->speed;
    }
      

    // Check if the first column is out of the screen and shift columns
    if (col->ls[0][0] < -col->width) {
        for (int i = 0; i < 2; i++) {
            col->ls[i][0] = col->ls[i + 1][0];
            col->ls[i][1] = col->ls[i + 1][1];
        }
        int lastIndex = 2;
        col->ls[lastIndex][0] = col->ls[lastIndex - 1][0] + col->distance + 60;
        int range = (WINDOWHEIGHT - col->blank - 120) / 10 + 1;
        col->ls[lastIndex][1] = (RNG_random() % range) * 10 + 60 + col->blank / 2;
    }

    // Draw the columns in their new positions
    drawColumns(col);
}

// Function to draw columns using the user's custom drawing function
void drawColumns(Columns* col) {
    for (int i = 0; i < 3; i++) {
        // Coordinates for the upper part of the column
        int x1 = col->ls[i][0];
        int y1 = 0; // Start from the top of the screen
        int x2 = x1 + col->width; // x1 + width of the column
        int y2 = col->ls[i][1] - col->blank / 2; // Top of the gap

        drawRectARGB32(x1, y1, x2, y2, 0x0032CD32, 1);

        // Coordinates for the lower part of the column
        y1 = col->ls[i][1] + col->blank / 2; // Bottom of the gap
        y2 = WINDOWHEIGHT; // Assuming WINDOWHEIGHT is the height of your screen

        drawRectARGB32(x1, y1, x2, y2, 0x0032CD32, 1);
    }
}
