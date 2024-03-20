#ifndef SFT_FIXED_NUM_H
#define SFT_FIXED_NUM_H
#include <stdint.h>

#ifdef INT128_MAX

#define sft_fixed_128(num, decimal_bits) ((num) * ((uint128_t)1 << (decimal_bits)))
#define sft_fixed_float_128(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / ((uint128_t)1 << (decimal_bits)))

#endif

#ifdef INT64_MAX

#define sft_fixed_64(num, decimal_bits) ((num) * ((uint64_t)1 << (decimal_bits)))
#define sft_fixed_float_64(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / ((uint64_t)1 << (decimal_bits)))

#endif

#ifdef INT32_MAX

#define sft_fixed_32(num, decimal_bits) ((num) * ((uint32_t)1 << (decimal_bits)))
#define sft_fixed_float_32(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / ((uint32_t)1 << (decimal_bits)))

#endif

#ifdef INT16_MAX

#define sft_fixed_16(num, decimal_bits) ((num) * ((uint16_t)1 << (decimal_bits)))
#define sft_fixed_float_16(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / ((uint16_t)1 << (decimal_bits)))

#endif

#define sft_fixed_8(num, decimal_bits) ((num) * ((uint8_t)1 << (decimal_bits)))
#define sft_fixed_float_8(fixed_num, decimal_bits, float_type) ((float_type)(fixed_num) / ((uint8_t)1 << (decimal_bits)))
#define sft_fixed_int(fixed_num, decimal_bits) ((fixed_num) >> (decimal_bits))

#endif
