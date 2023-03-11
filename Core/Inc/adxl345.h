/*
 * adxl345.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Khaled
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_
#include <stdint.h>

// Definition des registres qui contiennent les données

#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATAZ0 0x36
#define ADXL345_DATAZ1 0x37

// Fonctions d'initialisation et de lecture des données
// Fonction qui initialise le capteur
void ADXL_Init(void);
// Fonction pour lire les accéleration
void ADXL_ReadAccel(int16_t* accel_data);

#endif /* INC_ADXL345_H_ */





