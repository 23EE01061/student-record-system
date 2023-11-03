#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Used macro
#define max_yr  9999
#define min_yr  1990

#define max_size_user_name 30
#define max_size_password  20
#define FILE_NAME  "StudentRecordSystem.bin"
// Macro related to the students info
#define max_father_name 50
#define max_student_name 50
#define max_student_address 300
#define max_student_gender 300
#define max_student_branch 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[max_size_user_name];
    char password[max_size_password];
} sFileHeader;
//Elements of structure
typedef struct// to call in program
{
    char fatherName[max_father_name];// declare the character data type
    char studentName[max_student_name];// declare the character data type
    char studentAddr[max_student_address];// declare the character data type
    char studentBranch[max_student_branch];// declare the character data type
    char studentGender[max_student_gender];// declare the character data type
    Date studentbirthdate;// declare the integer data type
    unsigned int student_id; // declare the integer data type
    float studentfees;
} s_studentsInfo;
//Align the message
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//Head message
void headMessage(const char *message)
{
    system("cls");
    printf("%s\t\t\t***************************************************************************","\x1B[34m");
    printf("%s\n\t\t\t************                                                   ************","\x1B[33m");
    printf("\n\t\t\t************             STUDENT RECORD MANAGEMENT             ************");
    printf("\n\t\t\t************                                                   ************");
    printf("%s\n\t\t\t***************************************************************************","\x1B[34m");
    printf("\n\t\t\t---------------------------------------------------------------------------%s\n","\x1B[33m");
    printMessageCenter(message);
    printf("%s\n\t\t\t---------------------------------------------------------------------------","\x1B[34m");
}
//Display message
void welcomeMessage()
{
    
    printf("\n\n\n\n\n");
    printf("%s\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**","\x1B[36m");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("%s\n\t\t\t        =                  WELCOME                  =","\x1B[35m");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Student Record              =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("%s\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=","\x1B[36m");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("%s\n\n\n\t\t\t Enter any key to continue.....","\x1B[32m");
    getch();
}
//Validate name
int ValidName(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > max_yr ||
            validDate->yyyy < min_yr)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add student in list
