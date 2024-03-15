#ifndef DEF_H
#define DEF_H

#ifdef _MSC_VER
#define TYPEOF(expr) __typeof(expr)
#else
#define TYPEOF(expr) typeof(expr)
#endif

#endif
