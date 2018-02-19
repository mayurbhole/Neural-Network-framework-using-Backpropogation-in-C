LDFLAGS = -pthread -lpthread
CFLAGS = -g -Wall -Werror
backprop: backprop.o layer.o neuron.o
	$(CC) $(LDFLAGS) -o backprop backprop.o layer.o neuron.o -lm

backprop.o: backprop.c
	$(CC) $(CFLAGS) -c backprop.c

layer.o: layer.c
	$(CC) $(CFLAGS) -c layer.c

neuron.o: neuron.c
	$(CC) $(CFLAGS) -c neuron.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o backprop
