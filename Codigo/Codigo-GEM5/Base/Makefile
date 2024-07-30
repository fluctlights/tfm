TARGET_ISA=arm64
CC=aarch64-linux-gnu-gcc
OPTIMIZATION=-O0 -static
EXTRA_PARAMS=-DREPETITIONS=3
CFLAGS=-I$(GEM5_PATH)/include -I$(GEM5_PATH)/util/m5/src
LDFLAGS=-L$(GEM5_PATH)/util/m5/build/$(TARGET_ISA)/out -L/usr/lib/gcc-cross/aarch64-linux-gnu/11 -lm5 -lm

SRCS=benchmarks_menu.c solo_main.c 1000sumas_alu.c 1000sumas_fpu.c 1000mult_alu.c 1000mult_fpu.c 1000div_alu.c 1000div_fpu.c acceso_vector.c copia_vector.c
OBJS_DIR=build
OBJS=$(SRCS:%.c=$(OBJS_DIR)/%.o)
TARGET=benchmarks

# Create the directory for object files
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# Rule to compile each source file to an object file in the specified directory
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(OPTIMIZATION) $(EXTRA_PARAMS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

benchmarks: $(OBJS)
	$(CC) $(OPTIMIZATION) $(EXTRA_PARAMS) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJS_DIR)
