#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

// define constant
#define NUM_SEMESTERS 1
#define NUM_COURSES_PER_SEMESTER 6
#define TOTAL_NUM_STUDENTS 5000

#define GRADE_A 4.00
#define GRADE_A_MINUS 3.67
#define GRADE_B_PLUS 3.33
#define GRADE_B 3.00
#define GRADE_B_MINUS 2.67
#define GRADE_C_PLUS 2.33
#define GRADE_C 2.00
#define GRADE_F 0.00

// define structure
struct Course {
    char code[10], grade[3];
    int creditHours;
    double gradePoint, qualityPoint1Course;
};

struct Student {
    char studentName[31];
    int studentID, currentSem, stdRec, creditHours1Sem[NUM_COURSES_PER_SEMESTER], creditHoursAllSem;
    double GPAs[NUM_COURSES_PER_SEMESTER], CGPA, qualityPoint1Sem[NUM_COURSES_PER_SEMESTER], qualityPointAllSem;
    struct Course studentCourses[NUM_SEMESTERS][NUM_COURSES_PER_SEMESTER];
};

// define variable
int numStudent = 0, validation = 0, userRequireID;
struct Student students[TOTAL_NUM_STUDENTS];

// declaration for function
void modeSel();
int staffMode();
void studentMode();
void backFunc();
void suggFunc();
void graduate();
void header();
void calQualityPoint();
void calcreditHour();
void calGPA();
void calCGPA();
int staffSubMode();
void viewResult();
void recordRes();
void displayStudentData();

// main function
void main() {
    students[numStudent].stdRec = 0;
    modeSel();

    return 0;
}

// Function of select mode
void modeSel() {
    validation = 0;
    while (1) {
        int mode;
        do {
            printf("\n");
            printf("\t\t\t\t\tWelcome to Kolej Pasar GPA/CGPA Calculator!\n");
            printf("\t\t\t\t     =================================================\n\n\n");
            printf("\t\t\t\t\t      -------------------------------\n");
            printf("\t\t\t\t\t      |\t           Mode             |\n");
            printf("\t\t\t\t\t      |-----------------------------|\n");
            printf("\t\t\t\t\t      |                             |\n");
            printf("\t\t\t\t\t      |   [1] Staff Administrator   |\n");
            printf("\t\t\t\t\t      |                             |\n");
            printf("\t\t\t\t\t      |   [2] Student               |\n");
            printf("\t\t\t\t\t      |                             |\n");
            printf("\t\t\t\t\t      |   [3] Exit                  |\n");
            printf("\t\t\t\t\t      |                             |\n");
            printf("\t\t\t\t\t      -------------------------------\n\n");
            if (validation == 1) {
                printf("\t\t\t**************************************************************************\n");
                printf("\t\t\t*            Your mode number is invalid, please enter 1/2/3             *\n");
                printf("\t\t\t**************************************************************************\n\n");
            }
            printf("Please enter the mode number: ");
            scanf("%d", &mode);
            rewind(stdin);
            if (mode >= 1 && mode <= 3) {
                validation = 0;
                break;
            }
            else {
                validation = 1;
                system("cls");
            }
        } while (validation == 1);

        if (mode == 1) {
            system("cls");
            header();
            staffMode();
        }
        else if (mode == 2) {
            system("cls");
            header();
            studentMode();
            backFunc();
        }
        else {
            system("cls");
            exit(0);
        }
    }
    return 0;
}

// Function of staff administrator mode
int staffMode() {
    int submode = staffSubMode();
    system("cls");
    switch (submode) {
    case 1:
        recordRes();
        break;
    case 2:
        viewResult();
        break;
    case 3:
        modeSel();
        break;
    default:
        system("cls");
        exit(0);
        break;
    }
}


