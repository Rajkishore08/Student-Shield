#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ADMINS 5 // Maximum number of admin IDs
#define MAX_PASSWORD_LENGTH 20
#define MAX_DONORS 200
#define MAX_BLOOD_GROUP 20
// color declaring
#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
// printColorText("This is cyan text\n", CYAN);

FILE *fp;
long int size;
struct donor
{
    long long int id;
    char name[25];
    int age;
    char address1[70];
    char address2[70];
    char city[20];
    char phn[11];
    char bloodgrp[5];
    int birth_day[4];
    int birth_month[4];
    int birth_year[6];
    char email[40];
};
struct Student
{
    long long int id;
    char name[50];
};

// Declaration of Structures
struct donor b;

void putdonor();
void getdonor();
void donorbyid();
void donorbycity();
void menu();
void creden();
// Admin
void A();
void Adminmenu();
void modifyDonor();
void printNumberOfEntries();
void displayDonorsP();
void displayDonorsT();
void displayDonorsST();
void findClassDetails();
void findClassDetailsS();
// for Age
int calculateAge();

int compareDonorByBloodGroup();

void displayLoginTable();
// color funcion
void printColorText(const char *text, const char *color)
{
    printf("%s%s%s", color, text, RESET);
}

// Input Validationss

// Function to validate phone number
bool isValidPhoneNumber(const char *phoneNumber)
{
    // Validate the phone number using your desired criteria
    // Here is an example validation that checks if the phone number
    // consists of 10 digits only
    int length = strlen(phoneNumber);
    if (length != 10)
    {
        return false;
    }
    for (int i = 0; i < length; i++)
    {
        if (phoneNumber[i] < '0' || phoneNumber[i] > '9')
        {
            return false;
        }
    }
    return true;
}
// Function to validate email address
bool isValidEmailAddress(const char *email)
{
    // Validate the email address using your desired criteria
    // Here is an example validation that checks if the email address
    // contains a '@' symbol
    char *atSymbol = strchr(email, '@');
    return (atSymbol != NULL);
}
// Student id Validation
bool isValidStudentID(long long int studentID)
{
    // Validate the student ID using your desired criteria
    // Here is an example validation that checks if the ID is a positive number
    return (studentID > 0);
}

