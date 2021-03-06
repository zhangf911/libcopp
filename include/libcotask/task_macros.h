﻿/*
 * task_macros.h
 *
 *  Created on: 2014年5月6日
 *      Author: owent
 *
 *  Released under the MIT license
 */

#ifndef _COTASK_TASK_MACROS_H_
#define _COTASK_TASK_MACROS_H_

#include <stdint.h>

#include <libcopp/utils/errno.h>
#include <libcopp/utils/features.h>
#include <libcopp/coroutine/coroutine_context_container.h>

#include <libcotask/core/standard_new_allocator.h>
#include "libcotask/core/standard_int_id_allocator.h"
#include <libcotask/impl/task_impl.h>

namespace cotask {
    struct macro_coroutine
    {
        typedef copp::detail::coroutine_context_safe_base coroutine_t;
        typedef copp::allocator::default_statck_allocator stack_allocator_t;

        typedef copp::detail::coroutine_context_container<coroutine_t, stack_allocator_t> coroutine_container_t;
    };

    struct macro_task
    {
        typedef uint64_t id_t;
        typedef core::standard_int_id_allocator<uint64_t> id_allocator_t;

        typedef core::standard_new_allocator action_allocator_t;
        typedef core::standard_new_allocator task_allocator_t;
    };
}

#endif /* _COTASK_THIS_TASK_H_ */
