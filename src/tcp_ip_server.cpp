#include "tcp_ip_server.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <sys/time.h>
#include <fstream>
#include <regex>        // regex, sregex_token_iterator
#include <stdio.h>
#include <math.h>

// ----------------------------------------------------------------------
// newRequest
#define MAXPACKETSIZE 4096

// ----------------------------------------------------------------------

std::string trim(const std::string &s) {
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

// ----------------------------------------------------------------------

std::vector<std::string> parseArgs(std::string &sRequest) {
	std::vector<std::string> vArgs;
	std::istringstream f(sRequest);
	std::string s;
	while (getline(f, s, ' ')) {
		vArgs.push_back(trim(s));
	}
	return vArgs;
}

// ----------------------------------------------------------------------

void* newRequest(void *arg) {
	TCPIPServerClientConnection *pInfo = (TCPIPServerClientConnection *)arg;
	int nSockFd = pInfo->sockFd();
	std::cout << "Connected client from " << pInfo->address() << std::endl;

	pthread_detach(pthread_self());

	std::string sEnterCommand = "command> ";

	std::string sHello = "";
	sHello += "\033[2J"; // clear console
	sHello += "\033[1;1H"; // move cursor to 2,7
	sHello += "Welcome! (try 'help' for more information, and 'exit' for disconnect)\r\n";
	sHello += sEnterCommand;

	std::string sByeBye = "";
	sByeBye += "\033[2J"; // clear console
	sByeBye += "\033[1;1H"; // move cursor to 2,7
	sByeBye += "Bye-bye!\r\n";

	// send hello
	send(nSockFd, sHello.c_str(), sHello.length(),0);

	// read data from socket
	while(1) { // problem can be here
		char msg[MAXPACKETSIZE];
		memset(msg, 0, MAXPACKETSIZE);
		int n = recv(nSockFd, msg, MAXPACKETSIZE, 0);
		if (n == -1) {
			std::cout << nSockFd  << ": error read... \n";
			break;
		}
		if (n == 0) {
		   //close(nSockFd);
		   break;
		}
		msg[n]=0;

		std::string sRequest = std::string(msg);
		std::vector<std::string> vArgs = parseArgs(sRequest);
		std::string sResponse = "";

		// process exit command
		if (vArgs.size() > 0 && vArgs[0] == "exit") {
			send(nSockFd, sByeBye.c_str(), sByeBye.length(),0);
			break;
		}

		// process help command
		if (vArgs.size() > 0 && vArgs[0] == "help") {
			sResponse = pInfo->server()->help();
			sResponse = sHello + "\r\n\r\n" + sResponse;
			sResponse += "\033[2;10H"; // move cursor to 2,10
			send(nSockFd, sResponse.c_str(), sResponse.length(),0);
			continue;
		}

		// process other command
		std::string sCommand = "";
		if (vArgs.size() > 0) {
			sCommand = vArgs[0];
		}
		
		BaseHandler *pHandler = pInfo->server()->findHandler(sCommand);
		if (pHandler != NULL) {
			sResponse = pHandler->handle(vArgs);
		} else {
			sResponse = "Not found command '" + sCommand + "', please try 'help'";
		}

		sResponse = sHello + "\r\n\r\n" + sResponse;
		sResponse += "\033[2;10H"; // move cursor to 2,10
		send(nSockFd, sResponse.c_str(), sResponse.length(),0);
		usleep(100);
    }

	// close the socket
	close(nSockFd);
	std::cout << "Closed connection with client from " << pInfo->address() << std::endl;
	delete pInfo;
	return 0;
}

// ----------------------------------------------------------------------
// TCPIPServer

TCPIPServer::TCPIPServer() {
	std::cout << "Create TCP IP Server" << std::endl;
}

// ----------------------------------------------------------------------

void TCPIPServer::start(int nPort) {
	// m_pHandler = pHandler;
	m_nSockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(m_nSockFd <= 0){
		std::cerr << "Failed to establish socket connection" << std::endl;
		return;
	}
	int enable = 1;
	if (setsockopt(m_nSockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
		return;
	}

 	memset(&m_serverAddress, 0, sizeof(m_serverAddress));
	m_serverAddress.sin_family = AF_INET;
	m_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serverAddress.sin_port = htons(nPort);
	if(bind(m_nSockFd, (struct sockaddr *)&m_serverAddress, sizeof(m_serverAddress)) == -1){
		std::cerr << "Error binding to port " << nPort << std::endl;
		return;
	}
 	listen(m_nSockFd, 5);
	std::cout << "Server started on " << nPort << " port." << std::endl;

	std::string str;
	while(1) { // or problem can be here
		struct sockaddr_in clientAddress;
		socklen_t sosize  = sizeof(clientAddress);
		int nSockFd = accept(m_nSockFd,(struct sockaddr*)&clientAddress,&sosize);
		std::string sAddress = inet_ntoa(clientAddress.sin_addr);
		TCPIPServerClientConnection *pInfo = new TCPIPServerClientConnection(this, nSockFd, sAddress);

		pthread_create(&m_serverThread, NULL, &newRequest, (void *)pInfo);
		usleep(100);
	}
}

// ----------------------------------------------------------------------

void TCPIPServer::registerHandler(BaseHandler *pHandler) {
	std::string sName = pHandler->command();
	std::map<std::string, BaseHandler *>::iterator it = m_mapHandlers.find(sName);
	if(it != m_mapHandlers.end()) {
		std::cerr << "Handler '" << sName << "' - already registered, skipped " << std::endl;
	} else {
		m_mapHandlers[sName] = pHandler;
		std::cout << "Registered new handler '" << sName << "'" << std::endl;
	}
}

// ----------------------------------------------------------------------

BaseHandler *TCPIPServer::findHandler(const std::string &sCommand) {
	std::map<std::string, BaseHandler *>::iterator it = m_mapHandlers.find(sCommand);
	if (it != m_mapHandlers.end()) {
		return it->second;
	}
	return NULL;
}

// ----------------------------------------------------------------------

std::string TCPIPServer::help() {
	std::string sResult = "";
	sResult += "help - list of commands\r\n";
	sResult += "exit - disconnect\r\n";
	std::map<std::string, BaseHandler *>::iterator it;

	for ( it = m_mapHandlers.begin(); it != m_mapHandlers.end(); it++ ) {
		sResult += it->first + " " + it->second->usage() + " - " + it->second->description() + " \r\n";
	}
	return sResult;
}

// ----------------------------------------------------------------------

void TCPIPServer::stop() {
	close(m_nSockFd);
} 

// ----------------------------------------------------------------------

TCPIPServerClientConnection::TCPIPServerClientConnection(
	TCPIPServer *pTcpIpServer, int nSockFd, const std::string &sAddress) {
	
	m_pTcpIpServer = pTcpIpServer;
	m_nSockFd = nSockFd;
	m_sAddress = sAddress;
};

// ----------------------------------------------------------------------

int TCPIPServerClientConnection::sockFd() {
	return m_nSockFd; 
}

// ----------------------------------------------------------------------

std::string TCPIPServerClientConnection::address() {
	return m_sAddress;
}

// ----------------------------------------------------------------------

TCPIPServer *TCPIPServerClientConnection::server() {
	return m_pTcpIpServer;
}

// ----------------------------------------------------------------------