// Function to validate blood group
bool isValidBloodGroup(const char *bloodGroup)
{
    // Define your desired criteria for blood group validation
    // Here is an example validation that checks if the input is one of the common blood groups
    const char *validBloodGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-", "A1+", "A1-", "B1+", "B1-", "A1B+", "A2+"};
    int numValidBloodGroups = sizeof(validBloodGroups) / sizeof(validBloodGroups[0]);

    for (int i = 0; i < numValidBloodGroups; i++)
    {
        if (strcmp(bloodGroup, validBloodGroups[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

// Function to validate date of birth
bool isValidDateOfBirth(int day, int month, int year)
{
    // Perform your desired date of birth validation here
    // You can implement various checks such as range validation, leap year validation, etc.
    // Here is a simple example that checks if the date falls within a reasonable range

    // Check if year is within a reasonable range (e.g., 1900 to current year)
    int currentYear = 2023; // Change this to the current year
    if (year < 1900 || year > currentYear)
    {
        return false;
    }

    // Check if month is valid (between 1 and 12)
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Check if day is valid based on the month and year
    int daysInMonth;
    switch (month)
    {
    case 2: // February
        // Leap year calculation (simple rule)
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        daysInMonth = isLeapYear ? 29 : 28;
        break;
    case 4:  // April
    case 6:  // June
    case 9:  // September
    case 11: // November
        daysInMonth = 30;
        break;
    default:
        daysInMonth = 31;
        break;
    }

    if (day < 1 || day > daysInMonth)
    {
        return false;
    }

    return true;
}

void main()
{
    int i;
    i = 1;
    size = sizeof(b); // Finding the size of structure
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\t\t\t\t\t    ######  ######   #    #   ######    ######   #   #   ######  \n");
    printf("\t\t\t\t\t\t   #          #      #    #    #    #   #        ##  #     #    \n");
    printf("\t\t\t\t\t\t    ####      #      #    #    #    #   ####     # # #     #    \n");
    printf("\t\t\t\t\t\t        #     #      #    #    #    #   #        #  ##     #    \n");
    printf("\t\t\t\t\t\t   ######     #       ####    ######    ######   #   #     #    \n");
    printf("\n");
    printf("\t\t\t\t\t\t\t   ######   #   #   ######   ######   #       ######  \n");
    printf("\t\t\t\t\t\t\t  #         #   #     #      #        #        #    #  \n");
    printf("\t\t\t\t\t\t\t   ####     #####     #      ####     #        #    #  \n");
    printf("\t\t\t\t\t\t\t       #    #   #     #      #        #        #    #  \n");
    printf("\t\t\t\t\t\t\t  ######    #   #   ######   ######   ######  ######  \n");

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printColorText("\n\n\t\t\t\t\t||      ` STUDENT SHEILD: An Essential Emergency Database for College Life  `    ||", CYAN);
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t  ||      ` Specially For ~ Coimbatore Institue Of Technology ~ `    ||");
    system("cls");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\t\t\t\t\t    ######  ######   #    #   ######    ######   #   #   ######  \n");
    printf("\t\t\t\t\t\t   #          #      #    #    #    #   #        ##  #     #    \n");
    printf("\t\t\t\t\t\t    ####      #      #    #    #    #   ####     # # #     #    \n");
    printf("\t\t\t\t\t\t        #     #      #    #    #    #   #        #  ##     #    \n");
    printf("\t\t\t\t\t\t   ######     #       ####    ######    ######   #   #     #    \n");
    printf("\n");
    printf("\t\t\t\t\t\t\t   ######   #   #   ######   ######   #       ######  \n");
    printf("\t\t\t\t\t\t\t  #         #   #     #      #        #        #    #  \n");
    printf("\t\t\t\t\t\t\t   ####     #####     #      ####     #        #    #  \n");
    printf("\t\t\t\t\t\t\t       #    #   #     #      #        #        #    #  \n");
    printf("\t\t\t\t\t\t\t  ######    #   #   ######   ######   ######  ######  \n");

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t||      ` STUDENT SHEILD: An Essential Emergency Database for College Life  `    ||");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t  ||      ` Specially For ~ Coimbatore Institue Of Technology ~ `    ||");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\n\n\t\t\t\t\t\t\t    Program is Initializing !");
    Sleep(100);
    printf(".");
    Sleep(100);
    printf(".");
    Sleep(100);
    printf(".");
    Sleep(1000);
    SetColor(5);
    printf("\n\n\n\t\t\t\t||   LOGIN  SPACE  > > > > > > > > > > > > > > > > > > > > > > > > > > > > >\n\n");
    int choice;
    SetColor(14);
    printf("\t\t\t\tWelcome to Student Shield!\n");
    SetColor(5);
    printf("\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t\t|| (1)   STUDENT LOGIN      ||     (2)   ADMIN LOGIN      ||        (3)   EXIT PROGRAM      ||");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    SetColor(14);
    printColorText("\n\t\t\t\t|| Enter Your Choice   : ", GREEN);
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

        struct Student student;
        do
        {
            printColorText("\n\n\t\t\t\tEnter Student ID        : ", GREEN);
            scanf("%lld", &student.id);
            getchar(); // consume the newline character

            if (!isValidStudentID(student.id))
            {
                printf("\n\t\t\t\tInvalid Student ID... \n\t\t\t\tPlease enter a valid Student Id.\n");
            }
        } while (!isValidStudentID(student.id));
        printColorText("\n\n\t\t\t\tEnter Student Name      : ", GREEN);
        scanf("%s", student.name);
        saveStudentDetails(student);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t\tPress any key to continue...");
        getch();

        menu();
        break;
    case 2:
        A();
        break;

    case 3:
        exit(1);
        break;
    default:
        printf("\t\t\t\tInvalid choice...Please try again.\n");
        main();
        break;
    }
}
void SetColor(int ForgC)
{
    WORD wColor;
    // We will need this handle to get the current background attribute
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
};

void putdonor()
{
    char a;
    system("cls");
    fp = fopen("BDONOR.dat", "ab+"); // Opening a Binary File
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    fseek(fp, 0, SEEK_END); // Putting the Pointer at the end of the File
    do
    {
        system("cls");
        fflush(stdin);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\tEnter The Details as Same As CIT College Id Card ");
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        printColorText("\n\n\tEnter Student Name         : ", GREEN);
        fgets(b.name, sizeof(b.name), stdin);
        b.name[strcspn(b.name, "\n")] = '\0';

        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        do
        {
            printColorText("\n\n\tEnter Student ID          : ", GREEN);
            scanf("%lld", &b.id);
            getchar(); // consume the newline character
            SetColor(12);
            if (!isValidStudentID(b.id))
            {
                printf("\n\n\tInvalid student ID... \n\tPlease enter a valid Student Id.\n");
            }
        } while (!isValidStudentID(b.id));

        int birth_day, birth_month, birth_year;
        int current_day, current_month, current_year;
        int age;
        // Getting current date
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        current_day = t->tm_mday;
        current_month = t->tm_mon + 1;    // Month starts from 0
        current_year = t->tm_year + 1900; // Year is based on 1900
        /*
        // Prompting for date of birth
        printColorText("\n\n\tEnter your date of birth (DD MM YYYY)  : ", GREEN);
        scanf("%d %d %d", &birth_day, &birth_month, &birth_year);
        getchar();*/
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        while (1)
        {
            printColorText("\n\n\tEnter your date of birth (DD MM YYYY)  : ", GREEN);
            if (scanf("%d %d %d", &birth_day, &birth_month, &birth_year) != 3)
            {
                printf("\n\n\tInvalid date format. Please enter the date in DD MM YYYY format.\n");
                fflush(stdin);
                continue;
            }
            getchar(); // consume the newline character
            // Check if the date of birth is valid
            if (!isValidDateOfBirth(birth_day, birth_month, birth_year))
            {
                printf("\n\n\tInvalid date of birth. Please enter a valid date.\n");
                continue;
            }
            // Valid date of birth, break the loop
            break;
        }
        // Calculating age
        age = current_year - birth_year;

        // Adjusting age based on current month and day
        if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
        {
            age--;
        }
        // Displaying the calculated age
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t(Entered Age is %d years)\n", age);
        b.age = age; // Assigning the calculated age to b.age
        fflush(stdin);

        printColorText("\n\n\tEnter Address Line 1                   : ", GREEN);
        fgets(b.address1, sizeof(b.address1), stdin);
        b.address1[strcspn(b.address1, "\n")] = '\0';

        printColorText("\n\n\tEnter Address Line 2                   : ", GREEN);
        fgets(b.address2, sizeof(b.address2), stdin);
        b.address2[strcspn(b.address2, "\n")] = '\0';

        printColorText("\n\n\tEnter Student City                     : ", GREEN);
        fgets(b.city, sizeof(b.city), stdin);
        b.city[strcspn(b.city, "\n")] = '\0';

        do
        {
            printColorText("\n\n\tEnter Student's Blood Group            : ", GREEN);
            fgets(b.bloodgrp, sizeof(b.bloodgrp), stdin);

            b.bloodgrp[strcspn(b.bloodgrp, "\n")] = '\0';

            if (!isValidBloodGroup(b.bloodgrp))
            {
                printf("\n\n\tInvalid blood group. \n\tPlease enter a valid blood group.\n");
            }
        } while (!isValidBloodGroup(b.bloodgrp));

        do
        {
            printColorText("\n\n\tEnter Student Mobile Number            : ", GREEN);
            fgets(b.phn, sizeof(b.phn), stdin);

            b.phn[strcspn(b.phn, "\n")] = '\0';

            if (!isValidPhoneNumber(b.phn))
            {
                printf("\n\n\tInvalid phone number. \n\tPlease enter a 10-digit number.\n");
            }
        } while (!isValidPhoneNumber(b.phn));

        fflush(stdin);

        do
        {
            printColorText("\n\n\tEnter Student Mail ID                  : ", GREEN);
            fgets(b.email, sizeof(b.email), stdin);

            b.email[strcspn(b.email, "\n")] = '\0';

            if (!isValidEmailAddress(b.email))
            {
                printf("\n\n\tInvalid email address. \n\tPlease enter a valid email.\n");
            }
        } while (!isValidEmailAddress(b.email));

        fwrite(&b, sizeof(struct donor), 1, fp);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\n\tDo You Want to Add Another Student Data? (Y/N): ");
        fflush(stdin);
        scanf("%c", &a);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    } while (a == 'Y' || a == 'y');
    fclose(fp); // Closing the File
    system("cls");
    Adminmenu();
}

void getdonor()
{
    char bld[5];
    system("cls");
    fp = fopen("BDONOR.dat", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }

    fflush(stdin);

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t||      ` STUDENT SHIELD: An Essential Emergency Database for College Life  `    ||");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t  ||      ` Specially For ~ Coimbatore Institute Of Technology ~ `    ||");
    printf("\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\tEnter the Blood Group: ");
    scanf("%s", bld);
    rewind(fp);

    printColorText("=====================================================================================================================================================================================================================\n", RED);
    printf("| %-22s | %-13s | %-4s | %-50s | %-45s | %-16s | %-13s | %-25s |\n", "STUDENT NAME", "STUDENT ID", "AGE", "ADDRESS LINE 1", "ADDRESS LINE 2", "CITY", "MOBILE NUMBER", "EMAIL ID");
    printColorText("=====================================================================================================================================================================================================================\n", RED);

    int found = 0;

    while (fread(&b, sizeof(struct donor), 1, fp) == 1)
    {
        if (strcmp(b.bloodgrp, bld) == 0) // Matching the Blood group required with the ones present in the database
        {
            // Print table rows
            SetColor(15);
            printf("\n");
            printf("| %-22s | %-13lld | %-4d | %-50s | %-45s | %-16s | %-13s | %-25s |\n", b.name, b.id, b.age, b.address1, b.address2, b.city, b.phn, b.email);
            printColorText("_____________________________________________________________________________________________________________________________________________________________________________________________________________________", CYAN);
            printf("\n");

            found = 1;
        }
    }

    if (!found)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\n\n\t\t NO RECORDS FOUND FOR THE GIVEN BLOOD GROUP.....!!!");
    }

    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\nPress any key to continue...");
    getch();
    fclose(fp);
    menu();
}

void menu()
{
    int choice;
    system("cls");
    SetColor(5);
    printf("\t\t\t\t\t\t    ######  ######   #    #   ######    ######   #   #   ######  \n");
    printf("\t\t\t\t\t\t   #          #      #    #    #    #   #        ##  #     #    \n");
    printf("\t\t\t\t\t\t    ####      #      #    #    #    #   ####     # # #     #    \n");
    printf("\t\t\t\t\t\t        #     #      #    #    #    #   #        #  ##     #    \n");
    printf("\t\t\t\t\t\t   ######     #       ####    ######    ######   #   #     #    \n");
    printf("\n");
    printf("\t\t\t\t\t\t\t   ######   #   #   ######   ######   #      ######  \n");
    printf("\t\t\t\t\t\t\t  #         #   #     #      #        #       #    #  \n");
    printf("\t\t\t\t\t\t\t   ####     #####     #      ####     #       #    #  \n");
    printf("\t\t\t\t\t\t\t       #    #   #     #      #        #       #    #  \n");
    printf("\t\t\t\t\t\t\t  ######    #   #   ######   ######   ###### ######  \n");

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printColorText("\n\n||STUDENT SHEILD: ~ An Essential Emergency Database for College Life ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", MAGENTA);

    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n ||Specially For ~ Coimbatore Institue Of Technology ~|| >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\tEMERGENCY DATABASE - `C I T` ");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("(Student Access)");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\t1 ) Search by Blood Group \n\n");
    printf("\t2 ) Search by Student Id \n\n");
    printf("\t3 ) Search by Location \n\n");
    printf("\t4 ) Veiw Batch & Tutor Details \n\n");
    printf("\t5 ) To Veiw Admin Details \n\n");
    printf("\t6 ) Back to Login \n\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t7 ) Exit the program \n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    // printf("\t ~  Search by Student Id \n\n");
    // tutor acess for data security if necessary
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    printColorText("\n\tEnter Your Choice  : ", RED);
    scanf("%d", &choice);
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    switch (choice)
    {

    case 1:
        getdonor();
        break;

    case 2:
        donorbyid();
        break;

    case 3:
        donorbycity();
        break;

    case 4:
        findClassDetailsS();
        break;

    case 5:
        creden();
        break;

    case 6:
        main();
        break;

    case 7:
        exit(1);
        break;

    default:
        system("cls");
        printf("\n\n\t\tYou have Entered wrong choice.....!!!");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        main();
    }
}
void creden()
{
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    system("cls");
    printf("\n\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\tEMERGENCY DATABASE _ Speacially for CIT College \n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\nTeacher Incharge :-  ");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("Dr.Manjula Gandhi \n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("___________________________________________________________________________________________________________________________\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\nTeam Members :-\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n1 ) Raj Kishore S - 71762231040 - Msc SS (2022-2027)\n\n2 ) Pavimalini T  - 71762231040 - Msc SS (2022-2027)\n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n___________________________________________________________________________________________________________________________\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nContact Details for Any Quries\n\n Raj Kishore S -   Msc SS    (2022-2027)\n\n Mobile Number   : 7871421909\n\n Mail id         : 71762231040@cit.edu.in");

    printColorText("\n\n\nPress any key to continue...", RED);
    getch();
    menu();
}
typedef struct
{
    char username[20];
    char password[20];
} Admin;
void A()
{
    Admin admins[MAX_ADMINS]; // Array to store admin IDs
    int numAdmins = 5;        // Number of admin IDs
    char password[MAX_PASSWORD_LENGTH];
    char ch;
    int i = 0;

    // Define the admin credentials
    strcpy(admins[0].username, "Raj");
    strcpy(admins[0].password, "cit@2027");

    strcpy(admins[1].username, "Pavi");
    strcpy(admins[1].password, "cit@2027");

    strcpy(admins[2].username, "Manjulagandhi");
    strcpy(admins[2].password, "cit@2027");

    strcpy(admins[3].username, "Umarani");
    strcpy(admins[3].password, "cit@2027");

    strcpy(admins[4].username, "Jeyarani");
    strcpy(admins[4].password, "cit@2027");

    char username[20];

    // Prompt the user to enter username and password
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\t\t\t_________________________________~   ||  Admin Special Access  ||    ~__________________________________\n\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\t\t____________________ |  To Enter Admin Space Enter Your Valid Credentials  | ___________________________\n\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printColorText("\n\t\t\t\tEnter your Username  : ", CYAN);
    scanf("%s", username);
    printColorText("\n\t\t\t\tEnter your password  : ", CYAN);
    // scanf("%s", password);
    while (1)
    {
        ch = getch();

        if (ch == '\r') // Check for the Enter key (carriage return)
        {
            password[i] = '\0'; // Null-terminate the password string
            break;
        }
        else if (ch == '\b') // Check for the Backspace key
        {
            if (i > 0)
            {
                i--;
                putch('\b'); // Move the cursor back
                putch(' ');  // Erase the character
                putch('\b'); // Move the cursor back again
            }
        }
        else
        {
            if (i < MAX_PASSWORD_LENGTH - 1)
            {
                password[i] = ch;
                i++;
                putch('*'); // Print a star instead of the actual character
            }
        }
    }

    printf("\n\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");

    // Compare the entered username and password with the admin credentials
    int isAdmin = 0; // Flag to indicate admin access

    for (int i = 0; i < numAdmins; i++)
    {
        if (strcmp(username, admins[i].username) == 0 && strcmp(password, admins[i].password) == 0)
        {
            isAdmin = 1;
            break;
        }
    }

    if (isAdmin)
    {
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printColorText("\t\t\t\tLogin successful...\n\n\t\t\t\t Welcome, admin!!!\n", MAGENTA);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t\tPress any key to continue...");
        getch();
        Adminmenu();
    }
    else
    {
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\t\t\t\tInvalid username or password.\n\n Access denied.\n");
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t\tPress any key to continue...");
        getch();
        menu();
        // Add the code for handling incorrect login attempts here
    }
}

