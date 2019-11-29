
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_PRINT 80
#define MAX_LINE 16
 
struct ip_header
{
	#if defined(WORDS_BIENDIAN)   
	u_int8_t   ip_version : 4,
	ip_header_length : 4;
	#else   
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
	struct in_addr ip_souce_address; // 32
	struct in_addr ip_destination_address; // 32
};
 
struct ether_header
{
	u_int8_t ether_dhost[6]; //目的Mac地址   
	u_int8_t ether_shost[6]; //源Mac地址   
	u_int16_t ether_type;    //协议类型   
};
 
void ip_protocol_packet_callback(u_char*, const struct pcap_pkthdr*, const u_char*);
 
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
	printf("数据包长度:\n");
	printf("%d\n", packet_header->len);
	printf("---------以太网协议---------\n");
	ethernet_protocol = (struct ether_header*)packet_content;//获得数据包内容   
	printf("以太网类型:\n");
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
	checksum = ntohs(ip_protocol->ip_checksum);
	tos = ip_protocol->ip_tos;
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
	printf("源IP地址:%s\n", inet_ntoa(ip_protocol->ip_souce_address));
	printf("目的地址:%s\n", inet_ntoa(ip_protocol->ip_destination_address));
}
 

/* typedef pcap_if pcap_if_t;
 * struct pcap_if{
 *	struct pcap_if *next;   // next network interface device
 *  char *name;             // device name
 *  char *description;      // device description
 *  struct pcap_addr *addresses; // device address
 *  bpf_u_int32 flags;           // device flag
 * }
 *
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
	char bpf_filter_string[] = "ip";

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
	retval = pcap_loop(fp, 10, ethernet_protocol_packet_callback, user);
	printf("\n\nThe total number of packets being processed: %d\n", retval);
	return 0;

}

