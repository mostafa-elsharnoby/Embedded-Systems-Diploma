#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

void Ultrasonic_edgeProcessing(void);
void Ultrasonic_init(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_Trigger(void);


#endif
