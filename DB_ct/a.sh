./ecpg -t -c -I ./include -o ./test_pgSQL.c test_pgSQL.pgc 
gcc -I ./include -Wall -g ./test_pgSQL.c -L ./lib -lecpg -lpq -lpgtypes -o ./test_pgSQL
./test_pgSQL
