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

#ifndef __PD_SMBUF_H
#define __PD_SMBUF_H

#include <stddef.h>

#ifndef PD_SMBUF_MAXLEN_PER_NODE
#define PD_SMBUF_MAXLEN_PER_NODE 1024
#endif

typedef struct pd_smbuf {
    char buf[PD_SMBUF_MAXLEN_PER_NODE + 1];
    size_t buflen;
    struct pd_smbuf *prev;
    struct pd_smbuf *next;
} pd_smbuf_t;

#define pd_smbuf_for_each(el, root) \
    for ((el) = (root); (el) != NULL; (el) = (el)->next)

pd_smbuf_t *pd_smbuf_alloc(void);
pd_smbuf_t *pd_smbuf_init(const char *buf);

void pd_smbuf_insert_buf(pd_smbuf_t **root, const char *buf);
void pd_smbuf_append(pd_smbuf_t **root, pd_smbuf_t *buf);
void pd_smbuf_release(pd_smbuf_t *root);

size_t pd_smbuf_nodelen(pd_smbuf_t *buf);

#endif /* __PD_SMBUF_H */
