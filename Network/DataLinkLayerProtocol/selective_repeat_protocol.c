/************************************************************************
 > File Name: selective_repeat_protocol.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 07 Nov 2019 04:30:23 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"


#define MAX_SEQ 7
#define NR_BUFS ((MAX_SEQ+1)/2)
typedef enum{frame_arrival, cksum_err, timeout, network_layer_ready, ack_timeout} event_type;

boolean no_nak = true; // ???
seq_nr oldest_frame = MAX_SEQ+1;


static boolean between(seq_nr a, seq_nr b, seq_nr c)
{
	if ((a<=b && b<c) || (c<a && a<=b) || (b<c && c<a))
		return true;
	else
		return false;
}

static void send_frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
	frame s;
	s.kind = fk;
	if (fk == data)
		s.info = buffer[frame_nr % NR_BUFS];
	s.seq = frame_nr;
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
	if (fk == nak)
		no_nak = false; // one nak per frame, please 
	to_physical_layer(&s);
	if (fk == data) start_timer(frame_nr % NR_BUFS);
	stop_ack_timer();
}

void selective_repeat(void)
{
	seq_nr ack_expected;          // lower edge of sender window
	seq_nr next_frame_to_send;    // upper edge of sender window
	seq_nr frame_expected;        // lower edge of receiver window
	seq_nr too_far;               // upper edge of receiver window

	int i; // index into buffer pool
	frame r;
	packet out_buf[NR_BUFS];
	packet in_buf[NR_BUFS];
	boolean arrived[NR_BUFS];
	seq_nr nbuffered;  // number of buffer used << NR_BUFS
	event_type event;

	enable_network_layer();
	ack_expected = 0;
	next_frame_to_send = 0;
	frame_expected = 0;
	too_far = NR_BUFS;
	nbuffered = 0;
	for(i=0;i<NR_BUFS;i++) arrived[i] = false;

	while (true){
		wait_for_event(&event);
		switch(event){
			case network_layer_ready:
				from_network_layer(&out_buf[next_frame_to_send % NR_BUFS]);
				// to be continued ...
				send_frame
				break;
			case frame_arrival:
				break;
			case cksum_err:
				break;
			case timeout:
				break;
			case ack_timeout:
				break;
		}
		if (nbuffered < NR_BUFS) enable_network_layer();
		else disable_network_layer();
	}
	
}
