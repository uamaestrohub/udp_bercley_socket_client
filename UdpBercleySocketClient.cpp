#include <iostream>
#include <string>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	//std::string fileName;
	//fileName = "D:\\TableScan Turbo+.rar";
	/*std::cout << "enterFileName for send to server" << std::endl;
	std::cin >> fileName;*/
	
	///add check on the correctness of the input file name.

	FileManager fileManager;
	Socket socket;
	fileManager.readFile("D:\\TableScan Turbo+.rar");
	std::streamsize size = 0;
	while (size < fileManager.getFileSize())
	{
		socket.writeData(fileManager.getBuffer(), fileManager.getBufferSize());
		size += fileManager.getBufferSize();
	}
		
	fileManager.closeStream();
	
	socket.disconnect();
}

