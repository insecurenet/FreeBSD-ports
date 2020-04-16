/*
 * Copyright (C) 2002 WIDE Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

#include "common.h"

/* Mobility header */
struct ip6_mobility {
	u_int8_t ip6m_pproto;	/* following payload protocol (for PG) */
	u_int8_t ip6m_len;	/* length in units of 8 octets */
	u_int8_t ip6m_type;	/* message type */
	u_int8_t reserved;	/* reserved */
	u_int16_t ip6m_cksum;	/* sum of IPv6 pseudo-header and MH */
	union {
		u_int16_t	ip6m_un_data16[1]; /* type-specific field */
		u_int8_t	ip6m_un_data8[2];  /* type-specific fiedl */
	} ip6m_dataun;
};

#define ip6m_data16	ip6m_dataun.ip6m_un_data16
#define ip6m_data8	ip6m_dataun.ip6m_un_data8

#define IP6M_MINLEN	8

/* message type */
#define IP6M_BINDING_REQUEST	0	/* Binding Refresh Request */
#define IP6M_HOME_TEST_INIT	1	/* Home Test Init */
#define IP6M_CAREOF_TEST_INIT	2	/* Care-of Test Init */
#define IP6M_HOME_TEST		3	/* Home Test */
#define IP6M_CAREOF_TEST	4	/* Care-of Test */
#define IP6M_BINDING_UPDATE	5	/* Binding Update */
#define IP6M_BINDING_ACK	6	/* Binding Acknowledgement */
#define IP6M_BINDING_ERROR	7	/* Binding Error */

/* Mobility Header Options */
#define IP6MOPT_MINLEN		2
#define IP6MOPT_PAD1          0x0	/* Pad1 */
#define IP6MOPT_PADN          0x1	/* PadN */
#define IP6MOPT_REFRESH	      0x2	/* Binding Refresh Advice */
#define IP6MOPT_REFRESH_MINLEN  4
#define IP6MOPT_ALTCOA        0x3	/* Alternate Care-of Address */
#define IP6MOPT_ALTCOA_MINLEN  18
#define IP6MOPT_NONCEID       0x4	/* Nonce Indices */
#define IP6MOPT_NONCEID_MINLEN  6
#define IP6MOPT_AUTH          0x5	/* Binding Authorization Data */
#define IP6MOPT_AUTH_MINLEN    12

#if 0
static void
mobility_opt_print(struct sbuf *sbuf, const u_char *bp, int len)
{
	int i;
	int optlen;

	for (i = 0; i < len; i += optlen) {
		if (bp[i] == IP6MOPT_PAD1)
			optlen = 1;
		else {
			if (i + 1 < len)
				optlen = bp[i + 1] + 2;
			else
				goto trunc;
		}
		if (i + optlen > len)
			goto trunc;

		switch (bp[i]) {
		case IP6MOPT_PAD1:
			printf("(pad1)");
			break;
		case IP6MOPT_PADN:
			if (len - i < IP6MOPT_MINLEN) {
				printf("(padn: trunc)");
				goto trunc;
			}
			printf("(padn)");
			break;
		case IP6MOPT_REFRESH:
			if (len - i < IP6MOPT_REFRESH_MINLEN) {
				printf("(refresh: trunc)");
				goto trunc;
			}
			/* units of 4 secs */
			printf("(refresh: %d)",
				EXTRACT_16BITS(&bp[i+2]) << 2);
			break;
		case IP6MOPT_ALTCOA:
			if (len - i < IP6MOPT_ALTCOA_MINLEN) {
				printf("(altcoa: trunc)");
				goto trunc;
			}
			printf("(alt-CoA: %s)", ip6addr_string(&bp[i+2]));
			break;
		case IP6MOPT_NONCEID:
			if (len - i < IP6MOPT_NONCEID_MINLEN) {
				printf("(ni: trunc)");
				goto trunc;
			}
			printf("(ni: ho=0x%04x co=0x%04x)",
				EXTRACT_16BITS(&bp[i+2]),
				EXTRACT_16BITS(&bp[i+4]));
			break;
		case IP6MOPT_AUTH:
			if (len - i < IP6MOPT_AUTH_MINLEN) {
				printf("(auth: trunc)");
				goto trunc;
			}
			printf("(auth)");
			break;
		default:
			if (len - i < IP6MOPT_MINLEN) {
				printf("(sopt_type %d: trunc)", bp[i]);
				goto trunc;
			}
			printf("(type-0x%02x: len=%d)", bp[i], bp[i + 1]);
			break;
		}
	}
	return;

trunc:
	printf("[trunc] ");
}
#endif

/*
 * Mobility Header
 */
