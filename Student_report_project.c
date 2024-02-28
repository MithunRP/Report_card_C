#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

struct student {
    int rollno;
    char name[50];
    int os_marks, cn_marks, cc_marks, wcm_marks, sem_marks;
    float per;
    char grade;
    int std;
};

void intro() {
    printf("\n\n\n\t\tSTUDENT REPORT CARD PROJECT\n\n");
}

void write_student() {
    FILE *fptr;
    struct student st;
    int rollno;

    fptr = fopen("student.dat", "ab+");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    printf("\nPlease Enter The New Details of student \n");
    printf("\nEnter The roll number of student: ");
    scanf("%d", &rollno);

    // Check if the roll number already exists
    rewind(fptr); // Move file pointer to the beginning
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.rollno == rollno) {
            printf("\nRoll number %d is already assigned. Please enter a different roll number.\n", rollno);
            fclose(fptr);
            return;
        }
    }

    // If roll number does not exist, proceed with entering details
    st.rollno = rollno;

    printf("\nEnter The Name of student: ");
    scanf(" %[^\n]s", st.name);

    int totalMarks = 0; // variable to store total marks
    // Accepting marks for each subject and calculating total marks
    printf("\nEnter The marks in Operating Systems out of 100: ");
    scanf("%d", &st.os_marks);
    totalMarks += st.os_marks; // Adding marks to total
    if (st.os_marks > 100) {
        printf("Error: Marks cannot be more than 100.\n");
        fclose(fptr);
        return; // Exiting the function if marks are invalid
    }

    printf("\nEnter The marks in Computer Networks out of 100: ");
    scanf("%d", &st.cn_marks);
    totalMarks += st.cn_marks;
    if (st.cn_marks > 100) {
        printf("Error: Marks cannot be more than 100.\n");
        fclose(fptr);
        return;
    }

    printf("\nEnter The marks in Cloud Computing out of 100: ");
    scanf("%d", &st.cc_marks);
    totalMarks += st.cc_marks;
    if (st.cc_marks > 100) {
        printf("Error: Marks cannot be more than 100.\n");
        fclose(fptr);
        return;
    }

    printf("\nEnter The marks in World Class Manufacturing out of 100: ");
    scanf("%d", &st.wcm_marks);
    totalMarks += st.wcm_marks;
    if (st.wcm_marks > 100) {
        printf("Error: Marks cannot be more than 100.\n");
        fclose(fptr);
        return;
    }

    printf("\nEnter The marks in Software Engineering Management out of 100: ");
    scanf("%d", &st.sem_marks);
    totalMarks += st.sem_marks;
    if (st.sem_marks > 100) {
        printf("Error: Marks cannot be more than 100.\n");
        fclose(fptr);
        return;
    }

    // Checking total marks
    if (totalMarks > 500) {
        printf("Error: Total marks cannot exceed 500.\n");
        fclose(fptr);
        return;
    }

    // Calculating percentage
    st.per = totalMarks / 5.0;

    // Assigning grade based on the grading system
    if (st.per >= 90)
        st.grade = 'S';
    else if (st.per >= 80)
        st.grade = 'A';
    else if (st.per >= 50)
        st.grade = 'B';
    else if (st.per >= 33)
        st.grade = 'C';
    else
        st.grade = 'F';

    fwrite(&st, sizeof(st), 1, fptr);
    fclose(fptr);
    printf("\n\nStudent Record Has Been Created ");
}

void display_all() {
    FILE *fptr;
    struct student st;
    int found = 0; // Flag to track if records are found

    fptr = fopen("student.dat", "rb");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        found = 1; // Record found
        break;
    }

    fclose(fptr);

    if (found) {
        printf("\n\n\n");
        printf("============================================================================================================================\n");
        printf("| %-12s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-6s |\n", "Roll Number", "Name", "OS Marks", "CN Marks", "CC Marks", "WCM Marks", "SEM Marks", "Percentage", "Grade");
        printf("============================================================================================================================\n");

        fptr = fopen("student.dat", "rb");
        if (fptr == NULL) {
            printf("Error opening file.");
            return;
        }

        while (fread(&st, sizeof(st), 1, fptr) == 1) {
            printf("| %-12d | %-15s | %-10d | %-10d | %-10d | %-10d | %-10d | %-12.2f | %-6c |\n", st.rollno, st.name, st.os_marks, st.cn_marks, st.cc_marks, st.wcm_marks, st.sem_marks, st.per, st.grade);
        }

        printf("============================================================================================================================\n");
        fclose(fptr);
    } else {
        printf("\nNo records found.");
    }
}

