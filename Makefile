main: memtest.c minheap.c memory_allocator.c
	gcc -o memtest memtest.c minheap.c memory_allocator.c

clean:
	rm memtest

test: main
	./memtest