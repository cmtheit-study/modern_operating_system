#include <unistd.h>

int main() {
    execl("./hw", "./hw", NULL);
}