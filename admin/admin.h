typedef struct {
    char user[100];
    char password[50];
} ADMIN;

typedef struct node {
    ADMIN admin;
    struct node *next;
} NODE_ADMIN;

NODE_ADMIN* initAdmins();
