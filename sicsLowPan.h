#ifndef SICSLOWPAN_H_
#define SICSLOWPAN_H_

/**
 * \addtogroup sicslowpan
 * @{
 */

/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: sicslowpan.h,v 1.13 2010/03/26 10:28:51 joxe Exp $
 */
/**
 * \file
 *         Header file for the 6lowpan implementation
 *         (RFC4944 and draft-hui-6lowpan-hc-01)
 * \author Adam Dunkels <adam@sics.se>
 * \author Nicolas Tsiftes <nvt@sics.se>
 * \author Niclas Finne <nfi@sics.se>
 * \author Mathilde Durvy <mdurvy@cisco.com>
 * \author Julien Abeille <jabeille@cisco.com>
 */
  
#include "conf.h"
#include "rimeaddr.h"


/**
 * \name General sicslowpan defines
 * @{
 */
/* Min and Max compressible UDP ports - HC06 */
#define SICSLOWPAN_UDP_4_BIT_PORT_MIN                     0xF0B0
#define SICSLOWPAN_UDP_4_BIT_PORT_MAX                     0xF0BF   /* F0B0 + 15 */
#define SICSLOWPAN_UDP_8_BIT_PORT_MIN                     0xF000
#define SICSLOWPAN_UDP_8_BIT_PORT_MAX                     0xF0FF   /* F000 + 255 */

#define SICSLOWPAN_CONF_COMPRESSION_IPV6        0
#define SICSLOWPAN_CONF_COMPRESSION_HC1         1
#define SICSLOWPAN_CONF_COMPRESSION_HC06        2

/**
 * \name 6lowpan dispatches
 * @{
 */
#define SICSLOWPAN_DISPATCH_IPV6                    0x41 /* 01000001 = 65 */
#define SICSLOWPAN_DISPATCH_HC1                     0x42 /* 01000010 = 66 */
#define SICSLOWPAN_DISPATCH_IPHC                    0x60 /* 011xxxxx = ... */
#define SICSLOWPAN_DISPATCH_FRAG1                   0xc0 /* 11000xxx */
#define SICSLOWPAN_DISPATCH_FRAGN                   0xe0 /* 11100xxx */
/** @} */

/** \name HC1 encoding
 * @{
 */
#define SICSLOWPAN_HC1_NH_UDP                       0x02
#define SICSLOWPAN_HC1_NH_TCP                       0x06
#define SICSLOWPAN_HC1_NH_ICMP6                     0x04
/** @} */

/** \name HC_UDP encoding (works together with HC1)
 * @{
 */
#define SICSLOWPAN_HC_UDP_ALL_C                     0xE0
/** @} */

/**
 * \name IPHC encoding
 * @{
 */
/*
 * Values of fields within the IPHC encoding first byte
 * (C stands for compressed and I for inline)
 */
#define SICSLOWPAN_IPHC_FL_C                        0x10
#define SICSLOWPAN_IPHC_TC_C                        0x08
#define SICSLOWPAN_IPHC_NH_C                        0x04
#define SICSLOWPAN_IPHC_TTL_1                       0x01
#define SICSLOWPAN_IPHC_TTL_64                      0x02
#define SICSLOWPAN_IPHC_TTL_255                     0x03
#define SICSLOWPAN_IPHC_TTL_I                       0x00


/* Values of fields within the IPHC encoding second byte */
#define SICSLOWPAN_IPHC_CID                         0x80

#define SICSLOWPAN_IPHC_SAC                         0x40
#define SICSLOWPAN_IPHC_SAM_00                      0x00
#define SICSLOWPAN_IPHC_SAM_01                      0x10
#define SICSLOWPAN_IPHC_SAM_10                      0x20
#define SICSLOWPAN_IPHC_SAM_11                      0x30

#define SICSLOWPAN_IPHC_SAM_BIT                     4

