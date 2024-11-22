#include "IDL.h"
#include <math.h>

double *
add_1_svc(doublepair *argp, struct svc_req *rqstp)
{
    static double result;
    result = argp->a + argp->b;
    return &result;
}

double *
subtract_1_svc(doublepair *argp, struct svc_req *rqstp)
{
    static double result;
    result = argp->a - argp->b;
    return &result;
}

double *
multiply_1_svc(doublepair *argp, struct svc_req *rqstp)
{
    static double result;
    result = argp->a * argp->b;
    return &result;
}

double *
divide_1_svc(doublepair *argp, struct svc_req *rqstp)
{
    static double result;
    if (argp->b != 0) {
        result = argp->a / argp->b;
    } else {
        result = 0.0;  // Handle division by zero
    }
    return &result;
}

double *
sin_1_svc(double *argp, struct svc_req *rqstp)
{
    static double result;
    result = sin(*argp);
    return &result;
}

double *
cos_1_svc(double *argp, struct svc_req *rqstp)
{
    static double result;
    result = cos(*argp);
    return &result;
}

double *
tan_1_svc(double *argp, struct svc_req *rqstp)
{
    static double result;
    result = tan(*argp);
    return &result;
}

double *
log_1_svc(double *argp, struct svc_req *rqstp)
{
    static double result;
    if (*argp > 0) {
        result = log(*argp);
    } else {
        result = 0.0;  // Handle log of non-positive values
    }
    return &result;
}

