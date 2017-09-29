#include "rmref_h.h"

rmRef_H::rmRef_H()
{
}

rmRef_H rmRef_H::operator=(const rmRef_H &rm){
    rmRef_H rmResult;
    rmResult.key = rm.key;
    rmResult.value = rm.value;
    rmResult.value_size = rm.value_size;
    return rmResult;
}
bool rmRef_H::operator==(const rmRef_H &rm){
    bool flag = true;
    if(rm.key != this->key || rm.value != this->value || rm.value_size != this->value_size) {
       flag = false;
    }
    return flag;
}

bool rmRef_H::operator!=(const rmRef_H &rm){
    bool flag = false;
    if(rm.key != this->key || rm.value != this->value || rm.value_size != this->value_size) {
       flag = true;
    }
    return flag;
}
