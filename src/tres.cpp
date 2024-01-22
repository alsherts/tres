//
// tres.cpp    TCP Reversed Echo Server
//

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/DialogSocket.h"
#include "Poco/Process.h"
#include "Poco/NamedEvent.h"
#include <iostream>


using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactoryImpl;
using Poco::Net::StreamSocket;
using Poco::Net::DialogSocket;
using Poco::UInt16;
using Poco::Event;
using Poco::NamedEvent;
using Poco::Exception;


namespace
{
	const Poco::UInt16 listenport = 28888;
	const char *hellostring = "Welcome to POCO TCP server. Enter you string:";

	class ClientConnection: public TCPServerConnection
	{
	public:
		ClientConnection(const StreamSocket& s): TCPServerConnection(s)
		{
		}

		void run()
		{
			DialogSocket ds(socket());;
			ds.sendMessage(hellostring);
			try
			{
				std::string str;
				while(ds.receiveMessage(str))
				{
					reverse(str.begin(), str.end());
					ds.sendMessage(str);
				}
			}
			catch (Exception& exc)
			{
				std::cerr << "ClientConnection: " << exc.displayText() << std::endl;
			}
		}
	};

	typedef TCPServerConnectionFactoryImpl<ClientConnection> TCPFactory;
#if defined(POCO_OS_FAMILY_WINDOWS)
	NamedEvent terminator(ProcessImpl::terminationEventName(Process::id()));
#else
	Event terminator;
#endif
}

int main(int argc, char** argv)
{
	try
	{
		TCPServer srv(new TCPFactory(), listenport);
		srv.start();

		std::cout << "TCP server listening on port " << listenport << '.'
			 << std::endl << "Press Ctrl-C to quit." << std::endl;

		terminator.wait();
	}
	catch (Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}

	return 0;
}
