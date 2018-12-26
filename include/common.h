#ifndef COMMON_DS
#define COMMON_DS

#define __offsetof(st, m) __builtin_offsetof(st, m)

#define __container_of(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - __offsetof(type,member) );})

#define __swap(a, b, swap)({ \
		swap = a; \
		a = b; \
		b = swap ;})


#endif