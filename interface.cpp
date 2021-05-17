#include <iostream>
#include <stdlib.h>
#include <conio.h>
/**
    It Only Tell Complier That The Windows is Higher Version That xp / Vista

    By the Help of These I can Use GetConsoleWindow() Function

    Note :- Write This Line Before Including Windows.h Header File
            Otherwise It Doesn't Work
*/
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <dirent.h>
#include <vector>

#include "interface.h"
#include "search.h"
#include "string.h"

#define STANDARD_CONSOLE_SIZE MoveWindow(console,225,50,1080,720,TRUE);
#define CONSOLE_SIZE_FOR_SEARCHED_RESULTS MoveWindow(console,0,0,1550,820,TRUE);



using namespace std;

extern int searchResult;
extern vector<string> searchFilesPath;

void mainMenu()
{
    int choice = 0;
    while(3 != choice)
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tFile Explorer\n\n\n";

        cout << "1.Explore\n";
        cout << "2.Settings\n";
        cout << "3.Exit\n\n";

        cout << "Enter Your Choice\n";
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                explore();
                break;
            }
            case 2:
            {
                colorMenu();
                break;
            }
            case 3:
            {
                break;
            }
            default:
            {
                cout << "\nInvalid Choice :(\nTry again\nPress Any Key To Continue\n";
                getch();
                break;
            }
        }
    }
}

///Explore

