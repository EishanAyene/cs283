1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

It determines that a command's output is fully received by checking for an EOF character (RDSH_EOF_CHAR). A technique that can be used is to keep calling recv()

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

A network shell protocol can define and detect the beginning and end of a command by seeing if they are null terminated. Challenges if not handled correctly could be a buffer overflow or infinite loops.

3. Describe the general differences between stateful and stateless protocols.

A stateful protocol keeps information between the client and server, while a stateless protocol has no memory of past interactions.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

It is used when we want to prioritize speed and not reliability.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

Sockets are provided by the operating system to enable applications to use network communications.
