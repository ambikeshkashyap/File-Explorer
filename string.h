/// Copy The Contained Of Source String In Destination String
/// 1st Parameter Destination
/// 2nd Parameter Source
void stringCopy(char *,char *);

void stringCopy(char *destination,std :: string source);

char* stringConcate(char *,char *);

int stringLength(char *str);

/// It return Lower Case Of Given Character
char getLower(char );

/// It return Upper Case Of Given Character
char getUpper(char );

/// Compare Two String
/// if String Match Return 0
/// otherwise       Return 1
int stringCompare(char *,char *);

int isSubStringPresent(char *,char *); ///Naive Algorithm(Basic Algorithm) O(M*N)

void calculate_LPS(char *,int *,int);  /// Table For KMP Algorithm(LPS)

int kmp_isSubStringPresent(char *,char *,int *);
