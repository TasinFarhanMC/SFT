#ifndef SFT_FIXED_NUM_H
#define SFT_FIXED_NUM_H
#include <stdint.h>

#define sft_fixed_uint(fixed_num, decimal_bits) ((fixed_num) / (1 << (decimal_bits)))

#define sft_fixed_32(num, decimal_bits) ((num) >> (decimal_bits))

#define sft_fixed_32_float(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / (1 << (decimal_bits)))

#define sft_fixed_32_umul(a, b, decimal_bits) ((uint64_t)(a) * (b) >> (decimal_bits))

#define sft_fixed_32_udiv(fixed_num1, fixed_num2, decimal_bits) ((fixed_num1) >> (decimal_bits) / (fixed_num2))

#endif
