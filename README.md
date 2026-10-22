# TCP Socket Programs in C

Final project for the Computer Networks course, B.Sc. in Computer Science, HIT (2022).
Four client-server pairs over TCP on Linux, from a simple turn-based exchange to a
multi-client chat room with POSIX threads. Built with reference to course material and
common socket-programming examples.

## Programs

| Files | What it does | Port | Clients |
| --- | --- | --- | --- |
| `tcpServer.c`, `tcpClient.c` | Turn-based chat between the server and one client | 8080, set in code | One |
| `daytimeServer.c`, `daytimeClient.c` | The server sends each client the current date and time | Command-line argument | One at a time (iterative server) |
| `sendfilesServer.c`, `sendfilesClient.c` | The client sends `send.txt`, the server saves it as `recv.txt` | Set in code | One |
| `chatroomServer.c`, `chatroomClient.c` | Chat room: each message is sent to every other connected client | Command-line argument | Up to 100, one thread per client |

## Build

On Linux with gcc:

```sh
make          # builds all eight programs
make clean    # removes them
```

## Run

Chat room, each command in its own terminal:

```sh
./chatroomServer 4444
./chatroomClient 4444
./chatroomClient 4444
```

Type `exit` or press Ctrl+C to leave the chat.

Daytime service:

```sh
./daytimeServer 5000
./daytimeClient 5000
```

Turn-based chat: `./tcpServer`, then `./tcpClient`. Either side can type a line in turn.
Typing `exit` on the server side ends the session.

File transfer, from this folder (where `send.txt` is): `./sendfilesServer`, then `./sendfilesClient`.

## What the project covers

- The TCP call sequence: `socket`, `bind`, `listen` and `accept` on the server, `socket` and `connect` on the client.
- Iterative versus concurrent servers.
- POSIX threads: one thread per client on the server, and separate send and receive threads on the client.
- A mutex that protects the shared client list, and an atomic counter of connected clients.
- Network byte order (`htons`, `inet_addr`) and signal handling (`SIGPIPE`, `SIGINT`).

## What I would improve today

- **Message framing.** TCP is a byte stream, so a message can arrive split or merged with the next one. Each message should carry its length.
- **Scaling.** Replace the thread per client with an event loop (`epoll`), so the server can handle thousands of clients.
- **Locking.** Send to clients outside the client-list lock, so one slow client cannot hold up the others.
- **Byte order.** The file-transfer pair sets the port without `htons`, so on x86 it actually listens on port 36895, not 8080.
- **Robustness.** Check every buffer length and return value, and close every socket and file.
