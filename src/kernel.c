#include "uart0.h"
#include "mbox.h"
#include "framebf.h"
#include "ex1picture.h"
#include "frames.h"
#include "bird.h"
#include "utils.h"


// Breaking Bad frames
const unsigned long* frames[] = { epd_bitmap_frame1ezgif_frame_001, epd_bitmap_frame2ezgif_frame_002, epd_bitmap_frame3ezgif_frame_003, 
                                    epd_bitmap_frame4ezgif_frame_004, epd_bitmap_frame5ezgif_frame_005, epd_bitmap_frame6ezgif_frame_006, 
                                    epd_bitmap_frame7ezgif_frame_007, epd_bitmap_frame8ezgif_frame_008, epd_bitmap_frame9ezgif_frame_009, epd_bitmap_frame30ezgif_frame_030,
                                    epd_bitmap_frame64ezgif_frame_064, epd_bitmap_frame65ezgif_frame_065, epd_bitmap_frame66ezgif_frame_066,
                                    epd_bitmap_frame67ezgif_frame_067, epd_bitmap_frame68ezgif_frame_068, epd_bitmap_frame69ezgif_frame_069,
                                    epd_bitmap_frame70ezgif_frame_070, epd_bitmap_frame71ezgif_frame_071, epd_bitmap_frame72ezgif_frame_072,
                                    epd_bitmap_frame73ezgif_frame_073, epd_bitmap_frame74ezgif_frame_074, epd_bitmap_frame75ezgif_frame_075,
                                    epd_bitmap_frame76ezgif_frame_076, epd_bitmap_frame77ezgif_frame_077, epd_bitmap_frame78ezgif_frame_078,
                                    epd_bitmap_frame79ezgif_frame_079, epd_bitmap_frame80ezgif_frame_080, epd_bitmap_frame81ezgif_frame_081,
                                    epd_bitmap_frame82ezgif_frame_082, epd_bitmap_frame83ezgif_frame_083, epd_bitmap_frame84ezgif_frame_084,
                                    epd_bitmap_frame85ezgif_frame_085, epd_bitmap_frame86ezgif_frame_086, epd_bitmap_frame87ezgif_frame_087,
                                    epd_bitmap_frame88ezgif_frame_088, epd_bitmap_frame89ezgif_frame_089, epd_bitmap_frame90ezgif_frame_090,
                                    epd_bitmap_frame91ezgif_frame_091, epd_bitmap_frame92ezgif_frame_092, epd_bitmap_frame93ezgif_frame_093,
                                    epd_bitmap_frame94ezgif_frame_094, epd_bitmap_frame95ezgif_frame_095, epd_bitmap_frame96ezgif_frame_096,
                                    epd_bitmap_frame97ezgif_frame_097, epd_bitmap_frame98ezgif_frame_098, epd_bitmap_frame99ezgif_frame_99, 
                                    epd_bitmap_frame100ezgif_frame_100, epd_bitmap_frame101ezgif_frame_101, epd_bitmap_frame102ezgif_frame_102, epd_bitmap_frame103ezgif_frame_103,
                                    epd_bitmap_frame104ezgif_frame_104, epd_bitmap_frame105ezgif_frame_105, epd_bitmap_frame106ezgif_frame_106, epd_bitmap_frame107ezgif_frame_107
                                    
                        };

int total_frames = 8;

int imgHeight = 800;
int imgWidth = 800;
int currentY = 0;

void display_video();
void display_image();
void draw_frame();


void display_video() {
    int current_frame = 0;
    while (1) {
        for (int y = 0; y < imgHeight; y++) {
            for (int x = 0; x < imgWidth; x++) {
                unsigned int index = y * imgWidth + x;
                drawPixelARGB32(x, y, frames[current_frame][index]);
            }
        }
        
        // Move to the next frame
        current_frame = (current_frame + 1) % total_frames;
        
        // Wait for 100ms before displaying the next frame
        wait_msec(100);

        // Check if a mode change has been requested after displaying the frame
        if (check_for_mode_change()) {
            uart_puts("Exiting video mode.\n");
            return; // Exit the function if a mode change is requested
        }
    }
}


void display_image() {
    // Display a single image frame
    for (int y = 0; y < imgHeight; y++) {
        for (int x = 0; x < imgWidth; x++) {
            unsigned int index = y * imgWidth + x;
            drawPixelARGB32(x, y, epd_bitmap_linhtran[index]);
        }
    }
}

void clear_screen() {
    for (int y = 0; y < imgHeight; y++) {
        for (int x = 0; x < imgWidth; x++) {
            drawPixelARGB32(x, y, 0x00000000);  // Black color
        }
    }
}


