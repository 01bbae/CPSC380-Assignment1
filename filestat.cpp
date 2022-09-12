#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char *filename = argv[1];
        string filetype;
        struct stat buf;
        stat(filename, &buf);
        struct passwd pwd = *getpwuid(buf.st_uid);
        if ((buf.st_mode & S_IFMT) == S_IFDIR)
        {
            filetype = "Directory";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFREG)
        {
            filetype = "Regular file";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFSOCK)
        {
            filetype = "Socket";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFLNK)
        {
            filetype = "Symbolic link";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFBLK)
        {
            filetype = "Block special";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFCHR)
        {
            filetype = "Character special";
        }
        else if ((buf.st_mode & S_IFMT) == S_IFIFO)
        {
            filetype = "Named pipe";
        }
        else
        {
            filetype = "";
            printf("File Type is not of the 7 standard types: %s\n", strerror(errno));
        }

        cout << "Device: " << buf.st_dev << endl;
        cout << "Inode number: " << buf.st_ino << endl;
        cout << "Mode: " << filetype << endl;
        cout << "Username: " << pwd.pw_name << endl;
        cout << "Total Size: " << buf.st_blocks << endl;
        cout << "Date: " << ctime(&buf.st_mtime);
    }
    else
    {
        printf("Wrong number of arguements (Expected 1, Recived %d): %s\n", argc - 1, strerror(errno));
    }
    return 0;
}