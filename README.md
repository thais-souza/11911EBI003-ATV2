# PISCAR LED NO STM32F401

Os arquivos do repositório em questão tem o objetivo de enviar um comando para o microcontrolador STM32F401 piscar o seu LED integrado. Este está conectado à porta PC13, conforme o esquemático disponível em [STM32F401 Schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F401CCU6_WeAct_Black_Pill_V1.2.pdf). Para isso, tem-se quatro arquivos base:
- main.c
- startup.c
- linker script
- makefile.

Inicialmente é necessário definir as regiões de memória onde serão inseridos o stack pointer (SP), os vetores de interrupção, os dados pré-inicializados e não inicializados. Para isso, foi criada uma seção específica denominada **isr_vectors**, contendo o SP, os 15 vetores para as exceções do sistema e os outros 85 para requisições de interrupção gerais. Esses atributos foram colocados em sequência em um vetor dentro do **statup.c**. Além disso, uma vez que eles precisam estar na memória FLASH, essa imposição foi feita no **linker script**. Em relação aos dados do projeto, há a necessidade de a seção .bss ser inicializada em zero (por meio do **startup.c**), limpando qualquer valor existente previamente, e ser colocada na RAM (por meio do **linker script**). 