


// Constants for the RNG
#define M 4294967296ULL // 2^32
#define A 1664525
#define C 1013904223


// Structure to hold column data
typedef struct {
    int width;
    int height;
    int blank;
    int distance;
    int speed;
    int ls[3][2]; // Array to store positions of columns
} Columns;

// Function prototypes
void initColumns(Columns *col);
void drawColumns(Columns* col);
void updateColumns(Columns *col);
unsigned int RNG_random();
void clearColumns(int x1, int y1, int x2, int y2);