// gender can be added
void donorbycity()
{
    char city[20];
    char a = 'y';
    system("cls");
    fp = fopen("BDONOR.DAT", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    fflush(stdin);
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t\t||      ` STUDENT SHIELD: An Essential Emergency Database for College Life  `    ||");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t  ||      ` Specially For ~ Coimbatore Institute Of Technology ~ `    ||");
    printf("\n\tEnter the Location: ");
    scanf("%s", city);
    rewind(fp);

    // Print table headers
    printf("\n");
    printColorText("================================================================================================================================================================================================================================\n", RED);
    printf("| %-22s | %-13s | %-4s | %-8s | %-50s | %-45s | %-13s | %-25s |\n", "STUDENT NAME", "STUDENT ID", "AGE", "BLOOD GROUP", "ADDRESS LINE 1", "ADDRESS LINE 2", "MOBILE NUMBER", "EMAIL ID");
    printColorText("================================================================================================================================================================================================================================\n", RED);

    while (fread(&b, sizeof(struct donor), 1, fp) == 1)
    {
        if ((strcmp(b.city, city)) == 0) // Matching the city required with the ones present in the database
        {
            // Print table rows
            printf("| %-22s | %-13lld | %-4d | ", b.name, b.id, b.age);
            SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("%-11s", b.bloodgrp);
            SetColor(15);
            printf(" | %-50s | %-45s | %-13s | %-25s |\n", b.address1, b.address2, b.phn, b.email);
            printColorText("_______________________________________________________________________________________________________________________________________________________________________________________________________________________________\n", CYAN);
        }
    }

    fclose(fp);
    printf("\n\n\tPress any key to continue...");
    getch();
    menu();
}

