# Network-Application-basics
Basics of Network programming

TCPServer and TCPClient is the idle example to show the interaction between Client and Server interaction

For TCP:

Build the file with:
gcc TCPServer.c -o TCPServer

run this command in one terminal for the server:
./TCPServer 4444

Build the file with:
gcc TCPClient.c -o TCPClient

Open another terminal window for the client:
./TCPClient 4444

A prompt will appear to enter the file name. Type the filename as “HelloFile.txt”. This file is present in the same folder.
The filename is sent to the server, the server fetches the contents back to the client if its present and the client displays the contents of this file its the terminal.
On the server terminal, if the file is present, it prints that its reading the file name “HelloFile.txt” and If its not present, it prints that no file is found.

*****************************************************************************	
For UDP:

Build the file with:
gcc UDPServer.c -o UDPServer

run this command in one terminal for the server:
./UDPServer 4444

Build the file with:
gcc UDPClient.c -o UDPClient

Open another terminal window for the client:
./UDPClient 4444

A prompt will appear to enter the file name. Type the filename as “HelloFile.txt”. This file is present in the same folder.
The filename is sent to the server, the server fetches the contents back to the client if its present and the client displays the contents of this file its the terminal.
On the server terminal, if the file is present, it prints that its reading the file name “HelloFile.txt” and If its not present, it prints that no file is found.


*****************************************************************************	