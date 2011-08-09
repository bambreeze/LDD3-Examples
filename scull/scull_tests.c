/*
 * scull_tests.c -- test cases for the bare scull char module
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stropts.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/poll.h>
#include "scull_tests.h"

int scull_basic_read_write_tests()
{
    char buffer1[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    char buffer2[20]={0};
    int sculltest;
    int code,i;

    sculltest = open("/dev/scull0", O_WRONLY);
    for (i = 20; i > 0 ; i -= code)     {  
        if ((code=write(sculltest , &buffer1[20-i] , i)) != i) printf("write error! code=%d \n",code);
        else   printf("write ok! code=%d \n",code);
    }
    close(sculltest);

    sculltest = open("/dev/scull0",O_RDONLY );
    for ( i=20 ; i>0 ; i-=code)     {  
        if ((code=read(sculltest , &buffer2[20-i] , i)) != i) printf("read error! code=%d \n",code);
        else   printf("read ok! code=%d \n",code);
    }
    close(sculltest);

    for(i=0;i<20;i+=5) {
        printf("[%d]=%d [%d]=%d [%d]=%d [%d]=%d [%d]=%d\n",
                i,buffer2[i],i+1,buffer2[i+1],i+2,buffer2[i+2],
                i+3,buffer2[i+3],i+4,buffer2[i+4]);
    }
    printf("\n"); 

    return 0;
}

int scull_basic_ioctl_tests()
{
    char buffer1[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    char buffer2[20]={0};
    int sculltest;
    int code,i;

    if ((sculltest = open("/dev/scull0",O_RDWR )) < 0)	{
        printf("open error! \n"); 
        return(1);
    }

    printf("open scull ! \n"); 
    /**********************************tekkaman************************************/
    code = 10;
    if ( ioctl( sculltest , SCULL_IOCSQUANTUM , &code ) < 0) 	{
        printf("ioctl SCULL_IOCSQUANTUM error! \n"); 
        return(1);
    }

    printf("SCULL_IOCSQUANTUM-SCULL_IOCQQUANTUM : scull_quantum=%d \n" , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) );

    if ( ioctl( sculltest , SCULL_IOCTQUANTUM , 6 ) < 0) 	 {
        printf("ioctl SCULL_IOCTQUANTUM error! \n"); 
        return(1);
    }

    if ( ioctl( sculltest , SCULL_IOCGQUANTUM , &code ) < 0)  	  {
        printf("ioctl SCULL_IOCGQUANTUM error! \n"); 
        return(1);
    }
    printf("SCULL_IOCTQUANTUM-SCULL_IOCGQUANTUM : scull_quantum=%d \n", code);

    code = 10;

    if ( ioctl( sculltest , SCULL_IOCXQUANTUM , &code ) < 0) 	{
        printf("ioctl SCULL_IOCXQUANTUM error! \n"); 
        return(1);
    }

    printf("SCULL_IOCXQUANTUM : scull_quantum=%d --> %d\n" , code , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) );

    printf("SCULL_IOCHQUANTUM : scull_quantum=%d --> %d\n" , ioctl( sculltest , SCULL_IOCHQUANTUM , 6 ) , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) );

    /**********************************tekkaman************************************/

    code = 2;
    if ( ioctl( sculltest , SCULL_IOCSQSET , &code ) < 0) 	{
        printf("ioctl SCULL_IOCSQQSET error! \n"); 
        return(1);
    }

    printf("SCULL_IOCSQSET-SCULL_IOCQQSET : scull_qset=%d \n" , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    if ( ioctl( sculltest , SCULL_IOCTQSET , 4 ) < 0) 	 {
        printf("ioctl SCULL_IOCTQSET error! \n"); 
        return(1);
    }

    if ( ioctl( sculltest , SCULL_IOCGQSET , &code ) < 0)  	  {
        printf("ioctl SCULL_IOCGQSET error! \n"); 
        return(1);
    }
    printf("SCULL_IOCTQSET-SCULL_IOCGQSET : scull_qset=%d \n", code);

    code = 2;

    if ( ioctl( sculltest , SCULL_IOCXQSET , &code ) < 0) 	{
        printf("ioctl SCULL_IOCXQSET error! \n"); 
        return(1);
    }

    printf("SCULL_IOCXQSET : scull_qset=%d --> %d\n" , code , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    printf("SCULL_IOCHQSET : scull_qset=%d --> %d\n" , ioctl( sculltest , SCULL_IOCHQSET , 4 ) , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    /**********************************tekkaman************************************/
    printf("before reset : scull_quantum=%d  scull_qset=%d \n" , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    close(sculltest); 
    printf("close scull ! \n"); 
    if ((sculltest = open("/dev/scull0",O_RDWR )) < 0)	{
        printf("open error! \n"); 
        return(1);
    }
    printf("reopen scull ! \n"); 

    printf("reopen : scull_quantum=%d  scull_qset=%d \n" , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    for ( i=20 ; i>0 ; i-=code)		{  
        if ((code=write(sculltest , &buffer1[20-i] , i)) != i) printf("write error! code=%d i=%d \n",code,i);
        else   printf("write ok! code=%d \n",code);
    }

    if((code = lseek(sculltest , 0 , SEEK_SET)) != 0)	printf("llseek error! code=%d \n",code);
    printf("lseek scull  SEEK_SET-->0 ! \n"); 

    for ( i=20 ; i>0 ; i-=code)		{  
        if ((code=read(sculltest , &buffer2[20-i] , i)) != i) printf("read error! code=%d i=%d \n",code,i);
        else   printf("read ok! code=%d \n",code);
    }

    for(i=0;i<20;i+=5) 
        printf("[%d]=%d [%d]=%d [%d]=%d [%d]=%d [%d]=%d\n",i,buffer2[i],i+1,buffer2[i+1],i+2,buffer2[i+2],i+3,buffer2[i+3],i+4,buffer2[i+4]);

    //#if 0
    /**********************************tekkaman************************************/
    if ( ioctl( sculltest , SCULL_IOCRESET , NULL ) < 0) 	{
        printf("ioctl SCULL_IOCRESET error! \n"); 
        return(1);
    }
    printf("SCULL_IOCRESET \n" );

    printf("after reset : scull_quantum=%d  scull_qset=%d \n" , ioctl( sculltest , SCULL_IOCQQUANTUM , NULL ) , ioctl( sculltest , SCULL_IOCQQSET , NULL ) );

    close(sculltest); 
    printf("close scull ! \n"); 
    if ((sculltest = open("/dev/scull0",O_RDWR )) < 0)	{
        printf("open error! \n"); 
        return(1);
    }
    printf("reopen scull ! \n"); 


    for ( i=20 ; i>0 ; i-=code)		{  
        if ((code=write(sculltest , &buffer1[20-i] , i)) != i) printf("write error! code=%d i=%d \n",code,i);
        else   printf("write ok! code=%d \n",code);
    }

    if((code = lseek(sculltest , -10 , SEEK_CUR)) != 10)	printf("llseek error! code=%d \n",code);
    printf("lseek scull  SEEK_CUR-10-->10 ! \n"); 

    for ( i=10 ; i>0 ; i-=code)		{  
        if ((code=read(sculltest , &buffer2[10-i] , i)) != i) printf("read error! code=%d i=%d \n",code,i);
        else   printf("read ok! code=%d \n",code);
    }

    for(i=0;i<10;i+=5) 
        printf("[%d]=%d [%d]=%d [%d]=%d [%d]=%d [%d]=%d\n",i,buffer2[i],i+1,buffer2[i+1],i+2,buffer2[i+2],i+3,buffer2[i+3],i+4,buffer2[i+4]);

    if((code = lseek(sculltest , -20 , SEEK_END)) != 0)	printf("llseek error! code=%d \n",code);
    printf("lseek scull  SEEK_END-20-->0 ! \n"); 

    for ( i=20 ; i>0 ; i-=code)		{  
        if ((code=read(sculltest , &buffer2[20-i] , i)) != i) printf("read error! code=%d i=%d \n",code,i);
        else   printf("read ok! code=%d \n",code);
    }

    for(i=0;i<20;i+=5) 
        printf("[%d]=%d [%d]=%d [%d]=%d [%d]=%d [%d]=%d\n",i,buffer2[i],i+1,buffer2[i+1],i+2,buffer2[i+2],i+3,buffer2[i+3],i+4,buffer2[i+4]);
    close(sculltest);
    printf("close scull ! \n"); 

    printf("\n"); 

    return 0;
}

int gotdata=0;
void sighandler(int signo)
{
    if (signo==SIGIO)
        gotdata++;
    return;
}

char buffer[21];

int scull_async_tests()
{
    int pipetest0;
    int count;
    struct sigaction action;

    if ((pipetest0 = open("/dev/scullpipe0",O_RDONLY)) < 0)	{
        printf("open scullpipe0 error! \n"); 
        return(1);
    }

    memset(&action, 0, sizeof(action));
    action.sa_handler = sighandler;
    action.sa_flags = 0;

    sigaction(SIGIO, &action, NULL);

    fcntl(pipetest0, F_SETOWN, getpid());
    fcntl(pipetest0, F_SETFL, fcntl(pipetest0, F_GETFL) | FASYNC);

    while(1) {
        /* this only returns if a signal arrives */
        sleep(86400); /* one day */
        if (!gotdata)
            continue;
        count=read(pipetest0, buffer, 21);
        /* buggy: if avail data is more than 4kbytes... */
        write(1,buffer,count);
        gotdata=0;
        break;
    }

    close(pipetest0 );
    printf("close pipetest0  ! \n"); 

    printf("return !\n"); 
    return(0);
}

int scull_pipe_tests()
{
    char buffer1[20]={0};
    int pipetest0, pipetest1;
    int code=21, i=0;
    struct pollfd poll_list[2];
    int retval;



    if ((pipetest0 = open("/dev/scullpipe0",O_RDONLY)) < 0)	{
        printf("open scullpipe0 error! \n"); 
        return(1);
    }
    printf("open scullpipe0 ! \n"); 

    if ((pipetest1 = open("/dev/scullpipe1",O_RDONLY)) < 0)	{
        printf("open scullpipe1 error! \n"); 
        return(1);
    }
    printf("open scullpipe1 ! \n"); 

    if ( ioctl(pipetest0 ,  SCULL_P_IOCTSIZE , code ) < 0) 	{
        printf("pipetest0 ioctl  SCULL_P_IOCTSIZE error! \n"); 
        return(1);
    }

    printf(" SCULL_P_IOCTSIZE : scull_p_buffer0=%d !\n" ,ioctl( pipetest0 , SCULL_P_IOCQSIZE , NULL ) );


    if ( ioctl(pipetest1 ,  SCULL_P_IOCTSIZE , code ) < 0) 	{
        printf("pipetest1 ioctl  SCULL_P_IOCTSIZE error! \n"); 
        return(1);
    }

    printf(" SCULL_P_IOCTSIZE : scull_p_buffer1=%d !\n" ,ioctl( pipetest1 , SCULL_P_IOCQSIZE , NULL ) );

    close(pipetest0);
    printf("close pipetest0 ! \n"); 
    close(pipetest1);
    printf("close pipetest1 ! \n"); 
    if ((pipetest0 = open("/dev/scullpipe0",O_RDONLY)) < 0)	{
        printf("reopen scullpipe0 error! \n"); 
        return(1);
    }
    printf("reopen scullpipe0 ! \n"); 

    if ((pipetest1 = open("/dev/scullpipe1",O_RDONLY)) < 0)	{
        printf("reopen scullpipe1 error! \n"); 
        return(1);
    }
    printf("reopen scullpipe1 ! \n"); 


    poll_list[0].fd = pipetest0;
    poll_list[1].fd = pipetest1;
    poll_list[0].events = POLLIN|POLLRDNORM;
    poll_list[1].events = POLLIN|POLLRDNORM;

    while(1)
    {
        retval = poll(poll_list,(unsigned long)2,-1);
        /* retval 总是大于0或为-1，因为我们在阻塞中工作 */

        if(retval < 0)
        {
            fprintf(stderr,"poll错误: %s\n",strerror(errno));
            return -1;
        }

        if(poll_list[0].revents&(POLLIN|POLLRDNORM)) 
        {
            if ((code=read(pipetest0 , buffer1 , 20)) != 20) printf("read from pipetest0 error! code=%d\n",code);
            else   printf("read from pipetest0 ok! code=%d \n",code);

            for(i=0;i<20;i+=5) 
                printf("[%d]=%c [%d]=%c [%d]=%c [%d]=%c [%d]=%c\n",i,buffer1[i],i+1,buffer1[i+1],i+2,buffer1[i+2],i+3,buffer1[i+3],i+4,buffer1[i+4]);

        }

        if(poll_list[1].revents&(POLLIN|POLLRDNORM)) 
        {
            if ((code=read(pipetest1 , buffer1 , 20)) != 20) printf("read from pipetest1 error! code=%d \n",code);
            else   printf("read from pipetest1 ok! code=%d \n",code);

            for(i=0;i<20;i+=5) 
                printf("[%d]=%c [%d]=%c [%d]=%c [%d]=%c [%d]=%c\n",i,buffer1[i],i+1,buffer1[i+1],i+2,buffer1[i+2],i+3,buffer1[i+3],i+4,buffer1[i+4]);

        }

    }

    close(pipetest0 );
    printf("close pipetest0  ! \n"); 
    close(pipetest1 );
    printf("close pipetest1 ! \n"); 

    printf("\n"); 
    return(0);
}

static void print_help_message()
{
    printf("Usage: ./scull_tests <num>\n");
    printf("<num>: '1' = scull_basic_read_write_tests\n");
    printf("       '2' = scull_basic_ioctl_tests\n");
    printf("       '3' = scull_pipe_tests\n");
    printf("       '4' = scull_async_tests\n");
}

int main(int argc, char *argv[])
{
    int index = 0;

    if (argc != 2) {
        print_help_message();
        exit(0);
    }

    index = atoi(argv[1]);
    switch (index) {
        case 1:
            scull_basic_read_write_tests();
            break;
        case 2:
            scull_basic_ioctl_tests();
            break;
        case 3:
            scull_pipe_tests();
            break;
        case 4:
            scull_async_tests();
            break;
        default:
            print_help_message();
            break;
    }

    exit(0);
}
