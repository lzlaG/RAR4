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

void Read_File(string *path, Archive* Volume_Header, FILE_HEAD* Head_type)
{
    ifstream file(*path,ios::binary);
    if (!file)
    {
        cout << "Файл не открылся, ошибка" << "\n";
    }
    else
    {
    cout << "Файл успешно открылся" << "\n";
    file.seekg(0, ios::end);
    int length=file.tellg();
    file.seekg(0, ios::beg);
    unsigned char* buff = new unsigned char[length];
    file.read((char*)buff, length);
    file.close();
    int bytes = 0;
    int k=0;
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