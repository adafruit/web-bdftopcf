/*

Copyright 1991, 1993, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <X11/X.h>
#include <X11/Xproto.h>
#include "fontmisc.h"
#include <X11/fonts/fontstruct.h>
#include "fntfilio.h"
#include "fntfil.h"
#include "bdfint.h"
#include "pcf.h"
#include <stdio.h>
#include <X11/Xos.h>

#include <emscripten.h>

int
main(int argc, char *argv[])
{
}

EMSCRIPTEN_KEEPALIVE
int font_convert() {
    const char *input_name = "/input.bdf", *output_name="/output.pcf";
    FontRec font = { 0 };
    FontFilePtr input = NULL, output = NULL;
    int bit, byte, glyph, scan;

    FontDefaultFormat(&bit, &byte, &glyph, &scan);

    input = FontFileOpen(input_name);
    output = FontFileOpenWrite(output_name);
    int result = Successful;
    if (!input) {
        fprintf(stderr, "can't open bdf source file %s\n",
                input_name); fflush(stderr);
        result = 0;
    }
    if (!output) {
        fprintf(stderr, "can't open pcf sink file %s\n",
                output_name); fflush(stderr);
        result = 0;
    }
    if (result == Successful) {
        fprintf(stderr, "reading input font\n");
        result = bdfReadFont(&font, input, bit, byte, glyph, scan);
        if (result != Successful) {
            fprintf(stderr, "bdf input, corrupt\n");
        }
    }
    if (result == Successful) {
      fprintf(stderr, "preparing output font\n"); fflush(stderr);

        result = pcfWriteFont(&font, output);
        if (result != Successful) {
            fprintf(stderr, "can't write pcf file %s\n", output_name); fflush(stderr);
            remove(output_name);
        }
    }
    if (input)
        FontFileClose(input);
    if (output)
        FontFileClose(output);
    return (result == Successful);
}
