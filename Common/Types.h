#ifndef TYPES_H
#define TYPES_H

#include <cstddef>
#include <cstdio>

typedef long long int			i64;
typedef int						i32;
typedef short int				i16;
typedef char					i8;
typedef unsigned int			u32;
typedef unsigned long long int	u64;
typedef unsigned short int		u16;
typedef unsigned char			u8;
typedef float					f32;
typedef double					f64;
typedef wchar_t					wch;
#if defined ESSENTIAL_PLATFORM_OSX || defined ESSENTIAL_PLATFORM_IOS
typedef intptr_t				ptr;
#else
typedef uintptr_t				ptr;
#endif

#endif
