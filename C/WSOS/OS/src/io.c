#include "./io.h"
#include "./types.h"

// Track the current cursor's row and column
volatile int cursorCol = 0;
volatile int cursorRow = 0;

// Define a keymap to convert keyboard scancodes to ASCII
char keymap[128] = {};

// C version of assembly I/O port instructions
// Allows for reading and writing with I/O
// The keyboard status port is 0x64
// The keyboard data port is 0x60
// More info here:
// https://wiki.osdev.org/I/O_Ports
// https://wiki.osdev.org/Port_IO
// https://bochs.sourceforge.io/techspec/PORTS.LST

// outb (out byte) - write an 8-bit value to an I/O port address (16-bit)
void outb(uint16 port, uint8 value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
	return;
}

// outw (out word) - write an 16-bit value to an I/O port address (16-bit)
void outw(uint16 port, uint16 value)
{
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
	return;
}

// inb (in byte) - read an 8-bit value from an I/O port address (16-bit)
uint8 inb(uint16 port)
{
   uint8 ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// inw (in word) - read an 16-bit value from an I/O port address (16-bit)
uint16 inw(uint16 port)
{
   uint16 ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// intialize key map to keyboard scan codes
void initkeymap() {
    // Assign alphabet
    keymap[0x1E] = 'a';
    keymap[0x30] = 'b';
    keymap[0x2E] = 'c';
    keymap[0x20] = 'd';
    keymap[0x12] = 'e';
    keymap[0x21] = 'f';
    keymap[0x22] = 'g';
    keymap[0x23] = 'h';
    keymap[0x17] = 'i';
    keymap[0x24] = 'j';
    keymap[0x25] = 'k';
    keymap[0x26] = 'l';
    keymap[0x32] = 'm';
    keymap[0x31] = 'n';
    keymap[0x18] = 'o';
    keymap[0x19] = 'p';
    keymap[0x10] = 'q';
    keymap[0x13] = 'r';
    keymap[0x1F] = 's';
    keymap[0x14] = 't';
    keymap[0x16] = 'u';
    keymap[0x2F] = 'v';
    keymap[0x11] = 'w';
    keymap[0x2D] = 'x';
    keymap[0x15] = 'y';
    keymap[0x2C] = 'z';

    // Assign numbers 0-9
    keymap[0x02] = '1';
    keymap[0x03] = '2';
    keymap[0x04] = '3';
    keymap[0x05] = '4';
    keymap[0x06] = '5';
    keymap[0x07] = '6';
    keymap[0x08] = '7';
    keymap[0x09] = '8';
    keymap[0x0A] = '9';
    keymap[0x0B] = '0';


    // Assign space and new line characters
    keymap[0x39] = ' ';
    keymap[0x1C] = '\n';
}

// Poll keyboard input for scancode then return associated character
char getchar() {
    // Loop until valid input
    while (1) {
        // Loop polling until last bit of status is 1, signifying data is ready
        while ((inb(0x64) & 0x01) == 0);

        // Read scancode from data address
        uint16 code = inb(0x60);

        // If release, call again and wait for press
        if (code & 0x80) {
            return getchar();
        }

        // Return associated char
        return keymap[code];

    }
}

// Scan keyboard input for a string until ended by ENTER
void scanf(char string[]) {
    // Initial index on string
    int index = 0;

    // get first char
    char ch = getchar();

    // If char is not newline, append to string, print, and get next
    while (ch != '\n') {
        string[index] = ch;
        putchar(ch);
        index += 1;
        ch = getchar();
    }

    // End terminator character
    string[index] = '\0';
}

// Setting the cursor does not display anything visually
// Setting the cursor is simply used by putchar() to find where to print next
// This can also be set independently of putchar() to print at any x, y coordinate on the screen
void setcursor(int x, int y)
{
    // keep cursor within screen bounds
    cursorCol = x % 80;
    cursorRow = (y + x / 80) % 25;
}

// Using a pointer to video memory we can put characters to the display
// Every two addresses contain a character and a color
char putchar(char character)
{   
    // If newline character, increment to next line
    if (character == '\n') {
        setcursor(0, cursorRow + 1);
        return character;
    }

    char *screenPosition = (char *)0xB8000 + (2 * cursorCol) + (2 * 80 * cursorRow);

    *screenPosition = character;
    screenPosition++;

    //screenPosition = 0x2A; // 0x2A = b0010 1010 // 010 = 2 = green // 1010 = 10 = light green
    *screenPosition = 0x0F; // 0x0F b0000 1111 // 000 = 0 = black // 1111 = 15 = white
    screenPosition++;

    setcursor(cursorCol + 1, cursorRow);
    return character;
}

// Print the character array (string) using putchar()
// Print until we find a NULL terminator (0)
int printf(char string[]) 
{
    int count = 0;
    
    // loop through string until null terminator, and print each char
    while (string[count] != '\0') {
        putchar(string[count]);
        count++;
    }

    return count; 
}

// Prints an integer to the display
// Useful for debugging
int printint(uint32 n) 
{
	int characterCount = 0;
	if (n >= 10)
	{
        characterCount = printint(n / 10);
    }
    putchar('0' + (n % 10));
	characterCount++;

	return characterCount;
}

// Clear the screen by placing a ' ' character in every character location
void clearscreen()
{
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 80; x++) 
        {
            char *screenPosition = (char *)0xB8000 + (2 * x) + (2 * 80 * y);

            *screenPosition = ' ';
            screenPosition++;

            // *screenPosition = 0x2A; // 0x2A = b0010 1010 // 010 = 2 = green // 1010 = 10 = light green
            *screenPosition = 0x0F; // 0x0F b0000 1111 // 000 = 0 = black // 1111 = 15 = white
            screenPosition++;
        }
    }
    cursorCol = 0;
    cursorRow = 0;
    return;
}