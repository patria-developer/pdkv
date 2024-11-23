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

#include <pd_event.h>
#include <pd_hdlr.h>
#include <pd_net.h>
#include <pd_server.h>
#include <pd_tree.h>

int pd_run_server(void)
{
    pd_hdlr_t *hdlr;
    pd_net_t *net;
    pd_tree_t *tree;

    tree = NULL;
    net  = pd_net_alloc();

    if (!net)
        goto __fallback;

    hdlr = pd_hdlr_alloc();

    if (!hdlr)
        goto __release_net;

    pd_hdlr_build(&hdlr);
    pd_net_open(&net);

    if (pd_net_bind(&net, "0.0.0.0", 31337) < 0)
        goto __release_net;

    if (pd_net_listen(&net, PD_MAX_BACKLOG) < 0)
        goto __release_net;

    pd_event_loop(net, tree, hdlr);

__release_net:
    pd_net_release(net);

__fallback:
    return -1;
}
