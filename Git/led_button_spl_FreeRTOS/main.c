#include "main.h"

int main()
{

  pins_init();

  xTaskCreate(vTaskSelect, "Select", 32, NULL, 1, NULL);
  xTaskCreate(vTaskDown, "Down", 32, NULL, 1, NULL);

  vTaskStartScheduler();

  //бесконечный цикл
  while (1)
  {

  }
}

void pins_init(void) {

    PORT_InitTypeDef PortInit; //объявление структуры PortInit

    //включить тактирование портов С, B, E
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);

    //Инициализация порта кнопки SELECT (С2) на вход
    // направление передачи данных = вход
    PortInit.PORT_OE = PORT_OE_IN;
    // режим работы вывода порта = Порт
    PortInit.PORT_FUNC = PORT_FUNC_PORT;
    // режим работы выводе =цифровой
    PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    // скорость фронта вывода= медленный
    PortInit.PORT_SPEED = PORT_SPEED_SLOW;
    // выбор вывода 2 для инициализации
    PortInit.PORT_Pin = PORT_Pin_2;
    //инициализация порта С заданными параметрами
    PORT_Init(MDR_PORTC, &PortInit);

    //Инициализация порта кнопки RIGHT (B6) на вход
    // направление передачи данных = вход
    PortInit.PORT_OE = PORT_OE_IN;
    // режим работы вывода порта = Порт
    PortInit.PORT_FUNC = PORT_FUNC_PORT;
    // режим работы выводе =цифровой
    PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    // скорость фронта вывода= медленный
    PortInit.PORT_SPEED = PORT_SPEED_SLOW;
    // выбор вывода 6 для инициализации
    PortInit.PORT_Pin = PORT_Pin_6;
    //инициализация порта С заданными параметрами
    PORT_Init(MDR_PORTB, &PortInit);

    //Инициализация порта кнопки LEFT (E3) и DOWN (E1) на вход
    // направление передачи данных = вход
    PortInit.PORT_OE = PORT_OE_IN;
    // режим работы вывода порта = Порт
    PortInit.PORT_FUNC = PORT_FUNC_PORT;
    // режим работы выводе =цифровой
    PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    // скорость фронта вывода= медленный
    PortInit.PORT_SPEED = PORT_SPEED_SLOW;
    // выбор вывода 3 для инициализации
    PortInit.PORT_Pin = PORT_Pin_3 | PORT_Pin_1;
    //инициализация порта С заданными параметрами
    PORT_Init(MDR_PORTE, &PortInit);

    //Инициализация порта C на выход
    // направление передачи данных = Выход
    PortInit.PORT_OE = PORT_OE_OUT;
    // режим работы вывода порта = Порт
    PortInit.PORT_FUNC = PORT_FUNC_PORT;
    // режим работы вывода = Цифровой
    PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    // скорость фронта вывода = медленный
    PortInit.PORT_SPEED = PORT_SPEED_SLOW;
    // выбор всех выводов для инициализации
    PortInit.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1);
    //инициализация заданными параметрами порта C
    PORT_Init(MDR_PORTC, &PortInit);

    // выключить все светодиоды при старте
    PORT_ResetBits(MDR_PORTC, LED1 | LED2);
    //PORT_ResetBits(MDR_PORTC, LED2);

}

void vTaskSelect (void *argument){

  while(1)
  {

    //если нажат SELECT
        if (PORT_ReadInputDataBit(MDR_PORTC, PORT_Pin_2) == Bit_RESET)
        {
          // включить светодиоды
          PORT_SetBits(MDR_PORTC, LED1 | LED2);
          printf("Select pressed\n");
          fflush(stdout);
        }
        else
        {
          // выключить светодиоды
          PORT_ResetBits(MDR_PORTC, LED1 | LED2);
        }
        if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_6) == Bit_RESET)
        {
          PORT_SetBits(MDR_PORTC, LED2);
          printf("Right pressed\n");
          fflush(stdout);
        }
        else
          PORT_ResetBits(MDR_PORTC, LED2);
        if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_3) == Bit_RESET)
        {
          PORT_SetBits(MDR_PORTC, LED1);
          printf("Left pressed\n");
          fflush(stdout);
        }

  }

}

void vTaskDown (void *argument){

  while(1)
  {

    // DOWN
        if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_1) == Bit_RESET)
        {
           // включить светодиоды
           PORT_SetBits(MDR_PORTC, LED1 | LED2);
           printf("Select blink\n");
           fflush(stdout);
           for (int i = 0; i < 100000; i++) {}
           PORT_ResetBits(MDR_PORTC, LED1 | LED2);
           for (int i = 0; i < 100000; i++) {}
        }
        else
        {
           // выключить светодиоды
           PORT_ResetBits(MDR_PORTC, LED1 | LED2);
        }

          PORT_ResetBits(MDR_PORTC, LED1);

  }

}

void exit(int code)
{

}
