#include <windows.h>
#include <stdio.h>
#include <windowsx.h>
#include "question_answer_display.h"
#include "login_backend.h"
#include "logout.h"
#include "change_data.h"
#include "emailChecker.h"
#include "passwordhashing.h"


//macro to check the file messages
#define LOGIN_ACTIVATE 1
#define SIGNUP_ACTIVATE 2
#define REGISTER_USER_BUTTON 3
#define ADD_QUESTION_PAGE 4
#define ADD_QUESTION_TO_DATABASE 5
#define PRACTICE_QUESTION_BUTTON 6
#define SUBMIT_ANSWER 7
#define SIGN_OUT 8
#define BACK_TO_LOGIN 9
#define BACK_TO_OPTIONS 10
#define VIEW_STATUS_STUDENT 11
#define VIEW_STATUS_ADMIN 12
#define NEXT_STUDENT 13


//all the functions defined in the program
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void Login_page(HWND);
void Signup_page(HWND);
void options_page(HWND);
void destroy_login();
void destroy_option();
void add_question_page(HWND);
void practice_question_page(HWND, struct Question);
void clear_text();
void destroy_questions();
void destroy_questions_page();
void destroy_registration_page();
void display_status_page(HWND);
void destroy_status_page();
void display_status_page_admin(HWND);


// defination for different window handeler in the program for creating different elements in the window
HWND userName_label, userName, passWord_label, passWord, logiInButton,
    signUpButton, signUpTitle, firstName_label, firstName, lastName_label,
    lastName, eMail_label, eMail, confirmPassWord, confirmPassWord_label,
    registerButton, confirmPassIncorrect, statusPageButton, questionAnswerButton,
    addQuestionLabel, addQuestion, addOptionLabel, firstOption, secondOption, thirdOption,
    fourthOption, addQuestionToDatabase, correctAnswerLabel, correctAnswer, questionAddError,
    nextQuestion, answerNotChecked, logOutButton, backButton, emailInvalid, LoginUnsuccessfull,
    name_label, name, totalAttempts_label, totalAttempts, inCorrectAnswer, inCorrectAnswerLabel,
    scoreLabel, score, nextStudent, emailDouble;