void addstudentInDataBase()
{
    int x=0;
    s_studentsInfo addstudentInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW studentS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    int num;
    do
    {
        
        printf("%s\n\t\t\tstudent ID  = ","\x1B[32m");
        fflush(stdin);
        num=scanf("%u",&addstudentInfoInDataBase.student_id);
        if (num!= 1) {
        printf("\n\t\t\t%sStudent ID contain invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        } 
    } while (num != 1);
    do
    {
        printf("\n\t\t\tFather Name  = ");
        fflush(stdin);
        fgets(addstudentInfoInDataBase.fatherName,max_father_name,stdin);
        status = ValidName(addstudentInfoInDataBase.fatherName);
        if (!status)
        {
            printf("\n\t\t\t%sName contain invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tstudent Name  = ");
        fflush(stdin);
        fgets(addstudentInfoInDataBase.studentName,max_student_name,stdin);
        status = ValidName(addstudentInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\t%sName contain invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        }
    }
    while(!status);
    
    
    

    
    
    printf("\n\t\t\tstudent Address  = ");
    fflush(stdin);
    fgets(addstudentInfoInDataBase.studentAddr,max_student_address,stdin);
    status = ValidName(addstudentInfoInDataBase.studentAddr);
        
       
    
    
       do
    {
        printf("\n\t\t\tstudent Branch  = ");
        fflush(stdin);
        fgets(addstudentInfoInDataBase.studentBranch,max_student_branch,stdin);
        status = ValidName(addstudentInfoInDataBase.studentBranch);
        if (!status)
        {
            printf("\n\t\t\t%sBranch Name contains invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        }
    }
    while(!status);
       do
    {
        printf("\n\t\t\tstudent Gender  = ");
        fflush(stdin);
        fgets(addstudentInfoInDataBase.studentGender,max_student_gender,stdin);
        status = ValidName(addstudentInfoInDataBase.studentGender);
        if (!status)
        {
            printf("\n\t\t\t%sYour entry contains invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        }
    }
    while(!status);
    
    
    do
    {
        
        printf("\n\t\t\tstudent fees  = ");
        fflush(stdin);
        num=scanf("%f",&addstudentInfoInDataBase.studentfees);
        if (num!= 1) {
        printf("\n\t\t\t%sYour entry contains invalid character. Please enter again.%s","\x1B[31m","\x1B[32m");
        } 
    } while (num != 1);
    do
    {
        
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        fflush(stdin);
        scanf("%d/%d/%d",&addstudentInfoInDataBase.studentbirthdate.dd,&addstudentInfoInDataBase.studentbirthdate.mm,&addstudentInfoInDataBase.studentbirthdate.yyyy);
        //check date validity
        status = isValidDate(&addstudentInfoInDataBase.studentbirthdate);
        if (!status)
        {
            printf("\n\t\t\t%sPlease enter a valid date.%s","\x1B[31m","\x1B[32m");
        }
    }
    while(!status);
    fwrite(&addstudentInfoInDataBase,sizeof(addstudentInfoInDataBase), 1, fp);
    fclose(fp);
}
// search student
void searchstudent()
{
    int found = 0;
    int studentId =0;
    s_studentsInfo addstudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH student");
    //put the control on student detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter student ID NO to search:");
    fflush(stdin);
    scanf("%u",&studentId);
    printf("\n\t\t\t----------------------------------------------------------------------------");
    while (fread (&addstudentInfoInDataBase, sizeof(addstudentInfoInDataBase), 1, fp))
    {
        if(addstudentInfoInDataBase.student_id == studentId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("%s","\x1B[36m");
        printf("\n\t\t\tstudent id = %u\n",addstudentInfoInDataBase.student_id);
        printf("\t\t\tstudent Name = %s",addstudentInfoInDataBase.studentName);
        printf("\t\t\tstudent fees = %f\n",addstudentInfoInDataBase.studentfees);
        printf("\t\t\tFather Name = %s",addstudentInfoInDataBase.fatherName);
        printf("\t\t\tstudent Address = %s",addstudentInfoInDataBase.studentAddr);
        printf("\t\t\tstudent DATE OF BIRTH(day/month/year) =  (%d/%d/%d)\n",addstudentInfoInDataBase.studentbirthdate.dd,
               addstudentInfoInDataBase.studentbirthdate.mm, addstudentInfoInDataBase.studentbirthdate.yyyy);
        printf("\t\t\tstudent Branch = %s",addstudentInfoInDataBase.studentBranch);
        printf("\t\t\tstudent Gender = %s",addstudentInfoInDataBase.studentGender);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("%s\n\n\n\t\t\tPress any key to go to main menu.....","\x1B[32m");
    fflush(stdin);
    getchar();
}
// view students function
void viewstudent()
{
    int found = 0;
    s_studentsInfo addstudentInfoInDataBase = {0};
    FILE *fp = NULL;
    unsigned int countstudent = 1;
    headMessage("VIEW student DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    //Print student records
    while (fread (&addstudentInfoInDataBase, sizeof(addstudentInfoInDataBase), 1, fp))
    {
        printf("%s","\x1B[36m");
        printf("\n\t\t\tstudent id = %u\n",addstudentInfoInDataBase.student_id);
        printf("\t\t\tstudent Name = %s",addstudentInfoInDataBase.studentName);
        printf("\t\t\tstudent fees = %f\n",addstudentInfoInDataBase.studentfees);
        printf("\t\t\tFather Name = %s",addstudentInfoInDataBase.fatherName);
        printf("\t\t\tstudent Address = %s",addstudentInfoInDataBase.studentAddr);
        printf("\t\t\tstudent DATE OF BIRTH(day/month/year) =  (%d/%d/%d)\n",addstudentInfoInDataBase.studentbirthdate.dd,
               addstudentInfoInDataBase.studentbirthdate.mm, addstudentInfoInDataBase.studentbirthdate.yyyy);
        printf("\t\t\tstudent Branch = %s",addstudentInfoInDataBase.studentBranch);
        printf("\t\t\tstudent Gender = %s",addstudentInfoInDataBase.studentGender);
        found = 1;
        ++countstudent;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("%s\n\n\t\t\tPress any key to go to main menu.....","\x1B[32m");
    fflush(stdin);
    getchar();
}
// Delete student entry
void deletestudent()
{
    int found = 0;
    int studentDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_studentsInfo addstudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("Delete student Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter student ID NO. for delete:");
    scanf("%d",&studentDelete);
    while (fread (&addstudentInfoInDataBase, sizeof(addstudentInfoInDataBase), 1, fp))
    {
        if(addstudentInfoInDataBase.student_id != studentDelete)
        {
            fwrite(&addstudentInfoInDataBase,sizeof(addstudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
//function to update credential
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[max_size_user_name] = {0};
    unsigned char password[max_size_password] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,max_size_user_name,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,max_size_password,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\t Try Login again ...");
    fflush(stdin);
    getchar();
    exit(1);
}
//Display menu
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("%s\n\n\n\t\t\t1.Add student","\x1B[36m");
        printf("\n\t\t\t2.Search student");
        printf("\n\t\t\t3.View student");
        printf("\n\t\t\t4.Delete student");
        printf("\n\t\t\t5.Update Password");
        printf("\n\t\t\t0.logout");
        printf("%s\n\n\n\t\t\tEnter choice => ","\x1B[34m");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addstudentInDataBase();
            break;
        case 2:
            searchstudent();
            break;
        case 3:
            viewstudent();
            break;
        case 4:
            deletestudent();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
//login password
void login()
{
    unsigned char userName[max_size_user_name] = {0};
    unsigned char password[max_size_password] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,max_size_user_name,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,max_size_password,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//Check file exist or not
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="admin\n";
    const char defaultPassword[] ="iitbbs\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    system("cls");
    init();
    welcomeMessage();
    login();
    return 0;
}