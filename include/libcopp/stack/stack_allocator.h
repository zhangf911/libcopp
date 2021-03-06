#ifndef _COPP_STACKCONTEXT_STACK_ALLOCATOR_H_
#define _COPP_STACKCONTEXT_STACK_ALLOCATOR_H_


#include <libcopp/utils/features.h>

#include "allocator/stack_allocator_memory.h"
#include "allocator/stack_allocator_malloc.h"

#ifdef COPP_MACRO_USE_SEGMENTED_STACKS
#include "allocator/stack_allocator_split_segment.h"
#endif

#ifdef COPP_MACRO_COMPILER_MSVC
#include "allocator/stack_allocator_windows.h"
namespace copp {
    namespace allocator {
        typedef stack_allocator_windows default_statck_allocator;
    }
}
#else
#include "allocator/stack_allocator_posix.h"
namespace copp {
    namespace allocator {
        typedef stack_allocator_posix default_statck_allocator;
    }
}
#endif

#endif /* STACK_ALLOCATOR_H_ */
