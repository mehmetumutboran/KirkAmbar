#ifndef OBJECT_CONTROL_H
#define OBJECT_CONTROL_H

#include <stdint.h>
#include "objects.h"

typedef union{
    uint8_t u8[8];
    uint16_t u16[4];
    uint32_t u32[2];
} Obj_bytes_t;

typedef enum{
    OBJ_ERR_SUCCESS = 0x0000,
    OBJ_ERR_NO_INDEX = 0x0002,
    OBJ_ERR_NO_SUB_INDEX = 0x0004,
    OBJ_ERR_WRITEONLY = 0x0008,
    OBJ_ERR_READONLY = 0x0010,
    OBJ_ERR_NULL_PARAM = 0x0020,
} Obj_Error_Code;

typedef struct{
    void* data;
    const uint8_t* databuffer;
    uint16_t i_element;
    uint16_t index;
    uint8_t subIndex;
    uint8_t attr;
    uint16_t length;
} Obj_arg_t;

typedef struct{
    const Obj_index_t* obj_index;
    uint8_t nof_index;
    uint8_t databuffer[4];
    Obj_arg_t obj_arg;
} Obj_control_t;

Obj_Error_Code obj_read(Obj_control_t* control, uint16_t index, uint8_t subIndex);

Obj_Error_Code obj_write(Obj_control_t *control , uint16_t index, uint8_t subIndex);

#endif // OBJECT_CONTROL_H
