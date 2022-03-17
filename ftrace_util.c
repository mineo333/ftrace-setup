#include "ftrace_util.h"



const char* tracer = "function_graph"; //tracer to use. look in avaliable_tracers for list

const char* buffer_size = "1024"; //buffer size in kb. change this if you want 


int setup_tracer(){ //turns tracing on, sets pid, sets tracer, and sets buffersize
    
    uid_t uid = getuid();

    if(uid != 0){
        printf("ftrace setup failed: run as root\n");
        return -1;
    }

    
    
    char pid_buf[10];
    char read_after[10];
    memset(pid_buf, 0, 10);
    memset(read_after, 0, 10);
    pid_t pid = getpid(); //traces current PID, Changes this if you want
    sprintf(pid_buf, "%d", pid);

    
    


    
    int fd1 = open("/sys/kernel/tracing/set_ftrace_pid", O_RDWR | O_TRUNC);

    if(fd1 < 0){
        printf("1 tracer setup failed: %d\n", errno);
        return -1;
    }


    int err = write(fd1, pid_buf, strlen(pid_buf));
    

    if(err < 0){
        printf("2 tracer setup failed: %d\n", errno);
        return -1;
    }


    int fd2 = open("/sys/kernel/tracing/current_tracer", O_RDWR);

    if(fd2 < 0){
        printf("3 tracer setup failed: %d\n", errno);
        return -1;
    }

    err = write(fd2, tracer, strlen(tracer));

    if(err < 0){
        printf("4 tracer setup failed: %d\n", errno);
        return -1;
    }

    int fd3 = open("/sys/kernel/tracing/buffer_size_kb", O_RDWR | O_TRUNC);

    if(fd3 < 0){
        printf("5 tracer setup failed: %d\n", errno);
        return -1;
    }

    err = write(fd3, buffer_size, strlen(buffer_size));

    if(err < 0){
        printf("6 tracer setup failed: %d\n", errno);
        return -1;
    }

    int fd = open("/sys/kernel/tracing/tracing_on", O_RDWR | O_TRUNC);

    if(fd < 0){
        printf("tracer cleanup failed: %d\n", errno);
        return -1;
    }

    err = write(fd, "1", 1);

    if(err < 0){
        printf("tracer cleanup failed: %d\n", errno);
        return -1;
    }




    close(fd);
    close(fd1);
    close(fd2);
    close(fd3);

    


    return 0;
    

}

void disable_tracing(){ //turns tracing off. Does not clear /sys/kernel/tracing/trace
    uid_t uid = getuid();

    if(uid != 0){
        printf("ftrace setup failed: run as root\n");
        return;
    }

   
   
    int fd = open("/sys/kernel/tracing/tracing_on", O_RDWR | O_TRUNC);

    if(fd < 0){
        printf("tracer cleanup failed: %d\n", errno);
        return;
    }

    int err = write(fd, "0", 1);

    if(err < 0){
        printf("tracer cleanup failed: %d\n", errno);
        return;
    }

    close(fd);
}

void clear_trace(){ //clears /sys/kernel/tracing/trace 

    uid_t uid = getuid();

    if(uid != 0){
        printf("ftrace setup failed: run as root\n");
        return;
    }


    int fd2 = open("/sys/kernel/tracing/current_tracer", O_RDWR);
    
     write(fd2, "nop", 3);

     close(fd2);
}