void modifyDonor()
{
    long long int id;
    system("cls");
    fp = fopen("BDONOR.dat", "ab+");
    if (fp == NULL)
    {
        printf("Cannot Open File");
        exit(1);
    }
    printf("Enter the Student ID of the donor to modify: ");
    scanf("%lld", &id);
    fseek(fp, 0, SEEK_SET);
    while (fread(&b, sizeof(struct donor), 1, fp) == 1)
    {
        if (b.id == id)
        {
            SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\n\n\t~   Enter the Student's details For Modification  ~");
            SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            printColorText("\n\n\tEnter Student Name                     : ", GREEN);
            fflush(stdin);
            fgets(b.name, sizeof(b.name), stdin);
            b.name[strcspn(b.name, "\n")] = '\0';

            int birth_day, birth_month, birth_year;
            int current_day, current_month, current_year;
            int age;
            // Getting current date
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            current_day = t->tm_mday;
            current_month = t->tm_mon + 1;    // Month starts from 0
            current_year = t->tm_year + 1900; // Year is based on 1900

            // Prompting for date of birth
            printColorText("\n\n\tEnter your date of birth (DD MM YYYY)  : ", GREEN);
            scanf("%d %d %d", &birth_day, &birth_month, &birth_year);
            getchar();

            // Calculating age
            age = current_year - birth_year;

            // Adjusting age based on current month and day
            if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
            {
                age--;
            }
            // Displaying the calculated age
            printf("\n\n\tYour age is %d years.\n", age);
            b.age = age;
            fflush(stdin);

            printColorText("\n\n\tEnter Address Line 1                   : ", GREEN);
            fgets(b.address1, sizeof(b.address1), stdin);
            b.address1[strcspn(b.address1, "\n")] = '\0';

            printColorText("\n\n\tEnter Address Line 2                   : ", GREEN);
            fgets(b.address2, sizeof(b.address2), stdin);
            b.address2[strcspn(b.address2, "\n")] = '\0';

            printColorText("\n\n\tEnter Student City                     : ", GREEN);
            fgets(b.city, sizeof(b.city), stdin);
            b.city[strcspn(b.city, "\n")] = '\0';

            do
            {
                printColorText("\n\n\tEnter Student's Blood Group            : ", GREEN);
                fgets(b.bloodgrp, sizeof(b.bloodgrp), stdin);
                b.bloodgrp[strcspn(b.bloodgrp, "\n")] = '\0';

                if (!isValidBloodGroup(b.bloodgrp))
                {
                    printf("\n\n\tInvalid blood group. \n\tPlease enter a valid blood group.\n");
                }
            } while (!isValidBloodGroup(b.bloodgrp));

            do
            {
                printColorText("\n\n\tEnter Student Mobile Number            : ", GREEN);
                fgets(b.phn, sizeof(b.phn), stdin);
                b.phn[strcspn(b.phn, "\n")] = '\0';

                if (!isValidPhoneNumber(b.phn))
                {
                    printf("\n\n\tInvalid phone number. \n\tPlease enter a 10-digit number.\n");
                }
            } while (!isValidPhoneNumber(b.phn));

            fflush(stdin);

            do
            {
                printColorText("\n\n\tEnter Student Mail ID                  : ", GREEN);
                fgets(b.email, sizeof(b.email), stdin);
                b.email[strcspn(b.email, "\n")] = '\0';

                if (!isValidEmailAddress(b.email))
                {
                    printf("\n\n\tInvalid email address. \n\tPlease enter a valid email.\n");
                }
            } while (!isValidEmailAddress(b.email));

            fseek(fp, -sizeof(struct donor), SEEK_CUR);
            fwrite(&b, sizeof(struct donor), 1, fp);
            SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\n\n\tStudent details modified successfully!!!...............................");
            fclose(fp);
            Adminmenu();
        }
    }
    fclose(fp);
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\tStudent not found with the given Student ID.!!!");
    Adminmenu();
}

