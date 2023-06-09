#include <X11/Xlib.h>
#include <stdio.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "无法打开X服务器连接\n");
        return 1;
    }

    Window root = DefaultRootWindow(display);
    Window window = XCreateSimpleWindow(display, root, 100, 100, 400, 300, 1, 0, 0);
    GC gc = XCreateGC(display, window, 0, 0);
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

    XMapWindow(display, window);
    XFlush(display);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // 处理重绘事件
            printf("窗口重绘\n");
        } else if (event.type == KeyPress) {
            // 处理键盘按键事件
            printf("键盘按下\n");
        } else if (event.type == ConfigureNotify) {
            // 处理窗口大小变化事件
            printf("窗口大小变化\n");
        } else if (event.type == ClientMessage) {
            // 处理窗口关闭事件
            if (event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
                printf("窗口关闭\n");
                break;
            }
        }
    }
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