#define SICSLOWPAN_IPHC_M                           0x08
#define SICSLOWPAN_IPHC_DAC                         0x04
#define SICSLOWPAN_IPHC_DAM_00                      0x00
#define SICSLOWPAN_IPHC_DAM_01                      0x01
#define SICSLOWPAN_IPHC_DAM_10                      0x02
#define SICSLOWPAN_IPHC_DAM_11                      0x03

#define SICSLOWPAN_IPHC_DAM_BIT                     0

/* Link local context number */
#define SICSLOWPAN_IPHC_ADDR_CONTEXT_LL             0
/* 16-bit multicast addresses compression */
#define SICSLOWPAN_IPHC_MCAST_RANGE                 0xA0
/** @} */

/* NHC_EXT_HDR */
#define SICSLOWPAN_NHC_MASK                         0xF0
#define SICSLOWPAN_NHC_EXT_HDR                      0xE0

/**
 * \name LOWPAN_UDP encoding (works together with IPHC)
 * @{
 */
/**
 * \name LOWPAN_UDP encoding (works together with IPHC)
 * @{
 */
#define SICSLOWPAN_NHC_UDP_MASK                     0xF8
#define SICSLOWPAN_NHC_UDP_ID                       0xF0
#define SICSLOWPAN_NHC_UDP_CHECKSUMC                0x04
#define SICSLOWPAN_NHC_UDP_CHECKSUMI                0x00
/* values for port compression, _with checksum_ ie bit 5 set to 0 */
#define SICSLOWPAN_NHC_UDP_CS_P_00  0xF0 /* all inline */
#define SICSLOWPAN_NHC_UDP_CS_P_01  0xF1 /* source 16bit inline, dest = 0xF0 + 8 bit inline */
#define SICSLOWPAN_NHC_UDP_CS_P_10  0xF2 /* source = 0xF0 + 8bit inline, dest = 16 bit inline */
#define SICSLOWPAN_NHC_UDP_CS_P_11  0xF3 /* source & dest = 0xF0B + 4bit inline */
/** @} */


/**
 * \name The 6lowpan "headers" length
 * @{
 */

#define SICSLOWPAN_IPV6_HDR_LEN                     1    /*one byte*/
#define SICSLOWPAN_HC1_HDR_LEN                      3
#define SICSLOWPAN_HC1_HC_UDP_HDR_LEN               7
#define SICSLOWPAN_FRAG1_HDR_LEN                    4
#define SICSLOWPAN_FRAGN_HDR_LEN                    5
/** @} */

/**
 * \brief The header for fragments
 * \note We do not define different structures for FRAG1
 * and FRAGN headers, which are different. For FRAG1, the
 * offset field is just not used
 */
/* struct sicslowpan_frag_hdr { */
/*   u16_t dispatch_size; */
/*   u16_t tag; */
/*   u8_t offset; */
/* }; */

/**
 * \brief The HC1 header when HC_UDP is not used
 *
 * When all fields are compressed and HC_UDP is not used,
 * we use this structure. If HC_UDP is used, the ttl is
 * in another spot, and we use the sicslowpan_hc1_hc_udp
 * structure
 */
/* struct sicslowpan_hc1_hdr { */
/*   u8_t dispatch; */
/*   u8_t encoding; */
/*   u8_t ttl; */
/* }; */

/**
 * \brief HC1 followed by HC_UDP
 */
/* struct sicslowpan_hc1_hc_udp_hdr { */
/*   u8_t dispatch; */
/*   u8_t hc1_encoding; */
/*   u8_t hc_udp_encoding; */
/*   u8_t ttl; */
/*   u8_t ports; */
/*   u16_t udpchksum; */
/* }; */

/**
 * \brief An address context for IPHC address compression
 * each context can have upto 8 bytes
 */
struct sicslowpan_addr_context {
  u8_t used; /* possibly use as prefix-length */
  u8_t number;
  u8_t prefix[8];
};

/**
 * \name Address compressibility test functions
 * @{
 */

