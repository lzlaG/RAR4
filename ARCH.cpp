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
        while (bytes<length)
    {
        Volume_Header->header_crc[0]=buff[bytes];
        Volume_Header->header_crc[1]=buff[bytes+1];
        Volume_Header->header_type=buff[bytes+2];
        Volume_Header->header_flags[0]=buff[bytes+3];
        Volume_Header->header_flags[1]=buff[bytes+4];
        Volume_Header->header_size[0]=buff[bytes+5];
        Volume_Header->header_size[1]=buff[bytes+6];
        int razmer=(int)Volume_Header->header_size[0]+(int)Volume_Header->header_size[1];
        if (Volume_Header->header_type==0x74)
        {
            int name_len=(int)buff[bytes+26]+(int)buff[bytes+27];
            Head_type->PackSize[0]=buff[bytes+7];
            Head_type->PackSize[1]=buff[bytes+8];
            Head_type->PackSize[2]=buff[bytes+9];
            Head_type->PackSize[3]=buff[bytes+10];
            int size_of_packaged_data=(int)(Head_type->PackSize[0])+(int)(Head_type->PackSize[1])+(int)(Head_type->PackSize[2])+(int)(Head_type->PackSize[3]);
            for (int i=1; i<=name_len; i++)
            {
                cout << buff[i+bytes+31];
            }
            cout << "\n";
            bytes=bytes+razmer+size_of_packaged_data;
            k+=1;
            
        }
        else
        {
            bytes=bytes+razmer;
        }
        if (k==3)
        {
            break;
        }
    };
    };
};

int main()
{
    string path;
    cout << "Введите полный путь файла: ";
    getline(cin,path);
    Archive* OurRar = new Archive;
    FILE_HEAD* Header = new FILE_HEAD;
    string *get_path = &path;
    Read_File(get_path,OurRar,Header);
}