#ifndef _CLIENT_H
#define	_CLIENT_H

#include "Socket.h"
#include "Thread.h"
#include "Http.h"

class Client:public HttpResponse
{
private:
	Socket* socket;
public:
	Client(Socket* socket);
	~Client();
	void Run();
	void DirectSend(const char* buf,int len);
};

class ClientThreadLauncher:public Thread
{
public:
	Socket* socket;
	void Run();
};

#endif

