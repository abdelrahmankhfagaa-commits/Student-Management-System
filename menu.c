#include <stdio.h>
#include <stdlib.h>
#include "student.h"

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