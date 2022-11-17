/*-------------------------------------------------------------------------
 *
 * pg_nanoid.c
 *    a text search parser for Chinese
 *
 * Author: Jaimin Pan <jaimin.pan@gmail.com>
 *
 * IDENTIFICATION
 *    pg_nanoid.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include <float.h>
#include <math.h>
#include "lib/stringinfo.h"
#include "utils/guc.h"
#include "utils/elog.h"
#include "utils/varlena.h"
#include "miscadmin.h"


#if (PG_VERSION_NUM >= 100000)
#include "utils/varlena.h"
#endif

#ifdef HAVE_STRONG_RANDOM
bytea *gen_random_bytes(int len);
#endif


PG_MODULE_MAGIC;

void _PG_init(void);


/*
 * prototypes
 */
PG_FUNCTION_INFO_V1(pg_nanoid);
Datum pg_nanoid(PG_FUNCTION_ARGS);

/*
 * Module load callback
 */
void
_PG_init(void)
{

}

const char DEFAULT_CHARSET[64] = "_-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/*
 * functions
 */
Datum
pg_nanoid(PG_FUNCTION_ARGS)
{
#ifdef HAVE_STRONG_RANDOM
	int		len;
	text*	alphabet;
	text*	res;
	int		idx;
	char*	ptr;
	int		mask;
	int		bits;
	int		step;

	const char* charset = NULL;
	int charset_len = 0;

	if (PG_NARGS() == 2)
	{
		len = PG_GETARG_INT32(0);
		alphabet = PG_GETARG_TEXT_P(1);

		charset_len = VARSIZE(alphabet) - VARHDRSZ;
		charset = VARDATA(alphabet);

		if (charset_len < 1 || charset_len > 255)
			ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_INVOCATION_EXCEPTION),
				 errmsg("alphabet must contain between 1 and 255 symbols")));

	} else {
		len = PG_GETARG_INT32(0);
		charset_len = sizeof(DEFAULT_CHARSET);
		charset = DEFAULT_CHARSET;
		mask = 63;
	}

	bits = (int) floor(log(1.0 * (charset_len - 1)) / log(1.0 * 2));
	mask = (2 << bits) - 1;
	step = (int) ceil(1.6 * mask * len / charset_len);

	res = (text *) palloc(VARHDRSZ + len);
	SET_VARSIZE(res, VARHDRSZ + len);
	ptr =(char*) VARDATA(res);
	idx = 0;

	while(true) 
	{
		char* bytes = (char*) gen_random_bytes(step);

		for (int i = 0; i < step; i++)
		{
			int pos = (int) (bytes[i] & mask);

			if (pos < charset_len) {
				*ptr = charset[pos];
				++ptr;
				++idx;
				if (idx >= len) {
					PG_RETURN_POINTER(res); 
				}
			}
		}
	}

#else
	pg_attribute_noreturn();
#endif
}

#ifdef HAVE_STRONG_RANDOM
//  reference pgcrypto pg_random_bytes
bytea *
gen_random_bytes(int len)
{
	bytea	   *res;
	if (len < 1 || len > 1024)
		ereport(ERROR,
			(errcode(ERRCODE_EXTERNAL_ROUTINE_INVOCATION_EXCEPTION),
			 errmsg("Length not in range")));

	res = palloc(len);

	/* generate result */
	if (!pg_strong_random(res, len))
		ereport(ERROR,
			(errcode(ERRCODE_EXTERNAL_ROUTINE_INVOCATION_EXCEPTION),
			errmsg("generate random error")));

	return res;
}
#endif
