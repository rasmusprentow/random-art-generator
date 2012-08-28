#include <windows.h>
#include <gl/gl.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include <pthread.h>
#include "../XAG/bmpwrap.h"
#include "../XAG/walker.h"

#define DEBUG

void *walk_threaded (void * mp)
{
    struct metapicture * pic = (struct metapicture *) mp;
    walk(pic);
    return NULL;
}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
   // float theta = 0.0f;
   // const XSize = 640, YSize = 480;
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          800,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);







    unsigned char initialRed = 127;
    unsigned char initialGreen = 127;
    unsigned char initialBlue = 127;
   // int forceYes = 0;
    struct metapicture mp = {
        .size = 800*800,
        .width = 7000,
        .height = 5000,
        .name = "image",
        .pic = NULL,
        .iterations = 9750000000,  //.iterations = 6500000,
        .verbose = 1,
        .printBmpTemp = 0,
        .printBmp = 1,
        .done = 0,
        .seedRenew = 1000,
        .printPercentage = 1000000
    };




    mp.size = mp.height * mp.width;

	preparePicture(initialRed, initialGreen, initialBlue, &mp);







    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0, mp.width, mp.height, 0, 0, 1);
    glMatrixMode (GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);

    int  iret1;
    pthread_t thread1;

    iret1 = pthread_create( &thread1, NULL,walk_threaded, (void*) &mp);

    //walk(&mp);


    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            long int i = 0;

            //glVertex2f(x++, 10);
            for( i = 0; i < mp.size; i++){
                glColor3ub(mp.pic[i].red, mp.pic[i].green,mp.pic[i].blue);
                //glColor3ub(233,0,0);
                glVertex2f(getX(i, &mp),getY(i, &mp));
                //fwrite(&mp->pic[i], 4, 1,fp);
            }
            glEnd();
            SwapBuffers(hDC);

        }
    }

    pthread_join( thread1, NULL);

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

