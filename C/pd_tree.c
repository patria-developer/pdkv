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

#include <pd_tree.h>
#include <pd_hash.h>
#include <pd_smbuf.h>

pd_tree_data_t *pd_tree_data_alloc(void)
{
    pd_tree_data_t *ret;

    ret = calloc(1, sizeof(pd_tree_data_t));

    if (!ret)
        return NULL;

    return ret;
}

pd_tree_data_t *pd_tree_data_init(pd_smbuf_t *key, pd_smbuf_t *value)
{
    pd_tree_data_t *ret;

    ret = pd_tree_data_alloc();

    if (!ret)
        return NULL;

    ret->key = key;
    ret->value = value;
    return ret;
}

pd_tree_t *pd_tree_alloc(void)
{
    pd_tree_t *ret;

    ret = calloc(1, sizeof(pd_tree_t));

    if (!ret)
        return NULL;

    return ret;
}

void pd_tree_data_release(pd_tree_data_t *data)
{
    pd_smbuf_release(data->key);
    pd_smbuf_release(data->value);
    free(data);
}

pd_tree_t *pd_tree_init(pd_tree_data_t *data)
{
    size_t hash;
    pd_tree_t *ret;
    pd_smbuf_t *el;

    hash = 0;
    ret  = pd_tree_alloc();

    if (!ret)
        return NULL;

    pd_smbuf_for_each(el, data->key)
        hash += pd_hash(el->buf);

    pd_smbuf_for_each(el, data->value)
        hash += pd_hash(el->buf);

    ret->hash   = hash;
    ret->data   = data;
    ret->parent = ret->left = ret->right = NULL;

    return ret;
}

static int __pd_tree_cdef_fn(pd_tree_t *a, pd_tree_t *b)
{
    return a->hash - b->hash;
}

pd_tree_t *pd_tree_search(pd_tree_t *root, pd_tree_t *node)
{
    return pd_tree_search_fn(root, node, __pd_tree_cdef_fn);
}

pd_tree_t *pd_tree_search_fn(pd_tree_t *root, pd_tree_t *node,
                             int (*compare)(pd_tree_t *, pd_tree_t *))
{
    if (root == NULL || !compare(root, node))
        return root;

    if (compare(root, node) < 0)
        return pd_tree_search_fn(root->left, node, compare);

    return pd_tree_search_fn(root->right, node, compare);
}

pd_tree_t *pd_tree_search_key(pd_tree_t *root, const char *buf)
{
    if (root == NULL)
        return NULL;

    if (!strcmp(buf, root->data->key->buf))
        return root;

    if (strcmp(buf, root->data->key->buf))
        return pd_tree_search_key(root->left, buf);

    return pd_tree_search_key(root->right, buf);
}

pd_tree_t *pd_tree_min(pd_tree_t *root)
{
    pd_tree_t *tmp;

    tmp = root;

    while (tmp->left != NULL)
        tmp = tmp->left;

    return tmp;
}

pd_tree_t *pd_tree_max(pd_tree_t *root)
{
    pd_tree_t *tmp;

    tmp = root;

    while (tmp->right != NULL)
        tmp = tmp->right;

    return tmp;
}

void pd_tree_insert(pd_tree_t **root, pd_tree_t *node)
{
    pd_tree_t *tmp, *res;

    tmp = (*root);
    res = NULL;

    while (tmp != NULL) {
        res = tmp;
        tmp = res->hash < tmp->hash ? tmp->left : tmp->right;
    }

    node->parent = res;

    if (res == NULL) {
        *root = node;
        return;
    }

    if (node->hash < res->hash)
        res->left = node;
    else
        res->right = node;
}

static void pd_tree_transplant(pd_tree_t **root,
                               pd_tree_t *a, pd_tree_t *b)
{
    if (a->parent == NULL) {
        *root = b;
        return;
    }

    if (a == a->parent->left)
        a->parent->left = b;
    else
        a->parent->right = b;

    if (b != NULL)
        b->parent = a->parent;
}

void pd_tree_delete(pd_tree_t **root, pd_tree_t *node)
{
    pd_tree_t *tmp;

    if (node->left == NULL) {
        pd_tree_transplant(root, node, node->right);
        return;
    }

    if (node->right == NULL) {
        pd_tree_transplant(root, node, node->left);
        return;
    }

    tmp = pd_tree_min(node->right);

    if (tmp->parent != node) {
        pd_tree_transplant(root, tmp, tmp->right);
        tmp->right = node->right;
        tmp->right->parent = tmp;
    }

    pd_tree_transplant(root, node, tmp);
    tmp->left = node->left;
    tmp->left->parent = tmp;
}
