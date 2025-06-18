#include "kernel.hpp"
#include <cstring>  // para strcmp

void read_line(TerminalRootOS& terminal, char* buffer, int max_len) {
  int index = 0;
  while (index < max_len - 1) {
    uint8_t scancode = terminal.read_key_scancode();
    char c = terminal.translate_scancode(scancode);

    if (c == '\n') {
      terminal.printf("\n");
      break;
    } else if (c == '\b') {
      if (index > 0) {
        index--;
        terminal.printf("\b");
      }
    } else if (c && c >= 32 && c <= 126) {
      buffer[index++] = c;
      char out[2] = { c, '\0' };
      terminal.printf(out);
    }
  }
  buffer[index] = '\0';
}

void execute_command(TerminalRootOS& terminal, const char* input) {
  if (strcmp(input, "help") == 0) {
    terminal.printf("Comandos disponíveis:\n");
    terminal.printf("  help   - Lista os comandos\n");
    terminal.printf("  info   - Exibe informacoes do sistema\n");
    terminal.printf("  clear  - Limpa a tela\n");
    terminal.printf("  reboot - Reinicia o sistema\n");
  } else if (strcmp(input, "info") == 0) {
    terminal.printf("DranuxSO v1.0 - SO academico\n");
    terminal.printf("Compilado para arquitetura x86 32-bit\n");
    terminal.printf("Autor: Douglas - Centro Universitario Sao Judas\n");
  } else if (strcmp(input, "clear") == 0) {
    terminal.clear_screen();
  } else if (strcmp(input, "reboot") == 0) {
    terminal.printf("Reiniciando...\n");
    terminal.reboot_system();
  } else {
    terminal.printf("Comando desconhecido. Digite 'help' para ajuda.\n");
  }
}

extern "C" void kmain(void* multiboot_structure, unsigned int magicnumber) {
  TerminalRootOS terminal;

  terminal.printf("  +-----------------------------------------------+\n");
  terminal.printf("  |           ::     DranuxSO     ::              |\n");
  terminal.printf("  +-----------------------------------------------+\n");
  terminal.printf("  |     Centro Universitario Sao Judas Unimonte   |\n");
  terminal.printf("  +-----------------------------------------------+\n");
  terminal.printf("  |  Digite 'help' para comandos ou 'reboot'      |\n");
  terminal.printf("  +-----------------------------------------------+\n\n");

  while (1) {
    terminal.printf("> ");
    char input[128];
    read_line(terminal, input, sizeof(input));
    execute_command(terminal, input);
  }
}
