/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Paulus Gandung Prakosa <gandung@infradead.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PD_LIST_H
#define __PD_LIST_H

#include <stddef.h>

typedef struct pd_list {
    struct pd_list *prev;
    struct pd_list *next;
} pd_list_t;

#define pd_list_init_val(a, b) { (a), (b) }

#define pd_list(name) \
    pd_list_t name = pd_list_init_val(NULL, NULL)

#define pd_list_initref_ext(name, a, b) do { \
    (name)->prev = (a);
    (name)->next = (b);
} while (0);

static inline void pd_list_add(pd_list_t *root, pd_list_t *node)
{
    node->prev = !root->prev ? root : root->prev;
    node->next = NULL;

    if (node->prev)
        node->prev->next = node;

    root->prev = node;
}

static inline int pd_list_empty(pd_list_t *list)
{
    return list == NULL;
}

#define pd_list_entry(ptr, type, member) \
    pd_container_of(ptr, type, member)

#define pd_list_for_each(elm, list) \
    for ((elm) = (list); (elm) != NULL; (elm) = (elm)->next)

static inline size_t pd_list_count_nodes(pd_list_t *list)
{
    size_t count;
    pd_list_t *elm;

    count = 0;

    pd_list_for_each(elm, list)
        count++;

    return count;
}

#endif /* __PD_LIST_H */
