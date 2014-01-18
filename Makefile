CC=g++

OBJS=main.o node.o dataset.o charm.o rule.o utils.o
HEADERS=node.h dataset.h charm.h rule.h utils.h

all: $(OBJS) 	
	$(CC) $(OBJS) -o charm

$(OBJS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -rf *.o
