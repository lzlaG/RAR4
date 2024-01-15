#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Archive
{
    unsigned char header_crc[2];
    unsigned char header_type;
    unsigned char header_flags[2];
    unsigned char header_size[2];
};


struct FILE_HEAD
{
    char PackSize[4];
    char UnpSize[4];
    char HostOs;
    char FileCRC[4];
    char FileTime[4];
    char UnpVer;
    char Method;
    unsigned char NameSize[2];
    char FileAttr[4];
};



int main()
{
    string path;
    cout << "Введите полный путь файла: ";
    getline(cin,path);
    Archive* OurRar = new Archive;
    FILE_HEAD* Header = new FILE_HEAD;
    string *get_path = &path;

}