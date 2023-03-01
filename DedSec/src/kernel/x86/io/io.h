#pragma once

#include <pch/pch.h>

inline unsigned char inb(unsigned short port) {
	unsigned char data;
	asm volatile("inb %1, %0" : "=a"(data) : "dN"(port));
	return data;
}
