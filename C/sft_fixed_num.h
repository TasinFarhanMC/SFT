#ifndef SFT_FIXED_NUM_H
#define SFT_FIXED_NUM_H

#include <stdint.h>

#ifdef INT64_MAX

typedef uint64_t lq60_4;
typedef uint64_t lq56_8;
typedef uint64_t lq48_16;
typedef uint64_t lq32_32;
typedef uint64_t lq16_48;
typedef uint64_t lq8_56;
typedef uint64_t lq0_64;

typedef int64_t lsq59_4;
typedef int64_t lsq55_8;
typedef int64_t lsq47_16;
typedef int64_t lsq31_32;
typedef int64_t lsq15_48;
typedef int64_t lsq7_56;
typedef int64_t lsq0_63;

typedef uint32_t q28_4;
typedef uint32_t q24_8;
typedef uint32_t q16_16;
typedef uint32_t q8_24;
typedef uint32_t q4_28;
typedef uint32_t q0_32;

typedef int32_t sq27_4;
typedef int32_t sq23_8;
typedef int32_t sq15_16;
typedef int32_t sq7_24;
typedef int32_t sq3_28;
typedef int32_t sq0_31;

typedef uint16_t q12_4;
typedef uint16_t q8_8;
typedef uint16_t q4_12;
typedef uint16_t q0_16;

typedef uint16_t sq11_4;
typedef uint16_t sq7_8;
typedef uint16_t sq3_12;
typedef uint16_t sq0_15;

typedef uint8_t q4_4;
typedef uint8_t q2_6;
typedef uint8_t q0_8;

typedef uint8_t sq3_4;
typedef uint8_t sq1_6;
typedef uint8_t sq0_7;

#define Q16_16(val) ((q16_16)((val) * 0x10000))
#define INT_Q16_16(val) ((q16_16)((val) << 16))
#define Q16_16_INT(val) ((uint16_t)((val) >> 16))
#define Q16_16_DEC(val) ((val) & 0xFFFF)
#define Q16_16_FLOAT(val, t) ((t)(val) / 0x10000)

#elif defined(INT32_MAX)

typedef uint32_t lq28_4;
typedef uint32_t lq24_8;
typedef uint32_t lq16_16;
typedef uint32_t lq8_24;
typedef uint32_t lq4_28;
typedef uint32_t lq0_32;

typedef int32_t slq27_4;
typedef int32_t slq23_8;
typedef int32_t slq15_16;
typedef int32_t slq7_24;
typedef int32_t slq3_28;
typedef int32_t slq0_31;

typedef uint16_t q12_4;
typedef uint16_t q8_8;
typedef uint16_t q4_12;
typedef uint16_t q0_16;

typedef uint16_t sq11_4;
typedef uint16_t sq7_8;
typedef uint16_t sq3_12;
typedef uint16_t sq0_15;

typedef uint8_t q4_4;
typedef uint8_t q2_6;
typedef uint8_t q0_8;

typedef uint8_t sq3_4;
typedef uint8_t sq1_6;
typedef uint8_t sq0_7;

#else

typedef uint16_t lq12_4;
typedef uint16_t lq8_8;
typedef uint16_t lq4_12;
typedef uint16_t lq0_16;

typedef uint16_t slq11_4;
typedef uint16_t slq7_8;
typedef uint16_t slq3_12;
typedef uint16_t slq0_15;

typedef uint8_t q4_4;
typedef uint8_t q2_6;
typedef uint8_t q0_8;

typedef uint8_t sq3_4;
typedef uint8_t sq1_6;
typedef uint8_t sq0_7;

#endif
#endif
