#ifndef LFSR_H
#define LFSR_H
#include <stdint.h>

uint64_t rfsr42(uint64_t shift, uint64_t initial_state = 1ULL);
uint64_t rfsr4(uint64_t shift, uint64_t initial_state = 1ULL);

#endif
