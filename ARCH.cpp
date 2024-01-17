#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Archive
{
    char header_crc[2];
    char header_type;
    char header_flags[2];
    unsigned char header_size[2];
};


struct FILE_HEAD
{
    unsigned char PackSize[4];
    char UnpSize[4];
    char HostOs;
    char FileCRC[4];
    char FileTime[4];
    char UnpVer;
    char Method;
    char NameSize[2];
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
        int bytes = 0;
        int k=0;
        char letter;
        while (bytes<length)
        {
            file.seekg(bytes, ios::beg);
            file.read((char*)Volume_Header, sizeof(Archive));
            int razmer=(int)Volume_Header->header_size[0]+(int)Volume_Header->header_size[1];
            if (Volume_Header->header_type==0x74)
            {
                int pos = bytes +sizeof(Archive);
                file.seekg(pos);
                file.read((char*)Head_type, sizeof(FILE_HEAD));
                int name_len = (int)Head_type->NameSize[0]+(int)Head_type->NameSize[1];
                int size_of_packaged_data=(int)(Head_type->PackSize[0])+(int)(Head_type->PackSize[1])+(int)(Head_type->PackSize[2])+(int)(Head_type->PackSize[3]);
                pos = pos+sizeof(FILE_HEAD);
                file.seekg(pos);
                for (int i=0; i<name_len; i++)
                {
                    file.read(&letter,1);
                    cout << letter;
                };
                cout << "\n";
                bytes=bytes+razmer+size_of_packaged_data;
                k+=1;
            }
            else
            {
                bytes = bytes + razmer;
            }
            if (k==3)
            {
                break;
            }
        };
        file.close();
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