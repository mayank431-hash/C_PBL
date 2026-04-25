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