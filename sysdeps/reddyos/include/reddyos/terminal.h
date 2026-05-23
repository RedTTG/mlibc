#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void terminal_putc(char c);
void terminal_write(const char *s);
void terminal_write_u64(uint64_t value);
void terminal_write_u8(uint8_t value);
void terminal_write_hex_u64(uint64_t value);
void terminal_write_hex_u8(uint8_t value);

#ifdef __cplusplus
}
#endif