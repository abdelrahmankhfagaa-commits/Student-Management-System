#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for student information
typedef struct
{
    int ID;
    char name[30];
    float grade;
} student;

// Define an enumeration for user roles
typedef enum
{
    ADMIN = 1,
    STUDENT = 2
} role;

// Function prototypes
void add_student();
void view_all_students();
int find_student_by_id(int id);
void update_student_grade();
void delete_student();
void admin_menu();
void student_login();

// Global variables
student *students = NULL;
int studentCount = 0;

int main()
{
    while (1)
    {
        role userRole;
        printf("\nSelect user role (1 for Admin, 2 for Student, 0 to Exit): ");
        scanf("%d", &userRole);

        if (userRole == 0)
        {
            printf("Exiting...\n");
            break;
        }
        else if (userRole == ADMIN)
        {
            admin_menu();
        }
        else if (userRole == STUDENT)
        {
            student_login();
        }
        else
        {
            printf("Invalid user role selected.\n");
        }
    }

    // Free allocated memory after the loop ends
    free(students);
    return 0;
}

// Admin menu extracted into its own function
void admin_menu()
{
    int choice;
    do
    {
        printf("\nAdmin Menu:\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Update Student Grade\n");
        printf("4. Delete Student\n");
        printf("5. Back to Main Menu\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_student();
                break;
            case 2:
                view_all_students();
                break;
            case 3:
                update_student_grade();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);  // exit the whole program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

// --- Student login extracted into its own function ---
void student_login()
{
    int id;
    printf("Enter your student ID: ");
    scanf("%d", &id);

    int index = find_student_by_id(id);
    if (index != -1)
    {
        printf("Welcome, %s! Your grade is %.2f\n", students[index].name, students[index].grade);
    }
    else
    {
        printf("Student with ID %d not found.\n", id);
    }
}

void add_student()
{
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);

    // Check if the student ID already exists
    if (find_student_by_id(id) != -1)
    {
        printf("Student with ID %d already exists.\n", id);
        return;
    }

    // Safe realloc: use a temp pointer to avoid losing data on failure
    student *tmp = realloc(students, (studentCount + 1) * sizeof(student));
    if (tmp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    students = tmp;

    students[studentCount].ID = id;

    printf("Enter student name: ");
    scanf("%49s", students[studentCount].name);  // width limit to prevent buffer overflow

    float grade;
    do
    {
        printf("Enter student grade (0 - 100): ");
        scanf("%f", &grade);
        if (grade < 0 || grade > 100)
            printf("Invalid grade. Please enter a value between 0 and 100.\n");
    } while (grade < 0 || grade > 100);

    students[studentCount].grade = grade;
    studentCount++;

    printf("Student added successfully.\n");
}

void view_all_students()
{
    if (studentCount == 0)
    {
        printf("No students found.\n");
        return;
    }

    printf("\nID\tName\t\tGrade\n");
    printf("--------------------------------\n");
    for (int i = 0; i < studentCount; i++)
    {
        printf("%d\t%s\t\t%.2f\n", students[i].ID, students[i].name, students[i].grade);
    }
}

int find_student_by_id(int id)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].ID == id)
        {
            return i;
        }
    }
    return -1;  // student not found
}

void update_student_grade()
{
    int id;
    printf("Enter student ID to update grade: ");
    scanf("%d", &id);

    int index = find_student_by_id(id);
    if (index == -1)
    {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    float grade;
    do
    {
        printf("Enter new grade for student %s (0 - 100): ", students[index].name);
        scanf("%f", &grade);
        if (grade < 0 || grade > 100)
            printf("Invalid grade. Please enter a value between 0 and 100.\n");
    } while (grade < 0 || grade > 100);

    students[index].grade = grade;
    printf("Grade updated successfully.\n");
}

void delete_student()
{
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    int index = find_student_by_id(id);
    if (index == -1)
    {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    // Shift remaining students to fill the gap
    for (int i = index; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }
    studentCount--;

    // Resize the array, or free if empty
    if (studentCount == 0)
    {
        free(students);
        students = NULL;
    }
    else
    {
        student *tmp = realloc(students, studentCount * sizeof(student));
        if (tmp != NULL)
            students = tmp;
    }

    printf("Student deleted successfully.\n");
}