int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void mode_selection() {
    char mode = 0;
    while (1) {
        uart_puts("Select mode:\n");
        uart_puts("1: Game\n");
        uart_puts("2: Image\n");
        uart_puts("3: Video\n");
        uart_puts("4: Name Display\n");
        uart_puts("Enter choice: ");

        mode = uart_getc();
        uart_sendc(mode);  // Echo the character back to the console
        uart_puts("\n");

        switch (mode) {
           case '1':
                // Game mode: only display and update bird
                while (1) {
                    hitboxBird myBird;
                    initBird(&myBird, 100.0, 100.0, 100.0, 100.0, 0.0);

                    // Update bird and draw in smaller cycles before checking for input
                    for (int i = 0; i < 10; i++) {  // Smaller loop for faster response
                        updateBirdFall(&myBird);
                        updateBirdonClick(&myBird);
                        drawBird(&myBird);

                        // Check for mode change after each mini-cycle
                        if (check_for_mode_change()) {
                            uart_puts("Exiting game mode...\n");
                            return;  // Exit the function if a mode change is requested
                        }
                    }
                }
                break;

            case '2':
                display_image();
                while (!check_for_mode_change()) {  // Allow continuous image display until mode change
                    // Repeat the image display or maintain the display
                }
                break;

            case '3':
                display_video();
                while (!check_for_mode_change()) {  // Allow continuous name display until mode change
                    // Repeat the name display or maintain the display
                }
                break;  

            case '4':
                display_name();
                while (!check_for_mode_change()) {  // Allow continuous name display until mode change
                    // Repeat the name display or maintain the display
                }
                break;
            default:
                uart_puts("Invalid mode. Please try again.\n");
        }
    }
}


int check_for_mode_change() {
    if (uart_isReadByteReady()) {  // Non-blocking check for data availability
        char key = uart_getc();  // Read the character
        uart_sendc(key);  // Optional: Echo the character back for feedback
        if (key == 'r') {
            uart_puts("Exiting current mode...\n");
            clear_screen();
            return 1;  // Signal to exit the current mode
            
        }
    }
    return 0;  // Continue in the current mode
}





// void main(int argc, char **argv) {
//     // Initialize system
//     uart_init();
//     uart_puts("\n\nHello World\n");
//     framebf_init();

//     uart_puts("\nReceived arguments:\n");

//     if (argc > 1) {
//         uart_puts("First argument: ");
//         uart_puts(argv[1]);  // Directly print the first argument
//         uart_puts("\n");
//     } else {
//         uart_puts("No arguments received.\n");
//     }

//     hitboxBird myBird;

//     if (argc > 1) {
//         if (strcmp(argv[1], "mode=game") == 0) {
//             // Game mode: only display and update bird
//             while (1) {
                
//                 initBird(&myBird, 100.0, 100.0, 100.0, 100.0, 0.0);
//                 updateBirdFall(&myBird);
//                 updateBirdonClick(&myBird);
//                 drawBird(&myBird);
//             }
//         } else if (strcmp(argv[1], "mode=image") == 0) {
//             // Image display mode
//             display_image();
//             return; // Exit after displaying image
//         } else if (strcmp(argv[1], "mode=video") == 0) {
//             // Video display mode
//             display_video();
//             return; // Exit after displaying video
//         }
//     }

//     // Normal operation: Fall-through case when no specific mode is specified
//     while (1) {
//         if (uart_isReadByteReady()) {
//             char c = uart_getc();
//             uart_sendc(c);

//             switch (c) {
//                 case 'w':
//                     if (currentY > 0) currentY -= 10;
//                     break;
//                 case 's':
//                     if (currentY < (imgHeight - myBird.height)) currentY += 10;
//                     break;
//                 case 'v':
//                     display_video(); // Trigger video display again if needed
//                     break;
//                 case 'i':
//                     display_image(); // Trigger image display again if needed
//                     break;
//             }
//         }
//         updateBirdFall(&myBird);
//         updateBirdonClick(&myBird);
//         drawBird(&myBird);
//     }
// }

void main(int argc, char **argv) {
    // Initialize system
    uart_init();
    uart_puts("System Initialized. Welcome!\n");
    framebf_init();

    // Display mode selection menu
    mode_selection();

    // Fallback to continuous monitoring if mode exits improperly
    while (1) {
        if (uart_isReadByteReady()) {
            char c = uart_getc();
            uart_sendc(c);
        }
    }
}

//Task iii
void display_name() {
    char *names[] = {"Le Trung Kien", "Luu Tuan An", "Pham Nguyen Minh Dang", "Dang Vinh Luan"};
    unsigned int colors[] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00FFFF00}; // Red, Green, Blue, Yellow
    int numNames = sizeof(names) / sizeof(names[0]);

    int startY = 50; // Starting Y position for the first name
    for (int i = 0; i < numNames; i++)
    {
        drawString(100, startY, names[i], colors[i], 2); // X position, Y position, string, color, zoom
        startY += FONT_HEIGHT * 5 + 10;                  // Move to next line, increase by font height and some padding
    }
}

