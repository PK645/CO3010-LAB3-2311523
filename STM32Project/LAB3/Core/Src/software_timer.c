/*
 * software_timer.c
 *
 *  Created on: Nov 5, 2025
 *      Author: khanh
 */

#include "software_timer.h"

uint8_t  timerFlags[TIMER_NUMBER];
static int16_t timerCounters[TIMER_NUMBER];

static uint32_t accum_ms = 0;  // cộng dồn mili-giây thật từ ISR

void timerSet(int ticks, int index) {
    if (index >= 0 && index < TIMER_NUMBER) {
        if (ticks < 0) ticks = 0;
        timerCounters[index] = ticks;
        timerFlags[index] = 0;
    }
}

void timerSetMs(int duration_ms, int index) {
    if (duration_ms < 0) duration_ms = 0;
    // Quy đổi ms -> số tick logic (ceil)
    int ticks = (duration_ms + TIMER_DURATION - 1) / TIMER_DURATION;
    timerSet(ticks, index);
}

/* Mỗi lần gọi = trôi qua 1 tick logic (10 ms) */
void timerRun(void) {
    for (int i = 0; i < TIMER_NUMBER; i++) {
        if (timerCounters[i] > 0) {
            timerCounters[i]--;
            if (timerCounters[i] == 0) {
                timerFlags[i] = 1;
            }
        }
    }
}

/* Gọi trong HAL_TIM_PeriodElapsedCallback:
   actual_ms là chu kỳ ngắt thật (1, 10, 100...) */
void timerOnIsrElapsed(uint32_t actual_ms) {
    accum_ms += actual_ms;
    while (accum_ms >= TIMER_DURATION) {
        accum_ms -= TIMER_DURATION;
        timerRun();               // phát 1 tick logic = 10 ms
    }
}
