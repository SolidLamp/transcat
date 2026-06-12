#ifndef TRANSCAT_FLAGS_H
#define TRANSCAT_FLAGS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int len;
    uint8_t type;
    uint32_t colours[5];
} FLAG;

inline FLAG get_flag(char* string, size_t len);

#endif
