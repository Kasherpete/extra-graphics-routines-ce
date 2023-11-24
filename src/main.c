#include <keypadc.h>
#include <graphx.h>

#include <sys/timers.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include <debug.h>


static void drawTrapezoid(int x1, int x2, int x3, int x4, int y1, int y2) {


    int n1 = (((x2-x1)*100/(y1-y2)));
    int n2 = (((x3-x4)*100/(y1-y2)));

    int j = x1 * 100;
    int k = x4 * 100;
    int s = 0;

    if (y1 < y2) {
        dbg_printf("%d, %d\n", y2, y1);
        for (int i = y1; i < y2; i++) {
            
            j -= n1;
            k -= n2;
            s = j / 100;
            gfx_HorizLine(s, i, k / 100-s);
        }
    } else {
        for (int i = y1; i > y2; i--) {
            j += n1;
            k += n2;
            s = j / 100;
            gfx_HorizLine(s, i, k / 100-s);
        }
    }
}

static void drawTrapezoid_NoClip(int x1, int x2, int x3, int x4, int y1, int y2) {

    int n1 = (((x2-x1)*100/(y1-y2)));
    int n2 = (((x3-x4)*100/(y1-y2)));

    int j = x1 * 100;
    int k = x4 * 100;
    int s = 0;

    if (y1 < y2) {
        dbg_printf("%d, %d\n", y2, y1);
        for (int i = y1; i < y2; i++) {
            
            j -= n1;
            k -= n2;
            s = j / 100;
            gfx_HorizLingite_NoClip(s, i, k / 100-s);
        }
    } else {
        for (int i = y1; i > y2; i--) {
            j += n1;
            k += n2;
            s = j / 100;
            gfx_HorizLine_NoClip(s, i, k / 100-s);
        }
    }
}

static void drawRotateTrapezoid_NoClip(int y1, int y2, int y3, int y4, int x2, int x1) {

    int n1 = (((y2-y1)*100/(x1-x2)));
    int n2 = (((y3-y4)*100/(x1-x2)));

    int j = y1 * 100;
    int k = y4 * 100;
    int s = 0;

    if (x1 < x2) {
        for (int i = x1; i < x2; i++) {
            
            j -= n1;
            k -= n2;
            s = j / 100;
            gfx_VertLine_NoClip(i, s, k / 100-s);
        }
    } else {
        for (int i = x1; i > x2; i--) {
            j += n1;
            k += n2;
            s = j / 100;
            gfx_VertLine_NoClip(i, s, k / 100-s);
        }
    }
}

static void drawRotateTrapezoid(int y1, int y2, int y3, int y4, int x2, int x1) {

    int n1 = (((y2-y1)*100/(x1-x2)));
    int n2 = (((y3-y4)*100/(x1-x2)));

    int j = y1 * 100;
    int k = y4 * 100;
    int s = 0;

    if (x1 < x2) {
        for (int i = x1; i < x2; i++) {
            
            j -= n1;
            k -= n2;
            s = j / 100;
            gfx_VertLine(i, s, k / 100-s);
        }
    } else {
        for (int i = x1; i > x2; i--) {
            j += n1;
            k += n2;
            s = j / 100;
            gfx_VertLine(i, s, k / 100-s);
        }
    }
}

int main(void)
{

    

    gfx_Begin();
    gfx_ZeroScreen();

    gfx_SetColor(gfx_red);
    gfx_SetTextFGColor(gfx_red);

    uint8_t frame_count = 0;
    clock_t start_time = clock();
    uint8_t fps = 0;

    uint8_t mode = 0;

    while (!(kb_Data[6] & kb_Clear)) {
        
        // FPS calculation
        frame_count++;

        if (clock() - start_time >= CLOCKS_PER_SEC) {
            fps = frame_count;
            frame_count = 0;
            start_time = clock();
        }

        // handle input
        if (kb_Data[7] & kb_Up) {
            mode = 0;
        } else if (kb_Data[7] & kb_Down) {
            mode = 1;
        }

        

        // FPS counter
        gfx_ZeroScreen();
        gfx_SetTextXY(5,5);
        gfx_PrintString("FPS:");
        gfx_SetTextXY(35,5);
        gfx_PrintUInt(fps, 2);

        int y1 = 200; // top
        int y2 = 50;  // bottom
        int x1 = 10;  // left
        int x2 = 50;  // middle left
        int x3 = 180; // middle right
        int x4 = 200; // right

        /*     x2  x3
            y2 /----\
            y1/______\
             x1       x4
        */

       /* x1  x2
          |\   y1
          | \  y2
          | |
          | /  y3
          |/   y4
        */

        drawRotateTrapezoid(x1, x2, x3, x4, y1, y2);
        


        gfx_SwapDraw();

    }

    gfx_End();
    return 0;
}