//stores the information of the user in below structure
struct Register user;
//stores the question to show to the user or add question to the database
struct Question que;
int confirmpass = 1;
//the position of the student in the database to select
int student_postion = 1;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR args, int ncmdshow)
{
    /*******************************************************************************************
     * Every Windows program includes an entry-point function that is named either WinMain or 
     * wWinMain. Here is the signature for wWinMain.
     * 
     * 
     * The four parameters are:
     *  *   hInstance is something called a "handle to an instance" or "handle to a module." The 
     *  *   *   operating system uses this value to identify the executable (EXE) when it is 
     *  *   *   loaded in memory. The instance handle is needed for certain Windows functions—for 
     *  *   *   example, to load icons or bitmaps.
     *  *   hPrevInstance has no meaning. It was used in 16-bit Windows, but is now always zero.
     *  *   pCmdLine contains the command-line arguments as a Unicode string.
     *  *   nCmdShow is a flag that says whether the main application window will be minimized,
     *  *   * maximized, or shown normally.
     * 
     * 
     * WINAPI is the calling convention. A calling convention defines how a function receives  
     * parameters from the caller. For example, it defines the order that parameters appear on 
     * the stack.
     * 
     * 
     * How does the compiler know to invoke wWinMain instead of the standard main function? What
     *  actually happens is that the Microsoft C runtime library (CRT) provides an implementation \
     * of main that calls either WinMain or wWinMain.
    ********************************************************************************************/
    
    /*
        Contains the window class attributes that are registered by the RegisterClass function.
    */
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"MainWindow"; //class name of the window
    wc.lpfnWndProc = WindowProcedure;
    if (!RegisterClassW(&wc))
    {
        return -1;
    }
    /*Below code creates the window 
    SYNTAX:CreateWindowW(classname of the window, window name, type of the window, top_left postion x, y, size x, size y, NULL , NULL, NULL, NULL);
    */
    CreateWindowW(L"MainWindow", L"MCQ Evaluation Application", ((WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) ^ WS_MAXIMIZEBOX) | WS_VISIBLE, 0, 0, 500, 500, NULL, NULL, NULL, NULL);
    MSG msg = {0};

    //Message loop for running the window
    //Retrieves a message from the calling thread's message queue. The function 
    //dispatches incoming sent messages until a posted message is available for retrieval.
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        //Translates virtual-key messages into character messages. The character
        // messages are posted to the calling thread's message queue, to be read
        // the next time the thread calls the GetMessage or PeekMessage function.
        TranslateMessage(&msg);
        //Dispatches a message to a window procedure(WindowProcedure() in our case). It is typically used to 
        //dispatch a message retrieved by the GetMessage function.
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    /********************************************************************************************
     * Every window has an associated window procedure — a function that processes all messages 
     * sent or posted to all windows of the class. All aspects of a window's appearance and behavior
     *  depend on the window procedure's response to these messages. 
    *********************************************************************************************/
    switch (msg)
    {
    case WM_COMMAND:
        //WM_COMMAND is sent when the user selects a command item from a menu, when a control sends a notification
        // message to its parent window, or when an accelerator keystroke is translated.
        switch (wp)
        {
        case LOGIN_ACTIVATE:; //runs when the login button is pressed by the user
            /*DestroyWindow(HWND) function destroys the window or erases the element from the window
            HWND is the window handeler
            */
            DestroyWindow(emailInvalid);
            DestroyWindow(LoginUnsuccessfull);
            // wchar_t un[30];
            // wchar_t pw[30];
            char uname[30];
            char pword[150];
            GetWindowText(userName, uname, 30);
            GetWindowText(passWord, pword, 150);
            //uname is the username and pword is password
            // printf("%s\t%s", uname, pword);
            int emailValidation = emailValidate1(uname);
            if (emailValidation == 0)
            {
                emailInvalid = CreateWindowW(L"static", L"Please add @gmail.com and @email.com at the end.", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return -1;
            }
            char hello[150];
            passwordEncoder(pword, hello);
            strcpy(pword, hello);
            int loginCondition = login(uname, pword, &user);
            // //need to check  if the user name and password is correct or not;
            if (loginCondition == 1)
            {
                destroy_login();
                options_page(hWnd);
            }
            else
            {
                LoginUnsuccessfull = CreateWindowW(L"static", L"Please register to login", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return -1;
            }
            break;

        case SIGNUP_ACTIVATE: //this activates when the user presses the sign up button on the login page
            destroy_login();
            Signup_page(hWnd);
            break;

        case REGISTER_USER_BUTTON:; 
        //this activates when the user presses the register button in signup page
             DestroyWindow(emailInvalid);
            DestroyWindow(emailDouble);
            char confirm_password[30];
            char hashedpassword[30];
            user.score = 0;
            user.correct_answers = 0;
            user.incorrect_answers = 0;
            user.total_answers = 0;
            user.admin = 0;
            GetWindowText(firstName, user.firstname, 30);
            GetWindowText(lastName, user.lastname, 30);
            GetWindowText(eMail, user.email, 50);
            GetWindowText(userName, user.username, 30);
            GetWindowText(passWord, user.password, 30);
            GetWindowText(confirmPassWord, confirm_password, 30);
            if(strlen(user.password) < 8){
                confirmPassIncorrect = CreateWindowW(L"static", L"Password should be greater than 8 characters", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            if (strcmp(user.password, "") == 0 || strcmp(confirm_password, "") == 0)
            {
                confirmPassIncorrect = CreateWindowW(L"static", L"Please enter the password.", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            else if (strcmp(user.password, confirm_password) != 0)
            { //checks if the password and confirm password are same
                confirmpass = 0;
                confirmPassIncorrect = CreateWindowW(L"static", L"Password are not same.", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            int emailValidation1 = emailValidate1(user.email);
            if (emailValidation1 == 0)
            {
                emailInvalid = CreateWindowW(L"static", L"Please add @gmail.com and @email.com at the end.", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return -1;
            }
            int notValid = emailChecker (user.email);
        
                    // printf("%c", password3);
            char hello1[150];
            passwordEncoder(user.password, hello1);
            strcpy(user.password,hello1);
            // now here the user information is stored in the database
            if(notValid == 1){
                registration(user);
            }
            else{
                 emailDouble = CreateWindowW(L"static", L"User with this email has already been registered", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 425, 300, 25, hWnd, NULL, NULL, NULL);
                return -1;
            }

            //new page for students shows up
            destroy_registration_page();
            options_page(hWnd);
            break;

        case ADD_QUESTION_PAGE:; // this activate when admin presses the add question button in the option page
            destroy_option();
            add_question_page(hWnd);
            break;

        case ADD_QUESTION_TO_DATABASE:; //this statements are executed after addQuestionToDatabase buttonis pressed
            GetWindowText(addQuestion, que.question, 300);
            GetWindowText(firstOption, que.options[0], 50);
            GetWindowText(secondOption, que.options[1], 50);
            GetWindowText(thirdOption, que.options[2], 50);
            GetWindowText(fourthOption, que.options[3], 50);
            GetWindowText(correctAnswer, que.correct, 50);
            // printf("%s\n%s\n%s\n%s\n%s\n",que.question,que.options[0],que.options[1],que.options[2],que.options[3]);
            //below statements checks if all the options are present
            if (strcmp(que.options[0], "") == 0 || strcmp(que.options[1], "") == 0 || strcmp(que.options[2], "") == 0 || strcmp(que.options[3], "") == 0)
            {
                questionAddError = CreateWindowW(L"static", L"either options are empty", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 25, 400, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            //below statements checks if the correct answer lies in the option
            if (!(strcmp(que.options[0], que.correct) == 0 || strcmp(que.options[1], que.correct) == 0 || strcmp(que.options[2], que.correct) == 0 || strcmp(que.options[3], que.correct) == 0))
            {
                questionAddError = CreateWindowW(L"static", L"Correct answer doesn't match with any options", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 25, 400, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            DestroyWindow(questionAddError);
            //here the que structure stores all the values from the screen
            /*
                    que.question    -->     question inputed by the user
                    que.option[0]   -->     first option
                    que.option[1]   -->     second option
                    que.option[2]   -->     third option
                    que.option[3]   -->     fourth option
                    que.correct     -->     correct answer
                    */
            store_to_the_database(que);
            //now structure is processed and saved in the data base
            questionAddError = CreateWindowW(L"static", L"Question added sucessfully!!!", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 25, 400, 25, hWnd, NULL, NULL, NULL);
            //clear the text in the gui
            clear_text();
            break;

        case PRACTICE_QUESTION_BUTTON:;//this runs when user presses the practice quesiton button
            destroy_option();
            get_question(&que);
            //display the question here
            practice_question_page(hWnd, que);

            break;
        case SUBMIT_ANSWER:;// this runs when user presses the next question button in the quesiton page

            char answer[50];

            /*this if conditions check which option is checked*/
            if (Button_GetState(firstOption) == BST_CHECKED)
            {
                GetWindowText(firstOption, answer, 50);
            }
            else if (Button_GetState(secondOption) == BST_CHECKED)
            {
                GetWindowText(secondOption, answer, 50);
            }
            else if (Button_GetState(thirdOption) == BST_CHECKED)
            {
                GetWindowText(thirdOption, answer, 50);
            }
            else if (Button_GetState(fourthOption) == BST_CHECKED)
            {
                GetWindowText(fourthOption, answer, 50);
            }
            else
            {
                answerNotChecked = CreateWindowW(L"static", L"Nothing is selected", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 300, 400, 25, hWnd, NULL, NULL, NULL);
                return 0;
            }
            // printf("%s\n", answer);
            //answer is the option choosen by the user this need to be checked
            // printf("%d", user.score);
            user.total_answers++;
            if (strcmp(answer, que.correct) == 0)
            {
                user.score++;
                user.correct_answers++;
                user.score += 10;
            }
            else
            {
                user.incorrect_answers++;
            }
            //below function stores the user data every time he submits the answer;
            store_in_database(user);
            //now here the procssing is done for checking the answer and storing the status in the database
            get_question(&que);
            destroy_questions();
            practice_question_page(hWnd, que);
            break;
        case SIGN_OUT:;//this runs when user presses the signout button
            logout(user);
            remove_filename();
            destroy_option();
            DestroyWindow(logOutButton);
            Login_page(hWnd);
            break;
        case BACK_TO_LOGIN:;// runs when user presses the back button when the user is in signup page
            destroy_registration_page();
            Login_page(hWnd);
            break;
        case BACK_TO_OPTIONS:;// runs when the user presses button 
            destroy_status_page();
            destroy_questions_page();
            options_page(hWnd);
            break;
        case VIEW_STATUS_STUDENT:;//runs when the user presses the view status button in option page
            destroy_option();
            display_status_page(hWnd);
            break;
        case VIEW_STATUS_ADMIN:;//runs when the admin presses the view the status button in option page
            destroy_option();
            display_status_page_admin(hWnd);
            break;
        case NEXT_STUDENT:;//runs when the user presses the next student button in the view student status page
            destroy_status_page();
            display_status_page_admin(hWnd);
            break;
        }
        break;

    case WM_CREATE:; //runs only when the window is created for the first time.
        int active = check_active(&user);
        if (active == 0)
        {
            Login_page(hWnd);
        }
        else if (active == 1)
        {
            options_page(hWnd);
        }
        break;

    case WM_DESTROY: //this case checks if the windows is closed;
        PostQuitMessage(0);
        break;

    default: //for the dfault case
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void Login_page(HWND hWnd)
{ // this pages creates all the elements for the login page
    userName_label = CreateWindowW(L"static", L"Email:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 75, 200, 25, hWnd, NULL, NULL, NULL);
    userName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 150, 100, 200, 25, hWnd, NULL, NULL, NULL);
    passWord_label = CreateWindowW(L"static", L"Password:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 175, 200, 25, hWnd, NULL, NULL, NULL);
    passWord = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | WS_TABSTOP, 150, 200, 200, 25, hWnd, NULL, NULL, NULL);
    logiInButton = CreateWindowW(L"button", L"Log In", WS_VISIBLE | WS_CHILD, 200, 275, 100, 25, hWnd, (HMENU)LOGIN_ACTIVATE, NULL, NULL);
    signUpButton = CreateWindowW(L"button", L"Sign Up", WS_VISIBLE | WS_CHILD, 200, 325, 100, 25, hWnd, (HMENU)SIGNUP_ACTIVATE, NULL, NULL);
}

void destroy_login()
{ // destroys all the elements inside the login page
    DestroyWindow(emailInvalid);
    DestroyWindow(LoginUnsuccessfull);
    DestroyWindow(userName_label);
    DestroyWindow(userName);
    DestroyWindow(passWord_label);
    DestroyWindow(passWord);
    DestroyWindow(logiInButton);
    DestroyWindow(signUpButton);
}

void destroy_option()
{ // destroys all the elements inside option pages
    DestroyWindow(logOutButton);
    DestroyWindow(statusPageButton);
    DestroyWindow(questionAnswerButton);
}

void Signup_page(HWND hWnd)
{ //creates all the elements of the registration page
    backButton = CreateWindowW(L"button", L"Go Back", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 90, 40, hWnd, (HMENU)BACK_TO_LOGIN, NULL, NULL);
    signUpTitle = CreateWindowW(L"static", L"Sign UP", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 25, 100, 25, hWnd, NULL, NULL, NULL);
    firstName_label = CreateWindowW(L"static", L"First Name:", WS_VISIBLE | WS_CHILD, 50, 75, 125, 25, hWnd, NULL, NULL, NULL);
    firstName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 200, 75, 250, 25, hWnd, NULL, NULL, NULL);
    lastName_label = CreateWindowW(L"static", L"Last Name:", WS_VISIBLE | WS_CHILD, 50, 125, 125, 25, hWnd, NULL, NULL, NULL);
    lastName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 200, 125, 250, 25, hWnd, NULL, NULL, NULL);
    eMail_label = CreateWindowW(L"static", L"Email:", WS_VISIBLE | WS_CHILD, 50, 175, 125, 25, hWnd, NULL, NULL, NULL);
    eMail = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 200, 175, 250, 25, hWnd, NULL, NULL, NULL);
    userName_label = CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILD, 50, 225, 125, 25, hWnd, NULL, NULL, NULL);
    userName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 200, 225, 250, 25, hWnd, NULL, NULL, NULL);
    passWord_label = CreateWindowW(L"static", L"Password:", WS_VISIBLE | WS_CHILD, 50, 275, 125, 25, hWnd, NULL, NULL, NULL);
    passWord = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | WS_TABSTOP, 200, 275, 250, 25, hWnd, NULL, NULL, NULL);
    confirmPassWord_label = CreateWindowW(L"static", L"Confirm Password:", WS_VISIBLE | WS_CHILD, 50, 325, 125, 25, hWnd, NULL, NULL, NULL);
    confirmPassWord = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | WS_TABSTOP, 200, 325, 250, 25, hWnd, NULL, NULL, NULL);
    registerButton = CreateWindowW(L"button", L"Register", WS_VISIBLE | WS_CHILD, 200, 375, 100, 25, hWnd, (HMENU)REGISTER_USER_BUTTON, NULL, NULL);
}

void destroy_registration_page()
{
    //destroys all the elements of the registration page
    DestroyWindow(backButton);
    DestroyWindow(signUpTitle);
    DestroyWindow(firstName_label);
    DestroyWindow(firstName);
    DestroyWindow(lastName_label);
    DestroyWindow(lastName);
    DestroyWindow(eMail_label);
    DestroyWindow(eMail);
    DestroyWindow(userName_label);
    DestroyWindow(userName);
    DestroyWindow(passWord_label);
    DestroyWindow(passWord);
    DestroyWindow(confirmPassWord_label);
    DestroyWindow(confirmPassWord);
    DestroyWindow(registerButton);
    DestroyWindow(confirmPassIncorrect);
    DestroyWindow(emailInvalid);
}

void options_page(HWND hWnd)
{ //creates elements for the option page
    logOutButton = CreateWindowW(L"Button", L"Sign Out", WS_VISIBLE | WS_CHILD, 400, 10, 90, 40, hWnd, (HMENU)SIGN_OUT, NULL, NULL);
    if (user.admin == 1)
    { // checks if the loged in user is admin
        statusPageButton = CreateWindowW(L"button", L"View Student status", WS_VISIBLE | WS_CHILD, 150, 125, 200, 50, hWnd, (HMENU)VIEW_STATUS_ADMIN, NULL, NULL);
        questionAnswerButton = CreateWindowW(L"button", L"Add Questions", WS_VISIBLE | WS_CHILD, 150, 250, 200, 50, hWnd, (HMENU)ADD_QUESTION_PAGE, NULL, NULL); //pressing this buttion will open the add quesition page for admin
    }
    else if (user.admin == 0)
    { // checks if the loged in user is student
        statusPageButton = CreateWindowW(L"button", L"Your status", WS_VISIBLE | WS_CHILD, 150, 125, 200, 50, hWnd, (HMENU)VIEW_STATUS_STUDENT, NULL, NULL);
        questionAnswerButton = CreateWindowW(L"button", L"Practice Questions", WS_VISIBLE | WS_CHILD, 150, 250, 200, 50, hWnd, (HMENU)PRACTICE_QUESTION_BUTTON, NULL, NULL);
    }
}

void add_question_page(HWND hWnd)
{ // this is the user interface for admin to add question to the database
    backButton = CreateWindowW(L"button", L"Go Back", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 90, 30, hWnd, (HMENU)BACK_TO_OPTIONS, NULL, NULL);
    addQuestionLabel = CreateWindowW(L"static", L"Add your question below:", WS_VISIBLE | WS_CHILD, 50, 60, 400, 25, hWnd, NULL, NULL, NULL);
    addQuestion = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 50, 100, 400, 25, hWnd, NULL, NULL, NULL);
    addOptionLabel = CreateWindowW(L"static", L"Add your options below:", WS_VISIBLE | WS_CHILD, 50, 160, 400, 25, hWnd, NULL, NULL, NULL);
    firstOption = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 50, 200, 175, 25, hWnd, NULL, NULL, NULL);
    secondOption = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 275, 200, 175, 25, hWnd, NULL, NULL, NULL);
    thirdOption = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 50, 250, 175, 25, hWnd, NULL, NULL, NULL);
    fourthOption = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 275, 250, 175, 25, hWnd, NULL, NULL, NULL);
    correctAnswerLabel = CreateWindowW(L"static", L"Enter the correct answer from one of the above:", WS_VISIBLE | WS_CHILD, 50, 310, 400, 25, hWnd, NULL, NULL, NULL);
    correctAnswer = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, 50, 350, 175, 25, hWnd, NULL, NULL, NULL);
    addQuestionToDatabase = CreateWindowW(L"button", L"Add your question to database", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 400, 300, 25, hWnd, (HMENU)ADD_QUESTION_TO_DATABASE, NULL, NULL); // pressing this button will add the question to the database
}

void practice_question_page(HWND hWnd, struct Question que)
{
    //displays all the elements for the  practice quesion page 
    //retrieve the question here:

    wchar_t quest[300];
    wchar_t option[4][50];
    mbstowcs(quest, que.question, 300);
    mbstowcs(option[0], que.options[0], 50);
    mbstowcs(option[1], que.options[1], 50);
    mbstowcs(option[2], que.options[2], 50);
    mbstowcs(option[3], que.options[3], 50);
    backButton = CreateWindowW(L"button", L"Go Back", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 90, 30, hWnd, (HMENU)BACK_TO_OPTIONS, NULL, NULL);
    addQuestion = CreateWindowW(L"static", quest, WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 100, 400, 25, hWnd, NULL, NULL, NULL);
    firstOption = CreateWindowW(L"button", option[0], WS_VISIBLE | WS_CHILD | SS_CENTER | BS_AUTORADIOBUTTON, 50, 150, 150, 25, hWnd, NULL, NULL, NULL);
    secondOption = CreateWindowW(L"button", option[1], WS_VISIBLE | WS_CHILD | SS_CENTER | BS_AUTORADIOBUTTON, 250, 150, 150, 25, hWnd, NULL, NULL, NULL);
    thirdOption = CreateWindowW(L"button", option[2], WS_VISIBLE | WS_CHILD | SS_CENTER | BS_AUTORADIOBUTTON, 50, 200, 150, 25, hWnd, NULL, NULL, NULL);
    fourthOption = CreateWindowW(L"button", option[3], WS_VISIBLE | WS_CHILD | SS_CENTER | BS_AUTORADIOBUTTON, 250, 200, 150, 25, hWnd, NULL, NULL, NULL);
    nextQuestion = CreateWindowW(L"button", L"Next question", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 400, 200, 50, hWnd, (HMENU)SUBMIT_ANSWER, NULL, NULL);
}

void destroy_questions()
{
    //this destroys all the elements inside the question pages
    DestroyWindow(backButton);
    DestroyWindow(addQuestion);
    DestroyWindow(firstOption);
    DestroyWindow(secondOption);
    DestroyWindow(thirdOption);
    DestroyWindow(fourthOption);
    DestroyWindow(nextQuestion);
    DestroyWindow(answerNotChecked);
}

void destroy_questions_page()
{
    //destroys the element of the quesion page
    destroy_questions();
    DestroyWindow(addQuestionLabel);
    DestroyWindow(backButton);
    DestroyWindow(addOptionLabel);
    DestroyWindow(correctAnswerLabel);
    DestroyWindow(correctAnswer);
    DestroyWindow(addQuestionToDatabase);
}

void clear_text()
{
    //clears the text when the admin presses the add question to the data base in the add question page
    SetWindowTextW(addQuestion, L"");
    SetWindowTextW(firstOption, L"");
    SetWindowTextW(secondOption, L"");
    SetWindowTextW(thirdOption, L"");
    SetWindowTextW(fourthOption, L"");
    SetWindowTextW(correctAnswer, L"");
}

void display_status_page(HWND hWnd)
{
    //displays the status of the student
    backButton = CreateWindowW(L"button", L"Go Back", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 90, 30, hWnd, (HMENU)BACK_TO_OPTIONS, NULL, NULL);
    wchar_t string[70];
    name_label = CreateWindowW(L"static", L"Name:", WS_CHILD | WS_VISIBLE, 100, 100, 200, 25, hWnd, NULL, NULL, NULL);
    char data[70] = "";
    strcat(data, user.firstname);
    strcat(data, " ");
    strcat(data, user.lastname);
    mbstowcs(string, data, 70);
    name = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 100, 200, 25, hWnd, NULL, NULL, NULL);
    userName_label = CreateWindowW(L"static", L"Username:", WS_CHILD | WS_VISIBLE, 100, 150, 200, 25, hWnd, NULL, NULL, NULL);
    strcpy(data, user.username);
    mbstowcs(string, data, 70);
    userName = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 150, 200, 25, hWnd, NULL, NULL, NULL);
    eMail_label = CreateWindowW(L"static", L"Email:", WS_CHILD | WS_VISIBLE, 100, 200, 200, 25, hWnd, NULL, NULL, NULL);
    strcpy(data, user.email);
    mbstowcs(string, data, 70);
    eMail = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 200, 200, 25, hWnd, NULL, NULL, NULL);
    totalAttempts_label = CreateWindowW(L"static", L"Total attempts:", WS_CHILD | WS_VISIBLE, 100, 250, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(user.total_answers, data, 10);
    mbstowcs(string, data, 70);
    totalAttempts = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 250, 200, 25, hWnd, NULL, NULL, NULL);
    correctAnswerLabel = CreateWindowW(L"static", L"Correct answers:", WS_CHILD | WS_VISIBLE, 100, 300, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(user.correct_answers, data, 10);
    mbstowcs(string, data, 70);
    correctAnswer = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 300, 200, 25, hWnd, NULL, NULL, NULL);
    inCorrectAnswerLabel = CreateWindowW(L"static", L"Incorrect answers:", WS_CHILD | WS_VISIBLE, 100, 350, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(user.incorrect_answers, data, 10);
    mbstowcs(string, data, 70);
    inCorrectAnswer = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 350, 200, 25, hWnd, NULL, NULL, NULL);
    scoreLabel = CreateWindowW(L"static", L"Score:", WS_CHILD | WS_VISIBLE, 100, 400, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(user.score, data, 10);
    mbstowcs(string, data, 70);
    score = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 400, 200, 25, hWnd, NULL, NULL, NULL);
}

