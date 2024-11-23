# BSD 3-Clause License
#
# Copyright (c) 2024, Paulus Gandung Prakosa <gandung@infradead.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CC = gcc
CFLAGS += -I. -Wall -g -ggdb

SRCDIR = .

OBJS = \
	$(SRCDIR)/pd_cmd.o \
	$(SRCDIR)/pd_event.o \
	$(SRCDIR)/pd_hash.o \
	$(SRCDIR)/pd_hdlr.o \
	$(SRCDIR)/pd_main.o \
	$(SRCDIR)/pd_net.o \
	$(SRCDIR)/pd_server.o \
	$(SRCDIR)/pd_smbuf.o \
	$(SRCDIR)/pd_tree.o

all: pdkv

clean:
	rm -rf pdkv *.o

pdkv: $(OBJS)
	$(CC) $(CFLAGS) -o pdkv $(OBJS)

$(SRCDIR)/pd_cmd.o: $(SRCDIR)/pd_cmd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_event.o: $(SRCDIR)/pd_event.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_hash.o: $(SRCDIR)/pd_hash.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_hdlr.o: $(SRCDIR)/pd_hdlr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_main.o: $(SRCDIR)/pd_main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_net.o: $(SRCDIR)/pd_net.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_server.o: $(SRCDIR)/pd_server.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_smbuf.o: $(SRCDIR)/pd_smbuf.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pd_tree.o: $(SRCDIR)/pd_tree.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean
