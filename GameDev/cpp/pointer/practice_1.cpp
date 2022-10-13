#include <iostream>
using namespace std;

int StrLen(char *);
char* StrCpy(char *, char *);
char* StrCpy_1(char *, char*);
char* StrCat(char*, char*);
int Strcmp(char*, char*);
char* Reverse_string(char* );

#pragma warning(disable: 4996)
int main()
{
    const int BUF_SIZE = 100;
    char a[BUF_SIZE] = "Hello";
    char b[BUF_SIZE];
    char c[BUF_SIZE] = "World";

    int len = StrLen(a);
    cout << len << endl;

    //strcpy_s(b, a);
    StrCpy(b, a);
    StrCat(b, a);
    //int num = strcmp(a, b);
    int num = Strcmp(b, a);
    return 0;
}

int StrLen(char* str)
{
    int size = 0;
    bool found = false;
    while(str[size] != '\0')
    {
        size++;
    }
    return size;
}
char* StrCpy(char* dest, char* src)
{
    int i = 0;
    while(src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}
char* StrCpy_1(char*dest, char*src)
{
    char* ret = dest;
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
        // *dest++ = *src++
    }
    *dest = '\0';
    return ret;
}
char* StrCat(char*dest, char*src)
{
//    int len = StrLen(dest);
//    int i = 0;
//    while(src[i] != '\0')
//    {
//        dest[len + i] = src[i];
//        i++;
//    }
//    dest[len+i] = '\0';
    char*ret =dest;
    while(*dest != '\0')
        dest++;

    while(*src != '\0')
    {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}
int Strcmp(char*dest, char*src)
{
    int i = 0;
    while(dest[i] != '\0' || src[i] != '\0')
    {
        if (dest[i] > src[i])
            return 1;
        if (dest[i] < src[i])
            return -1;
        i++;
    }

}
char* Reverse_string(char* src)
{
    int len = StrLen(src);
    for (int i = 0; i < len/2; i++)
    {
        int temp = src[i];
        src[i] = src[len - i - 1];
        src[len - i - 1] = temp;
    }
    return src;
}