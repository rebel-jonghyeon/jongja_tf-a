#ifndef __STDARG_H
#define __STDARG_H

#ifndef _VA_LIST
#define _VA_LIST
typedef __builtin_va_list va_list;
#endif

#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

#define __va_copy(d,s) __builtin_va_copy(d,s)
#define va_copy(dest, src)  __builtin_va_copy(dest, src)

#endif /* __STDARG_H */
