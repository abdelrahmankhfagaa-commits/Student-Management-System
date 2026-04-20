// app.c
#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void run() {
    while (1) {
        role userRole;
        printf("\nSelect user role (1 for Admin, 2 for Student, 0 to Exit): ");
        scanf("%d", &userRole);

        if (userRole == 0) {
            printf("Exiting...\n");
            break;
        } else if (userRole == ADMIN) {
            admin_menu();
        } else if (userRole == STUDENT) {
            student_login();
        } else {
            printf("Invalid user role selected.\n");
        }
    }
    free(students);
}