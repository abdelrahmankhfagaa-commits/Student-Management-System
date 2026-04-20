#include <stdio.h>
#include <stdlib.h>
#include "student.h"

s_student *students = NULL;
int studentCount = 0;

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
    s_student *tmp = realloc(students, (studentCount + 1) * sizeof(s_student));
    if (tmp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    students = tmp;

    students[studentCount].ID = id;

    printf("Enter student name : ");
    scanf("%19s", students[studentCount].name);  // width limit to prevent buffer overflow

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
        //resize the array to the new student count
        s_student *tmp = realloc(students, studentCount * sizeof(s_student));
        if (tmp != NULL)
            students = tmp;
    }

    printf("Student deleted successfully.\n");
}
