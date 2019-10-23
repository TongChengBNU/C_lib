cp source.c source.pgc
../ecpg -t -c -I ../include -o ./intermediate.c source.pgc 
gcc -I ../include -Wall -g ./intermediate.c -L ../lib -lecpg -lpq -lpgtypes -o ./execute
./execute
