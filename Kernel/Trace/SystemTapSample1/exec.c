#include <unistd.h>
int main(int argc, char **argv)
{
        execl("./test", "hello", NULL);
        return 0;
}
