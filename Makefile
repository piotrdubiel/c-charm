CC=g++

OBJS=main.o graph.o dataset.o charm.o rule.o utils.o set.o hashtable.o iset.o rule_builder.o
HEADERS=graph.h dataset.h charm.h rule.h utils.h set.h hashtable.h iset.h rule_builder.h
CFLAGS=-g -ggdb

all: $(OBJS) 	
	$(CC) $(CFLAGS) $(OBJS) -o charm

$(OBJS): %.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
