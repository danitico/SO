/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EJERCICIO2_H_RPCGEN
#define _EJERCICIO2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct CLIENTE {
	char *nombrecompleto;
	int edad;
	char *provincia;
};
typedef struct CLIENTE CLIENTE;

struct INPUT_A {
	char *nombre_fichero;
	char *apellido;
};
typedef struct INPUT_A INPUT_A;

struct INPUT_B {
	char *nombre_fichero;
	int edad;
	char *provincia;
};
typedef struct INPUT_B INPUT_B;

struct OUTPUT_A_B {
	struct {
		u_int a_len;
		CLIENTE *a_val;
	} a;
};
typedef struct OUTPUT_A_B OUTPUT_A_B;

#define BASES_DATOS 0xA0000001
#define BASES_DATOS_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define A 1
extern  OUTPUT_A_B * a_1(INPUT_A *, CLIENT *);
extern  OUTPUT_A_B * a_1_svc(INPUT_A *, struct svc_req *);
#define B 2
extern  OUTPUT_A_B * b_1(INPUT_B *, CLIENT *);
extern  OUTPUT_A_B * b_1_svc(INPUT_B *, struct svc_req *);
extern int bases_datos_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define A 1
extern  OUTPUT_A_B * a_1();
extern  OUTPUT_A_B * a_1_svc();
#define B 2
extern  OUTPUT_A_B * b_1();
extern  OUTPUT_A_B * b_1_svc();
extern int bases_datos_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_CLIENTE (XDR *, CLIENTE*);
extern  bool_t xdr_INPUT_A (XDR *, INPUT_A*);
extern  bool_t xdr_INPUT_B (XDR *, INPUT_B*);
extern  bool_t xdr_OUTPUT_A_B (XDR *, OUTPUT_A_B*);

#else /* K&R C */
extern bool_t xdr_CLIENTE ();
extern bool_t xdr_INPUT_A ();
extern bool_t xdr_INPUT_B ();
extern bool_t xdr_OUTPUT_A_B ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EJERCICIO2_H_RPCGEN */