//Function of student mode
void studentMode() {
    int userInputID;
    char next;

    if (numStudent == 0) {
        printf("------------------------------------------ [student's result unrecorded yet !] -----------------------------------------\n\n");
    }
    else {
        // validation for student ID
        do {
            printf("\n\t\t\t\t\t       Enter student's ID  : KPKL");
            scanf("%d", &userInputID);
            rewind(stdin);
            for (int count = 0; count < numStudent; count++) {
                if (userInputID == students[count].studentID) {
                    system("cls");
                    printf("\n\t\t\t\t\t\t       Semester CGPA:\n");
                    printf("\t\t\t\t\t\t    ==================\n");
                    for (int sem = 0; sem < students[count].currentSem; sem++) {
                        printf("\n\t\t\t\t\t\t      Semester %d: %.2f\n", sem + 1, students[count].GPAs[sem]);
                    }
                    printf("\n\t\t\t\t------------------------ CGPA: %.2f --------------------------\n\n\n", students[count].CGPA);
                    printf("\t\t\t\tTo: %s\n", students[count].studentName);
                    userRequireID = count;
                    suggFunc();
                    printf("\n");
                    graduate();
                    printf("\n");
                    do {
                        printf("\n\nPress press enter to continue...");
                        next = getchar();

                        if (next == '\n') {
                            backFunc();
                        }
                        else while (getchar() != '\n');
                    } while (next != '\n');
                    validation = 0;
                    break;
                }
                else {
                    validation = 1;
                }
            }
            if (validation = 1) {
                if (userInputID >= 10000 && userInputID <= 99999) {
                    printf("\n\t\t\t------------[ Your result unrecorded yet ]-------------\n\n");
                    validation = 1;
                    break;
                }
                else {
                    printf("\n\t\t\t**************************************************************************\n");
                    printf("\t\t\t*               invalid student ID, please enter 5 numbers               *\n");
                    printf("\t\t\t**************************************************************************\n\n");
                    validation = 1;
                    break;
                }
            }
        } while (validation == 1);
    }
    return 0;
}

// Fuction of back to menu
void backFunc() {

    // for normal back selection
        int back = 0;
        // validation for number of back to menu
        do {
            printf("\n\n\t\t\t\t\t     -------------------------------\n");
            printf("\t\t\t\t\t     |           Selection         |\n");
            printf("\t\t\t\t\t     |-----------------------------|\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     |        [1] Main Menu        |\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     |        [2] Exit             |\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     -------------------------------\n");
            printf("\t\t\t\t\t       Enter your selection     :");
            scanf("%d", &back);
            rewind(stdin);
            if (back == 1 || back == 2) {
                switch (back) {
                case 1:
                    system("cls");
                    modeSel();
                    break;
                case 2:
                    system("cls");
                    exit(0);
                    break;
                default:
                    break;
                }
                validation = 0;
            }
            else {
                validation = 1;
                printf("\n\t\t\t**************************************************************************\n");
                printf("\t\t\t*                    invalid number, please enter 1/2                    *\n");
                printf("\t\t\t**************************************************************************");
            }

        } while (validation == 1);
    
    // for staff mode back selection
    
}

// Function of suggestion for student
void suggFunc() {
    if (students[userRequireID].CGPA == 4.00) {
        printf("\t\t\t\tYour grade is A\n\n");
        printf("\t\t\t\tCongratulations on achieving an A! That's excellent work. To \n\t\t\t\tmaintain this level of performance, I recommend continuing \n\t\t\t\twith your current study habits and time management strategies. \n\t\t\t\tConsider exploring advanced coursework or extracurricular \n\t\t\t\tactivities related to your field of interest to challenge \n\t\t\t\tyourself further.\n");
    }
    else if (students[userRequireID].CGPA >= 3.75) {
        printf("\t\t\t\tYour grade is A-\n\n");
        printf("\t\t\t\tA- is a great achievement! \n\t\t\t\tTo maintain or even improve your \n\t\t\t\tperformance, you might want to continue with your current \n\t\t\t\tstudy strategies. Consider engaging in class discussions \n\t\t\t\tand seeking out challenging projects to further enhance \n\t\t\t\tyour skills.\n");
    }
    else if (students[userRequireID].CGPA >= 3.50) {
        printf("\t\t\t\tYour grade is B+\n\n");
        printf("\t\t\t\tGetting a B+ is a solid performance. \n\t\t\t\tTo improve, you might \n\t\t\t\twant to review your study methods and time management. Try \n\t\t\t\tsetting aside specific study hours and consider seeking \n\t\t\t\thelp from professors or tutors if you find any challenging \n\t\t\t\ttopics. Aim to turn this B+ into an A next time!\n");
    }
    else if (students[userRequireID].CGPA >= 3.00) {
        printf("\t\t\t\tYour grade is B\n\n");
        printf("\t\t\t\tB is a respectable grade, but if you're aiming for improvement, \n\t\t\t\ttry to identify the specific areas where you lost points. \n\t\t\t\tReview your study habits and consider seeking additional \n\t\t\t\thelp or resources for those subjects. Setting a goal to \n\t\t\t\tconsistently earn at least a B+ next time is a good target.\n");
    }
    else if (students[userRequireID].CGPA >= 2.75) {
        printf("\t\t\t\tYour grade is B-\n\n");
        printf("\t\t\t\tB- shows promise, but there's room for improvement. Reflect \n\t\t\t\ton what contributed to this grade and work on those areas. \n\t\t\t\tIt might be beneficial to attend extra office hours with \n\t\t\t\tyour professors and use more diverse study methods.\n");
    }
    else if (students[userRequireID].CGPA >= 2.50) {
        printf("\t\t\t\tYour grade is C+\n\n");
        printf("\t\t\t\tC+ is a passing grade, but it indicates there's potential \n\t\t\t\tfor improvement. Analyze what led to this grade and make a \n\t\t\t\tplan to address those issues. Consider seeking help from a \n\t\t\t\ttutor or academic advisor to raise your performance.\n");
    }
    else if (students[userRequireID].CGPA >= 2.00) {
        printf("\t\t\t\tYour grade is C\n\n");
        printf("\t\t\t\tC is a passing grade, but it's generally considered average. \n\t\t\t\tTo improve, you should definitely review your study habits \n\t\t\t\tand seek additional support if needed. Set a goal to aim \n\t\t\t\tfor at least a B in your upcoming courses.\n");
    }
    else if (students[userRequireID].CGPA >= 0.00) {
        printf("\t\t\t\tYour grade is F\n\n");
        printf("\t\t\t\tF is a challenging situation, but it's important not to \n\t\t\t\tlose hope. Reflect on what led to this outcome, and consider \n\t\t\t\tdiscussing it with your professor or an academic advisor. \n\t\t\t\tYou may need to retake the course or make significant changes \n\t\t\t\tto your study habits. Create a plan to ensure you can avoid \n\t\t\t\tthis grade in the future.\n");
    }
}

