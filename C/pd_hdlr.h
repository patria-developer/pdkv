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

#ifndef __PD_HDLR_H
#define __PD_HDLR_H

#include <pd_smbuf.h>
#include <pd_net.h>
#include <pd_tree.h>

typedef enum pd_hdlr_type {
    GET,
    SET,
    DELETE,
    INVALID
} pd_hdlr_type_t;

typedef struct pd_hdlr {
    void (*get)(pd_tree_t **,
                pd_smbuf_t *, pd_net_t *, pd_smbuf_t *, pd_smbuf_t *);
    void (*set)(pd_tree_t **,
                pd_smbuf_t *, pd_net_t *, pd_smbuf_t *, pd_smbuf_t *);
    void (*delete)(pd_tree_t **,
                   pd_smbuf_t *, pd_net_t *, pd_smbuf_t *, pd_smbuf_t *);
    void (*invalid)(pd_tree_t **,
                    pd_smbuf_t *, pd_net_t *, pd_smbuf_t *, pd_smbuf_t *);
} pd_hdlr_t;

pd_hdlr_t *pd_hdlr_alloc(void);

void pd_hdlr_register(pd_hdlr_t **hdlr, pd_hdlr_type_t type,
                      void (*fn)(pd_tree_t **, pd_smbuf_t *,
                                 pd_net_t *, pd_smbuf_t *, pd_smbuf_t *));
void pd_hdlr_build(pd_hdlr_t **hdlr);
void pd_hdlr_release(pd_hdlr_t *hdlr);

#endif /* __PD_HDLR_H */
