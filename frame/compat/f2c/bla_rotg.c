/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"

#ifdef BLIS_ENABLE_BLAS2BLIS

/* srotg.f -- translated by f2c (version 19991025).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

/* Table of constant values */

static real sc_b4 = 1.f;

/* Subroutine */ int PASTEF77(s,rotg)(real *sa, real *sb, real *c__, real *s)
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal), bla_r_sign(real *, real *);

    /* Local variables */
    real r__, scale, z__, roe;


/*     construct givens plane rotation. */
/*     jack dongarra, linpack, 3/11/78. */


    roe = *sb;
    if (abs(*sa) > abs(*sb)) {
	roe = *sa;
    }
    scale = abs(*sa) + abs(*sb);
    if (scale != 0.f) {
	goto L10;
    }
    *c__ = 1.f;
    *s = 0.f;
    r__ = 0.f;
    z__ = 0.f;
    goto L20;
L10:
/* Computing 2nd power */
    r__1 = *sa / scale;
/* Computing 2nd power */
    r__2 = *sb / scale;
    r__ = scale * sqrt(r__1 * r__1 + r__2 * r__2);
    r__ = bla_r_sign(&sc_b4, &roe) * r__;
    *c__ = *sa / r__;
    *s = *sb / r__;
    z__ = 1.f;
    if (abs(*sa) > abs(*sb)) {
	z__ = *s;
    }
    if (abs(*sb) >= abs(*sa) && *c__ != 0.f) {
	z__ = 1.f / *c__;
    }
L20:
    *sa = r__;
    *sb = z__;
    return 0;
} /* srotg_ */

/* drotg.f -- translated by f2c (version 19991025).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

/* Table of constant values */

static doublereal dc_b4 = 1.;

/* Subroutine */ int PASTEF77(d,rotg)(doublereal *da, doublereal *db, doublereal *c__, doublereal *s)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), bla_d_sign(doublereal *, doublereal *);

    /* Local variables */
    doublereal r__, scale, z__, roe;


/*     construct givens plane rotation. */
/*     jack dongarra, linpack, 3/11/78. */


    roe = *db;
    if (abs(*da) > abs(*db)) {
	roe = *da;
    }
    scale = abs(*da) + abs(*db);
    if (scale != 0.) {
	goto L10;
    }
    *c__ = 1.;
    *s = 0.;
    r__ = 0.;
    z__ = 0.;
    goto L20;
L10:
/* Computing 2nd power */
    d__1 = *da / scale;
/* Computing 2nd power */
    d__2 = *db / scale;
    r__ = scale * sqrt(d__1 * d__1 + d__2 * d__2);
    r__ = bla_d_sign(&dc_b4, &roe) * r__;
    *c__ = *da / r__;
    *s = *db / r__;
    z__ = 1.;
    if (abs(*da) > abs(*db)) {
	z__ = *s;
    }
    if (abs(*db) >= abs(*da) && *c__ != 0.) {
	z__ = 1. / *c__;
    }
L20:
    *da = r__;
    *db = z__;
    return 0;
} /* drotg_ */

