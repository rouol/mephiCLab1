#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// constraints
char empty = '\0'; // empty char element
int N = 100; // max input string size
int max_command_len = 10;

// base
void Error(const char* msg)
{
    printf(msg);
    printf("\n");
    system("pause");
    exit(0);
}

// array structure
typedef struct Array {
    void* buffer;
    int count;
    int elem_size;
} Array;

// array functions
Array* CreatefromBuffer(int count, int elem_size, void* buffer) {

    Array* arr = (Array*)malloc(sizeof(Array));
    arr->count = count - 1;
    arr->elem_size = elem_size;
    arr->buffer = malloc(count * elem_size);

    memcpy(arr->buffer, buffer, count * elem_size);

    return arr;
}

void SetElement(Array* arr, int index, void* value) {
    void* p = (char*)arr->buffer + index * arr->elem_size;
    memcpy(p, value, arr->elem_size);
}

Array* Create(int count, int elem_size, void* default_elem) {

    Array* arr = (Array*)malloc(sizeof(Array));
    arr->count = count - 1;
    arr->elem_size = elem_size;
    arr->buffer = malloc(count * elem_size);

    for (int i = 0; i < count; i++)
        SetElement(arr, i, default_elem);

    return arr;
}

Array* CreateString(int count) {
    return Create(count, sizeof(char), &empty);
}

/* string functions */

// main-independent functions
char* GetCharfromArray(Array* arr) {

    char* str = (Array*)malloc(arr->count * sizeof(char));
    memcpy(str, arr->buffer, arr->count * sizeof(char));

    return str;
}

char GetArrElementStr(Array* arr, int index) {
    return (index >= 0 && index < arr->count) ? *((char*)arr->buffer + index) : NULL;
}

Array* ConcatStr(Array* strA, Array* strB) {

    // create new string
    void* bufferA = strA->buffer;
    void* bufferB = strB->buffer;

    int strA_count = strA->count;
    int strB_count = strB->count;

    int newstr_count = strA_count + strB_count;
    int newstr_elem_size = strA->elem_size;

    Array* new_str = CreateString(newstr_count);
    new_str->count = newstr_count;
    new_str->elem_size = newstr_elem_size;
    //new_str->buffer = malloc(newstr_count * newstr_elem_size);

    // copy data
    memcpy(new_str->buffer, bufferA, strA_count * sizeof(char));
    memcpy((char*)new_str->buffer + strA_count * sizeof(char), bufferB, strB_count * sizeof(char));

    return new_str;
}

Array* SliceStr(Array* str, int i, int j) {
    // define params
    int newstr_count = abs(j - i) + 1;
    int str_count = str->count;
    int newstr_elem_size = str->elem_size;

    // create new string
    Array* new_str = CreateString(newstr_count);
    new_str->count = newstr_count;
    new_str->elem_size = newstr_elem_size;
    //new_str->buffer = malloc(newstr_count * newstr_elem_size);

    // copy data
    memcpy(new_str->buffer, (char*)str->buffer + i * newstr_elem_size, newstr_count * newstr_elem_size);

    return new_str;
}

// destructors

void Deleteptr(void* p)
{
    if (!p)
        system("cls"), Error("Attempt to free null pointer");
    free(p);
    p = NULL;
}

void DeleteArray(Array* arr)
{
    if (!arr)
        system("cls"), Error("Attempt to free null pointer");

    Deleteptr(arr->buffer);
    Deleteptr(arr);
    arr = NULL;
}

// other
int countChar(char* str) {
    char* element = str;
    int count = 0;
    while (*element++ != '\0')
        count++;
    return count;
}

Array* CreatefromChar(char* charBuffer) {
    return CreatefromBuffer(countChar(charBuffer) + 1, sizeof(char), charBuffer);
}

Array* inputStr()
{
    printf("input string: ");

    char* input = (char*)malloc(N * sizeof(char));
    gets(input);

    return CreatefromChar(input);
}

void printStr(Array* str)
{
    for (int i = 0; i < str->count; i++)
        printf("%c", GetArrElementStr(str, i));
    printf("\n");
}

