#include "kernel.hpp"

// Implementação de strcmp para substituir libc
extern "C" int strcmp(const char* s1, const char* s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(unsigned char*)s1 - *(unsigned char*)s2;
}

TerminalRootOS::TerminalRootOS() {
  cursor_x = 0;
  cursor_y = 0;
  clear_screen();
}

void TerminalRootOS::move_cursor(int x, int y) {
  uint16_t pos = y * VGA_WIDTH + x;
  outb(0x3D4, 14);
  outb(0x3D5, (pos >> 8) & 0xFF);
  outb(0x3D4, 15);
  outb(0x3D5, pos & 0xFF);
}

void TerminalRootOS::advance_cursor() {
  cursor_x++;
  if (cursor_x >= VGA_WIDTH) {
    cursor_x = 0;
    cursor_y++;
    if (cursor_y >= VGA_HEIGHT) {
      cursor_y = 0;
    }
  }
  move_cursor(cursor_x, cursor_y);
}

void TerminalRootOS::put_char(char c) {
  volatile char* video = (volatile char*)VGA_MEMORY;
  if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  } else if (c == '\b') {
    if (cursor_x > 0) {
      cursor_x--;
      video[(cursor_y * VGA_WIDTH + cursor_x) * 2] = ' ';
    }
  } else {
    video[(cursor_y * VGA_WIDTH + cursor_x) * 2] = c;
    video[(cursor_y * VGA_WIDTH + cursor_x) * 2 + 1] = 0x07;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
      cursor_x = 0;
      cursor_y++;
    }
  }

  if (cursor_y >= VGA_HEIGHT) {
    cursor_y = 0;
  }

  move_cursor(cursor_x, cursor_y);
}

void TerminalRootOS::clear_screen() {
  volatile char* video = (volatile char*)VGA_MEMORY;
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      int index = (y * VGA_WIDTH + x) * 2;
      video[index] = ' ';
      video[index + 1] = 0x07;
    }
  }
  cursor_x = 0;
  cursor_y = 0;
  move_cursor(cursor_x, cursor_y);
}

void TerminalRootOS::printf(const char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    put_char(str[i]);
  }
}

uint8_t TerminalRootOS::read_key_scancode() {
  while ((inb(KEYBOARD_STATUS_PORT) & 1) == 0) {}
  return inb(KEYBOARD_DATA_PORT);
}

char TerminalRootOS::translate_scancode(uint8_t scancode) {
  const char scancode_map[] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0
  };

  if (scancode >= sizeof(scancode_map)) return 0;
  return scancode_map[scancode];
}

void TerminalRootOS::reboot_system() {
  uint8_t good = 0x02;
  while (good & 0x02) {
    good = inb(0x64);
  }
  outb(0x64, 0xFE);
  __builtin_unreachable();
}

inline uint8_t TerminalRootOS::inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

inline void TerminalRootOS::outb(uint16_t port, uint8_t value) {
  asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}
