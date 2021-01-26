
#include <stdio.h>
#include "filetrans/filetrans.h"
#include "mqtt/mqtt.h"

int main(int argc, char *argv[])
{
	printf("hello, world\n");
	listDir();
	cleanUp();
	testmqtt();

	return 0;
}