int isEqualStr(Array* strA, Array* strB, int method)
{
    int strA_count = strA->count;
    int strB_count = strB->count;

    // check emptyness
    if (strA_count == 0 && strB_count == 0)
        return 1;
    else if (strA_count == 0 || strB_count == 0)
        return 0;

    // check if size is different
    if (strA_count != strB_count) {
        return 0;
    }
    // if equal size
    else {
        switch (method)
        {
        case 1:
            for (int i = 0; i < strA_count; i++)
                if (GetArrElementStr(strA, i) != GetArrElementStr(strB, i))
                    return 0;
            return 1;
            break;
        case 2:
            for (int i = 0; i < strA_count; i++)
                if (tolower(GetArrElementStr(strA, i)) != tolower(GetArrElementStr(strB, i)))
                    return 0;
            return -1;
            break;
        default:
            return 0;
            break;
        }
    }
}

char GetCharElement(char* str, int index) {
    return (index >= 0 && index < countChar(str)) ? *((char*)str + index) : NULL;
}

int isEqualChar(char* strA, char* strB, int method)
{
    int strA_count = countChar(strA);
    int strB_count = countChar(strB);

    // check emptyness
    if (strA_count == 0 && strB_count == 0)
        return 1;
    else if (strA_count == 0 || strB_count == 0)
        return 0;

    // check if size is different
    if (strA_count != strB_count) {
        return 0;
    }
    // if equal size
    else {
        switch (method)
        {
        case 1:
            for (int i = 0; i < strB_count; i++)
                if (GetCharElement(strA, i) != GetCharElement(strB, i))
                    return 0;
                return 1;
            break;
        case 2:
            for (int i = 0; i < strB_count; i++)
                if (tolower(GetCharElement(strA, i)) != tolower(GetCharElement(strB, i)))
                    return 0;
                return -1;
            break;
        default:
            return 0;
            break;
        }
    }
}

char* findChar(char* str, char* substr, int method)
{
    // methods:
    // 1 - size matter
    // 2 - size doesn't matter

    int str_count = countChar(str);
    int substr_count = countChar(substr);

    if (str_count == 0) {
        return -1;
    }

    // check if substr is bigger
    if (substr_count > str_count) {
        return 0;
    }
    else if (substr_count == str_count) {
        isEqualChar(str, substr, method);
    }
    else {


        switch (method)
        {
        case 1:
            for (int i = 0; i < substr_count; i++) {
                if (GetCharElement(str, i) != GetCharElement(substr, i)) {
                    str++;
                    return findChar(str, substr, method);
                }
            }
            return str;
            break;
        case 2:
            for (int i = 0; i < substr_count; i++) {
                if (tolower(GetCharElement(str, i)) != tolower(GetCharElement(substr, i))) {
                    str++;
                    return findChar(str, substr, method);
                }
            }
            return str;
            break;
        default:
            return 0;
            break;
        }
    }
}

int SearchStr(Array* str, Array* substr, int method)
{
    // methods:
    // 1 - size matter
    // 2 - size doesn't matter

    //check if substr is bigger
    if (substr->count > str->count)
        return -1;
    
    // if equal
    if (abs(isEqualStr(str, substr, method)))
        return 0;

    // usual algo
    void* insertion = findChar(str->buffer, substr->buffer, method);

    if (insertion == 0)
        return -1;
    else
        return (int)((char*)insertion - (char*)str->buffer);
}

