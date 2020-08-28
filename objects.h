/** @file */
#ifndef OBJECTS_H
#define OBJECTS_H

#define NOF_INDEX_ARRAY 7

#include <stdint.h>

/**
 * Sub-indexes of objects structure
 */
/*0x1000*/ typedef struct{
    uint8_t noSubIndex;
    uint8_t LED1;
    uint8_t LED2;
    uint8_t LED3;
    uint8_t LED4;
} LED_Service_t;

/**
 * Sub-indexes of objects structure
 */
/*0x1001*/ typedef struct{
    uint8_t noSubIndex;
    uint8_t CH1_Duty;
    uint8_t CH2_Duty;
    uint16_t PWM_Status;
} PWM_Service_t;

/**
 * Structure for all objetcs
 */
typedef struct{
    /*0x1000*/ LED_Service_t LED_Service;
    /*0x1001*/ PWM_Service_t PWM_Service;
    /*0x1002*/ uint32_t value_1;
    /*0x1003*/ uint32_t value_2;
    /*0x2000*/ uint16_t value_3;
    /*0x2001*/ uint8_t value_4;
    /*0x2002*/ uint8_t value_5;
} objects_t;

/**
 * Index object structure
 */
typedef struct{
    uint16_t index;
    uint8_t nof_SubIndex;
    uint8_t attr;
    uint16_t length;
    void* data;
} Obj_index_t;

/**
 * SubIndex object structure
 */
typedef struct{
    void* data;
    uint16_t attr;
    uint16_t length;
} Obj_subIndex_t;

/**
 * RW determiner enum
 */
typedef enum{
    OBJ_WRITEABLE        = 0x0001U,
    OBJ_READABLE         = 0x0002U,
}obj_attr_t;

#endif // OBJECTS_H