void destroy_status_page()
{
    //destroys all the elements in the status page
    DestroyWindow(backButton);
    DestroyWindow(name_label);
    DestroyWindow(name);
    DestroyWindow(userName_label);
    DestroyWindow(userName);
    DestroyWindow(correctAnswer);
    DestroyWindow(eMail_label);
    DestroyWindow(eMail);
    DestroyWindow(totalAttempts_label);
    DestroyWindow(totalAttempts);
    DestroyWindow(correctAnswerLabel);
    DestroyWindow(inCorrectAnswerLabel);
    DestroyWindow(inCorrectAnswer);
    DestroyWindow(scoreLabel);
    DestroyWindow(score);
    DestroyWindow(nextStudent);
}

void display_status_page_admin(HWND hWnd)
{
    // displays the status of all the students 
    struct Register student;
    printf("\n\n%d\n\n", student_postion);
    get_student_data(&student, &student_postion);
    printf("\n\n%d\n\n", student_postion);
    backButton = CreateWindowW(L"button", L"Go Back", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 90, 30, hWnd, (HMENU)BACK_TO_OPTIONS, NULL, NULL);
    wchar_t string[70];
    name_label = CreateWindowW(L"static", L"Name:", WS_CHILD | WS_VISIBLE, 100, 50, 200, 25, hWnd, NULL, NULL, NULL);
    char data[70] = "";
    strcat(data, student.firstname);
    strcat(data, " ");
    strcat(data, student.lastname);
    mbstowcs(string, data, 70);
    name = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 50, 200, 25, hWnd, NULL, NULL, NULL);
    userName_label = CreateWindowW(L"static", L"Username:", WS_CHILD | WS_VISIBLE, 100, 100, 200, 25, hWnd, NULL, NULL, NULL);
    strcpy(data, student.username);
    mbstowcs(string, data, 70);
    userName = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 100, 200, 25, hWnd, NULL, NULL, NULL);
    eMail_label = CreateWindowW(L"static", L"Email:", WS_CHILD | WS_VISIBLE, 100, 150, 200, 25, hWnd, NULL, NULL, NULL);
    strcpy(data, student.email);
    mbstowcs(string, data, 70);
    eMail = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 150, 200, 25, hWnd, NULL, NULL, NULL);
    totalAttempts_label = CreateWindowW(L"static", L"Total attempts:", WS_CHILD | WS_VISIBLE, 100, 200, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(student.total_answers, data, 10);
    mbstowcs(string, data, 70);
    totalAttempts = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 200, 200, 25, hWnd, NULL, NULL, NULL);
    correctAnswerLabel = CreateWindowW(L"static", L"Correct answers:", WS_CHILD | WS_VISIBLE, 100, 250, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(student.correct_answers, data, 10);
    mbstowcs(string, data, 70);
    correctAnswer = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 250, 200, 25, hWnd, NULL, NULL, NULL);
    inCorrectAnswerLabel = CreateWindowW(L"static", L"Incorrect answers:", WS_CHILD | WS_VISIBLE, 100, 300, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(student.incorrect_answers, data, 10);
    mbstowcs(string, data, 70);
    inCorrectAnswer = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 300, 200, 25, hWnd, NULL, NULL, NULL);
    scoreLabel = CreateWindowW(L"static", L"Score:", WS_CHILD | WS_VISIBLE, 100, 350, 200, 25, hWnd, NULL, NULL, NULL);
    itoa(student.score, data, 10);
    mbstowcs(string, data, 70);
    score = CreateWindowW(L"static", string, WS_CHILD | WS_VISIBLE, 250, 350, 200, 25, hWnd, NULL, NULL, NULL);
    nextStudent = CreateWindowW(L"button", L"Next Student", WS_CHILD | WS_VISIBLE, 175, 400, 150, 50, hWnd, (HMENU)NEXT_STUDENT, NULL, NULL);
}