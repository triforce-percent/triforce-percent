#define MESSAGE_DATA_STATIC

#include "message_data_fmt.h"

#define DECLARE_MESSAGE(textId, type, yPos, message) \
    __attribute__((no_reorder)) const char _message_ ## textId [sizeof(message)] = { message END };

#include "messages.c"