/* crotg.f -- translated by f2c (version 19991025).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

/* Subroutine */ int PASTEF77(c,rotg)(singlecomplex *ca, singlecomplex *cb, real *c__, singlecomplex *s)
{
    /* System generated locals */
    real r__1, r__2;
    singlecomplex q__1, q__2, q__3;

    /* Builtin functions */
    double bla_c_abs(singlecomplex *), sqrt(doublereal);
    void bla_r_cnjg(singlecomplex *, singlecomplex *);

    /* Local variables */
    real norm;
    singlecomplex alpha;
    real scale;

    if (bla_c_abs(ca) != 0.f) {
	goto L10;
    }
    *c__ = 0.f;
    bli_csets( 1.f, 0.f, *s );
    bli_csets( bli_creal(*cb), bli_cimag(*cb), *ca );
    goto L20;
L10:
    scale = bla_c_abs(ca) + bla_c_abs(cb);
    bli_csets( (bli_creal(*ca) / scale), (bli_cimag(*ca) / scale), q__1 );
/* Computing 2nd power */
    r__1 = bla_c_abs(&q__1);
    bli_csets( (bli_creal(*cb) / scale), (bli_cimag(*cb) / scale), q__2 );
/* Computing 2nd power */
    r__2 = bla_c_abs(&q__2);
    norm = scale * sqrt(r__1 * r__1 + r__2 * r__2);
    r__1 = bla_c_abs(ca);
    bli_csets( (bli_creal(*ca) / r__1), (bli_cimag(*ca) / r__1), q__1 );
    bli_csets( (bli_creal(q__1)), (bli_cimag(q__1)), alpha );
    *c__ = bla_c_abs(ca) / norm;
    bla_r_cnjg(&q__3, cb);
    bli_csets( (bli_creal(alpha) * bli_creal(q__3) - bli_cimag(alpha) * bli_cimag(q__3)), (bli_creal(alpha) * bli_cimag(q__3) + bli_cimag(alpha) * bli_creal(q__3)), q__2 );
    bli_csets( (bli_creal(q__2) / norm), (bli_cimag(q__2) / norm), q__1 );
    bli_csets( bli_creal(q__1), bli_cimag(q__1), *s );
    bli_csets( (norm * bli_creal(alpha)), (norm * bli_cimag(alpha)), q__1 );
    bli_csets( bli_creal(q__1), bli_cimag(q__1), *ca );
L20:
    return 0;
} /* crotg_ */

/* zrotg.f -- translated by f2c (version 19991025).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

/* Subroutine */ int PASTEF77(z,rotg)(doublecomplex *ca, doublecomplex *cb, doublereal *c__, doublecomplex *s)
{
    /* System generated locals */
    doublereal d__1, d__2;
    doublecomplex z__1, z__2, z__3, z__4;

    /* Builtin functions */
    double bla_z_abs(doublecomplex *);
    void bla_z_div(doublecomplex *, doublecomplex *, doublecomplex *);
    double sqrt(doublereal);
    void bla_d_cnjg(doublecomplex *, doublecomplex *);

    /* Local variables */
    doublereal norm;
    doublecomplex alpha;
    doublereal scale;

    if (bla_z_abs(ca) != 0.) {
	goto L10;
    }
    *c__ = 0.;
    bli_zsets( 1., 0., *s );
    bli_zsets( bli_zreal(*cb), bli_zimag(*cb), *ca );
    goto L20;
L10:
    scale = bla_z_abs(ca) + bla_z_abs(cb);
    bli_zsets( (scale), (0.), z__2 );
    bla_z_div(&z__1, ca, &z__2);
/* Computing 2nd power */
    d__1 = bla_z_abs(&z__1);
    bli_zsets( (scale), (0.), z__4 );
    bla_z_div(&z__3, cb, &z__4);
/* Computing 2nd power */
    d__2 = bla_z_abs(&z__3);
    norm = scale * sqrt(d__1 * d__1 + d__2 * d__2);
    d__1 = bla_z_abs(ca);
    bli_zsets( (bli_zreal(*ca) / d__1), (bli_zimag(*ca) / d__1), z__1 );
    bli_zsets( (bli_zreal(z__1)), (bli_zimag(z__1)), alpha );
    *c__ = bla_z_abs(ca) / norm;
    bla_d_cnjg(&z__3, cb);
    bli_zsets( (bli_zreal(alpha) * bli_zreal(z__3) - bli_zimag(alpha) * bli_zimag(z__3)), (bli_zreal(alpha) * bli_zimag(z__3) + bli_zimag(alpha) * bli_zreal(z__3)), z__2 );
    bli_zsets( (bli_zreal(z__2) / norm), (bli_zimag(z__2) / norm), z__1 );
    bli_zsets( bli_zreal(z__1), bli_zimag(z__1), *s );
    bli_zsets( (norm * bli_zreal(alpha)), (norm * bli_zimag(alpha)), z__1 );
    bli_zsets( bli_zreal(z__1), bli_zimag(z__1), *ca );
L20:
    return 0;
} /* zrotg_ */

#endif

