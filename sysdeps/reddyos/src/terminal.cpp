#include <reddyos/syscustom.h>
#include <reddyos/terminal.h>

extern "C" void terminal_putc(char c)
{
    sys_term(c);
}

extern "C" void terminal_write(const char *s)
{
    if (s == NULL) {
        return;
    }

    while (*s != '\0') {
        terminal_putc(*s++);
    }
}

extern "C" void terminal_write_u64(uint64_t value)
{
    char buffer[21];
    size_t i = 0;

    if (value == 0) {
        terminal_putc('0');
        return;
    }

    while (value > 0 && i < sizeof(buffer)) {
        buffer[i++] = (char)('0' + (value % 10));
        value /= 10;
    }

    while (i > 0) {
        terminal_putc(buffer[--i]);
    }
}
extern "C" void terminal_write_u8(uint8_t value)
{
    char buffer[4];
    size_t i = 0;

    if (value == 0) {
        terminal_putc('0');
        return;
    }

    while (value > 0 && i < sizeof(buffer)) {
        buffer[i++] = (char)('0' + (value % 10));
        value /= 10;
    }

    while (i > 0) {
        terminal_putc(buffer[--i]);
    }
}

extern "C" void terminal_write_hex_u64(uint64_t value)
{
    static const char digits[] = "0123456789abcdef";

    terminal_write("0x");

    for (int shift = 60; shift >= 0; shift -= 4) {
        terminal_putc(digits[(value >> shift) & 0xF]);
    }
}

extern "C" void terminal_write_hex_u8(uint8_t value)
{
    static const char digits[] = "0123456789abcdef";

    terminal_write("0x");

    for (int shift = 4; shift >= 0; shift -= 4) {
        terminal_putc(digits[(value >> shift) & 0xF]);
    }
}