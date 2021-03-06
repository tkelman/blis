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

#define FUNCPTR_T dotxaxpyf_fp

typedef void (*FUNCPTR_T)(
                           conj_t conjat,
                           conj_t conja,
                           conj_t conjw,
                           conj_t conjx,
                           dim_t  m,
                           dim_t  b_n,
                           void*  alpha,
                           void*  a, inc_t inca, inc_t lda,
                           void*  w, inc_t incw,
                           void*  x, inc_t incx,
                           void*  beta,
                           void*  y, inc_t incy,
                           void*  z, inc_t incz
                         );

// If some mixed datatype functions will not be compiled, we initialize
// the corresponding elements of the function array to NULL.
#ifdef BLIS_ENABLE_MIXED_PRECISION_SUPPORT
static FUNCPTR_T GENARRAY3_ALL(ftypes,dotxaxpyf_kernel_void);
#else
#ifdef BLIS_ENABLE_MIXED_DOMAIN_SUPPORT
static FUNCPTR_T GENARRAY3_EXT(ftypes,dotxaxpyf_kernel_void);
#else
static FUNCPTR_T GENARRAY3_MIN(ftypes,dotxaxpyf_kernel_void);
#endif
#endif


void bli_dotxaxpyf_kernel( obj_t*  alpha,
                           obj_t*  at,
                           obj_t*  a,
                           obj_t*  w,
                           obj_t*  x,
                           obj_t*  beta,
                           obj_t*  y,
                           obj_t*  z )
{
	num_t     dt_a      = bli_obj_datatype( *a );
	num_t     dt_x      = bli_obj_datatype( *x );
	num_t     dt_y      = bli_obj_datatype( *y );

	conj_t    conjat    = bli_obj_conj_status( *at );
	conj_t    conja     = bli_obj_conj_status( *a );
	conj_t    conjw     = bli_obj_conj_status( *w );
	conj_t    conjx     = bli_obj_conj_status( *x );

	dim_t     m         = bli_obj_vector_dim( *z );
	dim_t     b_n       = bli_obj_vector_dim( *y );

	void*     buf_a     = bli_obj_buffer_at_off( *a );
	inc_t     rs_a      = bli_obj_row_stride( *a );
	inc_t     cs_a      = bli_obj_col_stride( *a );

	inc_t     inc_w     = bli_obj_vector_inc( *w );
	void*     buf_w     = bli_obj_buffer_at_off( *w );

	inc_t     inc_x     = bli_obj_vector_inc( *x );
	void*     buf_x     = bli_obj_buffer_at_off( *x );

	inc_t     inc_y     = bli_obj_vector_inc( *y );
	void*     buf_y     = bli_obj_buffer_at_off( *y );

	inc_t     inc_z     = bli_obj_vector_inc( *z );
	void*     buf_z     = bli_obj_buffer_at_off( *z );

	num_t     dt_alpha;
	void*     buf_alpha;

	num_t     dt_beta;
	void*     buf_beta;

	FUNCPTR_T f;

	// The datatype of alpha MUST be the type union of a and x. This is to
	// prevent any unnecessary loss of information during computation.
	dt_alpha  = bli_datatype_union( dt_a, dt_x );
	buf_alpha = bli_obj_buffer_for_1x1( dt_alpha, *alpha );

	// The datatype of beta MUST be the same as the datatype of y.
	dt_beta   = dt_y;
	buf_beta  = bli_obj_buffer_for_1x1( dt_beta, *beta );

	// Index into the type combination array to extract the correct
	// function pointer.
	f = ftypes[dt_a][dt_x][dt_y];

	// Invoke the function.
	f( conjat,
	   conja,
	   conjw,
	   conjx,
	   m,
	   b_n,
	   buf_alpha,
	   buf_a, rs_a, cs_a,
	   buf_w, inc_w,
	   buf_x, inc_x,
	   buf_beta,
	   buf_y, inc_y,
	   buf_z, inc_z );
}


#undef  GENTFUNC3U12
#define GENTFUNC3U12( ctype_a, ctype_b, ctype_c, ctype_ab, cha, chb, chc, chab, varname, kername ) \
\
void PASTEMAC3(cha,chb,chc,varname)( \
                                     conj_t conjat, \
                                     conj_t conja, \
                                     conj_t conjw, \
                                     conj_t conjx, \
                                     dim_t  m, \
                                     dim_t  b_n, \
                                     void*  alpha, \
                                     void*  a, inc_t inca, inc_t lda, \
                                     void*  w, inc_t incw, \
                                     void*  x, inc_t incx, \
                                     void*  beta, \
                                     void*  y, inc_t incy, \
                                     void*  z, inc_t incz \
                                   ) \
{ \
	PASTEMAC3(cha,chb,chc,kername)( conjat, \
	                                conja, \
	                                conjw, \
	                                conjx, \
	                                m, \
	                                b_n, \
	                                alpha, \
	                                a, inca, lda, \
	                                w, incw, \
	                                x, incx, \
	                                beta, \
	                                y, incy, \
	                                z, incz ); \
}

// Define the basic set of functions unconditionally, and then also some
// mixed datatype functions if requested.
INSERT_GENTFUNC3U12_BASIC( dotxaxpyf_kernel_void, DOTXAXPYF_KERNEL )

#ifdef BLIS_ENABLE_MIXED_DOMAIN_SUPPORT
INSERT_GENTFUNC3U12_MIX_D( dotxaxpyf_kernel_void, DOTXAXPYF_KERNEL )
#endif

#ifdef BLIS_ENABLE_MIXED_PRECISION_SUPPORT
INSERT_GENTFUNC3U12_MIX_P( dotxaxpyf_kernel_void, DOTXAXPYF_KERNEL )
#endif

