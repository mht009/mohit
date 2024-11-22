#include "IDL.h"
#include <stdio.h>

void
calculator_prog_1(char *host)
{
    CLIENT *clnt;
    double *result_1, *result_2, *result_3, *result_4;
    doublepair add_1_arg, subtract_1_arg, multiply_1_arg, divide_1_arg;
    double sin_1_arg, cos_1_arg, tan_1_arg, log_1_arg;
    double *result_5, *result_6, *result_7, *result_8;

#ifndef DEBUG
    clnt = clnt_create(host, CALCULATOR_PROG, CALCULATOR_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif  /* DEBUG */

    // Sample values
    add_1_arg.a = 5.0;
    add_1_arg.b = 3.0;
    subtract_1_arg.a = 8.0;
    subtract_1_arg.b = 2.0;
    multiply_1_arg.a = 4.0;
    multiply_1_arg.b = 6.0;
    divide_1_arg.a = 10.0;
    divide_1_arg.b = 2.0;

    // Operations
    result_1 = add_1(&add_1_arg, clnt);
    if (result_1 != NULL) printf("Addition: %.2f\n", *result_1);

    result_2 = subtract_1(&subtract_1_arg, clnt);
    if (result_2 != NULL) printf("Subtraction: %.2f\n", *result_2);

    result_3 = multiply_1(&multiply_1_arg, clnt);
    if (result_3 != NULL) printf("Multiplication: %.2f\n", *result_3);

    result_4 = divide_1(&divide_1_arg, clnt);
    if (result_4 != NULL) printf("Division: %.2f\n", *result_4);

    // Trigonometric and logarithmic functions
    sin_1_arg = 30.0;
    result_5 = sin_1(&sin_1_arg, clnt);
    if (result_5 != NULL) printf("Sin: %.2f\n", *result_5);

    cos_1_arg = 30.0;
    result_6 = cos_1(&cos_1_arg, clnt);
    if (result_6 != NULL) printf("Cos: %.2f\n", *result_6);

    tan_1_arg = 45.0;
    result_7 = tan_1(&tan_1_arg, clnt);
    if (result_7 != NULL) printf("Tan: %.2f\n", *result_7);

    log_1_arg = 10.0;
    result_8 = log_1(&log_1_arg, clnt);
    if (result_8 != NULL) printf("Log: %.2f\n", *result_8);

#ifndef DEBUG
    clnt_destroy(clnt);
#endif  /* DEBUG */
}

int
main(int argc, char *argv[])
{
    char *host;

    if (argc < 2) {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    calculator_prog_1(host);
    exit(0);
}

