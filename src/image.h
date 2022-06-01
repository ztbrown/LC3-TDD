#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>

int read_image(const char *path);
void read_image_file(FILE* file);
uint16_t swap16(uint16_t instr);

#endif // IMAGE_H

