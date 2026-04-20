#ifndef STUDENT_H
#define STUDENT_H

// Define a structure for student information
typedef struct {
    int ID;
    char name[20];
    float grade;
} s_student;

// Define an enumeration for user roles
typedef enum {
    ADMIN = 1,
    STUDENT
} role;

// Global variables
extern s_student *students;
extern int studentCount;

// Function prototypes
void add_student();
void view_all_students();
int  find_student_by_id(int id);
void update_student_grade();
void delete_student();
void admin_menu();
void student_login();
void run();
#endif