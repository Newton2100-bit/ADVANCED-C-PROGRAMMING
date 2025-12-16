
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

static inline uint32_t make_pixel(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 16) | (g << 8) | b;  // XRGB8888
}

int main()
{
    int fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd < 0) {
        perror("open");
        return 1;
    }

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);

    int width  = vinfo.xres;
    int height = vinfo.yres;
    int bpp    = vinfo.bits_per_pixel;   // should be 32
    long screensize = finfo.line_length * height;

    uint32_t *fb = (uint32_t*) mmap(NULL, screensize,
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fbfd, 0);

    if (fb == MAP_FAILED) {
        perror("mmap");
        close(fbfd);
        return 1;
    }

    // Draw a pixel at 100,100 -> bright red
    int x = 100, y = 100;
    fb[y * (finfo.line_length / 4) + x] = make_pixel(255, 0, 0);

    sleep(5);
    munmap(fb, screensize);
    close(fbfd);
    return 0;
}
