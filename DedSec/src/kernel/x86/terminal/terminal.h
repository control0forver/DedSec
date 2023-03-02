#pragma once

#include <pch/pch.h>


static class terminal {
public:
	/* Hardware text mode color constants. */
	enum vga_color
	{
		COLOR_BLACK = 0,
		COLOR_BLUE = 1,
		COLOR_GREEN = 2,
		COLOR_CYAN = 3,
		COLOR_RED = 4,
		COLOR_MAGENTA = 5,
		COLOR_BROWN = 6,
		COLOR_LIGHT_GREY = 7,
		COLOR_DARK_GREY = 8,
		COLOR_LIGHT_BLUE = 9,
		COLOR_LIGHT_GREEN = 10,
		COLOR_LIGHT_CYAN = 11,
		COLOR_LIGHT_RED = 12,
		COLOR_LIGHT_MAGENTA = 13,
		COLOR_LIGHT_BROWN = 14,
		COLOR_WHITE = 15,
	};

private:

	uint8_t make_color(enum vga_color fg, enum vga_color bg)
	{
		return fg | bg << 4;
	}

	uint16_t make_vgaentry(char c, uint8_t color)
	{
		uint16_t c16 = c;
		uint16_t color16 = color;
		return c16 | color16 << 8;
	}

	size_t strlen(const char* str)
	{
		size_t ret = 0;
		while (str[ret] != 0)
			ret++;
		return ret;
	}

public:

	static const size_t VGA_WIDTH = 80;
	static const size_t VGA_HEIGHT = 24;

private:
	size_t terminal_row;
	size_t terminal_column;
	uint8_t terminal_color;
	uint16_t* terminal_buffer;

// public get, private set data
public:
	size_t get_termianl_row() {
		return terminal_row;
	}
	size_t get_terminal_column() {
		return terminal_column;
	}
	uint8_t get_terminal_color() {
		return terminal_color;
	}

public:
	void setcolor(uint8_t color)
	{
		terminal_color = color;
	}

	void putentryat(char c, uint8_t color, size_t x, size_t y)
	{
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = make_vgaentry(c, color);
	}

	void putchar(char c)
	{
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
			{
				terminal_row = 0;
			}
		}
	}

	void print(const char* data)
	{
		size_t datalen = strlen(data);
		for (size_t i = 0; i < datalen; i++)
			putchar(data[i]);
	}

	void gotoxy(size_t x, size_t y) {
		terminal_row = y;
		terminal_column = x;
	}

	void offsetxy(size_t x, size_t y) {
		terminal_row += y;
		terminal_column += y;
	}

	void clear() {
		for (size_t y = 0; y < VGA_HEIGHT; y++)
		{
			for (size_t x = 0; x < VGA_WIDTH; x++)
			{
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			}
		}
		gotoxy(0, 0);
	}

	void initialize()
	{
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
		terminal_buffer = (uint16_t*)0xB8000;
		clear();
	}


	terminal() {

	}

	~terminal() {

	}

};