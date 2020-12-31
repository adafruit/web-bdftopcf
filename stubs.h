#include <stdio.h>
#include "fntfilst.h"
#include "font.h"

#ifndef True
#define True (-1)
#endif
#ifndef False
#define False (0)
#endif

#define OVERRIDE_DATA(sym)
#define OVERRIDE_SYMBOL(sym,...)
#define OVERRIDE_VA_SYMBOL(sym,f)

extern FontPtr find_old_font ( FSID id );
extern int set_font_authorizations ( char **authorizations,
				     int *authlen,
				     ClientPtr client );

extern unsigned long GetTimeInMillis (void);

extern void ErrorF(const char *format, ...);

/* end of file */
