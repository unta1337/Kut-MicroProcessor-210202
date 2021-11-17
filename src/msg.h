#ifndef _MSG_H
#define _MSG_H

#include "mbed.h"

void getString(Serial* src, char dest[], int size, char terminator = ';')
{
    char buffer = src->getc();
    
    for (int i = 0; i < size; i++)
        dest[i] = 0;
    
    int index = 0;
    while (buffer != terminator && index < size)
    {
        dest[index++] = buffer;
        buffer = src->getc();
    }
}

void msgOut(Serial* src, Serial* dest, char msg[])
{
    int index = 0;
    while (msg[index] != '\0')
        dest->putc(msg[index++]);
    dest->putc(';');
}

void msgIn(Serial* src, char dest[])
{
    getString(src, dest, 100);
}

#endif