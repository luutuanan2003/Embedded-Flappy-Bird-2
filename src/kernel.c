#include "uart0.h"
#include "mbox.h"
#include "framebf.h"
#include "ex1picture.h"
#include "frames.h"
#include "bird.h"


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


void display_video() {
    int current_frame = 0;
    while (1) {
        for (int y = 0; y < imgHeight; y++) {
            for (int x = 0; x < imgWidth; x++) {
                unsigned int index = y * imgWidth + x;
                drawPixelARGB32(x, y, frames[current_frame][index]);
            }
        }
        
        current_frame = (current_frame + 1) % total_frames; // Cycle through frames
        delay(500); // Delay for 100ms; adjust as needed for desired frame rate
    }
}




void main()
{
// set up serial console
uart_init();
// say hello
uart_puts("\n\nHello World");
// Initialize frame buffer
framebf_init();

// // Create and initialize the bird.

// hitboxBird myBird;

// initBird(&myBird, 100.0, 100.0, 100.0, 100.0, 0.0);


// // Calculate hitbox coordinates
// float x1 = myBird.x;
// float y1 = myBird.y;
// float x2 = myBird.x + myBird.width;
// float y2 = myBird.y + myBird.height;

// uart_puts("\nx1");

// uart_dec(x1);

// uart_puts("\ny1");

// uart_dec(y1);
// uart_puts("\nx2");

// uart_dec(x2);
// uart_puts("\ny2");

// uart_dec(y2);


// // Testing to draw the hitbox of the bird
// drawRectARGB32(x1, y1, x2, y2, 0x00AA0000, 1);
// //drawRectARGB32(100.5,100.5,400.5,400.5,0x00AA0000,1); //RED


// while(1) {
//     updateBirdFall(&myBird);
//     updateBirdonClick(&myBird);
// }




display_video();

// // Drawing the image
// for (int y = 0; y < imgHeight; y++) {
//     for (int x = 0; x < imgWidth; x++) {
//         unsigned int index = y * imgWidth + x;
//         drawPixelARGB32(x, y, epd_bitmap_linhtran[index]);
//     }
// }

// echo everything back
while(1) {
    if (uart_isReadByteReady()) {
        char c = uart_getc();
        if (c == 'w' && currentY > 0) {
            currentY -= 10; // Scroll up by 10 pixels
        } else if (c == 's' && currentY < (imgHeight - height)) {
            currentY += 10; // Scroll down by 10 pixels
        }
        scrollImage();
        uart_sendc(c);
    }
}
}

