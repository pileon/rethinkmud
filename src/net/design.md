# Network design

RethinkMUD can listen for and accept a multitude of connections on many different ports and using
many different protocols.

This is done by having an abstract `server` class as base, and each protocol implements its own
server class from this base class. Each implementation of the `server` base class can then be
instantiated multiple times for multiple ports.

The connections are handled in a similar way, with a basic and abstract `connection` base class,
which is then inherited for the protocols.

RethinkMUD will be using [Boost ASIO](http://www.boost.org/doc/libs/release/doc/html/boost_asio.html)
to assist with the networking. To run the ASIO main event loop, needed for the asynchronous functions,
a thread will be created.

All networking will be in the `rethinkmud::net` namespace.
