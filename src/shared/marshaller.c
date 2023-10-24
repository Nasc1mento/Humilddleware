//
// Created by afreis on 10/23/23.
//
#include <string.h>
#include <malloc.h>
#include "marshaller.h"


void marshall(const char *str, unsigned char *byteArray, size_t len) {
    byteArray = malloc(sizeof(unsigned char) * len);
    strcpy(byteArray, str);
}

void unmarshall(char *str, unsigned char *byteArray, size_t len) {
    str = malloc(sizeof(char) * len);
    strcpy(str, byteArray);
}