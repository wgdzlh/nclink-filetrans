
#include "util/utils.h"
#include "json/ujdecode.h"
#include "../ftp/ftplib.h"

#include "filetrans.h"

ftplib *ftp = nullptr;


void connectFtpServ()
{
	ftp = new ftplib();
	ftp->Connect("pi-ubt.local:21");
	ftp->Login("one", "1234");
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


int listDir()
{
	if (nullptr == ftp)
	{
		connectFtpServ();
	}
	ftp->Dir(NULL, "/ftp/one/test");
	return 0;
}


void cleanUp()
{
	disconnect();
}
