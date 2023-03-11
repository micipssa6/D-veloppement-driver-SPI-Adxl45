#include "adxl345.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

int main(void)
{
  HAL_Init();
  ADXL_Init(&hspi1);

  int16_t accel_data[3] = {0};
  while (1)
  {
    ADXL_ReadAccel(&hspi1, accel_data);
    printf("Acceleration - X: %d, Y: %d, Z: %d\n", accel_data[0], accel_data[1], accel_data[2]);
    HAL_Delay(500);
  }
}



