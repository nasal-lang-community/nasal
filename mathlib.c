#include <math.h>
#include <string.h>

#include "nasal.h"

// Toss a runtime error for any NaN or Inf values produced.  Note that
// this assumes an IEEE 754 format.
#define VALIDATE(r) (valid(r.num) ? (r) : die(c, __FUNCTION__+2))

static int valid(double d)
{
    union { double d; unsigned long long ull; } u;
    u.d = d;
    return ((u.ull >> 52) & 0x7ff) != 0x7ff;
}

static naRef die(naContext c, const char* fn)
{
    naRuntimeError(c, "floating point error in math.%s()", fn);
    return naNil();
}

static naRef f_sin(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to sin()");
    a.num = sin(a.num);
    return VALIDATE(a);
}

static naRef f_cos(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to cos()");
    a.num = cos(a.num);
    return VALIDATE(a);
}

static naRef f_exp(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to exp()");
    a.num = exp(a.num);
    return VALIDATE(a);
}

static naRef f_ln(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to ln()");
    a.num = log(a.num);
    return VALIDATE(a);
}

static naRef f_sqrt(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to sqrt()");
    a.num = sqrt(a.num);
    return VALIDATE(a);
}

static naRef f_atan2(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    naRef b = naNumValue(argc > 1 ? args[1] : naNil());
    if(naIsNil(a) || naIsNil(b))
        naRuntimeError(c, "non numeric argument to atan2()");
    a.num = atan2(a.num, b.num);
    return VALIDATE(a);
}

static naRef f_floor(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to floor()");
    a.num = floor(a.num);
    return VALIDATE(a);
}

static naRef f_ceil(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    if(naIsNil(a))
        naRuntimeError(c, "non numeric argument to ceil()");
    a.num = ceil(a.num);
    return VALIDATE(a);
}

static naRef f_mod(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    naRef b = naNumValue(argc > 1 ? args[1] : naNil());
    if(naIsNil(a) || naIsNil(b))
        naRuntimeError(c, "non numeric arguments to mod()");
    
    a.num = fmod(a.num, b.num);
    return VALIDATE(a);
}

static naRef f_clamp(naContext c, naRef me, int argc, naRef* args)
{
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    naRef b = naNumValue(argc > 1 ? args[1] : naNil());
    naRef x = naNumValue(argc > 2 ? args[2] : naNil());
    
    if(naIsNil(a) || naIsNil(b) || naIsNil(x))
        naRuntimeError(c, "non numeric arguments to clamp()");
    
    if (a.num < b.num) b.num = a.num;
    if (b.num > x.num) b.num = x.num;
    return VALIDATE(b);
}

static naRef f_periodic(naContext c, naRef me, int argc, naRef* args)
{
    double range;
    naRef a = naNumValue(argc > 0 ? args[0] : naNil());
    naRef b = naNumValue(argc > 1 ? args[1] : naNil());
    naRef x = naNumValue(argc > 2 ? args[2] : naNil());
    
    if(naIsNil(a) || naIsNil(b) || naIsNil(x))
        naRuntimeError(c, "non numeric arguments to periodic()");
  
    range = b.num - a.num;
    x.num = x.num - range*floor((x.num - a.num)/range);
    // two security checks that can only happen due to roundoff
    if (x.num <= a.num)
        x.num = a.num;
    if (b.num <= x.num)
        x.num = b.num;
    return VALIDATE(x);
      
//    x.num = SGMiscd::normalizePeriodic(a, b, x);
    return VALIDATE(x);
}

static naCFuncItem funcs[] = {
    { "sin", f_sin },
    { "cos", f_cos },
    { "exp", f_exp },
    { "ln", f_ln },
    { "sqrt", f_sqrt },
    { "atan2", f_atan2 },
    { "floor", f_floor },
    { "ceil", f_ceil },
    { "mod", f_mod },
    { "clamp", f_clamp },
    { "periodic", f_periodic },        
    { 0 }
};



naRef naInit_math(naContext c)
{
    naRef ns = naGenLib(c, funcs);
    naAddSym(c, ns, "pi", naNum(3.14159265358979323846));
    naAddSym(c, ns, "e", naNum(2.7182818284590452354));
    return ns;
}
