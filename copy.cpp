#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int progres = 0, curr_read, curr_write;
    const size_t SIZE_BUFFER = 50000;
    char *buf = nullptr;

    buf = (char *)malloc(SIZE_BUFFER); // просим ОС дать памяти под буфер

    if (NULL == buf) // провека, вдруг не даст
    {
        std::cout << "not memory!"
                  << "\n";
        return -1;
    }
    int fd_read, fd_write;
    fd_read = open(argv[1], O_RDONLY); // открываем файл источник
    if (fd_read == -1)                 // вдруг не открылся
    {
        std::cout << "cannot open file " << argv[1] << "\n";
        return -1;
    }

    fd_write = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // открывваем фалй приемник
    if (fd_read == -1)                                                                                                 // вдруг не открылся
    {
        std::cout << "cannot open file " << argv[2] << "\n";
        return -1;
    }

    size_t file_read, file_write;
    while ((file_read = read(fd_read, buf, SIZE_BUFFER)) > 0) // читаем до тех пока есть считанные байты
    {
        if (file_read == -1) // вдруг не прочитал
        {
            std::cout << "cannot read file " << argv[1] << "\n";
            free(buf);
            close(fd_read);
            close(fd_write);
            return -1;
        }

        if (file_read != SIZE_BUFFER) // проверим а полностью ли буфер занят
        {
            char *buf_new = (char *)malloc(file_read); // попросим еще памяти у ОС
            for (int i = 0; i < file_read; i++)        // добавим в новый буфер валидные данные
            {
                buf_new[i] = buf[i];
            }
            file_write = write(fd_write, buf_new, file_read); // запишем
            free(buf_new);                                    // освободим ресурс

            if (file_write == -1) // проверим вдруг не получилось
            {
                std::cout << "cannot write file " << argv[2] << "\n";
                free(buf);
                free(buf_new);
                close(fd_read);
                close(fd_write);
                return -1;
            }
        }
        else
        {
            file_write = write(fd_write, buf, SIZE_BUFFER); // пишем в файл
            if (file_write == -1)                           // проверим вдруг не получилось
            {
                std::cout << "cannot write file " << argv[2] << "\n";
                free(buf);
                close(fd_read);
                close(fd_write);
                return -1;
            }
        }

        if (file_write != file_read) // если что то пошло не так
        {
            std::cout << "warn!" << std::endl;
            return -1;
        }
        system("clear"); // что то типо прогресс бара
        progres += file_write;
        std::cout << "copy is: " << progres << " Byte"
                  << "\n";

        if (file_write == -1) // вдруг не прочитал
        {
            std::cout << "cannot write file " << argv[2] << "\n";
            free(buf);
            close(fd_read);
            close(fd_write);
            return -1;
        }
    }

    std::cout << "copy is OK!" << std::endl;

    // отдаем занятые ресурсы
    free(buf);
    close(fd_read);
    close(fd_write);
}