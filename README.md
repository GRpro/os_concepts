# OS concepts

Standalone programs for the Unix process model: a parent creates a child with `fork` and waits for it, two threads share a fixed-size queue, a pipe carries messages from parent to child, and a TCP echo server forks one process per connection. `make` compiles the programs this operating system supports and writes the binaries to `build/`.

```bash
mkdir -p build
```

`processes/fork_process.c`

```bash
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -o build/fork_process processes/fork_process.c
./build/fork_process
```

`threads/producer_consumer.c`

```bash
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -pthread -o build/producer_consumer threads/producer_consumer.c
./build/producer_consumer
```

`pipes/communicate.c`

```bash
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -o build/communicate pipes/communicate.c
./build/communicate
```

`pipes/set_pipe_size.c` (Linux only)

```bash
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE -o build/set_pipe_size pipes/set_pipe_size.c
./build/set_pipe_size
```

`sockets/server.c` and `sockets/client.c` — port 12345. Run the client in a second terminal. `quit` closes that connection.

```bash
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -o build/echo_server sockets/server.c
gcc -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -o build/echo_client sockets/client.c
./build/echo_server
./build/echo_client
```
