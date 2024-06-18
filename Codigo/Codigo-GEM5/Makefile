TARGET_ISA=arm64
CC=aarch64-linux-gnu-gcc
OPTIMIZATION=-O0 -static
EXTRA_PARAMS=-DREPETITIONS=3
CFLAGS=-I$(GEM5_PATH)/include -I$(GEM5_PATH)/util/m5/src
LDFLAGS=-L$(GEM5_PATH)/util/m5/build/$(TARGET_ISA)/out -L/usr/lib/gcc-cross/aarch64-linux-gnu/11 -lm5 -lm

SRCS=benchmarks_deploy_gem5.c dhrystone-gem5.c whetstone-gem5.c calcular-pi-gem5.c calcular-primos-gem5.c
OBJS=$(SRCS:.c=.o)
TARGET=benchmarks

# Rule to compile each source file to an object file
%.o: %.c
	$(CC) $(OPTIMIZATION) $(EXTRA_PARAMS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

benchmarks: $(OBJS)
	$(CC) $(OPTIMIZATION) $(EXTRA_PARAMS) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
