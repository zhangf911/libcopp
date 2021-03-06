extern "C" {
#include <signal.h>
}

#include <cstring>
#include <algorithm>
#include <assert.h>
#include <limits>


#include "libcopp/stack/stack_context.h"
#include "libcopp/fcontext/fcontext.hpp"
#include "libcopp/stack/allocator/stack_allocator_split_segment.h"


#ifdef COPP_MACRO_USE_SEGMENTED_STACKS
extern "C" {
void* __splitstack_makecontext( std::size_t, void* [COPP_MACRO_SEGMENTED_STACK_NUMBER], std::size_t *);

void __splitstack_releasecontext( void* [COPP_MACRO_SEGMENTED_STACK_NUMBER]);

void __splitstack_resetcontext( void* [COPP_MACRO_SEGMENTED_STACK_NUMBER]);

void __splitstack_block_signals_context( void* [COPP_MACRO_SEGMENTED_STACK_NUMBER], int* new_value, int* old_value);
}
#endif

#ifdef COPP_HAS_ABI_HEADERS
# include COPP_ABI_PREFIX
#endif


#if !defined (SIGSTKSZ)
# define SIGSTKSZ (8 * 1024)
# define UDEF_SIGSTKSZ
#endif

namespace copp { 
    namespace allocator {

        stack_allocator_split_segment::stack_allocator_split_segment() { }

        stack_allocator_split_segment::~stack_allocator_split_segment() { }

        bool stack_allocator_split_segment::is_stack_unbound() { return true; }

        std::size_t stack_allocator_split_segment::default_stacksize() {
            return minimum_stacksize();
        }

        std::size_t stack_allocator_split_segment::minimum_stacksize() {
            return SIGSTKSZ + sizeof(fcontext::fcontext_t) + 15;
        }

        std::size_t stack_allocator_split_segment::maximum_stacksize() {
            return std::numeric_limits<std::size_t>::max();
        }

        void stack_allocator_split_segment::allocate(stack_context & ctx, std::size_t size)
        {
            void* start_ptr = __splitstack_makecontext( size, ctx.segments_ctx, &ctx.size);
            assert(start_ptr);
            ctx.sp = static_cast<char *>(start_ptr) + ctx.size; // stack down

            int off = 0;
            __splitstack_block_signals_context(ctx.segments_ctx, &off, 0);
        }

        void stack_allocator_split_segment::deallocate(stack_context & ctx)
        {
            __splitstack_releasecontext( ctx.segments_ctx);
        }

    } 
}

#ifdef UDEF_SIGSTKSZ
# undef SIGSTKSZ
#endif

#ifdef COPP_HAS_ABI_HEADERS
# include COPP_ABI_SUFFIX
#endif
