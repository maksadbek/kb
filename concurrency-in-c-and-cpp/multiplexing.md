### Multiplexing
There are 4 appoaches to achieve a multiplexing in Linux and Unix systems.
Why do not just iterate of slave sockets and check whether a data is sent.
This would 
- Select - the classic way, it is system call `select`. 
To use the select we must create a set of slave connections with type of `fd_set`.
```C
fd_set slave_set;
```
By default the size of the set is equal to **1024**
This approach does not solve niether C10K nor C100K problems.
We must at first clean the set:
```C
FD_ZERO(&set);

// then add the master slave
FD_SET(MasterSocket, &set)

// receive connections
for (...) {
	if(FD_ISSET(*iter, &set)) {
		//...
	}

	if(FD_ISSET(MasterSocket, &set)) {
		// accept
	}
}
```

- epoll - this approach differs from select with the unlimited* number of file descriptors but there will be much more data transferred between the kernel and application.
Example:
```C
struct pollfd set[POLL_SIZE]; // we set the 1+max count of slave sockets
set[0].fd = master_socket;
set[0].events = POLLIN
poll(set, setsize /* count of elems */, -1 /* no timeout */)
```

