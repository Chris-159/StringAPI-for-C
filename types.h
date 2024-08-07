#pragma once
#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

/* Types for better readability */
typedef unsigned char       UCHAR_t;
typedef unsigned short      USHORT_t;
typedef unsigned int        UINT_t;
typedef unsigned long       ULONG_t;
typedef long long           LONGLONG_t;
typedef unsigned long long  ULONGLONG_t;

typedef char              boolean_t;  // bool type
typedef char              STATUS_t;   // status type (this stores the outcome of a function)
typedef unsigned short    INDEX_t;    // index type (for array indexing)

#define true  1
#define false 0

#endif // TYPES_H_INCLUDED