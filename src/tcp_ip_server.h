#ifndef TCP_IP_SERVER_H
#define TCP_IP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>
#include <queue>
#include "base_handler.h"

class TCPIPServer {
	public:

		TCPIPServer();
		void registerHandler(BaseHandler *pHandler);
		void start(int nPort);
		void stop();
		int n, pid;
		std::string help();
		BaseHandler *findHandler(const std::string &sCommand);

	private:
		pthread_t m_serverThread;
		std::map<std::string, BaseHandler *> m_mapHandlers;
		int m_nSockFd;
		// ILightHttpHandler *m_pHandler;
		struct sockaddr_in m_serverAddress;	
};

class TCPIPServerClientConnection {
	public:
		TCPIPServerClientConnection(TCPIPServer *pTcpIpServer, int nSockFd, const std::string &sAddress);
		int sockFd();
		std::string address();
		TCPIPServer *server();
	private:
		TCPIPServer *m_pTcpIpServer;
		int m_nSockFd;
		std::string m_sAddress;
};

#endif // TCP_IP_SERVER_H
