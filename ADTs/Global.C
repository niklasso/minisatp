#include <cassert>
#include <cstdarg>
#include <cstring>
#include <cstdio>


char* vnsprintf(const char* format, va_list args)
{
    static FILE* dummy = fopen("/dev/null", "wb");
    unsigned     chars_written;
    char*        ret;
    va_list      args_copy;

  #ifdef __va_copy
    __va_copy (args_copy, args);
  #else
    args_copy = args;
  #endif
    chars_written = vfprintf(dummy, format, args);
    ret = xmalloc<char>(chars_written + 1);
    ret[chars_written] = 255;
    args = args_copy;
    vsprintf(ret, format, args);
    assert(ret[chars_written] == 0);
    return ret;
}


char* nsprintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* ret = vnsprintf(format, args);
    va_end(args);
    return ret;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

macro bool hasChar(cchar* text, int chr) {
    while (*text != 0) if (*text++ == chr) return true;
    return false; }

void splitString(cchar* text, cchar* seps, vec<char*>& out)
{
    while (hasChar(seps, *text)) text++;
    if (*text == 0) return;
    cchar* start = text;
    for(;;){
        if (*text == 0 || hasChar(seps, *text)){
            out.push(xstrndup(start, text-start));
            while (hasChar(seps, *text)) text++;
            if (*text == 0) return;
            start = text;
        }else
            text++;
    }
}
