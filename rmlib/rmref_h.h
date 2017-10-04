#ifndef RMREF_H_H
#define RMREF_H_H


struct rmRef_H
{
public:
    char* key;
    void* value;
    int value_size;

    rmRef_H();
    rmRef_H(char *key, void *value, int value_size);

    rmRef_H operator=(const rmRef_H &rm);
    bool operator==(const rmRef_H &rm);
    bool operator!=(const rmRef_H &rm);
};
#endif // RMREF_H_H
