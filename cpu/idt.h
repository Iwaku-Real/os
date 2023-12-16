#pragma once
#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct {
  uint16_t offsetl;
  uint16_t selector;
  uint8_t _zero;
  uint8_t flags;
  uint16_t offseth;
} __attribute__((packed)) idt_gate_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute((packed)) idt_reg_t;

extern idt_gate_t idt[256];
extern idt_reg_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void idt_init();

#endif
