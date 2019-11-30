
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_PRINT 80
#define MAX_LINE 16
 
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

	char content[1024];
};
 
struct ether_header
{
	u_int8_t ether_dhost[6]; //目的Mac地址  dst MAC
	u_int8_t ether_shost[6]; //源Mac地址    src MAC 
	u_int16_t ether_type;    //协议类型     protocol type
};
 
void ip_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);
void tcp_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);
 
/* Definition of 'pcap_pkthdr'
 struct pcap_pkthdr{
    struct timeval ts;                  //捕获数据包的时间
    bpf_u_int32   caplen;        //捕获的长度
    bpf_u_int32   len;                //数据包长度  
 }
 */
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	u_short ethernet_type;
	struct ether_header *ethernet_protocol;
	u_char *mac_string;
	static int packet_number = 1;
	printf("----------------------------------------------\n");
	printf("捕获第%d个网络数据包\n", packet_number);
	printf("数据包长度(Length of packet):\n");
	printf("%d\n", packet_header->len);
	printf("---------以太网协议(Protocol of Ethernet)---------\n");
	ethernet_protocol = (struct ether_header*)packet_content;//获得数据包内容   
	printf("以太网类型(Type of Ethernet):\n");
	// network to host endian short(16 bits)
	ethernet_type = ntohs(ethernet_protocol->ether_type);//获得以太网类型   
	printf("%04x\n", ethernet_type);
	switch (ethernet_type)
	{
		case 0x0800: printf("上层协议是IP协议\n"); break;
		case 0x0806: printf("上层协议是ARP协议\n"); break;
		case 0x8035: printf("上层协议是RARP协议\n"); break;
		default:break;
	}
	printf("MAC帧源地址:\n");
	mac_string = ethernet_protocol->ether_shost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	printf("MAC帧目的地址:\n");
	mac_string = ethernet_protocol->ether_dhost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	if (ethernet_type == 0x0800)//继续分析IP协议   
	{
		ip_protocol_packet_callback(argument, packet_header, packet_content);
	}
	printf("----------------------------------------------\n");
	packet_number++;
}
 
 
void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	struct ip_header *ip_protocol;
	u_int header_length;
	u_int offset;
	u_char tos;
	u_int16_t checksum;
	//MAC首部是14位的，加上14位得到IP协议首部   
	ip_protocol = (struct ip_header *) (packet_content + 14);
	// checksum: 16 bits = 2 bytes, that is why use network to host short
	checksum = ntohs(ip_protocol->ip_checksum);
	tos = ip_protocol->ip_tos;
	// should we consider the special 3 bits before offset?????????
	offset = ntohs(ip_protocol->ip_off);
	printf("---------IP协议---------\n");
	printf("版本号:%d\n", ip_protocol->ip_version);
	printf("首部长度:%d\n", ip_protocol->ip_header_length);
	printf("服务质量:%d\n", tos);
	printf("总长度:%d\n", ntohs(ip_protocol->ip_length));
	printf("标识:%d\n", ntohs(ip_protocol->ip_id));
	printf("偏移:%d\n", (offset & 0x1fff) * 8);
	printf("生存时间:%d\n", ip_protocol->ip_ttl);
	printf("协议类型:%d\n", ip_protocol->ip_protocol);
	switch (ip_protocol->ip_protocol)
	{
	case 1: printf("上层协议是ICMP协议\n"); break;
	case 2: printf("上层协议是IGMP协议\n"); break;
	case 6: printf("上层协议是TCP协议\n"); break;
	case 17: printf("上层协议是UDP协议\n"); break;
	default:break;
	}
	printf("检验和:%d\n", checksum);
	printf("源IP地址:%s\n", inet_ntoa(ip_protocol->ip_source_address));
	printf("目的地址:%s\n", inet_ntoa(ip_protocol->ip_destination_address));
	//printf("Content:%s\n", ip_protocol->content);
	if(ip_protocol->ip_protocol == 6)
	{
		// continue to analyze TCP datagram
		tcp_protocol_packet_callback(argument, packet_header, packet_content);
	}
}
 
void tcp_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char* pcap_content)
{
	struct tcp_header *tcp_protocol;	
	// what is the offset??
	// ipv4 head 4*5=20
	tcp_protocol = (struct tcp_header *)(pcap_content + 20);
	u_int16_t checksum = ntohs(tcp_protocol->cksum);
	u_int16_t src_port = ntohs(tcp_protocol->src_port);
	u_int16_t dst_port = ntohs(tcp_protocol->dst_port);
	
	printf("---------IP协议---------\n");
	printf("Source port: %d\n", src_port);
	printf("Destination port: %d\n", dst_port);
	printf("Check sum: %d\n", checksum);
	printf("Content: %s\n", inet_ntoa(tcp_protocol->content));
	return;
}

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
 * pcap was defined in pcap.h and kind of complicated;
 * */
 
