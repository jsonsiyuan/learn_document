# 消息队列 #

web：
**https://www.ibm.com/developerworks/cn/linux/l-ipc/part3/**

    类似如下的数据结构
    struct msgbuf{
    long mtype;
    char mtext[1];
    };

> key=ftok(path_ptr, 'a');

**消息队列API**

> linux为操作系统V进程间通信的三种方式（消息队列、信号灯、共享内存区）提供了一个统一的用户界面：
> 
> int ipc(unsigned int call, int first, int second, int third, void * ptr, long fifth);


**系统V消息队列API**

	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>

---

	int msgget(key_t key, int msgflg)

- 如果没有消息队列与健值key相对应，并且msgflg中包含了IPC_CREAT标志位；
- key参数为IPC_PRIVATE
- 参数msgflg可以为以下：IPC_CREAT、IPC_EXCL、IPC_NOWAIT或三者的或结果。

调用返回：成功返回消息队列描述字，否则返回-1。

---

	int msgrcv(int msqid, struct msgbuf *msgp, int msgsz, long msgtyp, int msgflg);

- msqid为消息队列描述字；
- 消息返回后存储在msgp指向的地址，
- msgsz指定msgbuf的mtext成员的长度（即消息内容的长度），
- msgtyp为请求读取的消息类型；

**- 读消息标志msgflg可以为以下几个常值的或:**

1. IPC_NOWAIT 如果没有满足条件的消息，调用立即返回，此时，errno=ENOMSG
2. IPC_EXCEPT 与msgtyp>0配合使用，返回队列中第一个类型不为msgtyp的消息
3. IPC_NOERROR 如果队列中满足条件的消息内容大于所请求的msgsz字节，则把该消息截断，截断部分将丢失。

调用返回：成功返回读出消息的实际字节数，否则返回-1。

----

	int msgsnd(int msqid, struct msgbuf *msgp, int msgsz, int msgflg);

- 对发送消息来说，有意义的msgflg标志为IPC_NOWAIT，指明在消息队列没有足够空间容纳要发送的消息时，msgsnd是否等待

调用返回：成功返回0，否则返回-1。

------
	int msgctl(int msqid, int cmd, struct msqid_ds *buf);

- IPC_STAT：该命令用来获取消息队列信息，返回的信息存贮在buf指向的msqid结构中；
- IPC_SET：该命令用来设置消息队列的属性，要设置的属性存储在buf指向的msqid结构中；可设置属性包括：msg_perm.uid、msg_perm.gid、msg_perm.mode以及msg_qbytes，同时，也影响msg_ctime成员。
- IPC_RMID：删除msqid标识的消息队列；

----
    #include <sys/types.h>
    #include <sys/msg.h>
    #include <unistd.h>
    void msg_stat(int,struct msqid_ds );
    main()
    {
    int gflags,sflags,rflags;
    key_t key;
    int msgid;
    int reval;
    struct msgsbuf{
            int mtype;
            char mtext[1];
        }msg_sbuf;
    struct msgmbuf
        {
        int mtype;
        char mtext[10];
        }msg_rbuf;
    struct msqid_ds msg_ginfo,msg_sinfo;
    char* msgpath="/unix/msgqueue";
    key=ftok(msgpath,'a');
    gflags=IPC_CREAT|IPC_EXCL;
    msgid=msgget(key,gflags|00666);
    if(msgid==-1)
    {
        printf("msg create error\n");
        return;
    }
    //创建一个消息队列后，输出消息队列缺省属性
    msg_stat(msgid,msg_ginfo);
    sflags=IPC_NOWAIT;
    msg_sbuf.mtype=10;
    msg_sbuf.mtext[0]='a';
    reval=msgsnd(msgid,&msg_sbuf,sizeof(msg_sbuf.mtext),sflags);
    if(reval==-1)
    {
        printf("message send error\n");
    }
    //发送一个消息后，输出消息队列属性
    msg_stat(msgid,msg_ginfo);
    rflags=IPC_NOWAIT|MSG_NOERROR;
    reval=msgrcv(msgid,&msg_rbuf,4,10,rflags);
    if(reval==-1)
        printf("read msg error\n");
    else
        printf("read from msg queue %d bytes\n",reval);
    //从消息队列中读出消息后，输出消息队列属性
    msg_stat(msgid,msg_ginfo);
    msg_sinfo.msg_perm.uid=8;//just a try
    msg_sinfo.msg_perm.gid=8;//
    msg_sinfo.msg_qbytes=16388;
    //此处验证超级用户可以更改消息队列的缺省msg_qbytes
    //注意这里设置的值大于缺省值
    reval=msgctl(msgid,IPC_SET,&msg_sinfo);
    if(reval==-1)
    {
        printf("msg set info error\n");
        return;
    }
    msg_stat(msgid,msg_ginfo);
    //验证设置消息队列属性
    reval=msgctl(msgid,IPC_RMID,NULL);//删除消息队列
    if(reval==-1)
    {
        printf("unlink msg queue error\n");
        return;
    }
    }
    void msg_stat(int msgid,struct msqid_ds msg_info)
    {
    int reval;
    sleep(1);//只是为了后面输出时间的方便
    reval=msgctl(msgid,IPC_STAT,&msg_info);
    if(reval==-1)
    {
        printf("get msg info error\n");
        return;
    }
    printf("\n");
    printf("current number of bytes on queue is %d\n",msg_info.msg_cbytes);
    printf("number of messages in queue is %d\n",msg_info.msg_qnum);
    printf("max number of bytes on queue is %d\n",msg_info.msg_qbytes);
    //每个消息队列的容量（字节数）都有限制MSGMNB，值的大小因系统而异。在创建新的消息队列时，//msg_qbytes的缺省值就是MSGMNB
    printf("pid of last msgsnd is %d\n",msg_info.msg_lspid);
    printf("pid of last msgrcv is %d\n",msg_info.msg_lrpid);
    printf("last msgsnd time is %s", ctime(&(msg_info.msg_stime)));
    printf("last msgrcv time is %s", ctime(&(msg_info.msg_rtime)));
    printf("last change time is %s", ctime(&(msg_info.msg_ctime)));
    printf("msg uid is %d\n",msg_info.msg_perm.uid);
    printf("msg gid is %d\n",msg_info.msg_perm.gid);
    }