# DranuxSO

Um sistema operacional acadêmico **32-bit** desenvolvido como projeto educacional, baseado no kernel do [Terminal Root OS](https://github.com/terroo/terminalroot-os). O DranuxSO implementa um terminal interativo com comandos básicos e interface personalizada.

[DranuxSO - Sistema Operacional Acadêmico]

## Sobre o Projeto

O **DranuxSO** é um sistema operacional educacional desenvolvido para fins acadêmicos no Centro Universitário São Judas. O projeto demonstra conceitos fundamentais de sistemas operacionais, incluindo:

- Kernel básico em C++
- Interface de terminal VGA
- Sistema de entrada de teclado
- Processamento de comandos interativos
- Gerenciamento de memória e hardware

## Funcionalidades

### Comandos Disponíveis
- **`help`** - Lista todos os comandos disponíveis
- **`info`** - Exibe informações do sistema e autor
- **`clear`** - Limpa a tela do terminal
- **`reboot`** - Reinicia o sistema

### Características Técnicas
- Arquitetura x86 32-bit
- Kernel escrito em C++
- Assembly GNU para bootloader
- Interface VGA direta
- Sistema de entrada de teclado PS/2
- Terminal interativo com prompt

## Tecnologias Utilizadas

- **C++** - Linguagem principal do kernel
- **GNU Assembler** - Assembly para bootloader
- **Make** - Sistema de build
- **QEMU** - Emulação para testes

---

## Pré-requisitos

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential qemu-kvm
```

### Windows (WSL)
```bash
sudo apt update
sudo apt install build-essential qemu-kvm
```

### macOS
```bash
brew install gcc make qemu
```

## Compilação e Execução

### 1. Clone o repositório
```bash
git clone https://github.com/seu-usuario/dranuxso
cd dranuxso
```

### 2. Compile o projeto
```bash
make
```

### 3. Execute no QEMU
```bash
qemu-system-i386 -kernel DranuxOS.bin
```

**Alternativa para 64-bit:**
```bash
qemu-system-x86_64 -kernel DranuxOS.bin
```

## Instalação no GRUB (Opcional)

Para adicionar o DranuxSO ao menu de boot do GRUB Legacy:

1. **Mova o binário:**
```bash
sudo mv DranuxOS.bin /boot/dranuxso.bin
```

2. **Edite o GRUB:**
```bash
sudo vim /boot/grub/grub.cfg
```

3. **Adicione a entrada:**
```bash
### BEGIN DRANUXSO

menuentry 'DranuxSO - Sistema Acadêmico' {
  multiboot /boot/dranuxso.bin
  boot
}

### END DRANUXSO
```

> **Nota:** Esta opção não funciona em sistemas UEFI, apenas em BIOS Legacy.

---

## Estrutura do Projeto

```
DranuxSO/
├── main.cpp          # Ponto de entrada e lógica principal
├── kernel.cpp        # Implementação do kernel
├── kernel.hpp        # Definições da classe TerminalRootOS
├── loader.s          # Assembly do bootloader
├── linker.ld         # Script do linker
├── Makefile          # Configuração de build
├── DranuxOS.bin      # Binário executável
├── LICENSE           # Licença GPL v3
└── README.md         # Este arquivo
```

## Contexto Acadêmico

Este projeto foi desenvolvido como parte do curso de Organização de computadores e Sistemas Operacionais no **Centro Universitário São Judas**, demonstrando:

- Conceitos fundamentais de kernels
- Interação com hardware de baixo nível
- Desenvolvimento de sistemas embarcados
- Programação em Assembly e C++

## Modificações do Projeto Original

O DranuxSO é baseado no projeto [Terminal Root OS](https://github.com/terroo/terminalroot-os) de [terroo](https://github.com/terroo), com as seguintes modificações:

- Sistema de comandos interativo
- Interface personalizada para instituição acadêmica
- Funcionalidades adicionais (`help`, `info`, `clear`, `reboot`)
- Melhorias na entrada de teclado
- Processamento de comandos em tempo real
- Mensagens e branding personalizados

## Licença

Este projeto é licenciado sob a **GNU General Public License v3.0** - veja o arquivo [LICENSE](LICENSE) para detalhes.

O projeto original [Terminal Root OS](https://github.com/terroo/terminalroot-os) também está licenciado sob GPL v3.

## Autor

**Douglas** - Centro Universitário São Judas

## Agradecimentos

- [terroo](https://github.com/terroo) pelo projeto base [Terminal Root OS](https://github.com/terroo/terminalroot-os)
- Centro Universitário São Judas pelo suporte acadêmico
- Comunidade open source por disponibilizar ferramentas como QEMU e GCC

---

## Contribuições

Contribuições são bem-vindas! Este é um projeto educacional, então sinta-se à vontade para:

- Reportar bugs
- Sugerir melhorias
- Adicionar novas funcionalidades
- Melhorar a documentação

---

**DranuxSO v1.0** - Um sistema operacional educacional desenvolvido para fins acadêmicos.
