### event-loop

- libevent
- libev
- libuv
- boos::asio

These libraries makes a unify the code that uses `select`, `poll`, `epoll` and `kqueue`.
And the codebase takes the following form:
```C
#ifndef ...
...
#else
...
#endif
```

#### libevent
Currently, we know only 4 types of multiplexing:
- select
- poll
- epoll
- kqueue

But, libevent provides additional 3 types:
- devport
- evport
- win32

How libevent works(abstract):
it creates a object `event_base`, then we got a new connection we create a new event, we register it in the `event_base`.
This event has a function that must be called, we call it callback.


