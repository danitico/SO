/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ejercicio2.h"

bool_t
xdr_INPUT_A (XDR *xdrs, INPUT_A *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->nombre_fichero, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->apellido, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_INPUT_B (XDR *xdrs, INPUT_B *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->nombre_fichero, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->edad))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->provincia, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}
