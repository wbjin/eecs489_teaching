# Multiplexing

Sockets are, by default, block when you read or write to them. This is true for
listening sockets when you are waiting for new connections. If you wanted to
handle multiple connections simulatenously, you would need a way to wait for
new connections and handle existing connections. However, waiting for a new
connection is blocking. To handle multiple connections simulatenously, you can:
- Start a new thread or process per connection
- Use `poll`
- Use `select`

This directory contains examples on how to handle multiple connections
synchronously with poll or select. `poll` is a more flexibly, newer way of
multiplexing file I/O. You can specify which "events" or essentially signals to
poll for. `select` is an easier way of doing synchronous I/O multiplexing. To
run a multiplexed server, compile and run `poll.c` or `select.c`

```
gcc poll.c -o poll
./poll
```
or
```
gcc select.c -o select
./select
```

Connect to the server with `client.c`
```
gcc client.c -o client
./client
```