void donorbyid()
{
    long long int id;
    char choice = 'y'; // New variable to hold the user's choice
    system("cls");
    fp = fopen("BDONOR.DAT", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    fflush(stdin);
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\t\t\t||      ` STUDENT SHEILD: An Essential Emergency Database for College Life  `    ||");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\t\t\t\t\t  ||      ` Specially For ~ Coimbatore Institue Of Technology ~ `    ||");
    printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    printf("\n\tEnter the Student Id : ");
    scanf("%lld", &id);
    rewind(fp);

    while (fread(&b, size, 1, fp) == 1)
    {
        if (choice == 'Y' || choice == 'y')
        {
            if (b.id == id) // Matching the Bloodgroup required with the one's present in Database
            {
                SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\t\tTHE DETAILS OF STUDENTS WITH THE STUDENT ID HAVE BEEN DISPLAYED !!!\n");
                SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("\n\n\tStudent Name             : %s", b.name);
                printf("\n\n\tStudent ID               : %lld", b.id);
                // printf("Tutor Name                     :");
                printf("\n\n\tAge                      : %d", b.age);
                // printf("\n\n\tDate of Birth            : %d / %d / %d", b.birth_day, b.birth_month, b.birth_year);
                printf("\n\n\tAddress Line 1           : %s", b.address1);
                printf("\n\n\tAddress Line 2           : %s", b.address2);
                printf("\n\n\tCity                     : %s", b.city);
                printf("\n\n\tStudent Mobile Number    : %s", b.phn);
                printf("\n\n\tStudent Mail Id          : %s", b.email);
                SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\n\tStudent's Blood Group    : %s", b.bloodgrp);
                SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
                SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("\n\n\tSee More? (Y/N): ");
                fflush(stdin);
                scanf(" %c", &choice); // Notice the space before %c to consume the newline character
                if (choice == 'Y' || choice == 'y')
                {
                    printf("\n\tEnter the Student Id : ");
                    scanf("%lld", &id);
                    rewind(fp); // Reset the file pointer to search for the new ID
                }
            }
        }
    }

    if (choice == 'n' || choice == 'N')
    {
        fclose(fp);
        menu();
    }
    else
    {
        printf("\n\n\n\t\t NO MORE RECORDS FOUND.....!!!");
        printf("\n\n Back to Main Menu in 7 Seconds");
        Sleep(7000);
        fclose(fp);
        menu();
    }
}

