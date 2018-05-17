#ifndef KY_ALARM_H__
#define KY_ALARM_H__

typedef struct alarm s_alarm;

KAPI void ky_alarm_init(void);
KAPI s_alarm *ky_alarm_add(const s_chrono_duration *wake_up);

#endif /* ! KY_ALARM_H__ */
