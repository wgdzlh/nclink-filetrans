
#include<string>
#include "util/utils.h"
#include "../ftp/ftplib.h"

#include "filetrans.h"
#define GUARD_NULL if(nullptr==ftp)connectFtpServ()

using namespace std;

ftplib *ftp = nullptr;
string hostAndPort;
string username;
string password;


void connectFtpServ()
{
	ftp = new ftplib();
	ftp->Connect(hostAndPort.c_str());
	ftp->Login(username.c_str(), password.c_str());
}


void disconnect()
{
	if (nullptr != ftp)
	{
		ftp->Quit();
		delete ftp;
		ftp = nullptr;
	}
}


void setupServ(const char *hostPort, const char *user, const char *pwd)
{
	hostAndPort = hostPort;
	username = user;
	password = pwd;
}


int listDir(const char *dir)
{
	GUARD_NULL;
	ftp->Dir(NULL, dir);
	return 0;
}

int uploadFile(const char *localFile, const char * remoteFile)
{
	GUARD_NULL;
	ftp->Put(localFile, remoteFile, ftplib::image);
	return 0;
}

int downloadFile(const char *localFile, const char * remoteFile)
{
	GUARD_NULL;
	ftp->Get(localFile, remoteFile, ftplib::image);
	return 0;
}

void cleanupServ()
{
	disconnect();
}
