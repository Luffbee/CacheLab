.PHONY: test clean
cpp=g++ -std=c++14 -Wall -g

cachelab: main.o cache.o memory.o monitor.o
	$(cpp) -o cachelab main.o cache.o memory.o monitor.o

main.o: main.cpp cache.h
	$(cpp) -c main.cpp

cache.o: cache.cpp cache.h
	$(cpp) -c cache.cpp

memory.o: memory.cpp memory.h
	$(cpp) -c memory.cpp

monitor.o: monitor.cpp monitor.h
	$(cpp) -c monitor.cpp

test: cachelab
	./cachelab < test/copyshift_naive.in > test/copyshift_naive.out && \
		diff test/copyshift_naive.out test/copyshift_naive.ans && \
	./cachelab < test/copyshift_smart.in > test/copyshift_smart.out && \
		diff test/copyshift_smart.out test/copyshift_smart.ans

clean:
	rm cachelab main.o cache.o memory.o monitor.o
