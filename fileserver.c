#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE 1024

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char buffer[SIZE];
    time_t current_time;
    struct tm *time_info;
    char filename[100];

    // Get the current timestamp
    current_time = time(NULL);
    time_info = localtime(&current_time);
    strftime(filename, sizeof(filename), "file_%Y-%m-%d_%H-%M-%S", time_info);

    // Receive the file extension from the client
    char ext[10] = {0};
    recv(sockfd, ext, sizeof(ext), 0);
    strcat(filename, ".");
    strcat(filename, ext);

    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }

    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
        }
        fwrite(buffer, 1, n, fp);
    }

    printf("[+]Data written to the file: %s\n", filename);
    fclose(fp);
}


int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        perror("[-]Error in binding");
        exit(1);
    }
    printf("[+]Binding successful.\n");

    e = listen(sockfd, 10);
    if (e == 0)
    {
        printf("[+]Listening...\n");
    }
    else
    {
        perror("[-]Error in listening");
        exit(1);
    }

    while (1)
    {
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);

        if (new_sock < 0)
        {
            perror("[-]Error in accepting");
            exit(1);
        }

        printf("[+]Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

        write_file(new_sock);

        close(new_sock);

        printf("[+]Client disconnected. Listening for the next client...\n");
    }

    close(sockfd);

    return 0;
}
