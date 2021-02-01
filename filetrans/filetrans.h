#ifndef __FILETRANS_H__
#define __FILETRANS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum FileTransProtocol {
	FTP = 0,
	SFTP,
	TFTP,
	UNAVAILABLE
} FileTransProtocol;

typedef enum FileTransOperation {
	PUSH = 0,
	PULL,
	ADD,
	DEL,
	LIST,
	UNDEFINDED
} FileTransOperation;

FileTransProtocol cs2Protocol(const char *protocol);
FileTransOperation cs2Operation(const char *op);

int setupServ(const char *hostPort, const char *user, const char *pwd, FileTransProtocol proto);
int uploadFile(const char *localFile, const char * remoteFile);
int downloadFile(const char *localFile, const char * remoteFile);
int listDir(const char *dir);
double getProgressPercent();
void cleanupServ();

#ifdef __cplusplus
}
#endif

#endif
