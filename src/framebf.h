// ----------------------------------- framebf.h -------------------------------------
void framebf_init();
void scrollImage();
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);

//New Tags for Screen Display
#define MBOX_TAG_SETPHYWH 0x48003
#define MBOX_TAG_SETVIRTWH 0x48004
#define MBOX_TAG_SETVIRTOFF 0x48009
#define MBOX_TAG_SETDEPTH 0x48005
#define MBOX_TAG_SETPXLORDR 0x48006
#define MBOX_TAG_GETFB 0x40001
#define MBOX_TAG_GETPITCH 0x40008

extern int imgHeight;
extern int imgWidth;
extern int currentY;
extern const unsigned long epd_bitmap_linhtran[];
extern unsigned int height;