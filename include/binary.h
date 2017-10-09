#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>

#include "coral.h"


uint8_t *binary_serialize(Ast ast, lint *len);
Ast *binary_deserialize(uint8_t *binary, lint len);


#endif // BINARY_H
