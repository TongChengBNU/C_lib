/************************************************************************
 > File Name: sliding_window_1.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 07 Nov 2019 03:09:59 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <protocol.h>

#define MAX_SEQ 1
typedef enum{frame_arrival, cksum_err, timeout} event_type;

void sliding_window_1(void){
	seq_nr next_frame_to_send;
	seq_nr frame_expected;
	frame r, s;
	packet buffer;
	event_type event;

	next_frame_send = 0;
	frame_expected = 0;
	from_network_layer(&buffer);
	s.info = buffer;
	s.seq = next_frame_to_send;
	s.ack = 1 - frame_expected; // alternating, piggybacking
	to_physical_layer(&s);
	start_timer(s.seq);
	while (true){
		wait_for_event(&event);
		if (event == frame_arrival){
			from_physical_layer(&r);
			if (r.ack == frame_expected){
				to_network_layer(&r.info);
				inc(frame_expected);
			}
			if (r.ack == next_frame_to_send){
				stop_timer(next_frame_to_send);
				from_network_layer(&buffer);
				inc(next_frame_to_send);
			}
		}
		s.info = buffer;
		s.seq = next_frame_to_send;
		s.ack = 1 - frame_expected;
		to_physical_layer(&s);
		start_timer(s.seq);
	}

}


