#include <windows.h>
LRESULT CALLBACK WindowProcedure(HWND,UINT, WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR args,int ncmdshow ){
    WNDCLASSW wc ={0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"MainWindow";//class name of the window
    wc.lpfnWndProc =WindowProcedure;
    if(!RegisterClassW(&wc)){
        return -1;
    }
    /*Below code creates the window 
    SYNTAX:CreateWindowW(classname of the window, window name, type of the window, top_left postion x, y, size x, size y, NULL , NULL, NULL, NULL);
    */
    CreateWindowW(L"MainWindow",L"MCQ Evaluation Application",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,500,500,NULL,NULL,NULL,NULL);
    MSG msg = {0};
    //Message loop for running the window
    while(GetMessage(&msg,NULL,NULL,NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg, WPARAM wp ,LPARAM lp){
    switch(msg){
        case WM_DESTROY://this case checks if the windows is closed;
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd,msg, wp, lp);
    }
}
