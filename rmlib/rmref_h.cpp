#include "rmref_h.h"

rmRef_H::rmRef_H(){
    this->key = nullptr;
    this->value = nullptr;
    this->value_size = 0;
}

rmRef_H::rmRef_H(char *key, void *value, int value_size){
    this->key = key;
    this->value = value;
    this->value_size = value_size;
}

rmRef_H rmRef_H::operator=(const rmRef_H &rm){
    rmRef_H rmResult(rm.key, rm.value, rm.value_size);
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
