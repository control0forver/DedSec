#include <pch/pch.h>

#include "x86/io/io.h"
#include "x86/terminal/terminal.h"

unsigned char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.'};

void isr_keyboard() {
  unsigned char scancode = inb(0x60);
  if (scancode & 0x80) {
    // key rel
  } else {
    unsigned char ch = keyboard_map[scancode];
    if (ch != 0) {
      // key pushed
      char str[2] = {(char)ch, '\0'};
      terminal_writestring(str);
    }
  }
}

extern "C"{

void _kernel_main()
{
    terminal_initialize();
    terminal_writestring("DedSec");
    terminal_writestring("now on kernel_main");
    
    for (;;){
        isr_keyboard();
    }
}

}
