/** @file */
#ifndef OBJECT_CONTROL_H
#define OBJECT_CONTROL_H

#include <stdint.h>
#include "objects.h"

/**
 * Union for converting an existing integer variable between uint8 array and uint32 variable
 */
typedef union{
    uint8_t u8[8];
    uint16_t u16[4];
    uint32_t u32[2];
} Obj_bytes_t;

/**
 * Enum for defining the errors that we can encounter
 * OBJ_ERR_SUCCESS = action completed successfully
 * OBJ_ERR_NO_INDEX = there is no object in the objects array that has the given index
 * OBJ_ERR_NO_SUB_INDEX = there is no subindex object of an index object with given subindex number
 * OBJ_ERR_WRITEONLY = tried to read writeonly object
 * OBJ_ERR_READONLY = tried to write to a readonly object
 * OBJ_ERR_NULL_PARAM = control object which is used to reach the actual object is null
 */
typedef enum{
    OBJ_ERR_SUCCESS = 0x0000,
    OBJ_ERR_NO_INDEX = 0x0002,
    OBJ_ERR_NO_SUB_INDEX = 0x0004,
    OBJ_ERR_WRITEONLY = 0x0008,
    OBJ_ERR_READONLY = 0x0010,
    OBJ_ERR_NULL_PARAM = 0x0020,
} Obj_Error_Code;

/**
 * The structure for storing all the information about an object that we need to read or write
 */
typedef struct{
    void* data;
    const uint8_t* databuffer;
    uint16_t i_element;
    uint16_t index;
    uint8_t subIndex;
    uint8_t attr;
    uint16_t length;
} Obj_arg_t;

/**
 * The control structure that has objects info and the value which will be written to that object or read location that the value of the object goes
 */
typedef struct{
    const Obj_index_t* obj_index;
    uint8_t nof_index;
    uint8_t databuffer[4];
    Obj_arg_t obj_arg;
} Obj_control_t;

Obj_Error_Code obj_read(Obj_control_t* control, uint16_t index, uint8_t subIndex);

Obj_Error_Code obj_write(Obj_control_t *control , uint16_t index, uint8_t subIndex);

uint32_t Obj_getUint32(const uint8_t data[]);

uint16_t Obj_getUint16(const uint8_t data[]);

void Obj_setUint32(uint8_t data[], const uint32_t value);

void Obj_setUint16(uint8_t data[], const uint16_t value);

#endif // OBJECT_CONTROL_H
