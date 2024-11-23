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

#ifndef __PD_TREE_H
#define __PD_TREE_H

#include <pd_smbuf.h>

typedef struct pd_tree_data {
    pd_smbuf_t *key;
    pd_smbuf_t *value;
} pd_tree_data_t;

typedef struct pd_tree {
    size_t hash;
    pd_tree_data_t *data;
    struct pd_tree *parent;
    struct pd_tree *left;
    struct pd_tree *right;
} pd_tree_t;

pd_tree_data_t *pd_tree_data_alloc(void);
pd_tree_data_t *pd_tree_data_init(pd_smbuf_t *key, pd_smbuf_t *value);
void pd_tree_data_release(pd_tree_data_t *data);

pd_tree_t *pd_tree_alloc(void);
pd_tree_t *pd_tree_init(pd_tree_data_t *data);
pd_tree_t *pd_tree_search(pd_tree_t *root, pd_tree_t *node);
pd_tree_t *pd_tree_search_fn(pd_tree_t *root, pd_tree_t *node,
                           int (*compare)(pd_tree_t *, pd_tree_t *));
pd_tree_t *pd_tree_search_key(pd_tree_t *root, const char *buf);
pd_tree_t *pd_tree_min(pd_tree_t *root);
pd_tree_t *pd_tree_max(pd_tree_t *root);

void pd_tree_insert(pd_tree_t **root, pd_tree_t *node);
void pd_tree_delete(pd_tree_t **root, pd_tree_t *node);

#endif /* __PD_TREE_H */
