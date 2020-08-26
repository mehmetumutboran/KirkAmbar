#include "object_control.h"

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

static Obj_Error_Code getObjectAdress(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.data = object->data;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.data = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].data;

    return OBJ_ERR_SUCCESS;
};

static Obj_Error_Code getObjectLength(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.length = object->length;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.length = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].length;

    return OBJ_ERR_SUCCESS;
};

static Obj_Error_Code getObjectAttr(Obj_control_t* control){

    if (control == 0) return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) control->obj_arg.attr = object->attr;
    else if (object->nof_SubIndex < control->obj_arg.subIndex) return OBJ_ERR_NO_SUB_INDEX;
    else control->obj_arg.attr = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].attr;

    return OBJ_ERR_SUCCESS;
};

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

