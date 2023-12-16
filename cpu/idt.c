#include "idt.h"

void idt_set_gate(int n, uint32_t handler) {
  idt[n].offsetl = (uint16_t)((handler) & 0xffff);
  idt[n].selector = 8;
  idt[n]._zero = 0;
  idt[n].flags = 0x8e;
  idt[n].offseth = (uint16_t)(((handler) >> 16) & 0xffff);
}

void idt_init() {
  idt_reg.base = (uint32_t) &idt;
  idt_reg.limit = 256 * sizeof(idt_gate_t) - 1;
  asm volatile("lidtl (%0)" : : "r" (&idt_reg));
}