void explore()
{
    int choice = 0,result = 1;
    char path[MAX_PATH_SIZE],fileName[MAX_FILE_NAME],newFileName[MAX_FILE_NAME],tempPath[MAX_PATH_SIZE],ch;
    bool flag = true;

    while(NULL != selectDrive(path))
    {
        do
        {
            choice = 9999;
            system("cls");
            cout << "Current Path = " << path << endl << endl;
            if(true == flag)
            {
                result = listDirectoryOrFile(path);
            }
            else
            {
                flag = true;
            }

            if(-1 == result)
            {
                if(0 != previousPath(path))
                {
                    break;
                }
            }
            else if(isFile(path))
            {
                getFileName(path,fileName);

                while(4 != choice)
                {
                    system("cls");
                    cout << "Selected File = " << fileName << endl << endl;
                    cout << "Select Operation That You Want To Perform On File\n\n";
                    cout << "1.Open\n";
                    cout << "2.Rename\n";
                    cout << "3.Delete\n";
                    cout << "4.Go Back\n";
                    cout << "\nEnter Your Choice\n";
                    cin >> choice;
                    switch(choice)
                    {
                        case 1:                                                         /// Open File
                        {
                            if(openFile(path))
                            {
                                system("cls");
                                cout << "File Opened Successfully\n";
                            }
                            else
                            {
                                system("cls");
                                cout << "Unable To Open File\n";
                            }

                            Sleep(1000);

                            choice = 4;
                            break;
                        }
                        case 2:                                                          /// Rename
                        {
                            cout << "Enter New Name\n";
                            cin >> newFileName;

                            stringCopy(tempPath,path);
                            previousPath(tempPath);
                            stringConcate(tempPath,"\\");
                            stringConcate(tempPath,newFileName);

                            if(!rename(path,tempPath))
                            {
                                system("cls");
                                cout << "Name SuccessFully Changed...\n";
                            }
                            else
                            {
                                cout << "Error\n";
                            }

                            Sleep(1000);

                            choice = 4;
                            break;
                        }
                        case 3:                                                          /// Delete Using Windows.h Function (Remove)
                        {
                            if(!remove(path))
                            {
                                system("cls");
                                cout << "Deleted Successfully...\n";
                            }
                            else
                            {
                                cout << "Error\n";
                            }

                            Sleep(1000);

                            choice = 4;
                            break;
                        }
                        case 4:                                                          /// Go Back
                        {
                            break;
                        }
                        default:
                        {
                            cout << "\nInvalid Choice :(\nTry again\n";
                            break;
                        }
                    }
                    previousPath(path);
                }
            }
            else if(0 == result)
            {
                while(6 != choice)
                {
                    system("cls");
                    cout << "Selected Folder = " << path << endl << endl;
                    cout << "Select Operation That You Want To Perform On Folder\n\n";
                    cout << "1.Open\n";
                    cout << "2.Create\n";
                    cout << "3.Delete\n";
                    cout << "4.Rename\n";
                    cout << "5.Search\n";
                    cout << "6.Go Back\n";
                    cin >> choice;
                    switch(choice)
                    {
                        case 1:                                                          /// open
                        {
                            choice = 6;
                            break;
                        }
                        case 2:                                                          /// Create New Folder
                        {
                            char folderName[MAX_FILE_NAME];
                            cout << "Enter The Name Of Folder\n";
                            cin >> folderName;

                            stringConcate(path,"\\");
                            stringConcate(path,folderName);

                            if(!mkdir(path))
                            {
                                system("cls");
                                cout << "Folder Successfully Created...";
                            }
                            else
                            {
                                cout << "Folder Already Exist Or Invalid Folder Name\n";
                            }
                            previousPath(path);
                            Sleep(1000);

                            choice = 6;
                            break;
                        }
                        case 3:                                                          /// Delete Using Windows.h Function (System)
                        {                                                                /// By The Help Of CMD Command RD /S /Q "Path"
                            getFileName(path,fileName);
                            system("cls");
                            cout << "It Permanently Delete (" << fileName << ")\n";
                            cout << "Are You Sure (Y / N)\n";
                            do
                            {
                                ch = getch();
                                if('Y' == ch || 'y' == ch)
                                {
                                    stringConcate(tempPath,"RD /S /Q \"");
                                    stringConcate(tempPath,path);
                                    stringConcate(tempPath,"\"");

                                    system(tempPath);
                                    cout << "Folder SuccessFully deleted...\n";
                                    previousPath(path);
                                    Sleep(1000);
                                    ch = 'n';
                                }
                                if('n' == ch || 'N' == ch)
                                {
                                    break;
                                }
                            }while(1);
                            choice = 6;
                            break;
                        }
                        case 4:                                                          /// Rename
                        {
                            cout << "Enter New Name\n";
                            cin >> newFileName;

                            stringCopy(tempPath,path);
                            previousPath(tempPath);
                            stringConcate(tempPath,"\\");
                            stringConcate(tempPath,newFileName);

                            if(!rename(path,tempPath))
                            {
                                system("cls");
                                cout << "Name SuccessFully Changed...\n";
                                stringCopy(path,tempPath);
                            }
                            else
                            {
                                cout << "Error\n";
                            }
                            Sleep(1000);
                            choice = 6;

                            break;
                        }
                        case 5:                                                          /// Search
                        {
                            system("cls");
                            cout << "Enter File Name That You Want To Search In Path = " << path << endl;
                            cin >> fileName;
                            cout << "\n\n";

                            HWND console = GetConsoleWindow();
                            CONSOLE_SIZE_FOR_SEARCHED_RESULTS

                            search(path,fileName);
                            cout << "\n----------------\n";
                            cout << searchResult << " Result Found";
                            cout << "\n----------------\n";

                            cout << "-1.Go Back\n";
                            cout << "Enter Your Choice\n";

                            while(-1 != choice)
                            {
                                cin >> choice;
                                /// Valid Choice
                                if(choice > 0 && choice <= searchResult)
                                {
                                    stringCopy(path,searchFilesPath[choice - 1]);
                                    flag = false;
                                    break;
                                }
                                /// InValid Choice
                                else
                                {
                                    cout << "Invalid Choice :( Try Again\n";
                                }
                            }
                            searchResult = 0;
                            searchFilesPath.clear();
                            choice = 6;

                            STANDARD_CONSOLE_SIZE

                            break;
                        }
                        case 6:                                                          /// Go Back
                        {
                            break;
                        }
                        default:
                        {
                            cout << "\nInvalid Choice :(\nTry again";
                            break;
                        }
                    }
                }
            }

        }while(1);

    }

    return;
}

/// It Detect Extension Of File And Open File With Its Suitable Executable Program
/// Return Greater Value Than 32 When Open File SuccessFully
/// Else Return Smaller
int openFile(char *file)
{
    char newpath[MAX_PATH_SIZE] = "\"",executable[MAX_PATH_SIZE];

    stringCopy(executable,file);

    /// Adding quotes In File Name
    /// Example FileName = notes.txt
    /// To "notes.txt"
    stringConcate(newpath,file);
    stringConcate(newpath,"\"");

    return int(ShellExecute(0,"open",executable,newpath,NULL,SW_SHOW));
}

/// It Give Extension Of File
/// 1st Parameter Contain File Name And Second Contain That extension
void getExtension(char *file,char *extension)
{
    int counter = 0,i = 0;

    ///find The Last Occurrence Of Dot
    for(counter = stringLength(file) - 1;'.' != file[counter];counter--)
    {

    }

    extension[0] = file[counter];
    ///Copy The Extension From File To extension
    for(i = 1;'\0' != file[i + counter];i++)
    {
        extension[i] = file[i + counter];
    }
    extension[i] = '\0';

    return;
}

