#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "zookeeper.h"


void watcher(zhandle_t *zh,int type,int state,const char *path,void *watcherCtx){}

int main(int argc,char *argv[])
{
    int ret;

    const char *host = "127.0.0.1:2181";

    zhandle_t *zh = zookeeper_init(host,watcher,30000,0,0,0);
    if(zh == NULL)
    {
        fprintf(stderr,"Error when connecting to zookeeper servers...\n");
        exit(EXIT_FAILURE);
    }
	
	ret = zoo_exists(zh, "/zk/kv/db_pvid", 0, NULL);
	if( ret == ZNONODE ) { 

		ret = zoo_create(zh,"/zk/kv/db_pvid","",-1,&ZOO_OPEN_ACL_UNSAFE,0,NULL,0);
		if(ret)
		{
			fprintf(stderr,"Error %d for create\n",ret);
			exit(EXIT_FAILURE);
		}
		
	}

    while(1)
    {
        sleep(10000);
    }

    zookeeper_close(zh);
}