int
mobility_print(struct sbuf *sbuf, const u_char *bp, int len)
{
	const struct ip6_mobility *mh;
	const u_char *ep;
	int mhlen, hlen, type;
	char ip6addr[INET6_ADDRSTRLEN];

	mh = (const struct ip6_mobility *)bp;

	/* 'ep' points to the end of available data. */
	ep = bp + len;

#if 0
	if (!(ep - sizeof(mh->ip6m_len)) < ep) {
		/*
		 * There's not enough captured data to include the
		 * mobility header length.
		 *
		 * Our caller expects us to return the length, however,
		 * so return a value that will run to the end of the
		 * captured data.
		 *
		 * XXX - "ip6_print()" doesn't do anything with the
		 * returned length, however, as it breaks out of the
		 * header-processing loop.
		 */
		mhlen = ep - bp;
		goto trunc;
	}
#endif
	mhlen = (int)((mh->ip6m_len + 1) << 3);

	/* XXX ip6m_cksum */

	type = mh->ip6m_type;
	switch (type) {
	case IP6M_BINDING_REQUEST:
		sbuf_printf(sbuf, "BRR,");
		hlen = IP6M_MINLEN;
		break;
	case IP6M_HOME_TEST_INIT:
	case IP6M_CAREOF_TEST_INIT:
		sbuf_printf(sbuf, "%soTI,",
			type == IP6M_HOME_TEST_INIT ? "H" : "C");
		hlen = IP6M_MINLEN;
		sbuf_printf(sbuf, "%s, %08x:%08x,",
			       type == IP6M_HOME_TEST_INIT ? "Home" : "Care-of",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		hlen += 8;
		break;
	case IP6M_HOME_TEST:
	case IP6M_CAREOF_TEST:
		sbuf_printf(sbuf, "%soT,",
			type == IP6M_HOME_TEST ? "H" : "C");
		sbuf_printf(sbuf, "0x%x, ", EXTRACT_16BITS(&mh->ip6m_data16[0]));
		hlen = IP6M_MINLEN;
		sbuf_printf(sbuf, "%s, %08x:%08x,",
			       type == IP6M_HOME_TEST ? "Home" : "Care-of",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		hlen += 8;
		sbuf_printf(sbuf, "%08x:%08x,",
			       EXTRACT_32BITS(&bp[hlen]),
			       EXTRACT_32BITS(&bp[hlen + 4]));
		hlen += 8;
		break;
	case IP6M_BINDING_UPDATE:
		sbuf_printf(sbuf, "BINDINGUPDATE,");
		sbuf_printf(sbuf, "%d,", EXTRACT_16BITS(&mh->ip6m_data16[0]));
		hlen = IP6M_MINLEN;
		if (bp[hlen] & 0xf0)
			sbuf_printf(sbuf, " ");
		if (bp[hlen] & 0x80)
			sbuf_printf(sbuf, "A");
		if (bp[hlen] & 0x40)
			sbuf_printf(sbuf, "H");
		if (bp[hlen] & 0x20)
			sbuf_printf(sbuf, "L");
		if (bp[hlen] & 0x10)
			sbuf_printf(sbuf, "K");
		/* Reserved (4bits) */
		hlen += 1;
		/* Reserved (8bits) */
		hlen += 1;
		/* units of 4 secs */
		sbuf_printf(sbuf, "%d,", EXTRACT_16BITS(&bp[hlen]) << 2);
		hlen += 2;
		break;
	case IP6M_BINDING_ACK:
		sbuf_printf(sbuf, "BINDINGACK,");
		sbuf_printf(sbuf, "%d,", mh->ip6m_data8[0]);
		if (mh->ip6m_data8[1] & 0x80)
			sbuf_printf(sbuf, "K");
		/* Reserved (7bits) */
		hlen = IP6M_MINLEN;
		sbuf_printf(sbuf, "%d,", EXTRACT_16BITS(&bp[hlen]));
		hlen += 2;
		/* units of 4 secs */
		sbuf_printf(sbuf, "%d,", EXTRACT_16BITS(&bp[hlen]) << 2);
		hlen += 2;
		break;
	case IP6M_BINDING_ERROR:
		sbuf_printf(sbuf, "BINDINGERR,");
		sbuf_printf(sbuf, "%d,", mh->ip6m_data8[0]);
		/* Reserved */
		hlen = IP6M_MINLEN;
		memset(ip6addr, 0, INET6_ADDRSTRLEN);
		sbuf_printf(sbuf, "%s,", inet_ntop(AF_INET6, &bp[hlen], ip6addr, INET6_ADDRSTRLEN));
		hlen += 16;
		break;
	default:
		sbuf_printf(sbuf, "TYPE,%d,%d", type, mh->ip6m_len);
		return(mhlen);
		break;
	}
#if 0
	mobility_opt_print(sbuf, &bp[hlen], mhlen - hlen);
#endif

	return(mhlen);
}