void modify_student() {
    int rollno, found = 0;
    FILE *fptr, *temp;
    struct student st;

    printf("\n\n\tTo Modify ");
    printf("\n\n\tPlease Enter The roll number of student: ");
    scanf("%d", &rollno);
    fptr = fopen("student.dat", "rb+");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    temp = fopen("Temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file.");
        fclose(fptr);
        return;
    }

    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.rollno == rollno) {
            found = 1; // Record found
            printf("\nPrevious Record:\n");
            printf("============================================================================================================================\n");
            printf("| %-12s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-6s |\n", "Roll Number", "Name", "OS Marks", "CN Marks", "CC Marks", "WCM Marks", "SEM Marks", "Percentage", "Grade");
            printf("============================================================================================================================\n");
            printf("| %-12d | %-15s | %-10d | %-10d | %-10d | %-10d | %-10d | %-12.2f | %-6c |\n", st.rollno, st.name, st.os_marks, st.cn_marks, st.cc_marks, st.wcm_marks, st.sem_marks, st.per, st.grade);
            printf("============================================================================================================================\n");
            
            printf("\n\nEnter The New Details of student \n");
            printf("\nEnter The roll number of student: ");
            scanf("%d", &st.rollno);
            printf("\nEnter The Name of student: ");
            scanf(" %[^\n]s", st.name);
            printf("\nEnter The marks in Operating Systems out of 100: ");
            scanf("%d", &st.os_marks);
            printf("\nEnter The marks in Computer Networks out of 100: ");
            scanf("%d", &st.cn_marks);
            printf("\nEnter The marks in Cloud Computing out of 100: ");
            scanf("%d", &st.cc_marks);
            printf("\nEnter The marks in World Class Manufacturing out of 100: ");
            scanf("%d", &st.wcm_marks);
            printf("\nEnter The marks in Software Engineering Management out of 100: ");
            scanf("%d", &st.sem_marks);

            // Recalculate percentage and grade after modification
            int totalMarks = st.os_marks + st.cn_marks + st.cc_marks + st.wcm_marks + st.sem_marks;
            st.per = totalMarks / 5.0;
            if (st.per >= 90)
            st.grade = 'S';
            else if (st.per >= 80)
            st.grade = 'A';
            else if (st.per >= 50)
            st.grade = 'B';
            else if (st.per >= 33)
            st.grade = 'C';
            else
            st.grade = 'F';
         }
        fwrite(&st, sizeof(st), 1, temp);
    }

    fclose(temp);
    fclose(fptr);
    remove("student.dat");
    rename("Temp.dat", "student.dat");

    if (found == 0)
        printf("\n\n Record Not Found ");
    else
        printf("\n\n\t Record Updated");
}


void delete_student() {
    FILE *fptr, *temp;
    struct student st;
    int found = 0, rollno; // Flag to track if record is found

    printf("\nEnter the Roll Number of the student to delete: ");
    scanf("%d", &rollno);

    fptr = fopen("student.dat", "rb");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file.");
        fclose(fptr);
        return;
    }

    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.rollno == rollno) {
            found = 1; // Record found
            printf("\nDeleted Record:\n");
            printf("============================================================================================================================\n");
            printf("| %-12s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-6s |\n", "Roll Number", "Name", "OS Marks", "CN Marks", "CC Marks", "WCM Marks", "SEM Marks", "Percentage", "Grade");
            printf("============================================================================================================================\n");
            printf("| %-12d | %-15s | %-10d | %-10d | %-10d | %-10d | %-10d | %-12.2f | %-6c |\n", st.rollno, st.name, st.os_marks, st.cn_marks, st.cc_marks, st.wcm_marks, st.sem_marks, st.per, st.grade);
             printf("============================================================================================================================\n");
        } else {
            fwrite(&st, sizeof(st), 1, temp);
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (!found)
        printf("\nNo record found for the given Roll Number.");
}