void header() {
    printf("\n\t\t\t\t             Kolej Pasar GPA/CGPA Calculator!\n");
    printf("\t\t\t\t\t  ======================================\n");
}

// function of calculate quality point
void calQualityPoint() {

    for (int sem = 0; sem < students[numStudent].currentSem; sem++) {
        for (int course = 0; course < NUM_COURSES_PER_SEMESTER; course++) {
            if (strcmp(students[numStudent].studentCourses[sem][course].grade, "A") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_A;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "A-") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_A_MINUS;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "B+") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_B_PLUS;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "B") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_B;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "B-") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_B_MINUS;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "C+") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_C_PLUS;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "C") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_C;
            }
            else if (strcmp(students[numStudent].studentCourses[sem][course].grade, "F") == 0) {
                students[numStudent].studentCourses[sem][course].gradePoint = GRADE_F;
            }
            else {
                students[numStudent].studentCourses[sem][course].gradePoint = 0;
            }
            students[numStudent].studentCourses[sem][course].qualityPoint1Course = students[numStudent].studentCourses[sem][course].gradePoint * students[numStudent].studentCourses[sem][course].creditHours;
            students[numStudent].qualityPoint1Sem[sem] += students[numStudent].studentCourses[sem][course].qualityPoint1Course;
        }
        students[numStudent].qualityPointAllSem += students[numStudent].qualityPoint1Sem[sem];
    }
    return 0;
}

//function of calculate total credit hours
void calcreditHour() {

    for (int sem = 0; sem < students[numStudent].currentSem; sem++) {
        for (int course = 0; course < NUM_COURSES_PER_SEMESTER; course++) {
            students[numStudent].creditHours1Sem[sem] += students[numStudent].studentCourses[sem][course].creditHours;
        }
        students[numStudent].creditHoursAllSem += students[numStudent].creditHours1Sem[sem];
    }
    return 0;
}

//graduate
void graduate() {
    int remainSem;
    int remainCreHours;

    if (students[numStudent].creditHoursAllSem > 21) {
        printf("\t\t\t\t**You will be graduate ");
        if (students[numStudent].currentSem >= 3)
            printf("with a Certificate!!!**\n");
        else {
            printf("without a Certificate, please take attention!!!**\n");
            remainSem = NUM_COURSES_PER_SEMESTER - students[numStudent].currentSem;
            printf("\t\t\t\tYou still remaining %d semester for you to graduate \n\t\t\t\twith a Certificate.", remainSem);
        }
    }
    else
        printf("\t\t\t\t**You cannot graduate, please take attention!!!**");
    remainCreHours = 21 - students[numStudent].creditHoursAllSem;
    if (remainCreHours == 1)
        printf("\n\t\t\t\tYou still remaining %d credit hour for you to graduate \n\t\t\t\twith a Certificate.", remainCreHours);
    else
        printf("\n\t\t\t\tYou still remaining %d credit hours for you to graduate \n\t\t\t\twith a Certificate.", remainCreHours);
}

