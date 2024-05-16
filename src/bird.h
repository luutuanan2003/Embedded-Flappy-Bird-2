// constant for the bird
#define G 0.5
#define SPEEDFLY -8


// Structure to represent the bird.
typedef struct {
    float width;
    float height;
    float x;
    float y;
    float speed;
} hitboxBird;

// Function prototypes
void initBird(hitboxBird* bird, float width, float height, float x, float y, float speed);
void clearBird(hitboxBird* bird);
void updateBirdFall(hitboxBird* bird);
void updateBirdonClick(hitboxBird* bird);
