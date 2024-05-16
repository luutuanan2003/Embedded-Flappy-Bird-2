#ifndef FONT_H
#define FONT_H

// Declare enumerations or constants for dimensions
#define FONT_WIDTH 8      // Width in pixels
#define FONT_HEIGHT 8     // Height in pixels
#define FONT_BPG 8        // Bytes per character glyph
#define FONT_BPL 1        // Bytes per line
#define FONT_NUMGLYPHS 224 // Total number of characters in the font

// Declare the font array as extern if it's defined in a .c file
extern unsigned char font[FONT_NUMGLYPHS][FONT_BPG];

#endif // FONT_H