#include <fcntl.h>
#include <unistd.h>
#include <iostream>


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "need more arguments!"
                  << "\n";
        return -1;
    }

    int fd_read, fd_write, curr;
    char *buf = nullptr;
    char *buf_enter = nullptr;
    ssize_t file_read, file_write;
    int len = 10000;
    buf = (char *)malloc(len); // просим у ОС выделить память

    if (buf == NULL) // проверка
    {
        std::cout << "not memory"
                  << "\n";
        return -1;
    }

    std::cout << "open file " << argv[1] << "\n";
    fd_read = open(argv[1], O_RDONLY); // открываем файл на чтение
    fd_write = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // открываем файл на запись

    if (fd_read == -1) //проверка
    {
        std::cout << "cannor open file: " << argv[1] << "\n";
        return -1;
    }

    if (fd_write == -1) //проверка
        {
            std::cout << "cannot open file " << argv[2] << "\n";
            return -1;
        }




 
    file_read = read(fd_read, buf, len); // читаем файлик в буфер
    if (file_read == -1)
    {
        std::cout << "cannot read file " << argv[1] << "\n";
        return -1;
    }
    else if (file_read == 0)
    {
        std::cout << "file " << argv[1] << " is empty!"
                  << "\n";
    }
    else
    {
        
  
        file_write = write(fd_write, buf, len); // пишем в файл из буфера
        if (file_write == -1)
        {
            std::cout << "cannot write in file " << argv[2] << "\n";
            return -1;
        }
        std::cout << "I'm write " << file_write << " byte!"
                  << "\n";
    }
    // чистим ресурсы
    free(buf);
    close(fd_read);
    close(fd_write);
}