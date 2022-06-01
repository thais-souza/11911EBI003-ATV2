#include <stdint.h>

#define SRAM_START 0x20000000U                /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE (64U * 1024U)               /* Tam. SRAM STM32F401 64K */
#define SRAM_END ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F401 */

#define STACK_START SRAM_END                  /* Inicio da Stack */

/* Rotina para o tratamento da Reset Exception */
void reset_handler(void);
/* Por padrao, o endereco utilizado na tabela de vetores de interrupcao vem da rotina de tratamento geral
("default_handler"). No entanto, a funcao definida como weak pode ser sobrescrita durante o processo de 
linking por uma funcao com o mesmo nome em outro arquivo .c. Assim, nao e necessaria a recompilacao ou
alteracao do "startup.c" quando se implementar uma rotina de tratamento especializada.*/
void nmi_handler (void) __attribute__ ((alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler (void) __attribute__ ((weak, alias("default_handler")));

/* Variaveis exportadas pelo linker script */
extern uint32_t _sdata;             /* Inicio da secao .data */
extern uint32_t _edata;             /* Fim da secao .data */
extern uint32_t _la_data;           /* Endereco de carga na RAM da secao .data */
extern uint32_t _sbss;              /* Inicio da secao .bss */
extern uint32_t _ebss;              /* Fim da secao .bss */
extern uint32_t _etext;     

/* Vetor de interrupcoes: primeira posição para o SP e outras para as System Exceptions*/
/* Armazenamento da tabela do vetor de interrupções na secao ".isr_vectors" */
uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
    STACK_START,                          /* 0x0000 0000 */
    (uint32_t)reset_handler,              /* 0x0000 0004 */
    (uint32_t)nmi_handler,                /* 0x0000 0008 */
    (uint32_t)hardfault_handler,          /* 0x0000 000c */
    (uint32_t)memmanage_handler,          /* 0x0000 0010 */
    (uint32_t)busfault_handler,           /* 0x0000 0014 */
    (uint32_t)usagefault_handler,         /* 0x0000 0018 */
    0,                                    /* 0x0000 001c */
    0,                                    /* 0x0000 0020 */
    0,                                    /* 0x0000 0024 */
    0,                                    /* 0x0000 0028 */
    (uint32_t)svc_handler,                /* 0x0000 002c */
    (uint32_t)debugmon_handler,           /* 0x0000 0030 */
    0,                                    /* 0x0000 0034 */
    (uint32_t)pendsv_handler,             /* 0x0000 0038 */
    (uint32_t)systick_handler,            /* 0x0000 003c */
};

void reset_handler(void)
{
    /* Objetivo: copiar o conteudo da secao .data (initialized data) 
    da memoria FLASH para a SRAM e inicializar a secao .bss em zero e
    chamar a funcao main */

    uint32_t i;
    
    /* Copia a secao .data para a RAM */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;  /* Tamanho da secao .data */
    uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
    uint8_t *pSrc = (uint8_t*)&_etext;                      /* FLASH */
    for(i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    /* Preenche a secao .bss com zero */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;
    for(i = 0 ; i < size; i++)
    {
        *pDst++ = 0;
    }

    /* Chama a funcao main() */
    main();
}

void default_handler(void)
{
    while(1){};
}