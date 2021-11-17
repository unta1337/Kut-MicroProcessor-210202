#ifndef _MSG_H
#define _MSG_H

#include "mbed.h"

void getString(Serial* src, char dest[], int size)
{
    char buffer = src->getc();
    
    for (int i = 0; i < size; i++)
        dest[i] = 0;
    
    int index = 0;
    while (buffer != ';' && index < size)
    {
        dest[index++] = buffer;
        buffer = src->getc();
    }
}

void msgOut(Serial* src, Serial* dest)
{
    char str[100] = "";
    getString(src, str, 100);

    int index = 0;
    while (str[index] != '\0')
        dest->putc(str[index++]);
    dest->putc(';');
}

void msgIn(Serial* src, Serial* dest)
{
    char str[100] = "";
    getString(src, str, 100);
    dest->printf("%s\n", str);
}

void cmdOut(Serial* src, Serial* dest)
{
    char str[100] = "";
    getString(src, str, 100);
    dest->printf("%s\r\n", str);
}

#endif