///It Provide File Name Of The Which Is Selected By Path
void getFileName(char *path,char *fileName)
{
    int counter = 0,i = 0;

    ///find The Last Occurrence Of BackSlash
    for(counter = stringLength(path) - 1;'\\' != path[counter];counter--)
    {

    }
    counter++;

    ///Copy The FileName From Path To FileName(variable)
    for(i = 0;NULL != path[i + counter];i++)
    {
        fileName[i] = path[i + counter];
    }
    fileName[i] = '\0';

    return;
}

/// Return TRUE If Parameter Contain a Path Of File
/// Else Return FALSE
bool isFile(char *path)
{
    return !opendir(path);
}

///Search Menu

//void searchMenu()
//{
//    cout << "\nEnter File Name That You Want To Search In Path = " << path << endl;
//    //cin >> fileName;
//    cout << "\n\n";
//
//    int len = GetLogicalDriveStrings(DRIVE_NAME_SIZE,driveNames);
//
//    ///search In All Drives One By One
//    for(int i = 0;i < len;i+=4)
//    {
//        path[0] = driveNames[i];
//        path[1] = driveNames[i+1];
//        path[2] = driveNames[i+2];
//        path[3] = driveNames[i+2];
//        path[3] = '\0';
//        search(path,fileName);
//    }
//
//    cout << "\n----------------\n";
//    cout << searchResult << " Result Found";
//    cout << "\n----------------\n";
//    cout << "\nPress Enter Key To Go Back In Main Menu\n";
//    getch();
//    return;
//}

/// List All Files And Folder Which Is Present In Path(1st Parameter)
/// It Return 1 For Further Search
/// It Return 0 When Path Is Selected
/// It Return -1 When It Gives Previous Path
int listDirectoryOrFile(char *path)
{
    int subFolderIndex[1000],size = 0,counter = 1,choice = 0,status = -5;

    dirent *directoryEntry;
    DIR *dptr = opendir(path);

    while(NULL != (directoryEntry = readdir(dptr)))
    {
        if(stringCompare(directoryEntry->d_name,".") && stringCompare(directoryEntry->d_name,".."))
        {
            cout << size + 1 << ". " << directoryEntry->d_name << endl;
            subFolderIndex[size++] = counter;
        }
        counter++;
    }

    while(1)
    {
        cout << "\nEnter Your Choice\n";
        cout << "\n0.To Select Current Directory Or Folder\n";
        cout << "-1.Go In Previous Directory\n";
        cin >> choice;
        if(choice <= size && 0 < choice)
        {
            dptr = opendir(path);
            directoryEntry = readdir(dptr);
            seekdir(dptr,subFolderIndex[choice - 1]);
            stringConcate(path,"\\");
            stringConcate(path,directoryEntry->d_name);

            status = 1; /// Go For Further Search
            break;
        }
        else if(0 == choice)
        {
            status = 0; /// File Selected
            break;
        }
        else if(-1 == choice)
        {
            status = -1; /// Demand For Previous Path
            break;
        }
        else
        {
            cout << "\nInvalid Choice :(\nTry again\n";
        }
    }

    closedir(dptr);
    return status;
}

/// It Calculate Previous Path Of a Path
/// Return 0 When SuccessFully Give Previous Path
/// return -1 When There Is No Previous Path Present

int previousPath(char *path)
{
    int length = stringLength(path);
    int i = 0;

    if(4 < length)
    {
        for(i = length - 1;'\\' != path[i];i--)
        {

        }
        path[i] = '\0';
        return 0;
    }

    return -1;
}

/// ->It Prints All Drive Letter In Console And Take Input From User For A Particular Drive
///   And If The Input Is Valid Then It Return Path That Is Pointing To That Particular Drive
///   Which User Select

