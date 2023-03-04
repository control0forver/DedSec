#include <pch/pch.h>

#include "x86/io/io.h"
#include "x86/terminal/terminal.h"

unsigned char keyboard_map[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
	'.' };


void clear_input_buf() {
	for (; inb(0x64) & 0x01; )
		inb(0x60);
}

uint8_t get_key() {
	for (;;) {
		clear_input_buf();
		uint8_t scancode = inb(0x60);
		if (!(scancode & 0x80))
			return scancode;
	}
}

void new_line() {
	terminal::gotoxy(0, terminal::get_termianl_row() + 1);
}


extern "C" {

	void _kernel_main()
	{
		terminal::initialize();
		terminal::print("DedSec");
		new_line();
		terminal::print("now on kernel_main");

		get_key();


		terminal::clear();

		// keyboard io looping
		for (;;) {


			// Key Status
			// 0 -- none
			// 1 -- released
			// 2 -- pushed
			// 3 -- pushing

			static int key_status = 0;

			clear_input_buf();

			uint8_t scancode = inb(0x60);
			if ((scancode & 0x80) == 1) {
				// key rel

				if (key_status == 1)
					key_status = 0;

				key_status = 1;
			}
			if ((scancode & 0x80) == 0) {
				// key push

				if (key_status == 2)
					key_status = 3;

				key_status = 2;
			}

			switch (key_status) {
			default:
				break;

			case 1:
			{
				terminal::clear();
				terminal::print("Key Released");
				break;
			}

			case 2:
			{
				// echo key
				terminal::clear();
				terminal::putchar(keyboard_map[scancode]);

				break;
			}

			case 3:
			{
				break;

			}
			}


			continue;
		}

	}

}
