#include <iostream>
#include "Connection.hpp"
#include <cstdlib>
#include <termios.h>
#include <sys/poll.h>


using namespace std;

bool isEscPressed() {
    struct termios old_tio, new_tio; // Структуры для сохранения и восстановления настроек терминала
    tcgetattr(STDIN_FILENO, &old_tio); // Получаем текущие настройки терминала
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO); // Отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio); // Применяем новые настройки

    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    int res = poll(fds, 1, 0);
    if (res > 0) 
    {
        if (fds[0].revents & POLLIN) 
        {
                char c;
                std::cin >> c; 
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); // Восстанавливаем настройки терминала
                
                if(c == 27)// ASCII код для клавиши ESC
                {
                    std::cout << "Esc is pressed" << std::endl;
                    return true;
                }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); // Восстанавливаем настройки терминала
    return false; 
}


int main()
{
    Connection connection("google.com");

    while (!isEscPressed())
    {
        if (!connection.queue.isEmpty())
        {
            std::cout << connection.queue.dequeue() << std::endl;
        }
	   else
            usleep(100);
    }

    
    return 0;
}