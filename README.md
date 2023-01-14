# Network-App


##

## It's a Network app implemented in c programming. And is based on the TCP model.
## In order to run the app you need to open two terminal windows that contain the server and client code. In the first terminal your to run the server code by typing:

## gcc server.c -o server
## ./server port_number

## While for the other terminal your to use it as the client. In other to use it you type the following:

## gcc client.c -o client
## ./client ip_addr port_number
## you can make use of port numbers above 9000 for example 9898

# After that the client can proceed to messaging the server and vice versa.

# for the client to end communication with the server he needs to enter our default keyword "bye" after which the pipeline will be broken

# We made file transfer into a separate feature and thus has it's own folder called file transfer in which is found 2 other folders namely server folder and client folder.
# To run the server code for file transfer we do the following: first we open the server folder in the terminal and proceed to typing gcc server.c -o server then finally he types ./server.After which you will asked to enter the file name you want to transfer. After entering the file name you open the client folder in another terminal. Then you run gcc client.c -o client then you run ./client ip_addr_of_server which by default is 127.0.0.1. After which the file transfer process will begin and if the file is found the file will be transfered successfully.

# You can find this code on our group github project repository using the link: https://github.com/BertinAm/Network-App

