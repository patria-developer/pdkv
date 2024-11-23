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

#include <stdlib.h>
#include <string.h>

#include <pd_smbuf.h>

pd_smbuf_t *pd_smbuf_alloc(void)
{
    pd_smbuf_t *ret;

    ret = calloc(1, sizeof(pd_smbuf_t));

    if (!ret)
        return NULL;

    return ret;
}

static void __pd_smbuf_insert_buf(pd_smbuf_t **root, const char *buf)
{
    pd_smbuf_t *tmp;

    tmp = *root;

    while (1) {
        if (*buf == '\0')
            break;

        if (tmp->buflen == PD_SMBUF_MAXLEN_PER_NODE) {
            pd_smbuf_append(&tmp, pd_smbuf_alloc());
            tmp = tmp->next;
        }

        tmp->buf[tmp->buflen++] = *buf++;
    }

	return;
}

pd_smbuf_t *pd_smbuf_init(const char *buf)
{
    pd_smbuf_t *ret;

    ret = pd_smbuf_alloc();

    if (!ret)
        return NULL;

    __pd_smbuf_insert_buf(&ret, buf);

    return ret;
}

void pd_smbuf_insert_buf(pd_smbuf_t **root, const char *buf)
{
    __pd_smbuf_insert_buf(root, buf);
}

void pd_smbuf_append(pd_smbuf_t **root, pd_smbuf_t *buf)
{
    pd_smbuf_t *tmp;

    tmp = *root;

    while (tmp->next != NULL)
        tmp = tmp->next;

    buf->next = NULL;
    buf->prev = tmp;
    tmp->next = buf;
}

void pd_smbuf_release(pd_smbuf_t *root)
{
    pd_smbuf_release(root->next);
    free(root);
}

size_t pd_smbuf_nodelen(pd_smbuf_t *buf)
{
    size_t ncnt;

    ncnt = 0;

    while (buf != NULL) {
        ncnt++;
        buf = buf->next;
    }

    return ncnt;
}