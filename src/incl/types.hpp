#ifndef _TYPES_H
#define _TYPES_H

typedef long long 	 	int64_t;
typedef int				int32_t;
typedef short			int16_t;	
typedef char			int8_t;
typedef unsigned long long 	uint64_t;
typedef unsigned int		uint32_t;
typedef unsigned short		uint16_t;	
typedef unsigned char		uint8_t;
typedef unsigned int size_t;

typedef __builtin_va_list va_list;

#define va_start(v, l)		__builtin_va_start(v, l);
#define va_arg(v, l)		__builtin_va_arg(v, l);




#endif
