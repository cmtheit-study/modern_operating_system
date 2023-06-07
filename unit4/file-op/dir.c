#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkdir("./dirs", 0777);
    rmdir("./dirs");
    unlink("./dir");
}