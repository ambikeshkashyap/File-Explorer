///Main Interface
void mainMenu();

///Explore
void explore();

/// color Related Work
#define FOREGROUND 2
#define BACKGROUND 1

void colorMenu();

void colorInfo();

int changeColor(char ,int );

/// path Selection Work
#define DRIVE_NAME_SIZE 100

char *selectDrive(char *);

/// It Calculate Previous Path Of a Path
/// Return 0 When SuccessFully Give Previous Path
/// return -1 When There Is No Previous Path Present
int previousPath(char *);

/// List All Files And Folder Which Is Present In Path(1st Parameter)
/// It Return 1 For Further Search
/// It Return 0 When Path Is Selected
/// It Return -1 When It Gives Previous Path
int listDirectoryOrFile(char *);

/// Set Environment
/// Executes Before Main
void prepareEnviroment() __attribute__((constructor));

/// Return TRUE If Parameter Contain a Path Of File
/// Else Return FALSE
bool isFile(char *);

/// It Provide The FileName In 2nd Parameter(Char Array)
/// Of File Which Is Pointed \ Addressed By 1st Parameter
void getFileName(char *,char *);

/// It Detect Extension Of File And Open File With Its Suitable Executable Program
/// Return Greater Value Than 32 When Open File SuccessFully
/// Else Return Smaller
int openFile(char *);

/// It Give Extension Of File
/// 1st Parameter Contain File Name And Second Contain That extension
void getExtension(char *,char *);
