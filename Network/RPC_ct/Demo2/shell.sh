#!/bin/bash
gcc -Wall -o client client.c trans_clnt.c trans_cif.c
gcc -Wall -o server server.c trans_svc.c trans_sif.c
