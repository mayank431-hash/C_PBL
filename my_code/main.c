#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks[5];
    float cgpa;
};

// Function to calculate CGPA
float calculateCGPA(float marks[]) {
    float sum = 0;
    for(int i = 0; i < 5; i++) {
        sum += marks[i];
    }
    return (sum / 5) / 10; // simple CGPA logic
}

// Add student
void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks of 5 subjects:\n");
    for(int i = 0; i < 5; i++) {
        printf("Subject %d: ", i+1);
        scanf("%f", &s.marks[i]);
    }

    s.cgpa = calculateCGPA(s.marks);
     fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// Display all students
void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);

        printf("\nMarks: ");
        for(int i = 0; i < 5; i++) {
            printf("%.2f ", s.marks[i]);
        }

        printf("\nCGPA: %.2f\n", s.cgpa);
    }

    fclose(fp);
}
// Search student by roll
void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\n", s.roll);
            printf("Name: %s\n", s.name);

            printf("Marks: ");
            for(int i = 0; i < 5; i++) {
                printf("%.2f ", s.marks[i]);
            }

            printf("\nCGPA: %.2f\n", s.cgpa);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Record not found!\n");
    }

    fclose(fp);
}

// Simple login
int login() {
    char password[20];
    char correct[] = "admin123";

    printf("Enter Password: ");
    scanf("%s", password);

    if(strcmp(password, correct) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Main function
int main() {
    int choice;

    printf("==== University Result Management System ====\n");

    if(!login()) {
        printf("Access Denied!\n");
        return 0;
    }

    do {
        printf("\n\n1. Add Student");
        printf("\n2. Display All Students");
        printf("\n3. Search Student");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 4);

    return 0;
}