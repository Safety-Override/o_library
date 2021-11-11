/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#define o_likely(x)       __builtin_expect(!!(x),1)
#define o_unlikely(x)     __builtin_expect((x),0)
#define o_swap(a, b) do { __typeof__(a) temp = a; a = b; b = temp; } while (0)

#define o_max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define o_min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
