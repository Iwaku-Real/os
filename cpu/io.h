#ifndef IO_H
#define IO_H

#include <stdint.h>


/* io.h - provides functions for reading and writing to CPU I/O ports */


uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t data);

void outw(uint16_t port, uint16_t data);

#endif
