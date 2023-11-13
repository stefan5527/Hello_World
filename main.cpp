#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int pid1, pid2, pid3;

    pid1 = fork();

    if (pid1 == 0)
    {
        sleep(1);
        cout << "Procesul 1 a terminat.\n";
    } else {

        pid2 = fork();

        if (pid2 == 0)
        {
            sleep(2);
            cout << "Procesul 2 a terminat.\n";
        } else {
            pid3 = fork();

            if (pid3 == 0)
            {
                sleep(3);
                cout << "Procesul 3 a terminat.\n";
            } else
            {
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
                waitpid(pid3, NULL, 0);

                cout << "Toate procesele au terminat.\n";
            }
        }
    }

    return 0;
}
