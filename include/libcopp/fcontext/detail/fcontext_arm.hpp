
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef _COPP_BOOST_CONTEXT_DETAIL_FCONTEXT_ARM_H
#define _COPP_BOOST_CONTEXT_DETAIL_FCONTEXT_ARM_H

#include <cstddef>

#include <cstddef>
#include <stdint.h>

#include "libcopp/utils/features.h"
#include "libcopp/fcontext/detail/config.hpp"

#ifdef COPP_HAS_ABI_HEADERS
# include COPP_ABI_PREFIX
#endif
namespace copp {
    namespace fcontext {

extern "C" {

#define COPP_BOOST_CONTEXT_CALLDECL

struct stack_t
{
    void    *   sp;
    std::size_t size;

    stack_t() :
        sp( 0), size( 0)
    {}
};

struct fp_t
{
    uint32_t     fc_freg[16];

    fp_t() :
        fc_freg()
    {}
};

struct fcontext_t
{
    uint32_t     fc_greg[11];
    stack_t             fc_stack;
    fp_t                fc_fp;

    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_fp()
    {}
};

}

}}

#ifdef COPP_HAS_ABI_HEADERS
# include COPP_ABI_SUFFIX
#endif
#endif // BOOST_CONTEXT_DETAIL_FCONTEXT_ARM_H
