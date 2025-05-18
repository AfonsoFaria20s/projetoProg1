#ifndef ADMIN_H
#define ADMIN_H

typedef struct admin {
    char user[100];
    char password[100];
    int firstTime;
    struct admin *next;
} ADMIN;

ADMIN* initAdmins();
int saveAdminsToFile(ADMIN *admins);
ADMIN* findAdmin(ADMIN *admins, const char *username);
int updateAdminPassword(ADMIN *admins, const char *username, const char *newPassword);
void freeAdmins(ADMIN *admins);
void menuAdmin(int *opt);

#endif