#include "types.h"

#ifndef _PRINTF_H
#define _PRINTF_H

#ifndef va_arg
/*
 * Storage alignment properties
 */
#define	 NATIVE_INT		 int
#define  _AUPBND         (sizeof (NATIVE_INT) - 1)

/*
 * Variable argument list macro definitions
 */

#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_end(ap)      (void) 0
#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))



#endif /* va_arg */

int my_printf(const char *fmt, ...);
int my_scanf(const char * fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int vsscanf(const char * buf, const char * fmt, va_list args);

#endif /* _PRINTF_H */




