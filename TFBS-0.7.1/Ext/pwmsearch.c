/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.21 from the
 * contents of pwmsearch.xs. Do not edit this file, edit pwmsearch.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "pwmsearch.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "pwm_searchPFF.c"
#include <stdio.h>


#line 18 "pwmsearch.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)	S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage		S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 70 "pwmsearch.c"

XS(XS_TFBS__Ext__pwmsearch_search_xs); /* prototype to pass -Wmissing-prototypes */
XS(XS_TFBS__Ext__pwmsearch_search_xs)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 6)
       croak_xs_usage(cv,  "matrixfile, seqfile, threshold, tfname, tfclass, outfile");
    {
	char*	matrixfile = (char *)SvPV_nolen(ST(0));
	char*	seqfile = (char *)SvPV_nolen(ST(1));
	double	threshold = (double)SvNV(ST(2));
	char*	tfname = (char *)SvPV_nolen(ST(3));
	char*	tfclass = (char *)SvPV_nolen(ST(4));
	char*	outfile = (char *)SvPV_nolen(ST(5));
	int	RETVAL;
	dXSTARG;
#line 18 "pwmsearch.xs"
	do_search(matrixfile, seqfile, threshold, tfname, tfclass, outfile);
#line 93 "pwmsearch.c"
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_TFBS__Ext__pwmsearch); /* prototype to pass -Wmissing-prototypes */
XS(boot_TFBS__Ext__pwmsearch)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        (void)newXS("TFBS::Ext::pwmsearch::search_xs", XS_TFBS__Ext__pwmsearch_search_xs, file);
#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

