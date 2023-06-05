#ifndef STD_LIB
#define STD_LIB

typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef unsigned long size_t;
typedef __builtin_va_list va_list;
#define va_start(v, l)		__builtin_va_start(v, l);
#define va_arg(v, l)		__builtin_va_arg(v, l);

#include "stdio.hpp"
#include "stdmem.hpp"
#include "string.hpp"


#endif
