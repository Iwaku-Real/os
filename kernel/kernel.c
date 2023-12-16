#include "../drivers/vga.h"
#include "../cpu/idt.h"

void _kmain(void){
  idt_init();
  puts("Hello, world from a 32-bit kernel! \x01\x02\ntest", WHITE_ON_BLACK);
}
