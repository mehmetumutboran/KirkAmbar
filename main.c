/** @file */
#include <stdio.h>
#include "object_control.h"

/**** Used extern to obtain that object from another class that defines it. ****/
extern const Obj_index_t index_objects[NOF_INDEX_ARRAY];

static Obj_control_t obj_control;
Obj_control_t* control;

/**
 * @brief main Application layer of the project that includes test cases.
 * @return 0, return value is not important.
 */
int main()
{

    Obj_Error_Code err;

    /**** Read NullParam Error ****/
    err = obj_read(control, 0x1000, 3);
    if (err == OBJ_ERR_SUCCESS){
        printf("Successfully read: %X\n", Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Read error: %d\n", err);

    control = &obj_control;

    control->obj_index = index_objects;
    control->nof_index = NOF_INDEX_ARRAY;

    /**** Successful Write #1 ****/
    uint32_t data = 0x12345678;
    Obj_setUint32(control->databuffer, data);

    err = obj_write(control, 0x1002, 0);

    if (err == OBJ_ERR_SUCCESS){
        printf("Write successful to Index:0x%X subIndex:0x%X data:0x%X\n",
               control->obj_arg.index,
               control->obj_arg.subIndex,
               Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Write data error: %d\n", err);

    /**** Successful Write #2 ****/
    uint8_t data2 = 0x24;
    Obj_setUint32(control->databuffer, data2);

    err = obj_write(control, 0x1001, 2);

    if (err == OBJ_ERR_SUCCESS){
        printf("Write successful to Index:0x%X subIndex:0x%X data:0x%X\n",
               control->obj_arg.index,
               control->obj_arg.subIndex,
               Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Write data error: %d\n", err);

    /**** Write Index Error ****/
    uint32_t data3 = 0x11111111;
    Obj_setUint32(control->databuffer, data3);

    err = obj_write(control, 0x1004, 0);

    if (err == OBJ_ERR_SUCCESS){
        printf("Write successful to Index:0x%X subIndex:0x%X data:0x%X\n",
               control->obj_arg.index,
               control->obj_arg.subIndex,
               Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Write data error: %d\n", err);

    /**** Write Readonly Error ****/
    uint32_t data4 = 0x87654321;
    Obj_setUint32(control->databuffer, data4);

    err = obj_write(control, 0x1003, 0);

    if (err == OBJ_ERR_SUCCESS){
        printf("Write successful to Index:0x%X subIndex:0x%X data:0x%X\n",
               control->obj_arg.index,
               control->obj_arg.subIndex,
               Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Write data error: %d\n", err);

    /**** Successful Read ****/
    err = obj_read(control, 0x1002, 0);
    if (err == OBJ_ERR_SUCCESS){
        printf("Successfully read: %X\n", Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Read error: %d\n", err);

    /**** Successful Read #2 ****/
    err = obj_read(control, 0x1001, 2);
    if (err == OBJ_ERR_SUCCESS){
        printf("Successfully read: %X\n", Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Read error: %d\n", err);

    /**** Read SubIndex Error ****/
    err = obj_read(control, 0x1001, 6);
    if (err == OBJ_ERR_SUCCESS){
        printf("Successfully read: %X\n", Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Read error: %d\n", err);

    /**** Read Writeonly Error ****/
    err = obj_read(control, 0x2002, 0);
    if (err == OBJ_ERR_SUCCESS){
        printf("Successfully read: %X\n", Obj_getUint32(control->obj_arg.databuffer));
    } else printf("Read error: %d\n", err);

    return 0;
}

