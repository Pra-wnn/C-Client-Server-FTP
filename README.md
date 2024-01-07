# C-Client-Server-FTP 
A simple client server FTP made for Network Programming Class Project for Linux Systems.

NOTE: THIS PROGRAM IS MEANT TO BE RUN IN LINUX SYSTEMS . FOR WINDOWS THERE ARE FURTHER CHANGES NEED TO BE MADE.

![Image Example 1 ](https://github.com/Pra-wnn/C-Client-Server-FTP/blob/main/Screenshot%20(5909).png)


![Image Example 2 ](https://github.com/Pra-wnn/C-Client-Server-FTP/blob/main/Screenshot%20(5910).png)

![Image Example 3 ](https://github.com/Pra-wnn/C-Client-Server-FTP/blob/main/Screenshot%20(5911).png)

Instrcutions: 

Extract the Zip 

Change Dir 

Compile with gcc

gcc -o fileclient fileclient.c
gcc -o fileserver fileserver.c

run the indiviual code

for server:
./fileserver


for client:
./fileclient 127.0.0.1 /path/to/your/file.txt


Example code for client:

./fileclient 127.0.0.1 /home/proteus/Documents/linux.pdf


The data should be copied to the server code running directory in this case file_2023-07-26_09-45-14.pdf
