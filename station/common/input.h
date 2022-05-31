#ifndef __INPUT_H
#define __INPUT_H

typedef enum
{
    LOW_TO_HIGH = 1,
    HIGH_TO_LOW = 2,
    ANY_EDGE = 3
}   input_int_type_t;

typedef void (*input_int_handle_t) (int pin);
void input_create(int pin, input_int_type_t type);
void input_set_callback(void *cb);

#endif