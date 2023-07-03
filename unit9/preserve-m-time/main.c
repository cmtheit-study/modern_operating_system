//
// Created by cmtheit on 23-7-3.
//

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>

int main() {
    const char * vic = "file.txt";
    struct stat st;
    if (lstat(vic, &st)) {
        printf("Cannot stat file %s\n", vic);
        return 2;
    }
    struct timespec last_mtime = st.st_mtim;

    FILE * vic_file = fopen(vic, "w");
    if (!vic_file) {
        printf("Cannot open file %s\n", vic);
        return 1;
    }

    char time_buf[32] = {0};
    time_t time_t_now = time(NULL);
    struct tm * tms = localtime(&time_t_now);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tms);
    fprintf(vic_file, "%s", time_buf);
    fclose(vic_file);

    struct utimbuf utime_buf;
    utime_buf.actime = 0;
    utime_buf.modtime = last_mtime.tv_sec;
    utime(vic, &utime_buf);
    return 0;
}