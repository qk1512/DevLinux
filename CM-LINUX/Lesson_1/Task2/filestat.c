#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s <file_path>\n", prog_name);
}

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    // Structure to hold file metadata
    struct stat file_stat;

    // Use lstat to get file information
    if (lstat(argv[1], &file_stat) == -1)
    {
        perror("lstat");
        return 1;
    }

    // Print file path
    printf("File Path: %s\n", argv[1]);

    // Determine and print file type
    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode))
    {
        printf("Regular File\n");
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        printf("Directory\n");
    }
    else if (S_ISLNK(file_stat.st_mode))
    {
        printf("Symbolic Link\n");
    }
    else
    {
        printf("Other\n");
    }

    // Print file size
    printf("Size: %lld bytes\n", (long long)file_stat.st_size);

    // Convert and print last modified time
    char time_str[26];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last Modified: %s\n", time_str);

    return 0;
}