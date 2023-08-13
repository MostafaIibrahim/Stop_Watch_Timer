/*
 * seven_seg_config.h
 *
 *  Created on: Aug 12, 2023
 *      Author: SOFT ZONE
 */

#ifndef SEVEN_SEG_CONFIG_H_
#define SEVEN_SEG_CONFIG_H_

#define COMMON_ANODE

#define SEVEN_SEG_CONTROL_PORT              DIO_PORTA
#define SEVEN_SEG_DATA_PORT                 DIO_PORTC

#define SEC1_PIN               DIO_PIN0
#define SEC2_PIN               DIO_PIN1
#define MIN1_PIN               DIO_PIN2
#define MIN2_PIN               DIO_PIN3
#define HR1_PIN                DIO_PIN4
#define HR2_PIN                DIO_PIN5

#ifdef COMMON_ANODE
#define SEVEN_SEG_ENABLE                    DIO_LOW
#endif
#ifdef  COMMON_CATHODE
#define SEVEN_SEG_ENABLE                    DIO_HIGH
#endif

#endif /* SEVEN_SEG_CONFIG_H_ */
