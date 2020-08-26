#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>

/***** Sub-indexes variables structure ********************************************/
/*0x1000*/ typedef struct{
    uint8_t noSubIndex;
    uint8_t LED1;
    uint8_t LED2;
    uint8_t LED3;
    uint8_t LED4;
} LED_Service_t;

/*0x1001*/ typedef struct{
    uint8_t noSubIndex;
    uint8_t CH1_Duty;
    uint8_t CH2_Duty;
    uint16_t PWM_Status;
} PWM_Service_t;

/***** Structure for all objetcs ********************************************/
typedef struct{
    /*0x1000*/ LED_Service_t LED_Service;
    /*0x1001*/ PWM_Service_t PWM_Service;
    /*0x1002*/ uint32_t value_1;
    /*0x1003*/ uint32_t value_2;
    /*0x2000*/ uint16_t value_3;
    /*0x2001*/ uint8_t value_4;
} objects_t;

#endif // OBJECTS_H
