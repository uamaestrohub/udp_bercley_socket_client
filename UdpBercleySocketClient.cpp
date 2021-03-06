#include <iostream>
#include <string>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	std::string fileName;
	fileName = "D:\\pic.rar";
	//std::cout << "enterFileName for send to server" << std::endl;
	//std::cin >> fileName;
	
	///add check on the correctness of the input file name.

	FileManager fileManager;
	Socket socket;
	char opperationBuffer[8];
	fileManager.readFile(fileName);
	socket.sendCommand(FileManager::Commands::comSendFileSize);
	_itoa(static_cast<int>(fileManager.getFileSize()), opperationBuffer, 10);
	socket.writeData(opperationBuffer, 8);
	socket.sendCommand(FileManager::Commands::comSendFileNameSize);
	_itoa(static_cast<int>(fileManager.getFileNameSize()), opperationBuffer, 10);
	socket.writeData(opperationBuffer, 8);

	socket.sendCommand(FileManager::Commands::comSendFileName);
	char* fName = new char[fileName.size() + 1];
	std::copy(fileName.begin(), fileName.end(), fName);
	fName[fileName.size()] = '\0';
	socket.writeData(fName, fileName.size()+1);
	socket.sendCommand(FileManager::Commands::comSendFile);
	
	size_t buffSize = 1024;
	while (static_cast<size_t>(fileManager.getPos()) < fileManager.getFileSize())
	{
		socket.writeData(fileManager.getBuffer(), fileManager.getBufferSize());
	}
		
	fileManager.closeStream();
	
	socket.disconnect();
}

