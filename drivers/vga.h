#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "../cpu/io.h"

#define MAX_COLS 80
#define MAX_ROWS 25
#define WHITE_ON_BLACK 0x07

#define VGA_MEM_TEXT 0xb8000

enum {
  VGA_PORT_REG = 0x3d4,
  VGA_PORT_DATA = 0x3d5
};

enum {
  VGA_REG_CURH = 14,
  VGA_REG_CURL = 15
};

typedef struct vgacell {
  uint8_t ch;
  uint8_t attr;
} vgacell;

#define get_offset(col, row) (row * MAX_COLS + col)
#define get_row(offset) offset / MAX_COLS
#define get_col(offset) (offset-(get_row(offset)*MAX_COLS))

void vga_set_reg(uint8_t reg) {
  outb(VGA_PORT_REG, reg);
}

uint8_t vga_read_data() {
  return inb(VGA_PORT_DATA);
}

void vga_write_data(uint8_t data) {
  outb(VGA_PORT_DATA, data);
}

uint8_t vga_read_reg(uint8_t reg){
  vga_set_reg(reg);
  return vga_read_data();
}

void vga_write_reg(uint8_t reg, uint8_t data){
  vga_set_reg(reg);
  vga_write_data(data);
}

void vga_set_cur(int offset){
  vga_write_reg(VGA_REG_CURH, (uint8_t)(offset >> 8));
  vga_write_reg(VGA_REG_CURL, (uint8_t)(offset & 0xff));
}

int vga_get_cur(){
  vga_set_reg(VGA_REG_CURH);
  int offset = vga_read_data() << 8;
  vga_set_reg(VGA_REG_CURL);
  offset += vga_read_data();
  return offset;
}

/*
int putchar_at(char c, int col, int row, char attr){
  uint8_t *vmem = (uint8_t)VGA_MEM_TEXT;
  int offset = vga_get_cur();
 
  if(c == '\n'){
    row = get_row(offset);
    offset = get_offset(0, row+1);
  } else if(c == '\b'){
    vmem[offset] = 0;
    vmem[offset+1] = attr;
  } else {
    vmem[offset] = c;
    vmem[offset+1] = attr;
  }

  // TODO: scroll screen 

  vga_set_cur(offset);
  return offset;
}

void puts(char *str){
  int offset = 0;//vga_get_cur();
  int row = get_row(offset), col = get_col(offset);

  int i = 0;
  while(str[i]!=0) {
    offset = putchar_at(str[i++], col, row, WHITE_ON_BLACK);
    row = get_row(offset), col = get_col(offset);
  }
}
*/

void puts(char *str, const char attrib){
  vgacell *vmem = (vgacell*)0xb8000;
  char c;
  int cursor = vga_get_cur();
  
  while((c=(char)*str++)){
    if(c=='\n'){
      cursor = get_offset(0,get_row(cursor)+1);
    } else {
      vmem[cursor].ch = c;
      vmem[cursor++].attr = attrib;
    }

    vga_set_cur(cursor);
  }
}

#endif