//calculate GPA for a course
void calGPA() {
    for (int sem = 0; sem < students[numStudent].currentSem; sem++) {
        students[numStudent].GPAs[sem] = students[numStudent].qualityPoint1Sem[sem] / students[numStudent].creditHours1Sem[sem];
    }
}

//calculate CGPA 
void calCGPA() {
    students[numStudent].CGPA = students[numStudent].qualityPointAllSem / students[numStudent].creditHoursAllSem;
}

// admin's sub mode
int staffSubMode() {
    int submode = 0;
    printf("\t\t\t\t\t     -------------------------------\n");
    printf("\t\t\t\t\t     |\t        Staff Mode         |\n");
    printf("\t\t\t\t\t     |-----------------------------|\n");
    printf("\t\t\t\t\t     |                             |\n");
    printf("\t\t\t\t\t     |  [1] Record Student Result  |\n");
    printf("\t\t\t\t\t     |                             |\n");
    printf("\t\t\t\t\t     |  [2] View Student Result    |\n");
    printf("\t\t\t\t\t     |                             |\n");
    printf("\t\t\t\t\t     |  [3] Main Menu              |\n");
    printf("\t\t\t\t\t     |                             |\n");
    printf("\t\t\t\t\t     |  [4] Exit                   |\n");
    printf("\t\t\t\t\t     |                             |\n");
    printf("\t\t\t\t\t     -------------------------------\n\n");
    do {
        printf("Please enter the mode number: ");
        scanf("%d", &submode);
        rewind(stdin);
        if (!(submode >= 1 && submode <= 4)){
            printf("\n\t\t\t**************************************************************************\n");
            printf("\t\t\t*                invalid mode number, please enter again                 *\n");
            printf("\t\t\t**************************************************************************\n\n");
        }
    } while (!(submode >= 1 && submode <= 4));
    return submode;
}

