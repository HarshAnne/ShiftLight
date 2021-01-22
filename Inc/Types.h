#ifndef TYPES_H
#define TYPES_H


/* == Type Definitions ==================================================== */

typedef _Bool               boolean;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;

typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long long    sint64;

typedef uint8               uint8_least;
typedef uint16              uint16_least;
typedef uint32              uint32_least;

typedef sint8               sint8_least;
typedef sint16              sint16_least;
typedef sint32              sint32_least;

typedef float               float32;
typedef double              float64;


/* == Symbol Definitions ================================================== */

/* TRUE_FALSE */
#ifndef TRUE
#define TRUE                ((boolean) 1)
#endif
#ifndef FALSE
#define FALSE               ((boolean) 0)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

#endif /* TYPES_H */