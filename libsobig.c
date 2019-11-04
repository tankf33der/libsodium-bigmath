#include <stddef.h>
#include <stdint.h>

void
sodium_inc_asm(unsigned char *n, const size_t nlen)
{
    uint64_t t64, t64_2;
    uint32_t t32;

    if (nlen == 12U) {
        __asm__ __volatile__(
            "xorq %[t64], %[t64] \n"
            "xorl %[t32], %[t32] \n"
            "stc \n"
            "adcq %[t64], (%[out]) \n"
            "adcl %[t32], 8(%[out]) \n"
            : [t64] "=&r"(t64), [t32] "=&r"(t32)
            : [out] "D"(n)
            : "memory", "flags", "cc");
        return;
    } else if (nlen == 24U) {
        __asm__ __volatile__(
            "movq $1, %[t64] \n"
            "xorq %[t64_2], %[t64_2] \n"
            "addq %[t64], (%[out]) \n"
            "adcq %[t64_2], 8(%[out]) \n"
            "adcq %[t64_2], 16(%[out]) \n"
            : [t64] "=&r"(t64), [t64_2] "=&r"(t64_2)
            : [out] "D"(n)
            : "memory", "flags", "cc");
        return;
    } else if (nlen == 8U) {
        __asm__ __volatile__("incq (%[out]) \n"
                             :
                             : [out] "D"(n)
                             : "memory", "flags", "cc");
        return;
    }
}

void
sodium_inc(unsigned char *n, const size_t nlen)
{
    size_t        i = 0U;
    uint_fast16_t c = 1U;

    for (; i < nlen; i++) {
        c += (uint_fast16_t) n[i];
        n[i] = (unsigned char) c;
        c >>= 8;
    }
}

void
sodium_add_asm(unsigned char *a, const unsigned char *b, const size_t len)
{
    uint64_t t64, t64_2, t64_3;
    uint32_t t32;

    if (len == 12U) {
        __asm__ __volatile__(
            "movq (%[in]), %[t64] \n"
            "movl 8(%[in]), %[t32] \n"
            "addq %[t64], (%[out]) \n"
            "adcl %[t32], 8(%[out]) \n"
            : [t64] "=&r"(t64), [t32] "=&r"(t32)
            : [in] "S"(b), [out] "D"(a)
            : "memory", "flags", "cc");
        return;
    } else if (len == 24U) {
        __asm__ __volatile__(
            "movq (%[in]), %[t64] \n"
            "movq 8(%[in]), %[t64_2] \n"
            "movq 16(%[in]), %[t64_3] \n"
            "addq %[t64], (%[out]) \n"
            "adcq %[t64_2], 8(%[out]) \n"
            "adcq %[t64_3], 16(%[out]) \n"
            : [t64] "=&r"(t64), [t64_2] "=&r"(t64_2), [t64_3] "=&r"(t64_3)
            : [in] "S"(b), [out] "D"(a)
            : "memory", "flags", "cc");
        return;
    } else if (len == 8U) {
        __asm__ __volatile__(
            "movq (%[in]), %[t64] \n"
            "addq %[t64], (%[out]) \n"
            : [t64] "=&r"(t64)
            : [in] "S"(b), [out] "D"(a)
            : "memory", "flags", "cc");
        return;
    }
}

void
sodium_add(unsigned char *a, const unsigned char *b, const size_t len)
{
    size_t        i;
    uint_fast16_t c = 0U;

    for (i = 0U; i < len; i++) {
        c += (uint_fast16_t) a[i] + (uint_fast16_t) b[i];
        a[i] = (unsigned char) c;
        c >>= 8;
    }
}

void
sodium_sub_asm(unsigned char *a, const unsigned char *b, const size_t len)
{
    uint64_t t64_1, t64_2, t64_3, t64_4;
    uint64_t t64_5, t64_6, t64_7, t64_8;
    uint32_t t32;

    if (len == 64U) {
        __asm__ __volatile__(
            "movq   (%[in]), %[t64_1] \n"
            "movq  8(%[in]), %[t64_2] \n"
            "movq 16(%[in]), %[t64_3] \n"
            "movq 24(%[in]), %[t64_4] \n"
            "movq 32(%[in]), %[t64_5] \n"
            "movq 40(%[in]), %[t64_6] \n"
            "movq 48(%[in]), %[t64_7] \n"
            "movq 56(%[in]), %[t64_8] \n"
            "subq %[t64_1],   (%[out]) \n"
            "sbbq %[t64_2],  8(%[out]) \n"
            "sbbq %[t64_3], 16(%[out]) \n"
            "sbbq %[t64_4], 24(%[out]) \n"
            "sbbq %[t64_5], 32(%[out]) \n"
            "sbbq %[t64_6], 40(%[out]) \n"
            "sbbq %[t64_7], 48(%[out]) \n"
            "sbbq %[t64_8], 56(%[out]) \n"
            : [t64_1] "=&r"(t64_1), [t64_2] "=&r"(t64_2), [t64_3] "=&r"(t64_3), [t64_4] "=&r"(t64_4),
              [t64_5] "=&r"(t64_5), [t64_6] "=&r"(t64_6), [t64_7] "=&r"(t64_7), [t64_8] "=&r"(t64_8)
            : [in] "S"(b), [out] "D"(a)
            : "memory", "flags", "cc");
        return;
    }
}

void
sodium_sub(unsigned char *a, const unsigned char *b, const size_t len)
{
    uint_fast16_t c = 0U;
    size_t        i;

    for (i = 0U; i < len; i++) {
        c = (uint_fast16_t) a[i] - (uint_fast16_t) b[i] - c;
        a[i] = (unsigned char) c;
        c = (c >> 8) & 1U;
    }
}

