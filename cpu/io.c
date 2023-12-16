#include <stdint.h>
#include "io.h"

/* io.c - provides functions for reading and writing to CPU I/O ports */


uint8_t inb(uint16_t port){
  // inb() reads a byte from the I/O port number given as an argument

  // first, let's declare a variable to store our result
  uint8_t result;

  // we cannot use C to read from an I/O port, so we have to use assembly
  // it would be more compilcated to create another .asm file for this so we will instead use inline assembler syntax
  // this allows us to hardcode assembly instructions in C code wherever we need to
  // it looks complex at first, but I'll explain it here
  asm( // start of inline asm statement
  // first, we have our actual asm instruction(s)
  // this means read a byte from the port number specified by dx and put it into al
  "in %%dx, %%al"
  // colon denotes the end of instructions, next we have our output(s)
  // "=a" means we set to the value of the e'a'x register the C variable "result"
  : "=a" (result)
  // again we have a colon so end of outputs, these are the input(s)
  // we set the e'd'x register to the C variable "port"
  // notice how we don't use "=" here because it is an input
  : "d" (port)); // end of inline asm statement

  // now that our value is in "result", we can return it
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
