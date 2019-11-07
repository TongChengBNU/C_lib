/************************************************************************
 > File Name: Utopia_single_protocol.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 07 Nov 2019 02:42:33 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum{frame_arrival} event_type;
#include "protocol.h"

void sender{
	frame s;
	packet buffer;
	while (true){
		from_network_layer(&buffer);
		s.info = buffer;
		to_physical_layer(&s);
	}
}

void receiver{
	frame r;
	packet buffer;
	while (true){
		from_physical_layer(&r);	
		buffer = r.info;
		to_network_layer(&buffer);
	}
}
