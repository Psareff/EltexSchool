#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>

//#define MSQID ftok("./chat.1", '0')
#define PERMS 0666

#define MAX_STRING_LENGTH 100
#define INITIAL_TO_SERVER 1
#define COMMON_TO_SERVER 2
#define COMMON_TO_CLIENT 3
typedef struct 
{
    pid_t client_pid;
    int type;
    char data[MAX_STRING_LENGTH];
} message_t;