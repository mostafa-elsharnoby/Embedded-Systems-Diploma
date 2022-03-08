/*
 ================================================================================================
 Name        : motor.h
 Author      : Mostafa Elsharnoby
 Description : MC2 Code in Final Project
 Date        : 25/10/2021
 ================================================================================================
 */


#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

void motor_init();
void motor_CW();
void motor_ACW();
void motor_stop();


#endif /* MOTOR_H_ */
