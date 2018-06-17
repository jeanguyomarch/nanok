/* NanoK - MIT License */

#ifndef NANOK_ALARM_H__
#define NANOK_ALARM_H__

typedef struct alarm s_alarm;

KAPI void nk_alarm_init(void);
KAPI s_alarm *nk_alarm_add(const s_chrono_duration *wake_up);

#endif /* ! NANOK_ALARM_H__ */