// tests
int test() {
    // isEqualStr
    {
        char* str1 = "123";
        char* wrongstr = "ddd";
        Array* str1A = CreatefromChar(str1);
        Array* wrongstrA = CreatefromChar(wrongstr);
        if (
            (isEqualStr(str1A, str1A, 1)) &&
            (!isEqualStr(str1A, wrongstrA, 1))
            ) {
            DeleteArray(str1A);
            DeleteArray(wrongstrA);
            printf("isEqualStr - ok\n");
        }
        else {
            DeleteArray(str1A);
            DeleteArray(wrongstrA);
            return 0;
        }
    }
    // test ConcatStr
    {
        char* str1 = "123";
        char* str2 = "456";
        char* str12 = "123456";
        Array* str1A = CreatefromChar(str1);
        Array* str2A = CreatefromChar(str2);
        Array* str12A = CreatefromChar(str12);
        Array* concatstr = ConcatStr(str1A, str2A);
        if (isEqualStr(concatstr, str12A, 1)) {
            DeleteArray(str1A);
            DeleteArray(str2A);
            DeleteArray(str12A);
            DeleteArray(concatstr);
            printf("ConcatStr - ok\n");
        }
        else {
            DeleteArray(str1A);
            DeleteArray(str2A);
            DeleteArray(str12A);
            DeleteArray(concatstr);
            return 0;
        }

    }
    // test SliceStr
    {
        char* str = "0123456789abcdef";
        char* substr = "56789a";
        Array* strA = CreatefromChar(str);
        Array* substrA = CreatefromChar(substr);
        Array* slicestr = SliceStr(strA, 5, 10);
        if (isEqualStr(slicestr, substrA, 1)){
        	DeleteArray(strA);
        	DeleteArray(substrA);
        	DeleteArray(slicestr);
            printf("SliceStr - ok\n");
    	}
        else
        {
        	DeleteArray(strA);
        	DeleteArray(substrA);
        	DeleteArray(slicestr);
            return 0;
        }
    }
    // test SearchStr
    
    {
        char* str = "0123456789abcdef";
        char* substr1 = "56789abcd";
        char* substr2 = "56789AbCd";
        char* wrongstr = "dhrrhfrff";
        Array* strA = CreatefromChar(str);
        Array* substr1A = CreatefromChar(substr1);
        Array* substr2A = CreatefromChar(substr2);
        Array* wrongstrA = CreatefromChar(wrongstr);
        // size matter
        //printf("%d", SearchStr(strA, substr2A, 1));
        if (
            (SearchStr(strA, substr1A, 1) == 5) && 
            (SearchStr(strA, substr2A, 1) == -1) &&
            (SearchStr(strA, wrongstrA, 1) == -1)
            )
            printf("SliceStr-sm - ok\n");
        else{
        	DeleteArray(strA);
            DeleteArray(substr1A);
            DeleteArray(substr2A);
            DeleteArray(wrongstrA);
            return 0;
        }
        // not
        if (
            (SearchStr(strA, substr2A, 2) == 5) &&
            (SearchStr(strA, substr1A, 2) == 5) &&
            (SearchStr(strA, wrongstrA, 2) == -1)
            )
            printf("SliceStr-snm - ok\n");
        else{
        	DeleteArray(strA);
            DeleteArray(substr1A);
            DeleteArray(substr2A);
            DeleteArray(wrongstrA);
            return 0;
        }
        DeleteArray(strA);
        DeleteArray(substr1A);
        DeleteArray(substr2A);
        DeleteArray(wrongstrA);
    }
    return 1;

}


// UI
void sep() {
    printf("------------------------------------------\n");
}

void ui()
{
    // console command UI
    char* command = (char*)malloc(max_command_len * sizeof(char));

    while (1) {

        sep();
        printf("commands:\n");
        printf("	1 - concat\n");
        printf("	2 - slice\n");
        printf("	3 - search\n");
        printf("	/ - test\n");
        printf("	0 - exit\n");
        sep();

        gets(command);
        // if gets() smh reads \0
        if (*command == '\0') {
            gets(command);
        }

        // commands
        // exit
        if (*command == '0')
            break;
        // concat
        if (*command == '1') {
            Array* strA = inputStr();
            Array* strB = inputStr();
            Array* concatstr = ConcatStr(strA, strB);
            printStr(concatstr);
            DeleteArray(strA);
            DeleteArray(strB);
            DeleteArray(concatstr);
        }
        // slice
        if (*command == '2') {
            Array* str = inputStr();
            int i, j;
            printf("start index: ");
            scanf_s("%d", &i);
            printf("end index: ");
            scanf_s("%d", &j);
            if (i >= 0 && j < str->count) {
                Array* slicedstr = SliceStr(str, i, j);
                printStr(slicedstr);    
                DeleteArray(slicedstr);
            }
            else {
                printf("wrong indexes\n");
            }
            DeleteArray(str);
        }
        // search
        if (*command == '3') {
            printf("size matter? [y/n]\n");
            gets(command);
            Array* strA = inputStr();
            Array* strB = inputStr();
            if (*command == 'y')
                printf("%d", SearchStr(strA, strB, 1));
            else
                printf("%d", SearchStr(strA, strB, 2));
            printf("\n");
            DeleteArray(strA);
            DeleteArray(strB);
        }
        //test
        if (*command == '/') {
            printf("Testing started\n");
            if (test())
                printf("Testing finished\n");
            else
                printf("Testing failed\n");
                
        }
    }

    Deleteptr(command);
}

int main() {
    ui();
}