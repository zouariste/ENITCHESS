#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

STARTUPINFO sti = {0};
SECURITY_ATTRIBUTES sats = {0};
PROCESS_INFORMATION pi = {0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[2048];
DWORD writ, excode, read, available;

std::string getNextMove(std::string position)
{     
	std::string str;
	position = "position startpos moves "+position+"\ngo\n";	

	WriteFile(pipin_w, position.c_str(), position.length(),&writ, NULL);
    Sleep(500);
        
    PeekNamedPipe(pipout_r, buffer,sizeof(buffer), &read, &available, NULL);   
    do
    {   
        ZeroMemory(buffer, sizeof(buffer));
		if(!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break; 
        buffer[read] = 0;	
		str+=(char*)buffer;
    }
    while(read >= sizeof(buffer));

	int n = str.find("bestmove");  
	if (n!=-1) return str.substr(n+9,4);
			 
    return "error";
}

#endif CONNECTOR_H