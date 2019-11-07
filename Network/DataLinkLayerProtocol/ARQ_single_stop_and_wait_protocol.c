/************************************************************************
 > File Name: Utopia_single_protocol.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 07 Nov 2019 02:42:33 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQ 1
typedef enum{frame_arrival, cksum_err, timeout} event_type;
#include "protocol.h"

void sender3(void){
	seq_nr next_frame_to_send;
	frame s;
	packet buffer;
	event_type event;

	next_frame_to_send = 0;
	from_network_layer(&buffer);
	while (true){
		s.info = buffer;
		s.seq = next_frame_to_send;
		to_physical_layer(&s);
		start_timer(s.seq);
		wait_for_event(&event);
		if (event == frame_arrival){
			from_physical_layer(&s);
			if (s.ack == next_frame_to_send){
				stop_timer(s.seq);
				from_network_layer(&buffer);
				inc(next_frame_to_send);
			}
		}
	}
}

void receiver3(void){
	seq_nr frame_expected;
	frame r, s;
	packet buffer;
	event_type event;
	frame_expected = 0;
	while (true){
		wait_for_event(&event);
		if (event == frame_arrival){
			from_physical_layer(&r);	
			if (r.seq == frame_expected){
				buffer = r.info;
				to_network_layer(&buffer);
				inc(frame_expected);
			}
			s.ack = 1 - frame_expected;
			// to be continued;
			
		}
	}
}
