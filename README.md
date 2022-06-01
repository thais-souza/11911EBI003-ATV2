# PISCAR LED NO STM32F401

Os arquivos do repositório em questão tem o objetivo de enviar um comando para o microcontrolador STM32F401 piscar o seu LED integrado. Este está conectado à porta PC13, conforme o esquemático disponível em [STM32F401 Schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F401CCU6_WeAct_Black_Pill_V1.2.pdf). Para isso, tem-se quatro arquivos base:
- main.c
- startup.c
- linker script
- makefile.

Inicialmente é necessário definir as regiões de memória onde serão inseridos o stack pointer (SP), os vetores de interrupção, os dados pré-inicializados e não inicializados. Para isso, foi criada uma seção específica denominada **isr_vectors**, contendo o SP, os 15 vetores para as exceções do sistema e os outros 85 para requisições de interrupção gerais. Esses atributos foram colocados em sequência em um vetor dentro do **startup.c**. Além disso, uma vez que eles precisam estar na memória FLASH, essa imposição foi feita no **linker script**.

Em relação aos dados do projeto, há a necessidade da seção .bss ser inicializada em zero (por meio do **startup.c**), limpando qualquer valor existente previamente, e ser colocada na RAM (por meio do **linker script**). Já a seção .data deve ser copiada da memória FLASH para a RAM, conforme feito nos dois arquivos citados. A partir dessa alocação de memória para os espaços devidos, faz-se o programa principal, **main.c**.

Para a configuração da porta PC13, habilita-se o clock do GPIOC, o que é feito por meio do registrador RCC_AHB1RSTR. Então, é configurado o modo de operação do GPIO (como uma saída de propósito geral), o tipo de saída (push-pull) e a configuração da saída (nem pull-up e nem pull-down). Essas características são impostas no **main.c** anteriormente à execução dos comandos em looping. Foi utilizado como base o [STM32F401 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00096844-stm32f401xb-c-and-stm32f401xd-e-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf).

Por fim, para que o LED piscasse, o bit correspondente era setado ou resetado após um determinado período de tempo definido pela variável LED_DELAY. Destaca-se que o processo de compilação foi automatizado com o arquivo **Makefile**. Assim, as diretivas de compilação e as opções do linker, assim como a definição de quais arquivos gerar e a lista de dependências, não precisavam ser escritas a cada compilação. 