/**
 * \brief check whether we can compress the IID in
 * address 'a' to 16 bits.
 * This is used for unicast addresses only, and is true
 * if the address is on the format <PREFIX>::0000:00ff:fe00:XXXX
 * NOTE: we currently assume 64-bits prefixes
 */
#define sicslowpan_is_iid_16_bit_compressable(a) \
  ((((a)->u16[4]) == 0) &&                       \
   (((a)->u8[10]) == 0)&&			    \
   (((a)->u8[11]) == 0xff)&&			    \
   (((a)->u8[12]) == 0xfe)&&			    \
   (((a)->u8[13]) == 0))

/**
 * \brief check whether the 9-bit group-id of the
 * compressed multicast address is known. It is true
 * if the 9-bit group is the all nodes or all routers
 * group.
 * \param a is typed u8_t *
 */
#define sicslowpan_is_mcast_addr_decompressable(a) \
   (((*a & 0x01) == 0) &&                           \
    ((*(a + 1) == 0x01) || (*(a + 1) == 0x02)))

/**
 * \brief check whether the 112-bit group-id of the
 * multicast address is mappable to a 9-bit group-id
 * It is true if the group is the all nodes or all
 * routers group.
*/
#define sicslowpan_is_mcast_addr_compressable(a) \
  ((((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u16[5]) == 0) &&                       \
   (((a)->u16[6]) == 0) &&                       \
   (((a)->u8[14]) == 0) &&                       \
   ((((a)->u8[15]) == 1) || (((a)->u8[15]) == 2)))

/* FFXX::00XX:XXXX:XXXX */
#define sicslowpan_is_mcast_addr_compressable48(a) \
  ((((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u8[10]) == 0))

/* FFXX::00XX:XXXX */
#define sicslowpan_is_mcast_addr_compressable32(a) \
  ((((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u16[5]) == 0) &&                       \
   (((a)->u8[12]) == 0))

/* FF02::00XX */
#define sicslowpan_is_mcast_addr_compressable8(a) \
  ((((a)->u8[1]) == 2) &&                        \
   (((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u16[5]) == 0) &&                       \
   (((a)->u16[6]) == 0) &&                       \
   (((a)->u8[14]) == 0))

/*---FROM uip.h---*/
#define uip_is_addr_mac_addr_based(a, m) \
  ((((a)->u8[8])  == (((m)->addr[0]) ^ 0x02)) &&   \
   (((a)->u8[9])  == (m)->addr[1]) &&            \
   (((a)->u8[10]) == (m)->addr[2]) &&            \
   (((a)->u8[11]) == (m)->addr[3]) &&            \
   (((a)->u8[12]) == (m)->addr[4]) &&            \
   (((a)->u8[13]) == (m)->addr[5]) &&            \
   (((a)->u8[14]) == (m)->addr[6]) &&            \
   (((a)->u8[15]) == (m)->addr[7]))
   
   
/**
 * \brief is addr (a) a link local unicast address, see RFC3513
 *  i.e. is (a) on prefix FE80::/10
 *  a is of type uip_ipaddr_t*
 */
#define uip_is_addr_link_local(a) \
  ((((a)->u8[0]) == 0xFE) && \
  (((a)->u8[1]) == 0x80))
  
  /**
 * \brief is address a multicast address, see RFC 3513
 * a is of type uip_ipaddr_t*
 * */
#define uip_is_addr_mcast(a)                    \
  (((a)->u8[0]) == 0xFF)
  
  /**
 * \brief Is IPv6 address a the unspecified address
 * a is of type uip_ipaddr_t
 */
#define uip_is_addr_unspecified(a)               \
  ((((a)->u16[0]) == 0) &&                       \
   (((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u16[5]) == 0) &&                       \
   (((a)->u16[6]) == 0) &&                       \
   (((a)->u16[7]) == 0))
   
   
   #define uip_ipaddr_prefixcmp(addr1, addr2, length) (memcmp(addr1, addr2, length>>3) == 0)

/** @} */

/*-----------------------------------------------------------------------------*/
/*------------------------------ API DESCRIPTION ------------------------------*/
/*-----------------------------------------------------------------------------*/

/*
 * This function initializes the 6loWPAN contexts for compression.
 * Must be called just once and before compressing or decompressing.
 */
void sicslowpan_init(uip_lladdr_t* myMac);

/*
 * This is the function to call in order to compress an IPv6 packet into a 6loWPAN packet.
 * 
 * Preconditions: 
 * 	The 'uip_lladdr' global variable must have the value of the link (MAC) layer address of the source (sender).
 * 	The 'uip_buf' pointer must buffer the IPv6 packet that is willing to be compressed.
 * 	The 'uip_len' variable's value must correspond to the length of the IPv6 packet placed in 'uip_buf'.
 *  
 * Postconditions:
 * 	The 'uip_6lp_buf' variable will point to the buffer that will contain the compressed IPv6 packet (the 6loWPAN packet) that must be sent by the link (MAC) layer.
 *  The 'uip_6lp_len' variable will contain the length of the compressed IPv6 packet (the 6loWPAN packet) that must be sent by the link (MAC) layer.
 * 
 * Returns: 0 if it fails, 1 in other case.
 * 
 * localdest: This is a pointer to the data structure that contains the link layer (MAC) address of the destination to send the frame.
 * 
 * IMPORTANT: The buffers containing the IPv6 packets and the compressed 6loWPAN packets consist in UINT16 positions where each contains only ONE byte represented by the 8 less significant bits.
 */
uint8_t output(uip_lladdr_t *localdest);


/*
 * This is the function to call in order to decompress an incoming 6loWPAN packet into an IPv6 packet.
 * 
 * Preconditions:
 *	The 'uip_6lp_buf' variable must point to the buffer that contains the incoming compressed IPv6 packet (the 6loWPAN packet) that is willing to be decompressed.
 *      The 'uip_6lp_len' variable must contain the length of the compressed IPv6 packet (the 6loWPAN packet) that is willing to be decompressed.
 * 
 * Postconditions: 
 * 	The 'uip_buf' pointer will buffer the IPv6 packet that was obtained by decompressing the 6loWPAN incoming packet pointed by the 'uip_6lp_buf'.
 * 	The 'uip_len' variable's value will correspond to the length of the IPv6 packet pointed by 'uip_buf', obtained by the decompression.
 * 
 * Parameters:
 * 	uip_lladdr_source: This is a pointer to a data structure that contains the link layer (MAC) address of the source that sent the received frame.
 * 	uip_lladdr_destination: This is a pointer to a data structure that contains the link layer (MAC) address of the destination of the received frame.
 * 
 * IMPORTANT: The buffers containing the IPv6 packets and the compressed 6loWPAN packets consist in UINT16 positions where each contains only ONE byte represented by the 8 less significant bits.
 */
void input(uip_lladdr_t *uip_lladdr_source, uip_lladdr_t *uip_lladdr_destination);

//ADDED ALE
typedef union {
  uint8_t u8[UIP_BUFSIZE];
} uip_ll_buf_t;

//The buffer that will contain the compressed IPv6 packet (the 6loWPAN packet) that must be sent by the link (MAC) layer.
//It is also the buffer the buffer that contains the incoming compressed IPv6 packet (the 6loWPAN packet) that is willing to be decompressed.
extern uip_ll_buf_t uip_6lp_buf;

//The variable that will contain the length of the compressed IPv6 packet (the 6loWPAN packet) that must be sent by the link (MAC) layer.
//It is also the length of the compressed IPv6 packet (the 6loWPAN packet) that is willing to be decompressed.
extern u16_t uip_6lp_len;

//The pointer to the buffer where the decompressed ipv6 packet will be
//This pointer has to be initialized by the user of output and input 6lowpan functions 
extern uint8_t* uip_buf;

//The amount of valid data bytes in the uip_buf buffer
extern uint16_t uip_length;

extern uip_lladdr_t* uip_lladdr;
		
#endif /*SICSLOWPAN_H_*/
