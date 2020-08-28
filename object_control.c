/** @file */
#include "object_control.h"

/**
 * @brief Obj_getUint32 To convert the 8 bit integer data array to a 32 bit integer value
 * @param data 8 bit integer array
 * @return 32 bit integer value
 */
uint32_t Obj_getUint32(const uint8_t data[])
{
    Obj_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    b.u8[2] = data[2];
    b.u8[3] = data[3];
    return b.u32[0];
}

/**
 * @brief Obj_getUint16 To convert the 8 bit integer data array to a 16 bit integer value
 * @param data 8 bit integer array
 * @return 16 bit integer value
 */
uint16_t Obj_getUint16(const uint8_t data[]){
    Obj_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    return b.u16[0];
}

/**
 * @brief Obj_setUint32 To set the 8 bit integer data array with coming 32 bit integer value
 * @param data 8 bit integer data array to be set
 * @param value 32 bit integer value
 */
void Obj_setUint32(uint8_t data[], const uint32_t value)
{
    Obj_bytes_t b;
    b.u32[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
    data[2] = b.u8[2];
    data[3] = b.u8[3];
}

/**
 * @brief Obj_setUint16 To set the 8 bit integer data array with coming 16 bit integer value
 * @param data 8 bit integer data array to be set
 * @param value 16 bit integer value
 */
void Obj_setUint16(uint8_t data[], const uint16_t value){
    Obj_bytes_t b;
    b.u16[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
}

/**
 * @brief findObject To find the location of the object inside the objects array that has the same index with control object and locate&save the location of that object to control object
 * @param control The control object used to acquire the index of the object in the objects array
 * @return Appropriate Obj_Err_Code enum showing the result of the find object action
 */
static Obj_Error_Code findObject(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* indexListHead;

    uint16_t index = control->obj_arg.index;

    for (int i = 0; i < control->nof_index; i++) {

        indexListHead = &control->obj_index[i];

        if (indexListHead->index == index) {

            control->obj_arg.i_element = i;
            return OBJ_ERR_SUCCESS;
        }

    }

    return OBJ_ERR_NO_INDEX;
};

/**
 * @brief getObjectAdress To find out whether the wanted object is a index object or subindex object and after that to get the address of the wanted object in the memory using the information about the type of the object
 * @param control The control object used to acquire the location of the object in the memory
 * @return Appropriate Obj_Err_Code enum showing the result of the get object address action
 */
static Obj_Error_Code getObjectAdress(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.data = object->data;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.data = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].data;

    return OBJ_ERR_SUCCESS;
};

/**
 * @brief getObjectLength To find out whether the wanted object is a index object or subindex object and after that to get the length that the wanted object covers in the memory using the information about the type of the object
 * @param control The control object used to acquire the area that the object covers in the memory
 * @return Appropriate Obj_Err_Code enum showing the result of the get object length action
 */
static Obj_Error_Code getObjectLength(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.length = object->length;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.length = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].length;

    return OBJ_ERR_SUCCESS;
};

/**
 * @brief getObjectAttr To find out whether the wanted object is a index object or subindex object and after that to get the read/write attribute of the object using the information about the type of the object
 * @param control The control object used to acquire the read/write attribute of the object
 * @return Appropriate Obj_Err_Code enum showing the result of the get object attribute action
 */
static Obj_Error_Code getObjectAttr(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.attr = object->attr;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.attr = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].attr;

    return OBJ_ERR_SUCCESS;
};

/**
 * @brief initWriteRead Starts reading object or writing to the object process after getting all of the information about the target object
 * @param control The object that stores all the needed information to locate the target object
 * @param index The index of the target object
 * @param subIndex The subIndex number of the target object (if the target object is an index object than this will be 0)
 * @return Appropriate Obj_Err_Code enum showing the result of initiating reading or writing process
 */
static Obj_Error_Code initWriteRead(Obj_control_t* control, uint16_t index, uint8_t subIndex) {

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    control->obj_arg.index = index;
    control->obj_arg.subIndex = subIndex;

    err = findObject(control);
    if (err != OBJ_ERR_SUCCESS) return err;

    err = getObjectAdress(control);
    if (err != OBJ_ERR_SUCCESS) return err;

    err = getObjectLength(control);
    if (err != OBJ_ERR_SUCCESS) return err;

    err = getObjectAttr(control);
    if (err != OBJ_ERR_SUCCESS) return err;

    control->obj_arg.databuffer = (const uint8_t*)&control->databuffer;

    return OBJ_ERR_SUCCESS;
};

/**
 * @brief obj_read Main function to read a target object in the memory
 * @param control The object that stores all the needed information to locate the target object
 * @param index The index of the target object
 * @param subIndex The subIndex number of the target object (if the target object is an index object than this will be 0)
 * @return Appropriate Obj_Err_Code enum showing the result of reading process
 */
Obj_Error_Code obj_read(Obj_control_t* control, uint16_t index, uint8_t subIndex){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    err = initWriteRead(control, index, subIndex);
    if (err != OBJ_ERR_SUCCESS) return err;

    uint8_t* buffer = (uint8_t*) control->obj_arg.databuffer;
    uint8_t* Objectdata = (uint8_t*) control->obj_arg.data;
    uint8_t length = control->obj_arg.length;

    if ((control->obj_arg.attr & OBJ_READABLE) == 0) return OBJ_ERR_WRITEONLY;

    if (Objectdata != 0) {
        while (length--){
            *(buffer++) = *(Objectdata++);
        }
    }

    return OBJ_ERR_SUCCESS;
};

/**
 * @brief obj_write Main function to write to a target object in the memory
 * @param control The object that stores all the needed information to locate the target object
 * @param index The index of the target object
 * @param subIndex The subIndex number of the target object (if the target object is an index object than this will be 0)
 * @return Appropriate Obj_Err_Code enum showing the result of writing process
 */
Obj_Error_Code obj_write(Obj_control_t* control, uint16_t index, uint8_t subIndex){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    err = initWriteRead(control, index, subIndex);
    if (err != OBJ_ERR_SUCCESS) return err;

    uint8_t* buffer = (uint8_t*) control->obj_arg.databuffer;
    uint8_t* Objectdata = (uint8_t*) control->obj_arg.data;
    uint8_t length = control->obj_arg.length;

    if ((control->obj_arg.attr & OBJ_WRITEABLE) == 0) return OBJ_ERR_READONLY;

    if (Objectdata != 0) {
        while (length--){
            *(Objectdata++) = *(buffer++);
        }
    }

    return OBJ_ERR_SUCCESS;
};

