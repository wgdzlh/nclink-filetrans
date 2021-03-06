
#include <iostream>
#include <cstring>
#include <string>
// #include<map>
#include <sys/stat.h>

#include "ftp/ftplib.h"

#include "filetrans.h"

#define PROGRESS_REPORT_BYTES 	10240000
#define GUARD_NULL				if(nullptr==ftp)connectServ()

using namespace std;

static ftplib *ftp = nullptr;
static string hostAndPort;
static string username;
static string password;
static FileTransProtocol protocol;

static off64_t localFileSize;
static off64_t remoteFileSize;
static bool uploading;
// thread safe?
// static std::map<string, double> progressPercents;


FileTransProtocol cs2Protocol(const char *protocol)
{
	if (strcmp(protocol, "FTP") == 0)
	{
		return FTP;
	} else if (strcmp(protocol, "SFTP") == 0)
	{
		return SFTP;
	} else if (strcmp(protocol, "TFTP") == 0)
	{
		return TFTP;
	} else
	{
		return UNAVAILABLE;
	}
}


FileTransOperation cs2Operation(const char *op)
{
	if (strcmp(op, "pull") == 0)
	{
		return PULL;
	} else if (strcmp(op, "push") == 0)
	{
		return PUSH;
	} else
	{
		return UNDEFINDED;
	}
}


static void setLocalFileSize(const char *filename)
{
	struct stat st;
	stat(filename, &st);
	localFileSize = st.st_size;
}


static void setRemoteFileSize(const char *filename)
{
	int ret;
	ftp->Size(filename, &ret, ftplib::image);
	remoteFileSize = ret;
}


static int progressCallback(off64_t xfered, void *arg)
{
	std::cout << xfered << " bytes transed." << std::endl;
	if (uploading)
		remoteFileSize = xfered;
	else
		localFileSize = xfered;
	return 1;
}


static void connectFtpServ()
{
	ftp = new ftplib();
	ftp->SetCallbackBytes(PROGRESS_REPORT_BYTES);
	ftp->SetCallbackXferFunction(progressCallback);
	ftp->Connect(hostAndPort.c_str());
	ftp->Login(username.c_str(), password.c_str());
}


static void connectServ()
{
	switch (protocol)
	{
	case FTP:
		connectFtpServ();
		break;
	default:
		std::cout << "File trans protocol not supported yet, abort." << std::endl;
		break;
	}
}


static void disconnect()
{
	if (nullptr != ftp)
	{
		switch (protocol)
		{
		case FTP:
			ftp->Quit();
			break;
		default:
			break;
		}
		delete ftp;
		ftp = nullptr;
	}
}


int setupServ(const char *hostPort, const char *user, const char *pwd, FileTransProtocol proto)
{
	if (FTP != proto) {
		return -1;
	}
	hostAndPort = hostPort;
	username = user;
	password = pwd;
	protocol = proto;
	// progressPercents[mtid] = .0;
	return 0;
}


int listDir(const char *dir)
{
	GUARD_NULL;
	ftp->Dir(NULL, dir);
	return 0;
}


int uploadFile(const char *localFile, const char *remoteFile)
{
	GUARD_NULL;
	setLocalFileSize(localFile);
	remoteFileSize = 0;
	uploading = true;
	ftp->Put(localFile, remoteFile, ftplib::image);
	return 0;
}


int downloadFile(const char *remoteFile, const char *localFile)
{
	GUARD_NULL;
	localFileSize = 0;
	setRemoteFileSize(remoteFile);
	uploading = false;
	ftp->Get(localFile, remoteFile, ftplib::image);
	return 0;
}


double getProgressPercent()
{
	if (nullptr != ftp)
	{
		// return progressPercents[mtid];
		return uploading ?
			remoteFileSize / (double)localFileSize :
			localFileSize / (double)remoteFileSize;
	}
	return .0;
}


void cleanupServ()
{
	disconnect();
	// progressPercents.erase(mtid);
}
