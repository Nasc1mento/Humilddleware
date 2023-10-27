//
// Created by afreis on 10/23/23.
//

#ifndef HUMILDDLEWARE_MARSHALLER_H
#define HUMILDDLEWARE_MARSHALLER_H

#include <stddef.h>

void marshall(const char *str, unsigned char *byteArray, size_t len);

void unmarshall(char *str, unsigned char *byteArray, size_t len);

#endif //HUMILDDLEWARE_MARSHALLER_H
