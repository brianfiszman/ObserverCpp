# Welcome to my repository 
## What is this?
This program is intended to work as an observer design pattern's example, written as a TCP
Server that receives connections and notifies its clients whenever someone connects or
disconnects.
<br><br>
## How do I build it?
Just compile it running ```make``` on your console.
<br><br>

## How do I run it?

Almost as simple as before, just ```cd``` inside the project folder after compiling and ```./server [PORT NUMBER]```.
By the moment you execute, the server will be listening for connections.

For fun, I use `netcat` to connect to this program which not only provides you with a client
fully capable of getting output sent from the server but also input from the client.

If you are testing on localhost all you have to do is having **netcat** installed and then:
```nc localhost [PORT NUMBER]```

The port number you choose must be the same than the one you choose for the server.