/*
 * Copyright (c) 2002-2018 "Neo4j,"
 * Neo4j Sweden AB [http://neo4j.com]
 *
 * This file is part of Neo4j.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef SEABOLT_MEM
#define SEABOLT_MEM

#include <stdio.h>

#include "config.h"


SEABOLT_EXPORT void* BoltMem_reverse_copy(void * dest, const void * src, size_t n);

#if IS_BIG_ENDIAN
    #define memcpy_be(target, src, n) memcpy(target, src, n)
#else
    #define memcpy_be(target, src, n) BoltMem_reverse_copy(target, src, n)
#endif


/**
 * Allocate memory.
 *
 * @param new_size
 * @return
 */
SEABOLT_EXPORT void* BoltMem_allocate(size_t new_size);

/**
 * Reallocate memory.
 *
 * @param ptr
 * @param old_size
 * @param new_size
 * @return
 */
SEABOLT_EXPORT void* BoltMem_reallocate(void* ptr, size_t old_size, size_t new_size);

/**
 * Deallocate memory.
 *
 * @param ptr
 * @param old_size
 * @return
 */
SEABOLT_EXPORT void* BoltMem_deallocate(void* ptr, size_t old_size);

/**
 * Allocate, reallocate or free memory for data storage.
 *
 * Since we recycle values, we can also potentially recycle
 * the dynamically-allocated storage.
 *
 * @param ptr a pointer to the existing memory (if any)
 * @param old_size the number of bytes already allocated
 * @param new_size the new number of bytes required
 */
SEABOLT_EXPORT void* BoltMem_adjust(void* ptr, size_t old_size, size_t new_size);

/**
* Duplicates the memory region specified by ptr and ptr_size.
*
* @param ptr
* @param ptr_size
* @return
*/
SEABOLT_EXPORT void* BoltMem_duplicate(const void *ptr, size_t ptr_size);

/**
 * Retrieve the amount of memory currently allocated.
 *
 * @return
 */
SEABOLT_EXPORT size_t BoltMem_current_allocation();

/**
 *
 * @return
 */
SEABOLT_EXPORT size_t BoltMem_peak_allocation();

/**
 * Get an activity count for memory (de/re/-)allocation.
 *
 * @return
 */
SEABOLT_EXPORT int64_t BoltMem_allocation_events();


#endif // SEABOLT_MEM
