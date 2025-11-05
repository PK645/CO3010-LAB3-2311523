/*
 * software_timer.h
 *
 *  Created on: Nov 5, 2025
 *      Author: khanh
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include <stdint.h>

#define TIMER_NUMBER        4
#define TIME_DURATION      10   // tick logic cố định 10 ms

extern uint8_t timerFlags[TIMER_NUMBER];

/* Đặt timer theo số tick logic (mỗi tick = 10 ms) */
void timerSet(int ticks, int index);

/* Đặt timer theo mili-giây, tự quy đổi ra tick logic */
void timerSetMs(int duration_ms, int index);

/* Chạy 1 bước tick logic (giảm bộ đếm 1 tick = 10 ms) */
void timerRun(void);

/* Gọi trong ISR: báo đã trôi qua actual_ms (1, 10, 100...) */
void timerOnIsrElapsed(uint32_t actual_ms);

#endif /* INC_SOFTWARE_TIMER_H_ */