///   If User Enter 0 Then It Normally Return NULL
///   Design Issue
char *selectDrive(char *path)
{
    system("cls");
    char driveNames[DRIVE_NAME_SIZE];
    int len = GetLogicalDriveStrings(DRIVE_NAME_SIZE,driveNames),choice = 0;

    cout << "Select Drive->\n\n";

    if(0 < len)
    {
        for(int i = 0;i < len;i+=4)
        {
            cout << i/4 + 1 << ". " << driveNames[i] << driveNames[i+1] << driveNames[i+2] << endl;
        }
        cout << "\nPress -1 To Back In Main Menu\n";
        while(1)
        {
            cout << "\nEnter Your Choice\n";
            cin >> choice;
            if(0 < choice && choice * 4 <= len)
            {
                int key = (choice - 1) * 4;
                path[0] = driveNames[key];
                path[1] = driveNames[key + 1];
                path[2] = driveNames[key + 2];
                path[3] = '\0';
                return path;
            }
            else if(-1 == choice) ///User Does Not Want To Select File
            {
                return NULL;
            }
            else
            {
                cout << "\nInvalid Choice :(\nTry again\nPress Any To Retry...\n";
                getch();
            }
        }
    }
    return NULL;
}

/// #Color Related Work
/// ->Color Menu
void colorMenu()
{
    int choice = 0;
    char colorCode = '\0';

    while(3 != choice)
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tSettings\n\n\n";

        cout << "1.text Color\n";
        cout << "2.Background Color\n";
        cout << "3.Previous Menu\n\n";

        cout << "Enter Your Choice\n";
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                system("cls");
                colorInfo();
                cout << "Enter Color Code\n";
                cin >> colorCode;
                if(!changeColor(colorCode,FOREGROUND))
                {
                    cout << "Text Color Successfully Changed\n";
                }
                else
                {
                    cout << "Error In Changing Text Color\nPlease Contact Administrator\n\n";
                }
                cout << "Press Any Key To Continue...\n";
                getch();
                return;
            }
            case 2:
            {
                system("cls");
                colorInfo();
                cout << "Enter Color Code\n";
                cin >> colorCode;
                if(!changeColor(colorCode,BACKGROUND))
                {
                    cout << "Background Color Successfully Changed\n";
                }
                else
                {
                    cout << "Error In Changing Background Color\nPlease Contact Administrator\n\n";
                }
                cout << "Press Any Key To Continue...\n";
                getch();
                return;
            }
            case 3:
            {
                break;
            }
            default:
            {
                cout << "\nInvalid Choice :(\nTry again\nPress Any To Retry...\n";
                getch();
                break;
            }
        }
    }
    return;
}

/// ->It Change BackGround Color If Mode = 1
/// ->And Change Text Color If Mode = 2
/// ->It Gives Error When Color Code And Mode Is Not Valid

int changeColor(char colorCode,int mode)    ///First = BackGround , Second = Text Color
{
    FILE *fptr = fopen("C:\\File Explorer\\color.txt","r+");
    int status = -1;
    if(NULL != fptr)
    {
        char colorCommand[] = "color   ";

        colorCommand[5 + mode] = colorCode;

        if(2 == mode)
        {
            fseek(fptr,6,0);
            colorCommand[6] = fgetc(fptr);
        }
        else
        {
            fseek(fptr,7,0);
            colorCommand[7] = fgetc(fptr);
        }

        fseek(fptr,5 + mode,0);
        fputc(colorCommand[5 + mode],fptr);

        system(colorCommand);

        fclose(fptr);
        status = 0;
    }
    else
    {
        status = -1;
    }

    return status;
}

/// ->It Prints Color Code

void colorInfo()
{
    printf("\n");
    printf("0 = Black  \t 8 = Gray\n");
    printf("1 = Blue   \t 9 = Light Blue\n");
    printf("2 = Green  \t A = Light Green\n");
    printf("3 = Aqua   \t B = Light Aqua\n");
    printf("4 = Red    \t C = Light Red\n");
    printf("5 = Purple \t D = Light Purple\n");
    printf("6 = Yellow \t E = Light Yellow\n");
    printf("7 = White  \t F = Bright White\n\n");
}

/// #Constructor

void prepareEnviroment()
{
    HWND console = GetConsoleWindow();
    STANDARD_CONSOLE_SIZE
    SetConsoleTitle("File Explorer");

    FILE *fptr = fopen("C:\\File Explorer\\color.txt","r");
    char colorCode[10] = "color   ";

    if(NULL != fptr)
    {
        fseek(fptr,6,0);

        for(int counter = 6;counter <= 7;counter++)
        {
            colorCode[counter] = fgetc(fptr);
        }

        fclose(fptr);
    }
    else
    {
        mkdir("C:\\File Explorer");
        fptr = fopen("C:\\File Explorer\\color.txt","w");

        colorCode[6] = '3';
        colorCode[7] = 'e';

        fputs(colorCode,fptr);

        fclose(fptr);

    }
    system(colorCode);
}
