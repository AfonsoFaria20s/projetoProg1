typedef struct {
    char user[100];
    char password[50];
} ADMIN;

typedef struct node {
    ADMIN admin;
    struct node *next;
} NODE;

NODE* initAdmins();