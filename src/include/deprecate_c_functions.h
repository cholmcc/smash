/*
 *
 *    Copyright (c) 2015
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 *
 */

#ifndef SRC_INCLUDE_DEPRECATE_C_FUNCTIONS_H_
#define SRC_INCLUDE_DEPRECATE_C_FUNCTIONS_H_

/**\file
 * This file should only be included to find deprecated calls to the C library.
 * It should not be included in default builds since it slows down compilation.
 */

#include "forwarddeclarations.h"
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdio>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <cwctype>
#include "macros.h"

namespace Smash {

/**
 * This macro is used to define functions that are in the C library and in the
 * std namespace. If a call to such a function without explicit namespace
 * qualification is made it will then call the function from the Smash
 * namespace. Since the functions here are marked as deprecated they issue a
 * warning if some code tries to use a C library function call.
 *
 * Rationale: Functions in the C library are not overloaded for different data
 * types. Thus a call to e.g. `x = abs(x)` with `float x` is a call to `x =
 * static_cast<float>(abs(static_cast<double>(x)))`. These casts are executed
 * implicitly and therefore not noticed if the cast was unintentional.
 *
 * And then, of course, this is C++ code. The ability to call C functions exists
 * in C++ because C headers should compile in C++. The only correct way to write
 * C++ code is to use the C++ interface. This may enable additional optimization
 * opportunities.
 */
#define SMASH_DEPRECATE_NONSTD(fun__)                                               \
  template <typename... Ts>                                                         \
  SMASH_DEPRECATED(                                                                 \
      "Please add the std:: namespace for this function.") auto fun__(Ts&&... args) \
      ->decltype(std::fun__(args...)) {                                             \
    return std::fun__(args...);                                                     \
  }
SMASH_DEPRECATE_NONSTD(abort)
SMASH_DEPRECATE_NONSTD(abs)
SMASH_DEPRECATE_NONSTD(acos)
SMASH_DEPRECATE_NONSTD(acosh)
SMASH_DEPRECATE_NONSTD(asctime)
SMASH_DEPRECATE_NONSTD(asin)
SMASH_DEPRECATE_NONSTD(asinh)
SMASH_DEPRECATE_NONSTD(atan)
SMASH_DEPRECATE_NONSTD(atan2)
SMASH_DEPRECATE_NONSTD(atanh)
SMASH_DEPRECATE_NONSTD(atexit)
SMASH_DEPRECATE_NONSTD(atof)
SMASH_DEPRECATE_NONSTD(atoi)
SMASH_DEPRECATE_NONSTD(atol)
SMASH_DEPRECATE_NONSTD(bsearch)
SMASH_DEPRECATE_NONSTD(btowc)
SMASH_DEPRECATE_NONSTD(calloc)
SMASH_DEPRECATE_NONSTD(cbrt)
SMASH_DEPRECATE_NONSTD(ceil)
SMASH_DEPRECATE_NONSTD(clearerr)
SMASH_DEPRECATE_NONSTD(clock)
SMASH_DEPRECATE_NONSTD(copysign)
SMASH_DEPRECATE_NONSTD(cos)
SMASH_DEPRECATE_NONSTD(cosh)
SMASH_DEPRECATE_NONSTD(ctime)
SMASH_DEPRECATE_NONSTD(difftime)
SMASH_DEPRECATE_NONSTD(div)
SMASH_DEPRECATE_NONSTD(erf)
SMASH_DEPRECATE_NONSTD(erfc)
SMASH_DEPRECATE_NONSTD(exit)
SMASH_DEPRECATE_NONSTD(exp)
SMASH_DEPRECATE_NONSTD(exp2)
SMASH_DEPRECATE_NONSTD(expm1)
SMASH_DEPRECATE_NONSTD(fabs)
SMASH_DEPRECATE_NONSTD(fclose)
SMASH_DEPRECATE_NONSTD(fdim)
SMASH_DEPRECATE_NONSTD(feof)
SMASH_DEPRECATE_NONSTD(ferror)
SMASH_DEPRECATE_NONSTD(fflush)
SMASH_DEPRECATE_NONSTD(fgetc)
SMASH_DEPRECATE_NONSTD(fgetpos)
SMASH_DEPRECATE_NONSTD(fgets)
SMASH_DEPRECATE_NONSTD(fgetwc)
SMASH_DEPRECATE_NONSTD(fgetws)
SMASH_DEPRECATE_NONSTD(floor)
SMASH_DEPRECATE_NONSTD(fma)
SMASH_DEPRECATE_NONSTD(fmax)
SMASH_DEPRECATE_NONSTD(fmin)
SMASH_DEPRECATE_NONSTD(fmod)
SMASH_DEPRECATE_NONSTD(fopen)
SMASH_DEPRECATE_NONSTD(fpclassify)
SMASH_DEPRECATE_NONSTD(fprintf)
SMASH_DEPRECATE_NONSTD(fputc)
SMASH_DEPRECATE_NONSTD(fputs)
SMASH_DEPRECATE_NONSTD(fputwc)
SMASH_DEPRECATE_NONSTD(fputws)
SMASH_DEPRECATE_NONSTD(fread)
SMASH_DEPRECATE_NONSTD(free)
SMASH_DEPRECATE_NONSTD(freopen)
SMASH_DEPRECATE_NONSTD(frexp)
SMASH_DEPRECATE_NONSTD(fscanf)
SMASH_DEPRECATE_NONSTD(fseek)
SMASH_DEPRECATE_NONSTD(fsetpos)
SMASH_DEPRECATE_NONSTD(ftell)
SMASH_DEPRECATE_NONSTD(fwide)
SMASH_DEPRECATE_NONSTD(fwprintf)
SMASH_DEPRECATE_NONSTD(fwrite)
SMASH_DEPRECATE_NONSTD(fwscanf)
SMASH_DEPRECATE_NONSTD(getc)
SMASH_DEPRECATE_NONSTD(getchar)
SMASH_DEPRECATE_NONSTD(getenv)
SMASH_DEPRECATE_NONSTD(getwc)
SMASH_DEPRECATE_NONSTD(getwchar)
SMASH_DEPRECATE_NONSTD(gmtime)
SMASH_DEPRECATE_NONSTD(hypot)
SMASH_DEPRECATE_NONSTD(ilogb)
SMASH_DEPRECATE_NONSTD(isalnum)
SMASH_DEPRECATE_NONSTD(isalpha)
SMASH_DEPRECATE_NONSTD(iscntrl)
SMASH_DEPRECATE_NONSTD(isdigit)
SMASH_DEPRECATE_NONSTD(isfinite)
SMASH_DEPRECATE_NONSTD(isgraph)
SMASH_DEPRECATE_NONSTD(isgreater)
SMASH_DEPRECATE_NONSTD(isgreaterequal)
SMASH_DEPRECATE_NONSTD(isinf)
SMASH_DEPRECATE_NONSTD(isless)
SMASH_DEPRECATE_NONSTD(islessequal)
SMASH_DEPRECATE_NONSTD(islessgreater)
SMASH_DEPRECATE_NONSTD(islower)
SMASH_DEPRECATE_NONSTD(isnan)
SMASH_DEPRECATE_NONSTD(isnormal)
SMASH_DEPRECATE_NONSTD(isprint)
SMASH_DEPRECATE_NONSTD(ispunct)
SMASH_DEPRECATE_NONSTD(isspace)
SMASH_DEPRECATE_NONSTD(isunordered)
SMASH_DEPRECATE_NONSTD(isupper)
SMASH_DEPRECATE_NONSTD(iswalnum)
SMASH_DEPRECATE_NONSTD(iswalpha)
SMASH_DEPRECATE_NONSTD(iswcntrl)
SMASH_DEPRECATE_NONSTD(iswctype)
SMASH_DEPRECATE_NONSTD(iswdigit)
SMASH_DEPRECATE_NONSTD(iswgraph)
SMASH_DEPRECATE_NONSTD(iswlower)
SMASH_DEPRECATE_NONSTD(iswprint)
SMASH_DEPRECATE_NONSTD(iswpunct)
SMASH_DEPRECATE_NONSTD(iswspace)
SMASH_DEPRECATE_NONSTD(iswupper)
SMASH_DEPRECATE_NONSTD(iswxdigit)
SMASH_DEPRECATE_NONSTD(isxdigit)
SMASH_DEPRECATE_NONSTD(labs)
SMASH_DEPRECATE_NONSTD(ldexp)
SMASH_DEPRECATE_NONSTD(ldiv)
SMASH_DEPRECATE_NONSTD(lgamma)
SMASH_DEPRECATE_NONSTD(llrint)
SMASH_DEPRECATE_NONSTD(llround)
SMASH_DEPRECATE_NONSTD(localeconv)
SMASH_DEPRECATE_NONSTD(localtime)
SMASH_DEPRECATE_NONSTD(log)
SMASH_DEPRECATE_NONSTD(log10)
SMASH_DEPRECATE_NONSTD(log1p)
SMASH_DEPRECATE_NONSTD(log2)
SMASH_DEPRECATE_NONSTD(logb)
SMASH_DEPRECATE_NONSTD(longjmp)
SMASH_DEPRECATE_NONSTD(lrint)
SMASH_DEPRECATE_NONSTD(lround)
SMASH_DEPRECATE_NONSTD(malloc)
SMASH_DEPRECATE_NONSTD(mblen)
SMASH_DEPRECATE_NONSTD(mbrlen)
SMASH_DEPRECATE_NONSTD(mbrtowc)
SMASH_DEPRECATE_NONSTD(mbsinit)
SMASH_DEPRECATE_NONSTD(mbsrtowcs)
SMASH_DEPRECATE_NONSTD(mbstowcs)
SMASH_DEPRECATE_NONSTD(mbtowc)
SMASH_DEPRECATE_NONSTD(memchr)
SMASH_DEPRECATE_NONSTD(memcmp)
SMASH_DEPRECATE_NONSTD(memcpy)
SMASH_DEPRECATE_NONSTD(memmove)
SMASH_DEPRECATE_NONSTD(memset)
SMASH_DEPRECATE_NONSTD(mktime)
SMASH_DEPRECATE_NONSTD(modf)
SMASH_DEPRECATE_NONSTD(nan)
SMASH_DEPRECATE_NONSTD(nanf)
SMASH_DEPRECATE_NONSTD(nanl)
SMASH_DEPRECATE_NONSTD(nearbyint)
SMASH_DEPRECATE_NONSTD(nextafter)
SMASH_DEPRECATE_NONSTD(nexttoward)
SMASH_DEPRECATE_NONSTD(perror)
SMASH_DEPRECATE_NONSTD(pow)
SMASH_DEPRECATE_NONSTD(printf)
SMASH_DEPRECATE_NONSTD(putc)
SMASH_DEPRECATE_NONSTD(putchar)
SMASH_DEPRECATE_NONSTD(puts)
SMASH_DEPRECATE_NONSTD(putwc)
SMASH_DEPRECATE_NONSTD(putwchar)
SMASH_DEPRECATE_NONSTD(qsort)
SMASH_DEPRECATE_NONSTD(raise)
SMASH_DEPRECATE_NONSTD(rand)
SMASH_DEPRECATE_NONSTD(realloc)
SMASH_DEPRECATE_NONSTD(remainder)
SMASH_DEPRECATE_NONSTD(remove)
SMASH_DEPRECATE_NONSTD(remquo)
SMASH_DEPRECATE_NONSTD(rename)
SMASH_DEPRECATE_NONSTD(rewind)
SMASH_DEPRECATE_NONSTD(rint)
SMASH_DEPRECATE_NONSTD(round)
SMASH_DEPRECATE_NONSTD(scalbln)
SMASH_DEPRECATE_NONSTD(scalbn)
SMASH_DEPRECATE_NONSTD(scanf)
SMASH_DEPRECATE_NONSTD(setbuf)
SMASH_DEPRECATE_NONSTD(setlocale)
SMASH_DEPRECATE_NONSTD(setvbuf)
SMASH_DEPRECATE_NONSTD(signal)
SMASH_DEPRECATE_NONSTD(signbit)
SMASH_DEPRECATE_NONSTD(sin)
SMASH_DEPRECATE_NONSTD(sinh)
SMASH_DEPRECATE_NONSTD(sprintf)
SMASH_DEPRECATE_NONSTD(sqrt)
SMASH_DEPRECATE_NONSTD(srand)
SMASH_DEPRECATE_NONSTD(sscanf)
SMASH_DEPRECATE_NONSTD(strcat)
SMASH_DEPRECATE_NONSTD(strchr)
SMASH_DEPRECATE_NONSTD(strcmp)
SMASH_DEPRECATE_NONSTD(strcoll)
SMASH_DEPRECATE_NONSTD(strcpy)
SMASH_DEPRECATE_NONSTD(strcspn)
SMASH_DEPRECATE_NONSTD(strerror)
SMASH_DEPRECATE_NONSTD(strftime)
SMASH_DEPRECATE_NONSTD(strlen)
SMASH_DEPRECATE_NONSTD(strncat)
SMASH_DEPRECATE_NONSTD(strncmp)
SMASH_DEPRECATE_NONSTD(strncpy)
SMASH_DEPRECATE_NONSTD(strpbrk)
SMASH_DEPRECATE_NONSTD(strrchr)
SMASH_DEPRECATE_NONSTD(strspn)
SMASH_DEPRECATE_NONSTD(strstr)
SMASH_DEPRECATE_NONSTD(strtod)
SMASH_DEPRECATE_NONSTD(strtok)
SMASH_DEPRECATE_NONSTD(strtol)
SMASH_DEPRECATE_NONSTD(strtoul)
SMASH_DEPRECATE_NONSTD(strxfrm)
SMASH_DEPRECATE_NONSTD(swprintf)
SMASH_DEPRECATE_NONSTD(swscanf)
SMASH_DEPRECATE_NONSTD(system)
SMASH_DEPRECATE_NONSTD(tan)
SMASH_DEPRECATE_NONSTD(tanh)
SMASH_DEPRECATE_NONSTD(tgamma)
SMASH_DEPRECATE_NONSTD(time)
SMASH_DEPRECATE_NONSTD(tmpfile)
SMASH_DEPRECATE_NONSTD(tmpnam)
SMASH_DEPRECATE_NONSTD(tolower)
SMASH_DEPRECATE_NONSTD(toupper)
SMASH_DEPRECATE_NONSTD(towctrans)
SMASH_DEPRECATE_NONSTD(towlower)
SMASH_DEPRECATE_NONSTD(towupper)
SMASH_DEPRECATE_NONSTD(trunc)
SMASH_DEPRECATE_NONSTD(ungetc)
SMASH_DEPRECATE_NONSTD(ungetwc)
SMASH_DEPRECATE_NONSTD(vfprintf)
SMASH_DEPRECATE_NONSTD(vfwprintf)
SMASH_DEPRECATE_NONSTD(vprintf)
SMASH_DEPRECATE_NONSTD(vsprintf)
SMASH_DEPRECATE_NONSTD(vswprintf)
SMASH_DEPRECATE_NONSTD(vwprintf)
SMASH_DEPRECATE_NONSTD(wcrtomb)
SMASH_DEPRECATE_NONSTD(wcscat)
SMASH_DEPRECATE_NONSTD(wcschr)
SMASH_DEPRECATE_NONSTD(wcscmp)
SMASH_DEPRECATE_NONSTD(wcscoll)
SMASH_DEPRECATE_NONSTD(wcscpy)
SMASH_DEPRECATE_NONSTD(wcscspn)
SMASH_DEPRECATE_NONSTD(wcsftime)
SMASH_DEPRECATE_NONSTD(wcslen)
SMASH_DEPRECATE_NONSTD(wcsncat)
SMASH_DEPRECATE_NONSTD(wcsncmp)
SMASH_DEPRECATE_NONSTD(wcsncpy)
SMASH_DEPRECATE_NONSTD(wcspbrk)
SMASH_DEPRECATE_NONSTD(wcsrchr)
SMASH_DEPRECATE_NONSTD(wcsrtombs)
SMASH_DEPRECATE_NONSTD(wcsspn)
SMASH_DEPRECATE_NONSTD(wcsstr)
SMASH_DEPRECATE_NONSTD(wcstod)
SMASH_DEPRECATE_NONSTD(wcstok)
SMASH_DEPRECATE_NONSTD(wcstol)
SMASH_DEPRECATE_NONSTD(wcstombs)
SMASH_DEPRECATE_NONSTD(wcstoul)
SMASH_DEPRECATE_NONSTD(wcsxfrm)
SMASH_DEPRECATE_NONSTD(wctob)
SMASH_DEPRECATE_NONSTD(wctomb)
SMASH_DEPRECATE_NONSTD(wctrans)
SMASH_DEPRECATE_NONSTD(wctype)
SMASH_DEPRECATE_NONSTD(wmemchr)
SMASH_DEPRECATE_NONSTD(wmemcmp)
SMASH_DEPRECATE_NONSTD(wmemcpy)
SMASH_DEPRECATE_NONSTD(wmemmove)
SMASH_DEPRECATE_NONSTD(wmemset)
SMASH_DEPRECATE_NONSTD(wprintf)
SMASH_DEPRECATE_NONSTD(wscanf)
#undef SMASH_DEPRECATE_NONSTD

}  // namespace Smash

#endif  // SRC_INCLUDE_DEPRECATE_C_FUNCTIONS_H_
