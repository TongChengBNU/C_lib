

#include <stdio.h>
#include <stdlib.h>
#include "pcap_ct.h"

// crc32 reverse table
//extern alt_u32 Table1[256];
int tcp_udp_data_offset=0;

 
int main()
{
	//生成翻转表，是官方推荐的，故称其为normal_table
	//gen_normal_table(Table1);


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
	//char bpf_filter_string[] = "src or dst net 172.81 and port 8080";

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

void show_curTime()
{
	time_t now;
	now = time(NULL);
	printf("Current time: %s", ctime(&now));
}

void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	u_short ethernet_type;
	struct ether_header *ethernet_protocol;
	u_char *mac_string;
	static int packet_number = 1;
	char *cksum_ptr;

	printf("----------------------------------------------\n");
	printf("-- No.%d packet\n", packet_number);
	printf("Length of packet: %d\n", packet_header->len);
	printf("Arrival time: %s", ctime(&packet_header->ts.tv_sec));
	show_curTime();
	putchar('\n');

	printf("---------Protocol of Ethernet---------\n");
	ethernet_protocol = (struct ether_header*)packet_content;   
	// dst mac
	printf("MAC destination address:\n");
	mac_string = ethernet_protocol->ether_dhost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	// src mac
	printf("MAC source address:\n");
	mac_string = ethernet_protocol->ether_shost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	// type 
	ethernet_type = ntohs(ethernet_protocol->ether_type);   
	printf("Type of Ethernet: %04x ", ethernet_type);
	switch (ethernet_type)
	{
		case 0x0800: printf("IP Protocol\n"); break;
		case 0x0806: printf("ARP Protocol\n"); break;
		case 0x8035: printf("RARP Protocol\n"); break;
		default:break;
	}

	// check sum, packet_content in pcap does not contain preamable and crc
	//printf("Check sum of frame:\n");
	//cksum_ptr = (char *)(packet_content + (packet_header->len-4));
	//for(int i=0;i<4;i++)
	//{
	//	printf("%x ", *(cksum_ptr++));
	//}
	//putchar('\n');
	//alt_u8 *crc_content_ptr = (alt_u8 *)packet_content;
	//alt_u8 *crc_stop_ptr = (alt_u8 *)(packet_content + (packet_header->len-4));
	////使用翻转表，官方推荐的，很快
	//printf("Reverse Table  ref + xor : %08x\n",Reverse_Table_CRC(crc_content_ptr, packet_header->len-4, Table1));



	if (ethernet_type == 0x0800)  
	{
		// continue to analyze IP Protocol
		ip_protocol_packet_callback(argument, packet_header, packet_content+sizeof(struct ether_header));
	}
	printf("----------------------------------------------\n\n\n\n");
	packet_number++;
}
 
void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	struct ip_header *ip_protocol;
	u_int16_t checksum;
	// frame of Ethernet: (8) + 6 + 6 + 2   
	// preamable + dst mac + src mac + type + data
	ip_protocol = (struct ip_header *) (packet_content);
	// checksum: 16 bits = 2 bytes, that is why use network to host short
	//checksum = ntohs(ip_protocol->ip_checksum);
	// should we consider the special 3 bits before offset?????????
	//offset = ntohs(ip_protocol->ip_off);
	printf("---------IP Protocol---------\n");
	printf("Version:%d\n", ip_protocol->ip_version);
	printf("Header length:%d\n", ip_protocol->ip_header_length);
	printf("Type of Service:%d\n", ip_protocol->ip_tos);
	printf("Total length:%d\n", ntohs(ip_protocol->ip_length));
	printf("Identifier:%d\n", ntohs(ip_protocol->ip_id));
	printf("Offset:%d\n", (ip_protocol->ip_off & 0x1fff) * 8);
	printf("TTL:%d\n", ip_protocol->ip_ttl);
	printf("Protocol Type:%d ", ip_protocol->ip_protocol);
	switch (ip_protocol->ip_protocol)
	{
		case 1: printf("ICMP Protocol\n"); break;
		case 2: printf("IGMP Protocol\n"); break;
		case 6: printf("TCP Protocol\n"); break;
		case 17: printf("UDP Protocol\n"); break;
		default:break;
	}
	printf("Check sum:%d\n", ip_protocol->ip_checksum);
	printf("Source IP address:%s\n", inet_ntoa(ip_protocol->ip_source_address));
	printf("Destination IP address:%s\n", inet_ntoa(ip_protocol->ip_destination_address));
	//printf("Content:%s\n", ip_protocol->content);
	if(ip_protocol->ip_protocol == 6)
	{
		// continue to analyze TCP datagram
		tcp_protocol_packet_callback(argument, packet_header, packet_content+sizeof(struct ip_header) );
	}
	else if(ip_protocol->ip_protocol == 17)
	{
		// continue to analyze UDP datagram
		udp_protocol_packet_callback(argument, packet_header, packet_content+sizeof(struct ip_header) );
	}
}
 
void tcp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *pcap_header, const u_char* packet_content)
{
	struct tcp_header *tcp_protocol;	
	// ipv4 head 4*5=20
	tcp_protocol = (struct tcp_header *)(packet_content);
	u_int16_t checksum = ntohs(tcp_protocol->cksum);
	u_int16_t src_port = ntohs(tcp_protocol->src_port);
	u_int16_t dst_port = ntohs(tcp_protocol->dst_port);
	u_int16_t hdr_offset = ntohs(tcp_protocol->hdrLen);
	
	printf("---------TCP Protocol---------\n");
	printf("Source port: %d\n", src_port);
	printf("Destination port: %d\n", dst_port);
	printf("Offset: %x | %d\n", hdr_offset>>12, hdr_offset>>12);
	printf("Check sum: %d\n", checksum);
	//printf("Content: \n%s\n", tcp_protocol->content+20+tcp_udp_data_offset);
	//printf("Content: \n%s\n", tcp_protocol->content+2*(hdr_offset>>12));
	printf("Content: \n%s\n", (packet_content)+4*(hdr_offset>>12));
	return;
}

void udp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *pcap_header, const u_char* packet_content)
{
	struct udp_header *udp_protocol;	
	// ipv4 head 4*2=8
	udp_protocol = (struct udp_header *)(packet_content);
	u_int16_t udp_length = ntohs(udp_protocol->udp_length);
	u_int16_t checksum = ntohs(udp_protocol->cksum);
	u_int16_t src_port = ntohs(udp_protocol->src_port);
	u_int16_t dst_port = ntohs(udp_protocol->dst_port);
	
	printf("---------UDP Protocol---------\n");
	printf("Source port: %d\n", src_port);
	printf("Destination port: %d\n", dst_port);
	printf("Length of UDP: %d\n", udp_length);
	printf("Check sum: %d\n", checksum);

	//int option=40;
	//for(int i=0;i<option;i++)
	//{
	//	printf("Content %d: %x\n", i,udp_protocol->content[i]);
	//}
	// after testing, the offset should be 26
	printf("Content: \n%s\n", packet_content+sizeof(struct udp_header));

	return;
}
