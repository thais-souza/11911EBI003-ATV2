PROG = blinky
# Nome do arquivo executável a ser gerado

CC = arm-none-eabi-gcc
# Nome do executável do compilador
LD = arm-none-eabi-gcc
# Nome do executável do linker

CP = arm-none-eabi-objcopy

CFLAGS = -c -mcpu=cortex-m4 -mthumb -Wall -O0
# Diretivas de compilação
LFLAGS = -nostdlib -T stm32f401-rom.ld
# Opções do linker

OBJS = startup.o \
	   main.o

all: $(PROG).elf

$(PROG).elf: $(OBJS)
	$(LD) $(LFLAGS) $^ -o $@
	$(CP) $(PROG).elf -O binary $(PROG).bin
# "$<" é o primeiro elemento da lista de pré-requisitos
# "$^" são todos os pré-requisitos
# "$@" é o alvo da regra
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
# "%" é o nome do target ("%.o" target-pattern, "%.c" prereq-patterns)

clean:
	rm -f *.o *.elf

# Remove todos os arquivos objeto (terminados em .o)
# Se fossemos remover apenas o "main.o": rm -f main.o