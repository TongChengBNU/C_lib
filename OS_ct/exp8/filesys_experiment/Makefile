# makefile 

Object_path = ./Object/

filesys: $(Object_path)main.o $(Object_path)igetput.o $(Object_path)iallfre.o $(Object_path)ballfre.o $(Object_path)name.o $(Object_path)access.o $(Object_path)log.o $(Object_path)close.o $(Object_path)create.o $(Object_path)delete.o $(Object_path)dir.o $(Object_path)dirlt.o $(Object_path)open.o $(Object_path)rdwt.o $(Object_path)format.o $(Object_path)install.o $(Object_path)halt.o
	#gcc -o filesys main.o igetput.o iallfre.o ballfre.o name.o access.o log.o close.o create.o delete.o dir.o dirlt.o open.o rdwt.o format.o install.o halt.o
	gcc -o filesys $^

# 17 .c files
$(Object_path)main.o: main.c filesys.h
	gcc -c main.c -o $@

$(Object_path)igetput.o: igetput.c filesys.h
	gcc -c igetput.c -o $@

$(Object_path)iallfre.o: iallfre.c filesys.h
	gcc -c iallfre.c -o $@

$(Object_path)ballfre.o: ballfre.c filesys.h
	gcc -c ballfre.c -o $@

$(Object_path)name.o: name.c filesys.h
	gcc -c name.c -o $@

$(Object_path)access.o: access.c filesys.h
	gcc -c access.c -o $@

$(Object_path)log.o: log.c filesys.h
	gcc -c log.c -o $@

$(Object_path)close.o: close.c filesys.h
	gcc -c close.c -o $@

$(Object_path)create.o: create.c filesys.h
	gcc -c create.c -o $@

$(Object_path)delete.o: delete.c filesys.h
	gcc -c delete.c -o $@

$(Object_path)dir.o: dir.c filesys.h
	gcc -c dir.c -o $@

$(Object_path)dirlt.o: dirlt.c filesys.h
	gcc -c dirlt.c -o $@

$(Object_path)open.o: open.c filesys.h
	gcc -c open.c -o $@

$(Object_path)rdwt.o: rdwt.c filesys.h
	gcc -c rdwt.c -o $@

$(Object_path)format.o: format.c filesys.h
	gcc -c format.c -o $@

$(Object_path)install.o: install.c filesys.h
	gcc -c install.c -o $@

$(Object_path)halt.o: halt.c filesys.h
	gcc -c halt.c -o $@

