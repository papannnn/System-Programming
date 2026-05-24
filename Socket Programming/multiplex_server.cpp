#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define SOCKET_NAME "/tmp/SocketTutorial"
#define BUFFER_SIZE 128

void addFdToArr(std::vector<int> &fdArr, const int &fd) {
    for (int i = 0 ; i < fdArr.size(); i++) {
        if (fdArr[i] != -1) {
            continue;
        }
        fdArr[i] = fd;
        break;
    }
}

void removeFdToArr(std::vector<int> &fdArr, const int &fd) {
    for (int i = 0; i < fdArr.size(); i++) {
        if (fdArr[i] == fd) {
            fdArr[i] = -1;
            break;
        }
    }
}

void refreshFdSet(fd_set *read_fd, std::vector<int> &fdArr) {
    FD_ZERO(read_fd);
    for (int i = 0; i < fdArr.size(); i++) {
        if (fdArr[i] != -1) {
            FD_SET(fdArr[i], read_fd);
        }
    }
}

int getMaxFDForSelect(std::vector<int> &fdArr) {
    int result = -1;
    for (int i = 0 ; i< fdArr.size(); i++) {
        result = std::max(result, fdArr[i]);
    }
    return result + 1;
}

int main () {
    unlink(SOCKET_NAME);

    int connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connection_socket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_un sockAddr;
    memset(&sockAddr, 0, sizeof(sockaddr_un));
    sockAddr.sun_family = AF_UNIX;
    strcpy(sockAddr.sun_path, SOCKET_NAME);

    int ret = bind(connection_socket, reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockaddr_un));
    if (ret == -1) {
        std::cout << "Failed bind socket" << std::endl;
        return -1;
    }

    ret = listen(connection_socket, 20);
    if (ret == -1) {
        std::cout << "Failed to listen socket" << std::endl;
        return -1;
    }

    std::vector<int> fdArr(32, -1);
    std::unordered_map<int, int> mappingValue;
    addFdToArr(fdArr, connection_socket);

    fd_set read_fd;
    while (true) {
        refreshFdSet(&read_fd, fdArr);
        select(getMaxFDForSelect(fdArr), &read_fd, NULL, NULL, NULL);

        if (FD_ISSET(connection_socket, &read_fd)) {
            std::cout << "New connection established" << std::endl;

            int data_socket = accept(connection_socket, NULL, NULL);
            if (data_socket == -1) {
                std::cout << "Failed accepting connection" << std::endl;
                return -1;
            }

            addFdToArr(fdArr, data_socket);
        } else {
            for (int i = 0 ; i < fdArr.size(); i++) {
                if (FD_ISSET(fdArr[i], &read_fd)) {
                    int clientFD = fdArr[i];
                    char buffer[BUFFER_SIZE];
                    memset(buffer, 0, BUFFER_SIZE);

                    ret = read(clientFD, buffer, BUFFER_SIZE);
                    if (ret == -1) {
                        std::cout << "Failed to read client socket" << std::endl;
                        return -1;
                    }

                    int value;
                    memcpy(&value, buffer, sizeof(int));
                    if (value == 0) {
                        sprintf(buffer, "Value sum is: %d", mappingValue[clientFD]);
                        mappingValue[clientFD] = 0;
                        int ret = write(clientFD, buffer, BUFFER_SIZE);
                        if (ret == -1) {
                            std::cout << "Failed writing to client" << std::endl;
                            return -1;
                        }
                        removeFdToArr(fdArr, clientFD);
                        close(clientFD);
                    } else {
                        mappingValue[clientFD] += value;
                    }
                }
            }
        }
    }
    close(connection_socket);
    unlink(SOCKET_NAME);
}