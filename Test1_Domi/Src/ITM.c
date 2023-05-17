#include "ITM.h"
#include <stdio.h>
#include <stdint.h>

int _write(int file, char *ptr, int len) {
    int i;
    for (i = 0; i < len; i++) {
        ITM_SendChar(*ptr++);
    }
    return len;
}


