#ifndef _MAIN_H
#define _MAIN_H

#include "gpio_init.h"
#include "PWMs.h"
#include "button_checks.h"

#define signalFlag 0x01

osThreadId_t t1;
osThreadId_t t2;
osThreadId_t t3;
uint32_t flagsSet2;
uint32_t flagsSet3;
uint32_t flagsWait2;
uint32_t flagsWait3;
void thread1(void* argum);
void thread2(void* argum);
void thread3(void* argum);

#endif /*_MAIN_H*/
