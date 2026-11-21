CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
BUILD   := build

PROGRAMS := \
	$(BUILD)/fork_process \
	$(BUILD)/producer_consumer \
	$(BUILD)/communicate \
	$(BUILD)/echo_server \
	$(BUILD)/echo_client

ifeq ($(shell uname -s),Linux)
PROGRAMS += $(BUILD)/set_pipe_size
endif

.PHONY: all clean run-fork run-threads run-pipe

all: $(PROGRAMS)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/fork_process: processes/fork_process.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD)/producer_consumer: threads/producer_consumer.c | $(BUILD)
	$(CC) $(CFLAGS) -pthread -o $@ $<

$(BUILD)/communicate: pipes/communicate.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD)/set_pipe_size: pipes/set_pipe_size.c | $(BUILD)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

$(BUILD)/echo_server: sockets/server.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD)/echo_client: sockets/client.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

run-fork: $(BUILD)/fork_process
	./$(BUILD)/fork_process

run-threads: $(BUILD)/producer_consumer
	./$(BUILD)/producer_consumer

run-pipe: $(BUILD)/communicate
	./$(BUILD)/communicate

clean:
	rm -rf $(BUILD)
