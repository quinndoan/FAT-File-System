#include <strHandler.h>

uint16_t getStrLen(const char *str)
{
    uint16_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}