// function of check student data
void viewResult() {
    int userInputNum, numRecordedStu, way = 0, selection, menu, userInputID;
    header();
    printf("\n");

    if (numStudent != 0) {
        for (numRecordedStu = 0; numRecordedStu < 5000; numRecordedStu++) {
            if (students[numRecordedStu].stdRec == 1) {
                printf("\t\t\t\t\t     [NO.%d] Name        : %s\n", numRecordedStu + 1, students[numRecordedStu].studentName);
                printf("\t\t\t\t\t            Student ID  : KPKL%d\n\n", students[numRecordedStu].studentID);
            }
            else {
                break;
            }
        }
        do {
            printf("\n\n\t\t\t\t\t     -------------------------------\n");
            printf("\t\t\t\t\t     |\t        Selection          |\n");
            printf("\t\t\t\t\t     -------------------------------\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     |    [1] Number of student    |\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     |    [2] Student's ID         |\n");
            printf("\t\t\t\t\t     |                             |\n");
            printf("\t\t\t\t\t     -------------------------------\n");
            printf("\t\t\t\t\t        Choose a way to search  : ");
            scanf("%d", &way);
            rewind(stdin);
            switch (way) {
            case 1:
                do {
                    system("cls");
                    printf("\n\n\n");
                    header();
                    for (numRecordedStu = 0; numRecordedStu < 5000; numRecordedStu++) {
                        if (students[numRecordedStu].stdRec == 1) {
                            printf("\t\t\t\t\t     [NO.%d] Name        : %s\n", numRecordedStu + 1, students[numRecordedStu].studentName);
                            printf("\t\t\t\t\t            Student ID  : KPKL%d\n\n", students[numRecordedStu].studentID);
                        }
                        else {
                            break;
                        }
                    }
                    printf("\n\n\t\t\t\t\t     Enter the number of each student:");
                    scanf("%d", &userInputNum);
                    rewind(stdin);
                    if (userInputNum > 0 && userInputNum <= numRecordedStu) {
                        if (students[userInputNum - 1].stdRec == 1) {
                            validation = 0;
                            printf("\t\t\t\t----------------------------------------------------------\n");
                            printf("\t\t\t\t      Student Name\t\t\t     : %s\n", students[userInputNum - 1].studentName);
                            printf("\t\t\t\t      Student ID\t\t\t     : KPKL%d\n", students[userInputNum - 1].studentID);
                            printf("\t\t\t\t      Current semester session\t\t     : Semester %d\n", students[userInputNum - 1].currentSem);
                            printf("\t\t\t\t----------------------------------------------------------\n");
                            printf("\n\t\t\t\t**********************************************************\n\n");
                            printf("\t\t\t\t\t\t      GPA Result\n");
                            printf("\t\t\t\t   ====================================================\n");
                            for (int sem = 0; sem < students[userInputNum - 1].currentSem; sem++) {
                                printf("\t\t\t\t     Semester %d\t\t\t             : %.2f\n", sem + 1, students[userInputNum - 1].GPAs[sem]);
                            }
                            printf("\n\t\t\t\t\t\t      CGPA Result\n");
                            printf("\t\t\t\t   ====================================================\n");
                            printf("\t\t\t\t     CGPA\t\t\t             : %.2f\n", students[userInputNum - 1].CGPA);
                            do {
                                printf("\n\n\t\t\t\t          -------------------------------------\n");
                                printf("\t\t\t\t          |                                   |\n");
                                printf("\t\t\t\t          |  [1] View other student's result  |\n");
                                printf("\t\t\t\t          |                                   |\n");
                                printf("\t\t\t\t          |  [2] Back to Selection            |\n");
                                printf("\t\t\t\t          |                                   |\n");
                                printf("\t\t\t\t          |  [3] Main Menu                    |\n");
                                printf("\t\t\t\t          |                                   |\n");
                                printf("\t\t\t\t          -------------------------------------\n");
                                printf("\t\t\t\t               Enter your selection     :");
                                scanf("%d", &menu);

                                switch (menu) {
                                case 1:
                                    validation = 2;
                                    break;
                                case 2:
                                    validation = 1;
                                    system("cls");
                                    break;
                                case 3:
                                    system("cls");
                                    modeSel();
                                    break;
                                default:
                                    printf("\n\t\t\t**************************************************************************\n");
                                    printf("\t\t\t*            invalid number of selection, please enter again             *\n");
                                    printf("\t\t\t**************************************************************************\n\n");
                                    break;
                                }
                            } while (!(menu >= 1 && menu <= 3));
                        }
                        else {
                            printf("------------[ Your result unrecorded yet ]-------------\n\n");
                            validation = 1;
                        }
                    }
                    else {
                        printf("\n\t\t\t**************************************************************************\n");
                        printf("\t\t\t*                             invalid number                             *\n");
                        printf("\t\t\t**************************************************************************");
                        do {
                            printf("\n\n\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [1] Enter again                  |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [2] Back to Selection            |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [3] Main Menu                    |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t               Enter your selection     :");
                            scanf("%d", &menu);

                            switch (menu) {
                            case 1:
                                validation = 2;
                                break;
                            case 2:
                                validation = 1;
                                break;
                            case 3:
                                system("cls");
                                modeSel();
                                break;
                            default:
                                printf("\n\t\t\t**************************************************************************\n");
                                printf("\t\t\t*            invalid number of selection, please enter again             *\n");
                                printf("\t\t\t**************************************************************************\n\n");
                                break;
                            }
                        } while (!(menu >= 1 && menu <= 3));
                        validation = 2;
                        break;
                    }
                } while (validation == 2);
                break;
            case 2:
                do {
                    system("cls");
                    printf("\n\n\n");
                    header();
                    for (numRecordedStu = 0; numRecordedStu < 5000; numRecordedStu++) {
                        if (students[numRecordedStu].stdRec == 1) {
                            printf("\t\t\t\t\t     [NO.%d] Name        : %s\n", numRecordedStu + 1, students[numRecordedStu].studentName);
                            printf("\t\t\t\t\t            Student ID  : KPKL%d\n\n", students[numRecordedStu].studentID);
                        }
                        else {
                            break;
                        }
                    }
                    printf("\n\nEnter student's ID: KPKL");
                    scanf("%d", &userInputID);
                    rewind(stdin);
                    for (int count = 0; count < numStudent; count++) {
                        if (userInputID == students[count].studentID) {
                            printf("\t\t\t          --------------------------------------------------\n");
                            printf("\t\t\t            Student Name\t\t\t: %s\n", students[count].studentName);
                            printf("\t\t\t            Student ID\t\t\t\t: KPKL%d\n", students[count].studentID);
                            printf("\t\t\t            Current semester session\t\t: Semester %d\n", students[count].currentSem);
                            printf("\t\t\t          --------------------------------------------------\n");
                            printf("\n\t\t\t     ************************************************************\n\n");
                            printf("\t\t\t\t\t            GPA Result\n");
                            printf("\t\t\t         ====================================================\n");
                            for (int sem = 0; sem < students[count].currentSem; sem++) {
                                printf("\t\t\t           Semester %d\t\t\t       : %.2f\n", sem + 1, students[count].GPAs[sem]);
                            }
                            printf("\n\t\t\t\t\t            CGPA Result\n");
                            printf("\t\t\t         ====================================================\n");
                            printf("\t\t\t           CGPA\t\t\t\t       : %.2f\n", students[count].CGPA);
                            validation = 0;
                            break;
                        }
                        else {
                            validation = 2;
                        }
                    }
                    if (validation == 2) {
                        printf("\n\t\t\t**************************************************************************\n");
                        printf("\t\t\t*                             invalid student ID                         *\n");
                        printf("\t\t\t**************************************************************************");
                        do {
                            printf("\n\n\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [1] Enter again                  |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [2] Back to Selection            |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [3] Main Menu                    |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t                Enter your selection     :");
                            scanf("%d", &menu);

                            switch (menu) {
                            case 1:
                                validation = 2;
                                break;
                            case 2:
                                validation = 1;
                                system("cls");
                                break;
                            case 3:
                                system("cls");
                                modeSel();
                                break;
                            default:
                                printf("\n\t\t\t**************************************************************************\n");
                                printf("\t\t\t*            invalid number of selection, please enter again             *\n");
                                printf("\t\t\t**************************************************************************\n\n");
                                break;
                            }
                        } while (!(menu >= 1 && menu <= 3));
                    }
                    else {
                        do {
                            printf("\n\n\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [1] View other student's result  |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [2] Back to Selection            |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          |  [3] Main Menu                    |\n");
                            printf("\t\t\t\t          |                                   |\n");
                            printf("\t\t\t\t          -------------------------------------\n");
                            printf("\t\t\t\t                Enter your selection     :");
                            scanf("%d", &menu);

                            switch (menu) {
                            case 1:
                                validation = 2;
                                break;
                            case 2:
                                system("cls");
                                validation = 1;
                                break;
                            case 3:
                                system("cls");
                                modeSel();
                                break;
                            default:
                                printf("\n\t\t\t**************************************************************************\n");
                                printf("\t\t\t*            invalid number of selection, please enter again             *\n");
                                printf("\t\t\t**************************************************************************\n\n");
                                break;
                            }
                        } while (!(menu >= 1 && menu <= 3));
                    }
                } while (validation == 2);
                break;
            default:
                printf("\n\t\t\t**************************************************************************\n");
                printf("\t\t\t*                   invalid number, please enter again                   *\n");
                printf("\t\t\t**************************************************************************");
                validation = 1;
                break;
            }
        } while (validation == 1);
    }
    else {
        printf("\n------------------------------------------ [student's result unrecorded yet !] -----------------------------------------\n\n");
        printf("\n\n\t\t\t\t             -------------------------------\n");
        printf("\t\t\t\t             |           Selection         |\n");
        printf("\t\t\t\t             |-----------------------------|\n");
        printf("\t\t\t\t             |                             |\n");
        printf("\t\t\t\t             |    [1] Back to staf mode    |\n");
        printf("\t\t\t\t             |                             |\n");
        printf("\t\t\t\t             |    [2] Main Menu            |\n");
        printf("\t\t\t\t             |                             |\n");
        printf("\t\t\t\t             |    [3] Exit                 |\n");
        printf("\t\t\t\t             |                             |\n");
        printf("\t\t\t\t             -------------------------------\n");
        do {
            printf("\t\t\t\t              Enter Your selection      : ");
            scanf("%d", &selection);
            switch (selection) {
            case 1:
                validation = 0;
                system("cls");
                staffMode();
                break;
            case 2:
                validation = 0;
                system("cls");
                modeSel();
                break;
            case 3:
                validation = 0;
                system("cls");
                exit(0);
                break;
            default:
                printf("\n\t\t\t**************************************************************************\n");
                printf("\t\t\t*                   invalid number, please enter again                   *\n");
                printf("\t\t\t**************************************************************************");
                validation = 1;
                break;
            }
        } while (validation == 1);
    }

    return 0;
}

