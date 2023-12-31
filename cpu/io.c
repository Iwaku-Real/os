#include <stdint.h>
#include "io.h"

uint8_t inb(uint16_t port){
  uint8_t result;
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

uint16_t inw(uint16_t port){
  uint16_t result;
  asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void outb(uint16_t port, uint8_t data){
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

void outw(uint16_t port, uint16_t data){
  asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
