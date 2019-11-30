/************************************************************************
 > File Name: pcap_ct.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sat 30 Nov 2019 06:05:35 PM CST
************************************************************************/

#ifndef PCAP_CT
#define PCAP_CT

#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define MAX_PRINT 80
#define MAX_LINE 16

// #define ETHER_MAX_DATA_LENGTH 1500


struct tcp_header
{
	u_int16_t src_port;  // source port
	u_int16_t dst_port;  // destination port
	unsigned int seq_num; // sequence number
	unsigned int ack_num; // acknowledge number
	u_int8_t hdrLen; // 4 bit header length  4 bit null
	u_int8_t flags;  // 8 bit independent flags
	u_int16_t window; // size of window
	u_int16_t cksum;  // check sum
	u_int16_t urgent_ptr; // urgent pointer
	//unsigned int options;
	char content[1024];
};

struct udp_header
{
	u_int16_t src_port;
	u_int16_t dst_port;
	u_int16_t udp_length;
	u_int16_t cksum;
	char content[1024];	
};


struct ip_header
{
	#if defined(WORDS_BIENDIAN)   
	u_int8_t   ip_version : 4,
	ip_header_length : 4;
	#else   
	// split the 8 bits into 2*4 bits
	u_int8_t   ip_header_length : 4,
	ip_version : 4;
	#endif   
	u_int8_t    ip_tos; // type of service 6+2
	u_int16_t   ip_length; // total length 16
	u_int16_t   ip_id; // identification 16
	u_int16_t   ip_off; // offset 1+1+1+13
	u_int8_t    ip_ttl; // time to live 8
	u_int8_t    ip_protocol; // protocol 8
	u_int16_t   ip_checksum; // header checksum 16
	struct in_addr ip_source_address; // 32
	struct in_addr ip_destination_address; // 32
	unsigned int options_pad;
};

struct ether_header
{
	// why no preamable????????
	u_int8_t ether_dhost[6]; //目的Mac地址  dst MAC 6 byte
	u_int8_t ether_shost[6]; //源Mac地址    src MAC 6 byte
	u_int16_t ether_type;    //协议类型     protocol type
};

/* Definition of 'pcap_pkthdr'
 struct pcap_pkthdr{
    struct timeval ts;           //捕获数据包的时间
    bpf_u_int32   caplen;        //捕获的长度
    bpf_u_int32   len;           //数据包长度  
 }

struct timeval
{
__time_t tv_sec;        // Seconds
__suseconds_t tv_usec;  // Microseconds
}
 */

/* typedef pcap_if pcap_if_t;
 * struct pcap_if{
 *	   struct pcap_if *next;   // next network interface device
 *     char *name;             // device name
 *     char *description;      // device description
 *     struct pcap_addr *addresses; // device address
 *     bpf_u_int32 flags;           // device flag
 * }
 *
 * struct pcap_addr{
 *     struct pcap_addr *next, 
 *     struct sockaddr *addr,
 *     struct sockaddr *netmask,
 *     struct sockaddr *broadaddr,
 *     struct sockaddr *dstaddr
 * }
 *
 * typedef pcap pcap_t;
 * //  pcap was defined in pcap.h and kind of complicated;
 * */


void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content);
void ip_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);
void tcp_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);
void udp_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);

void show_curTime();

/*  Protocol number         Protocol
 *       00                   IP
 *       01                   ICMP
 *       02                   IGMP
 *       06                   TCP
 *       17                   UDP
 * */
































#endif
