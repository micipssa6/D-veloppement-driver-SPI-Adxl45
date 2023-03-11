/*
 * adxl345.c
 *
 *  Created on: Mar 11, 2023
 *      Author: Khaled
 */

#include "adxl345.h"
#include <stdint.h>
#include "stm32f4xx_hal_spi.h"

void ADXL_Init(SPI_HandleTypeDef* hspi)
{
  uint8_t tx_buffer[2] = {0}; // Buffer pour la trame d'initialisation

  // Activer la mesure en écrivant la valeur 0x08 dans le registre POWER_CTL
  tx_buffer[0] = 0x2D;
  tx_buffer[1] = 0x08;
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);   // Activer le CS
  HAL_SPI_Transmit(hspi, tx_buffer, 2, 100);               // Envoyer la trame
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);     // Désactiver le CS

  // Configurer le registre DATA_FORMAT pour avoir une résolution de 4mg/LSB et une plage de ±2g
  tx_buffer[0] = 0x31;
  tx_buffer[1] = 0x08;
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);   // Activer le CS
  HAL_SPI_Transmit(hspi, tx_buffer, 2, 100);               // Envoyer la trame
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);     // Désactiver le CS
}

void ADXL_ReadAccel(SPI_HandleTypeDef* hspi, int16_t* accel_data)
{
  uint8_t tx_buffer[7] = {0};  // Buffer pour la trame de lecture
  uint8_t rx_buffer[7] = {0};  // Buffer pour la réception de la trame

  // Configurer le premier octet (0x32) pour lire les données des 3 axes
  tx_buffer[0] = ADXL345_DATAX0 | (1 << 7) | (1 << 6) | (1 << 5);

  // Envoyer la trame de lecture
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);   // Activer le CS
  HAL_SPI_TransmitReceive(hspi, tx_buffer, rx_buffer, 7, 100); // Envoyer et recevoir la trame
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);     // Désactiver le CS
  // Les données des axes X, Y et Z sont stockées dans les octets 1 à 6 de la trame reçue
  // Les octets sont stockés en little-endian, donc il faut inverser l'ordre des octets pour obtenir la valeur correcte
  accel_data[0] = (rx_buffer[1] << 8) | rx_buffer[0];
  accel_data[1] = (rx_buffer[3] << 8) | rx_buffer[2];
  accel_data[2] = (rx_buffer[5] << 8) | rx_buffer[4];
 }
