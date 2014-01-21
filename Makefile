CC=g++

OBJS=main.o graph.o dataset.o charm.o rule.o utils.o set.o
HEADERS=graph.h dataset.h charm.h rule.h utils.h set.h

all: $(OBJS) 	
	$(CC) $(OBJS) -o charm

$(OBJS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -rf *.o
