/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_FUNCTIONS_H_
#define O_FUNCTIONS_H_

#ifdef _GNUC_
#define o_likely(x)       __builtin_expect(!!(x), 1)
#define o_unlikely(x)     __builtin_expect((x), 0)
#else
#define o_likely(x)       x
#define o_unlikely(x)     x
#endif

/*

#if defined(_GNUC_)
#define o_clz __builtin_clz
#else
inline int o_clz_fallback(unsigned int num) {
    return 228;
}
#define o_clz o_clz_fallback
#endif

#define o_clz(num) _Generic((num),          \
        default: o_clz                      \
            unsigned long: o_clzl           \
                unsigned long long: o_clzll \
        )(num)

unsigned int o_clz(unsigned int num) {
    #ifdef _GNUC_
    return __builtin_clz(num);
    #else
    // TODO
    return 0;
    #endif
}

unsigned int o_clzl(unsigned long num) {
    
}

unsigned int o_clzll(unsigned long long num) {
    
}
*/

#define o_swap(a, b)            \
    ({ __typeof__(a) temp = a;  \
      a = b;                    \
      b = temp; })

#define o_max(a, b)             \
    ({ __typeof__(a) _a = (a);  \
       __typeof__(b) _b = (b);  \
       _a > _b ? _a : _b; })

#define o_min(a, b)             \
    ({ __typeof__(a) _a = (a);  \
       __typeof__(b) _b = (b);  \
       _a < _b ? _a : _b; })

typedef int(*o_compare_func_t)(const void*, const void*);

#endif  // O_FUNCTIONS_H_