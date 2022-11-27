all:main

main:rmd.o rmdi.o
	gcc $^ -o $@


.PHONY:clean
clean:
	rm -rf  *.o  main