int main()
{
	pcap_t *fp;
	// *alldev: ptr of link list of struct pcap_if_t
	// *d: moving ptr or tmp ptr;
	// errbuf: string of error info
	pcap_if_t *alldev, *d;
	char errbuf[30];
	u_char user[30];
	
	// retval: return value of func 'pcap_findalldevs'
	// i: count of network interface device
	// inum: interface number
	int retval, i, inum;

	// typedef unsigned int bpf_u_int32
	bpf_u_int32 net_mask; //掩码地址   
	bpf_u_int32 net_ip;  //网络地址   
	struct bpf_program bpf_filter; //BPF过滤规则   
	//char bpf_filter_string[] = "ip";
	char bpf_filter_string[] = "src or dst net 172.81";

	// pcap_findalldevs()函数获取已连接的网络适配器列表
	// int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf)
	// *alldevsp: 指向网卡链表头一个节点的指针
	// *errbuf: 错误信息
	retval = pcap_findalldevs(&alldev, errbuf);
	if (retval == -1)
	{
		printf("find all devs failed\n");
	}
	i = 0;
	for (d = alldev; d != NULL; d = d->next)
	{
		printf("%d. %s", i, d->name);
		i++;
		if (d->description == NULL)
		{
			printf("description: none\n");
		}
		else
		{
			printf("description: %s\n", d->description);
		}
	}
	if (i == 0)
	{
		printf("no network dev avaliable\n");
	}
	printf("choose one interface number:");
	scanf("%d", &inum);

	printf("\n\nFirst device address:%s\n\n", inet_ntoa(((struct sockaddr_in *)(alldev->addresses->addr))->sin_addr));
	printf("\n\nFirst device name:%s\n\n", alldev->name);
	// move ptr 'd' to our 'inum'-th device
	for (d = alldev, i = 0; i < inum ; d = d->next, i++);
	// delete info in 'errbuf'
	memset(errbuf, 0, sizeof(errbuf));

	// pcap_open_live(): open network device 
	// pcap_t *pcap_open_live(
	//		char *device,  // device name
	//		int snaplen,   // length of packet, MAX 65535
	//		int promisc,   // 1 is promiscuous mode: receive all packet passing through the network interface card
	//      int to_ms,     // time slot
	//      char *ebuf     // error buffer
	// )
	// P.S.: this function must be called under root.
	fp = pcap_open_live(d->name, 65535, 1, 1000, errbuf);
	if (fp == NULL)
	{
		printf("open failed\n");
		exit(1);
	}	


    /* Check the link layer. We support only Ethernet for simplicity. */
    if(pcap_datalink(fp) != DLT_EN10MB)
    {
        fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
        /* Free the device list */
        pcap_freealldevs(alldev);
        return -1;
    }

	// pcap_lookupnet: return  is used to determine the network number and mask associated with the network device device. Both netp and maskp are bpf_u_int32 pointers. A return of -1 indicates an error in which case errbuf is filled in with an appropriate error message.
	// int pcap_lookupnet(
	//    const char * 	device,
	//    bpf_u_int32 * netp,
	//    bpf_u_int32 * maskp,
	//    char * errbuf
	// )
	if( (pcap_lookupnet(d->name, &net_ip, &net_mask, errbuf)) == -1)
	{ 
		fprintf(stderr, "pcap_lookupnet error;\n");
		exit(1);
	}
	// pcap_compile: pcap_compile() is used to compile the string str into a filter program. program is a pointer to a bpf_program struct and is filled in by pcap_compile(). 
	// int pcap_compile	(
	//   pcap_t * p,
	//   struct bpf_program * fp,
	//   char * str,
	//   int optimize,
	//   bpf_u_int32 netmask	 
	// )	
	pcap_compile(fp, &bpf_filter, bpf_filter_string, 0, net_mask);   
 	// pcap_setfilter: Associate a filter to a capture.
	// int pcap_setfilter(pcap_t *p, struct bpf_program *fp)
	pcap_setfilter(fp, &bpf_filter);

	// pcap_dispatch: pcap_dispatch() is used to collect and process packets. cnt specifies the maximum number of packets to process before returning. This is not a minimum number; Return the number of read packets
	// int pcap_dispatch(
	//  pcap_t * p,
	//  int cnt,
	//  pcap_handler callback,
	//  u_char * user
	// )
	// retval = pcap_dispatch(fp, 10, ethernet_protocol_packet_callback, user);

	// pcap_loop: 
	// int pcap_loop(	
	//    pcap_t * p,
	//    int cnt,
	//    pcap_handler callback,
	//    u_char * user	 
	// )	
	//retval = pcap_loop(fp, 20, ethernet_protocol_packet_callback, user);
	//printf("\n\nThe total number of packets being processed: %d\n", retval);
	// free all devices
	pcap_freealldevs(alldev);
	retval = pcap_loop(fp, 0, ethernet_protocol_packet_callback, user);
	return 0;

}

