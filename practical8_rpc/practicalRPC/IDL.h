/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _IDL_H_RPCGEN
#define _IDL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct doublepair {
	double a;
	double b;
};
typedef struct doublepair doublepair;

#define CALCULATOR_PROG 0x31234567
#define CALCULATOR_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define ADD 1
extern  double * add_1(doublepair *, CLIENT *);
extern  double * add_1_svc(doublepair *, struct svc_req *);
#define SUBTRACT 2
extern  double * subtract_1(doublepair *, CLIENT *);
extern  double * subtract_1_svc(doublepair *, struct svc_req *);
#define MULTIPLY 3
extern  double * multiply_1(doublepair *, CLIENT *);
extern  double * multiply_1_svc(doublepair *, struct svc_req *);
#define DIVIDE 4
extern  double * divide_1(doublepair *, CLIENT *);
extern  double * divide_1_svc(doublepair *, struct svc_req *);
#define SIN 5
extern  double * sin_1(double *, CLIENT *);
extern  double * sin_1_svc(double *, struct svc_req *);
#define COS 6
extern  double * cos_1(double *, CLIENT *);
extern  double * cos_1_svc(double *, struct svc_req *);
#define TAN 7
extern  double * tan_1(double *, CLIENT *);
extern  double * tan_1_svc(double *, struct svc_req *);
#define LOG 8
extern  double * log_1(double *, CLIENT *);
extern  double * log_1_svc(double *, struct svc_req *);
extern int calculator_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ADD 1
extern  double * add_1();
extern  double * add_1_svc();
#define SUBTRACT 2
extern  double * subtract_1();
extern  double * subtract_1_svc();
#define MULTIPLY 3
extern  double * multiply_1();
extern  double * multiply_1_svc();
#define DIVIDE 4
extern  double * divide_1();
extern  double * divide_1_svc();
#define SIN 5
extern  double * sin_1();
extern  double * sin_1_svc();
#define COS 6
extern  double * cos_1();
extern  double * cos_1_svc();
#define TAN 7
extern  double * tan_1();
extern  double * tan_1_svc();
#define LOG 8
extern  double * log_1();
extern  double * log_1_svc();
extern int calculator_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_doublepair (XDR *, doublepair*);

#else /* K&R C */
extern bool_t xdr_doublepair ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_IDL_H_RPCGEN */