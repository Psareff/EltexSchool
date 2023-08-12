#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>

//#define MSQID ftok("./chat.1", '0')
#define PERMS 00666

#define MAX_STRING_LENGTH 100

#define MSG_TYPE_STRING 1
#define MSG_TYPE_FINISH 255

typedef struct 
{
    int type;
    int data;
} message_t;