#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "zookeeper.h"



void update_server_list(zhandle_t *zh)
{
    // update server list
    int i;
    struct String_vector paths;
    int ret = zoo_get_children(zh,"/zk/kv",1,&paths);// note: free mem
    if(ret)
    {
        fprintf(stderr,"Error %d for get_children\n",ret);
        exit(EXIT_FAILURE);
    }
    for(i = 0;i < paths.count;i++)
        printf("/zk/kv/%s\n",paths.data[i]);

    putchar('\n');
}


/*ZOO_CREATED_EVENT：节点创建事件，需要watch一个不存在的节点，当节点被创建时触发，此watch通过zoo_exists()设置
ZOO_DELETED_EVENT：节点删除事件，此watch通过zoo_exists()或zoo_get()设置
ZOO_CHANGED_EVENT：节点数据改变事件，此watch通过zoo_exists()或zoo_get()设置
ZOO_CHILD_EVENT：子节点列表改变事件，此watch通过zoo_get_children()或zoo_get_children2()设置
ZOO_SESSION_EVENT：会话失效事件，客户端与服务端断开或重连时触发
ZOO_NOTWATCHING_EVENT：watch移除事件，服务端出于某些原因不再为客户端watch节点时触发

state=-112 会话超时状态
state= -113　认证失败状态
state=  1 连接建立中
state= 2 (暂时不清楚如何理解这个状态,ZOO_ASSOCIATING_STATE)
state=3 连接已建立状态
state= 999 无连接状态


type=1 创建节点事件
type=2 删除节点事件
type=3 更改节点事件
type=4 子节点列表变化事件
type= -1 会话session事件
type=-2 监控被移除事件

*/

void watcher(zhandle_t *zh,int type,int state,const char *path,void *watcherCtx)
{
    int status = 0;
	
	printf("path=%s\n",path);
    printf("state=%d\n",state);

    printf("type=%d\n",type);

    if(type == ZOO_CHILD_EVENT && strcmp(path,"/zk") == 0)
    {
        update_server_list(zh);
        status = 1;
    }
    if (!status)
        update_server_list(zh);
}

int main(int argc,char *argv[])
{
    const char *host = "127.0.0.1:2181";

    zhandle_t *zh = zookeeper_init(host,watcher,30000,0,0,0);
    if(zh == NULL)
    {
        fprintf(stderr,"Error when connecting to zookeeper servers...\n");
        exit(EXIT_FAILURE);
    }

    // client context
    while(1)
    {
        sleep(10000);
    }

    zookeeper_close(zh);
}
