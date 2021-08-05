#include<windows.h>
#include<stdio.h>

#define LOGIN_ACTIVATE 1

LRESULT CALLBACK WindowProcedure(HWND,UINT, WPARAM,LPARAM);
void Login_page(HWND);


HWND userName,passWord;


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
        case WM_COMMAND:
            switch(wp){
                case LOGIN_ACTIVATE:;//runs when the login 
                    wchar_t un[30];
                    wchar_t pw[30];
                    GetWindowTextW(userName,un,30);
                    GetWindowTextW(passWord,pw,30);
                    char uname[30];
                    char pword[30];
                    wcstombs(uname,un,30);
                    wcstombs(pword,pw,30);
                    printf("%s\t%s",uname,pword);
                    // //need to check  if the user name and password is correct or not;
                    break;
            }
            break;
        case WM_CREATE://runs only when the window is created for the first time.
            Login_page(hWnd);
            break;
        case WM_DESTROY://this case checks if the windows is closed;
            PostQuitMessage(0);
            break;
        default://for the dfault case
            return DefWindowProcW(hWnd,msg, wp, lp);
    }
}


void Login_page(HWND hWnd){
    CreateWindowW(L"static",L"Username:",WS_VISIBLE|WS_CHILD|SS_CENTER,150,75,200,25,hWnd,NULL,NULL,NULL);
    userName = CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER,150,100,200,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"static",L"Password:",WS_VISIBLE|WS_CHILD|SS_CENTER,150,175,200,25,hWnd,NULL,NULL,NULL);
    passWord = CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_PASSWORD,150,200,200,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"button",L"Log In",WS_VISIBLE|WS_CHILD,200,275,100,25,hWnd,(HMENU)LOGIN_ACTIVATE,NULL,NULL);
    CreateWindowW(L"button",L"Sign Up",WS_VISIBLE|WS_CHILD,200,325,100,25,hWnd,NULL,NULL,NULL);
}