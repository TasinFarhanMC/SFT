#ifndef SFT_FIXED_NUM_H
#define SFT_FIXED_NUM_H
#include <stdint.h>

#ifdef INT64_MAX

#define sft_fixed_int64(num, decimal_bits) ((num) * ((uint64_t)1 << (decimal_bits)))

#endif
#endif
