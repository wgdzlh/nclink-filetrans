#ifndef __FILETRANS_H__
#define __FILETRANS_H__

#ifdef __cplusplus
extern "C" {
#endif

void setupServ(const char *hostPort, const char *user, const char *pwd);
int uploadFile(const char *localFile, const char * remoteFile);
int downloadFile(const char *localFile, const char * remoteFile);
int listDir(const char *dir);
void cleanupServ();

#ifdef __cplusplus
}
#endif

#endif
