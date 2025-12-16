#include <X11/Xlib.h>
#include <stdio.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Can't open display\n");
        return 1;
    }

    Window root = DefaultRootWindow(display);
    
    // Try to claim the consultant role
    XSelectInput(display, root, SubstructureRedirectMask | SubstructureNotifyMask);
    
    XSync(display, False);
    
    // If we get here without error, we're the WM now!
    printf("Successfully registered as window manager!\n");
    
    // Event loop would go here to handle window requests
    
    XCloseDisplay(display);
    return 0;
}
