#include <iostream>
using namespace std;

#include <dirent.h>
#include <vector>

#include "search.h"
#include "string.h"

vector<string> searchFilesPath;
int searchResult = 0,size = 0;
int lps[MAX_FILE_NAME];

void search(char *path,char *filename)
{
    size = stringLength(filename);
    calculate_LPS(filename,lps,size);
    searchDirectory(path,filename);
}

///Search For Particular File In Directory
void searchDirectory(char *path,char *filename)
{
    dirent *directoryEntry = NULL;
    DIR *dptr = opendir(path);

    if(NULL == path)
    {
        return;
    }

    char newpath[MAX_PATH_SIZE];

    while(NULL != (directoryEntry = readdir(dptr)))
    {
        if(stringCompare(directoryEntry->d_name,".") && stringCompare(directoryEntry->d_name,".."))
        {
            if(-1 < kmp_isSubStringPresent(directoryEntry->d_name,filename,lps))
            {
                cout << ++searchResult << ". "<< directoryEntry->d_name << "\t\t" << path << endl;

                /// Getting Path Of Searched Result
                stringCopy(newpath,path);
                stringConcate(newpath,"\\");
                stringConcate(newpath,directoryEntry->d_name);

                /// Storing Search Result Path
                searchFilesPath.push_back(newpath);
            }

            stringCopy(newpath,path);
            stringConcate(newpath,"\\");
            stringConcate(newpath,directoryEntry->d_name);

            searchDirectory(newpath,filename);
        }
    }

    closedir(dptr);
    return;
}