void recordRes() {
    header();
    // validation for student's name
    do {
        printf("Enter student's name: ");
        scanf("%[^\n]", students[numStudent].studentName);
        rewind(stdin);
        if (strlen(students[numStudent].studentName) >= 3 && strlen(students[numStudent].studentName) <= 30) {
            validation = 0;
            for (int x = 0; students[numStudent].studentName[x]; x++) {
                if (isalpha(students[numStudent].studentName[x]) || students[numStudent].studentName[x] == ' ' || students[numStudent].studentName[x] == '/') {
                    validation = 0;
                }
                else {
                    validation = 1;
                    break;
                }
            }
        }
        else
            validation = 1;

        switch (validation) {
        case 1:
            printf("\n\t\t\t**************************************************************************\n");
            printf("\t\t\t*                invalid Student Name, please enter again                *\n");
            printf("\t\t\t**************************************************************************\n\n");
            break;
        default:
            break;
        }
    } while (validation == 1);

    // validation for student's ID
    do {
        printf("\nEnter student's ID : KPKL");
        scanf("%d", &students[numStudent].studentID);
        rewind(stdin);
        if (students[numStudent].studentID < 10000 || students[numStudent].studentID > 99999) {
            printf("\n\t\t\t**************************************************************************\n");
            printf("\t\t\t*               invalid Student ID, please enter 5 numbers               *\n");
            printf("\t\t\t**************************************************************************\n\n");
            validation = 1;
            break;
        }
        else {
            validation = 0;
        }

    } while (validation == 1);

    // validation for current semester session
    do {
        printf("\nEnter current semester session : ");
        scanf("%d", &students[numStudent].currentSem);
        rewind(stdin);
        if (students[numStudent].currentSem >= 1 && students[numStudent].currentSem <= 3) {
            validation = 0;

        }
        else {
            validation = 1;
            printf("\n\t\t\t**************************************************************************\n");
            printf("\t\t\t*          invalid current semester session, please enter again          *\n");
            printf("\t\t\t**************************************************************************\n");
        }
    } while (validation == 1);

    system("cls");

    for (int sem = 0; sem < students[numStudent].currentSem; sem++) {
        displayStudentData();
        printf("\n**************************************************************\n\n");
        printf("\t      ====================================\n");
        printf("\t          Enter details for Semester %d\n", sem + 1);
        printf("\t      ====================================\n\n\n");
        for (int course = 0; course < NUM_COURSES_PER_SEMESTER; course++) {
            // validation for course code
            do {
                if (validation == 0) {
                    printf("   --------------------------------------------------------\n");
                    printf("\t\t\t   Course %d\n", course + 1);
                    printf("   --------------------------------------------------------\n\n");
                }
                printf("        Enter course code\t\t\t  : ");
                scanf("%s", students[numStudent].studentCourses[sem][course].code);
                rewind(stdin);
                if (strlen(students[numStudent].studentCourses[sem][course].code) == 7) {
                    for (int alp = 0; alp < 3; alp++) {
                        if (isupper(students[numStudent].studentCourses[sem][course].code[alp]))
                            validation = 0;
                        else {
                            validation = 1;
                            break;
                        }
                    }
                    if (validation == 0) {
                        for (int dig = 3; dig < 7; dig++) {
                            if (isdigit(students[numStudent].studentCourses[sem][course].code[dig]))
                                validation = 0;
                            else {
                                validation = 1;
                                break;
                            }
                        }
                    }
                }
                else validation = 1;
                switch (validation) {
                case 1:
                    printf("\n**************************************************************\n");
                    printf("*                     invalid course code,                   *\n");
                    printf("*     please enter 3 upper case character and 4 numbers      *\n");
                    printf("**************************************************************\n\n");
                    break;
                default:
                    break;
                }
            } while (validation == 1);
            // validation for credit hours
            do {
                printf("\n        Enter credit hours\t\t\t  : ");
                scanf("%d", &students[numStudent].studentCourses[sem][course].creditHours);
                rewind(stdin);
                if (students[numStudent].studentCourses[sem][course].creditHours == 1 || students[numStudent].studentCourses[sem][course].creditHours == 2 || students[numStudent].studentCourses[sem][course].creditHours == 3 || students[numStudent].studentCourses[sem][course].creditHours == 4 || students[numStudent].studentCourses[sem][course].creditHours == 5) {
                    validation = 0;
                    
                }
                else {
                    validation = 1;
                    printf("\n**************************************************************\n");
                    printf("*          invalid credit hours, please enter again          *\n");
                    printf("**************************************************************\n");
                    
                }
            } while (validation == 1);

            // validation for grade
            do {
                printf("\n        [ A/A-/B+/B/B-/C+/C/F ]");
                printf("\n        Enter grade obtained\t\t\t  : ");
                scanf("%s", students[numStudent].studentCourses[sem][course].grade);
                rewind(stdin);
                if ((strlen(students[numStudent].studentCourses[sem][course].grade) == 1 || strlen(students[numStudent].studentCourses[sem][course].grade) == 2) && isupper(students[numStudent].studentCourses[sem][course].grade[0])) {
                    if (students[numStudent].studentCourses[sem][course].grade[1] == '+' || students[numStudent].studentCourses[sem][course].grade[1] == '-' || students[numStudent].studentCourses[sem][course].grade[1] == NULL){
                        validation = 0;
                    }
                    else {
                        validation = 1;
                        printf("\n**************************************************************\n");
                        printf("*              invalid grade, please enter again             *\n");
                        printf("**************************************************************\n");
                    }
                }
                else
                {
                    validation = 1;
                    printf("\n**************************************************************\n");
                    printf("*              invalid grade, please enter again             *\n");
                    printf("**************************************************************\n");
                }

            } while (validation == 1);

            if (course < NUM_COURSES_PER_SEMESTER - 1)
                printf("\n");
        }
        calQualityPoint();
        calcreditHour();
        calGPA();
        printf("\n\n");
        printf("\t\t      Semester %d Result\n", sem + 1);
        printf("\t\t    =====================\n\n");
        printf("      Total Quality Point\t\t\t : %.2lf\n", students[numStudent].qualityPoint1Sem[sem]);
        printf("      Total Credit Hours \t\t\t : %d\n", students[numStudent].creditHours1Sem[sem]);
        printf("      GPA\t\t\t\t\t : %.2lf\n", students[numStudent].GPAs[sem]);
        char next;
        do {
            printf("\n\nPress press enter to continue...");
            next = getchar();
            
            if (next == '\n') {
                system("cls");
            }
            else while (getchar() != '\n');
        } while (next != '\n');
    }

    calCGPA();
    displayStudentData();
    printf("\n************************************************************\n\n");
    printf("\t\t       GPA Result\n");
    printf("    ====================================================\n");
    for (int sem = 0; sem < students[numStudent].currentSem; sem++) {
        printf("      Semester %d\t\t\t       : %.2f\n", sem + 1, students[numStudent].GPAs[sem]);
    }
    printf("\n\t\t       CGPA Result\n");
    printf("    ====================================================\n");
    printf("      CGPA\t\t\t\t       : %.2f\n", students[numStudent].CGPA);

    students[numStudent].stdRec = 1;
    numStudent++;
    while (1) {
        int back;
        // validation for number of back to menu
        do {
            printf("\n\n\t      --------------------------------\n");
            printf("\t      |           Selection          |\n");
            printf("\t      |------------------------------|\n");
            printf("\t      |                              |\n");
            printf("\t      |   [1] Record next student    |\n");
            printf("\t      |                              |\n");
            printf("\t      |   [2] View Students Result   |\n");
            printf("\t      |                              |\n");
            printf("\t      |   [3] Main Menu              |\n");
            printf("\t      |                              |\n");
            printf("\t      |   [4] Exit                   |\n");
            printf("\t      |                              |\n");
            printf("\t      --------------------------------\n");
            printf("\t         Enter your selection     :");
            scanf("%d", &back);
            rewind(stdin);
            if (back >= 1 && back <= 4) {
                switch (back) {
                case 1:
                    system("cls");
                    recordRes();
                    break;
                case 2:
                    system("cls");
                    viewResult();
                    break;
                case 3:
                    system("cls");
                    modeSel();
                    break;
                case 4:
                    system("cls");
                    exit(0);
                    break;
                default:
                    break;
                }
                validation = 0;
            }
            else {
                validation = 1;
                printf("\n\t\t\t**************************************************************************\n");
                printf("\t\t\t*                 invalid number, please enter 1/2/3/4                   *\n");
                printf("\t\t\t**************************************************************************");
            }
        } while (validation == 1);
    }
    return 0;
}
void displayStudentData() {
    printf("     ------------------------------------------------------\n");
    printf("         Student Name\t\t\t: %s\n", students[numStudent].studentName);
    printf("         Student ID\t\t\t: KPKL%d\n", students[numStudent].studentID);
    printf("         Current semester session\t: Semester %d\n", students[numStudent].currentSem);
    printf("     ------------------------------------------------------\n");
}
