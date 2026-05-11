#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(void) {
    uint16_t a = 0x1234;
    uint32_t b = 0x56789abc;

    printf("a = %x\n", a); // 0x1234
    printf("b = %x\n", b); // 0x56789abc

    printf("a = %x %x\n", ((uint8_t *)&a)[0], ((uint8_t *)&a)[1]);
    printf("b = %x %x %x %x\n", ((uint8_t *)&b)[0], ((uint8_t *)&b)[1], ((uint8_t *)&b)[2], ((uint8_t *)&b)[3]);

    /* 端序转换 */
    a = htons(a);
    b = htonl(b);

    printf("a = %x\n", a); // 0x3412
    printf("b = %x\n", b); // 0xbc9a7856

    return 0;
}