void Adminmenu()
{
    int choice;
    system("cls");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("||  ADMIN ACCESS SPACE  > > > > > > > > > > > > > > > > > > > > > > > > > > > > >\n\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("||  STUDENT SHEILD: ~ An Essential Emergency Database for College Life  ` ||\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t\tEMERGENCY DATABASE - `C I T` \n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\t1 ) Add a New Entry\n\n");
    printf("\t2 ) Modify Entry \n\n");
    printf("\t3 ) Veiw No of Entries \n\n");
    printf("\t4 ) Veiw All Entries \n\n");
    printf("\t5 ) Veiw All Entries(Tabular Printing) \n\n");
    printf("\t6 ) Veiw All Entries( Sorted By Blood Group ) \n\n");
    printf("\t7 ) Veiw Batch & Tutor Details \n\n");
    printf("\t8 ) Veiw Student Logins \n\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t9 ) Back To Login \n\n");
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\t Enter Your Choice : ");
    scanf("%d", &choice);
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    switch (choice)
    {
    case 1:
        putdonor();
        break;

    case 2:
        modifyDonor();
        break;

    case 3:
        printNumberOfEntries();
        break;

    case 4:
        displayDonorsP();
        break;

    case 5:
        displayDonorsT();
        break;

    case 6:
        displayDonorsST();
        break;

    case 7:
        findClassDetails();
        break;

    case 8:
        displayLoginTable();
        break;

    case 9:
        main();
        break;

    default:
        system("cls");
        printf("\n\n\t\tYou have Entered wrong choice.....!!!");
        Sleep(100);
        menu();
    }
};

void printNumberOfEntries()
{
    int count = 0;
    fp = fopen("BDONOR.dat", "rb");
    if (fp == NULL)
    {
        printf("Cannot Open File");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(struct donor);
    fclose(fp);
    printf("Number of entries in the Binary file: %d\n", count);
    printf("\n\nPress any key to continue...");
    getch();
    Adminmenu();
}

int calculateAge()
{
    int birth_day, birth_month, birth_year;
    int current_day, current_month, current_year;
    int age;
    // Getting current date
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    current_day = t->tm_mday;
    current_month = t->tm_mon + 1;    // Month starts from 0
    current_year = t->tm_year + 1900; // Year is based on 1900

    // Calculating age
    age = current_year - birth_year;
    // Adjusting age based on current month and day
    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
    {
        age--;
    }
}
void displayDonorsT()
{
    system("cls");
    fp = fopen("BDONOR.dat", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printColorText("\n\t\t\tDISPLAYING ALL STUDENTS DETAILS\n", CYAN);
    printf("\n\n");

    // Print table headers
    printColorText("=====================================================================================================================================================================================================================\n\n", RED);
    printf("| %-22s | %-13s | %-4s | %-50s | %-45s | %-16s | %-13s | %-25s |\n", "STUDENT NAME", "STUDENT ID", "AGE", "ADDRESS LINE 1", "ADDRESS LINE 2", "CITY", "MOBILE NUMBER", "EMAIL ID");
    printColorText("\n=====================================================================================================================================================================================================================\n\n", RED);

    while (fread(&b, sizeof(struct donor), 1, fp) == 1)
    {
        // Print table rows
        printf("\n");
        printf("| %-22s | %-13lld | %-4d | %-50s | %-45s | %-16s | %-13s | %-25s |\n", b.name, b.id, b.age, b.address1, b.address2, b.city, b.phn, b.email);
        printColorText("_____________________________________________________________________________________________________________________________________________________________________________________________________________________", CYAN);
        printf("\n");
    }

    fclose(fp);
    printf("\nPress any key to continue...");
    getch();
    Adminmenu();
}

void displayDonorsST()
{
    system("cls");
    fp = fopen("BDONOR.dat", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printColorText("\n\t\t\tDISPLAYING ALL STUDENTS DETAILS\n", CYAN);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    // Print table headers
    printColorText("=====================================================================================================================================================================================================================\n", RED);
    printf("| %-22s | %-13s | %-4s | %-50s | %-45s | %-16s | %-13s | %-25s |\n", "STUDENT NAME", "STUDENT ID", "AGE", "ADDRESS LINE 1", "ADDRESS LINE 2", "CITY", "MOBILE NUMBER", "EMAIL ID");

    // Read all donors into an array
    struct donor donors[MAX_DONORS];
    int numDonors = 0;
    while (fread(&donors[numDonors], sizeof(struct donor), 1, fp) == 1)
    {
        numDonors++;
    }

    // Sort the donors array by blood group
    qsort(donors, numDonors, sizeof(struct donor), compareDonorByBloodGroup);

    // Print the sorted table
    char currentBloodGroup[MAX_BLOOD_GROUP];
    strcpy(currentBloodGroup, "");
    for (int i = 0; i < numDonors; i++)
    {
        struct donor b = donors[i];

        if (strcmp(b.bloodgrp, currentBloodGroup) != 0)
        {
            strcpy(currentBloodGroup, b.bloodgrp);
            printColorText("\n=====================================================================================================================================================================================================================\n", GREEN);
            printColorText("\n||  Blood Group : ", RED);
            printf("%s", currentBloodGroup);
            printColorText("    ||\n", RED);
            printColorText("_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n", CYAN);
        }
        // Print table rows
        printf("| %-22s | %-13lld | %-4d | %-50s | %-45s | %-16s | %-13s | %-25s |\n", b.name, b.id, b.age, b.address1, b.address2, b.city, b.phn, b.email);
        printColorText("_____________________________________________________________________________________________________________________________________________________________________________________________________________________", CYAN);
        printf("\n");
    }

    fclose(fp);
    printf("\nPress any key to continue...");
    getch();
    Adminmenu();
}

int compareDonorByBloodGroup(const void *a, const void *b)
{
    struct donor *donorA = (struct donor *)a;
    struct donor *donorB = (struct donor *)b;
    return strcmp(donorA->bloodgrp, donorB->bloodgrp);
}

void displayDonorsP()
{
    system("cls");
    fp = fopen("BDONOR.dat", "rb");
    if (fp == NULL)
    {
        puts("Cannot Open File");
        exit(1);
    }
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printColorText("\n\t\t\tDISPLAYING ALL STUDENTS DETAILS\n", CYAN);
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n");

    while (fread(&b, sizeof(struct donor), 1, fp) == 1)
    {

        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\tStudent Name             : %s", b.name);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\tStudent ID               : %lld", b.id);
        printf("\n\tAge                      : %d", b.age);
        printf("\n\tAddress Line 1           : %s", b.address1);
        printf("\n\tAddress Line 2           : %s", b.address2);
        printf("\n\tCity                     : %s", b.city);
        printf("\n\tStudent Mobile Number    : %s", b.phn);
        printf("\n\tStudent Mail Id          : %s", b.email);
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\tStudent's Blood Group    : %s\n", b.bloodgrp);
        printf("\n");
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n");
    }

    fclose(fp);
    printf("\nPress any key to continue...");
    getch();
    Adminmenu();
}

void findClassDetails()
{
    long long int studentID;
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("______________________________________\n");
    printf("\nEnter Student ID: ");
    scanf("%lld", &studentID);
    printf("______________________________________\n\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("||  TUTOR DETAILS  > > > > > > > > > > > > > > > > > > > > > > > > > > > > >\n");
    printf("\nStudent ID: %lld\n\n", studentID);

    if (studentID >= 71762231001LL && studentID <= 71762231060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :   MSc SS\n\n");
        printf("\t\tTutor     :   Umarani\n\n");
        printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :   2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        Adminmenu();
    }
    else if (studentID >= 71762232001LL && studentID <= 71762232060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :   MSc DS\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :   2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        Adminmenu();
    }
    else if (studentID >= 71762233001LL && studentID <= 71762233060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :  MSc DCS\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :  2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        Adminmenu();
    }
    else if (studentID >= 71762234001LL && studentID <= 71762234060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :  MSc AIML\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :  2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        Adminmenu();
    }
    else
    {
        printColorText("\t\tNo students found in the given ID range\n\n", RED);
        printColorText("\t\tEnter a Valid Student ID\n\n", RED);
        printf("\nPress any key to continue...");
        getch();
        findClassDetails();
        return;
    }
}

void findClassDetailsS()
{
    long long int studentID;
    SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("______________________________________\n");
    printf("\nEnter Student ID: ");
    scanf("%lld", &studentID);
    printf("______________________________________\n\n");
    SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("||  TUTOR DETAILS  > > > > > > > > > > > > > > > > > > > > > > > > > > > > >\n");
    printf("\nStudent ID: %lld\n\n", studentID);

    if (studentID >= 71762231001LL && studentID <= 71762231060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :   MSc SS\n\n");
        printf("\t\tTutor     :   Umarani\n\n");
        printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :   2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        menu();
    }
    else if (studentID >= 71762232001LL && studentID <= 71762232060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :   MSc DS\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :   2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        menu();
    }
    else if (studentID >= 71762233001LL && studentID <= 71762233060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :  MSc DCS\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :  2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        menu();
    }
    else if (studentID >= 71762234001LL && studentID <= 71762234060LL)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\tClass     :  MSc AIML\n\n");
        // printf("\t\tTutor     :   Umarani\n\n");
        // printf("\t\tContact   :   +91 98944 51914\n\n");
        printf("\t\tBatch     :  2022-27\n");
        printColorText("\n\nPress any key to continue...", RED);
        getch();
        menu();
    }
    else
    {
        printColorText("\t\tNo students found in the given ID range\n\n", RED);
        printColorText("\t\tEnter a Valid Student ID\n\n", RED);
        printf("\nPress any key to continue...");
        getch();
        findClassDetails();
        return;
    }
}

void saveStudentDetails(struct Student student)
{
    FILE *file = fopen("student_details.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file!");
        return;
    }

    fprintf(file, "Student ID   : %lld\n", student.id);
    fprintf(file, "Student Name : %s\n", student.name);
    fclose(file);
}

void displayLoginTable()
{
    FILE *file = fopen("student_details.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file!");
        return;
    }

    int numEntries = 0; // Variable to store the number of entries
    char line[100];

    // Count the number of entries in the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "Student ID   :") != NULL)
        {
            numEntries++;
        }
    }

    // Reset the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    printColorText("=======================================================================================================================\n", RED);
    printf("\n\n\t\t\t|| LOGIN DETAILS ||\n");
    printColorText("=======================================================================================================================\n", RED);
    SetColor(10);
    printf("| %-13s | %-22s |\n", "STUDENT ID", "STUDENT NAME");
    printf("-----------------------------------------------------------------------------------------\n");
    SetColor(15);
    // Display the table
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "Student ID   :") != NULL)
        {
            char id[16];
            sscanf(line, "Student ID   : %s", id);
            fgets(line, sizeof(line), file);
            char name[50];
            sscanf(line, "Student Name : %[^\n]", name);
            SetColor(15);
            printf("| %-13s | %-22s |\n", id, name);
        }
    }

    printf("-----------------------------------------------------------------------------------------\n");
    SetColor(14);
    // Display the number of entries
    printf("Total Entries: %d\n", numEntries);
    printf("-----------------------------------------------------------------------------------------\n");

    fclose(file);
    printf("\nPress any key to continue...");
    getch();
    Adminmenu();
    return;
}