void search_student() {
    FILE *fptr;
    struct student st;
    int found = 0, rollno; // Flag to track if record is found

    printf("\nEnter the Roll Number of the student to search: ");
    scanf("%d", &rollno);

    fptr = fopen("student.dat", "rb");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    printf("\n\n\n");
    printf("============================================================================================================================\n");
    printf("| %-12s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-6s |\n", "Roll Number", "Name", "OS Marks", "CN Marks", "CC Marks", "WCM Marks", "SEM Marks", "Percentage", "Grade");
    printf("============================================================================================================================\n");

    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.rollno == rollno) {
            found = 1; // Record found
            printf("| %-12d | %-15s | %-10d | %-10d | %-10d | %-10d | %-10d | %-12.2f | %-6c |\n", st.rollno, st.name, st.os_marks, st.cn_marks, st.cc_marks, st.wcm_marks, st.sem_marks, st.per, st.grade);
            break; // Exit loop after finding the record
        }
    }

    printf("============================================================================================================================\n");
    fclose(fptr);

    if (!found)
        printf("\nNo record found for the given Roll Number.");
}


void entry_menu() {
    char ch2;
    do {
        printf("\n\n\n\tENTRY MENU");
        printf("\n\n\t1.CREATE STUDENT RECORD");
        printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
        printf("\n\n\t3.SEARCH STUDENT RECORD ");
        printf("\n\n\t4.MODIFY STUDENT RECORD");
        printf("\n\n\t5.DELETE STUDENT RECORD");
        printf("\n\n\t6.BACK TO MAIN MENU");
        printf("\n\n\tPlease Enter Your Choice (1-6) ");
        scanf(" %c", &ch2);
        switch (ch2) {
            case '1':
                write_student();
                break;
            case '2':
                display_all();
                break;
            case '3':
                search_student();
                break;
            case '4':
                modify_student();
                break;
            case '5':
                delete_student();
                break;
            case '6':
                return;
            default:
                printf("\a");
                entry_menu();
        }
    } while (ch2 != '6');
}

void display_all_sorted() {
    FILE *fptr;
    struct student st;
    struct student students[MAX_STUDENTS]; // Array to store all students
    int count = 0;

    fptr = fopen("student.dat", "rb");
    if (fptr == NULL) {
        printf("Error opening file.");
        return;
    }

    // Read all records and store them in the array
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        students[count++] = st;
    }

    fclose(fptr);

    // Sort the array based on percentage in descending order
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].per < students[j + 1].per) {
                struct student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Display the sorted records
    printf("\n\n\n\t\tDISPLAY ALL RECORDS (Descending Order of Percentage)\n\n");
    printf("============================================================================================================================\n");
    printf("| %-12s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-6s |\n", "Roll Number", "Name", "OS Marks", "CN Marks", "CC Marks", "WCM Marks", "SEM Marks", "Percentage", "Grade");
    printf("============================================================================================================================\n");
    for (int i = 0; i < count; i++) {
        printf("| %-12d | %-15s | %-10d | %-10d | %-10d | %-10d | %-10d | %-12.2f | %-6c |\n", students[i].rollno, students[i].name, students[i].os_marks, students[i].cn_marks, students[i].cc_marks, students[i].wcm_marks, students[i].sem_marks, students[i].per, students[i].grade);
    }
    printf("============================================================================================================================\n");
}

void result_menu() {
    char choice;
    do {
        printf("\n\n\n\tRESULT MENU");
        printf("\n\n\t1. Display All Records (Descending Order of Percentage)");
        printf("\n\n\t2. Back to Main Menu");
        printf("\n\n\tPlease Select Your Option (1-2) ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                display_all_sorted();
                break;
            case '2':
                return;
            default:
                printf("\nInvalid choice! Please select a valid option (1-2).\n");
        }
    } while (1);
}

int main() {
    char ch;
    intro();
    do {
        printf("\n\n\n\tMAIN MENU");
        printf("\n\n\t01. RESULT MENU");
        printf("\n\n\t02. ENTRY/EDIT MENU");
        printf("\n\n\t03. EXIT");
        printf("\n\n\tPlease Select Your Option (1-3) ");
        scanf(" %c", &ch);
        switch (ch) {
            case '1':
                result_menu();
                break;
            case '2':
                entry_menu();
                break;
            case '3':
                printf("\nExiting Program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select a valid option (1-3).\n");
        }
    } while (ch != '3');
    return 0;
}