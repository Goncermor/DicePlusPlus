#include <iostream>
#include <locale.h>
#include <wchar.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <wchar.h>

#define Title "     ____  _\n    / __ \\(_)_______    __    __\n   / / / / / ___/ _ \\__/ /___/ /_\n  / /_/ / / /__/  __/_  __/_  __/\n /_____/_/\\___/\\___/ /_/   /_/"
#define CubeTop  L"┌───────┐"
#define CubeBottom  L"└───────┘"
#define Edge  L"│"
#define Space "  "
#define Color_Cyan 11
#define Color_White 7
#define Color_Green 10

std::wstring Creator[] = {
    L"   ______                                                    ",
    L"  / ____/___  ____  ________  _________ ___  ____  _____     ",
    L" / / __/ __ \\/ __ \\/ ___/ _ \\/ ___/ __ `__ \\/ __ \\/ ___/    ",
    L"/ /_/ / /_/ / / / / /__/  __/ /  / / / / / / /_/ / /         ",
    L"\\____/\\____/_/ /_/\\___/\\___/_/  /_/ /_/ /_/\\____/_/          "
};

std::wstring QR[] = {
    L" ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
    L" █ ▄▄▄▄▄ █▀▄▄     ██ ▄▄▄▄▄ █ ",
    L" █ █   █ █▄▀█▄██  ██ █   █ █ ",
    L" █ █▄▄▄█ █ ▄▀▄▀█▄ ▄█ █▄▄▄█ █ ",
    L" █▄▄▄▄▄▄▄█ █ █ █▄█▄█▄▄▄▄▄▄▄█ ",
    L" █ ▄▀▄▀█▄▄█▀██  ▄▄▄█ ▄▄█▄▄▀█ ",
    L" █ ▄▀ ▄▄▄▀ ▀▀▀█▀▄▀ █   ██▄▄█ ",
    L" █▄▄▀▀▀ ▄ ▀█▄█ ▄██▄   █ ▀▄ █ ",
    L" █▄▀▀██▄▄▀▄██▄ ▀ ▀ █▀▄ █▄▀▄█ ",
    L" █▄▄██▄█▄▄ ▄▄ ▄▀█  ▄▄▄  ▄█▀█ ",
    L" █ ▄▄▄▄▄ █▄  █▄▄▄▄ █▄█  ▀  █ ",
    L" █ █   █ █▀█▄▄▀▄▄█▄▄▄   ▀███ ",
    L" █ █▄▄▄█ █▀▄ ▀▀ █▀ ▀█▄▄▀▄█▄█ ",
    L" █▄▄▄▄▄▄▄█▄▄▄▄▄▄█▄▄██▄███▄▄█ ",
    L"http://profile.goncermor.com/"
};

const std::wstring Faces[6][3] = {
    {L"       ", L"   ■   ", L"       "},
    {L"     ■ ", L"       ", L" ■     "},
    {L"     ■ ", L"   ■   ", L" ■     "},
    {L" ■   ■ ", L"       ", L" ■   ■ "},
    {L" ■   ■ ", L"   ■   ", L" ■   ■ "},
    {L" ■ ■ ■ ", L"       ", L" ■ ■ ■ "}
};

const std::wstring Texts[3][2] = {
    {L"Dado++ por Goncermor [DEMO] -> https://github.com/Goncermor/Dice++", L"Dice++ By Goncermor[DEMO]->https://github.com/Goncermor/Dice++ Console"},
    {L"Digite o numero de dados: ", L"Enter number of dices: "},
    {L"Você obteve: ", L"You got: "}
};
int Lang = 1;

HANDLE console;
COORD topLeft = { 0, 0 };
CONSOLE_SCREEN_BUFFER_INFO screen;

void Clear() {
    // Substitute all chars in the console by " " and then go to 0,0 (A.K.A. Clear the console)
    DWORD written;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void DrawCubes(int Count, int *DiceValues) {
    // Draw the cubes tops
    for (int Cube = 0; Cube < Count; Cube++) std::wcout << CubeTop << Space;
    std::wcout << std::endl;

    // Print line by line
    for (int Line = 0; Line != 3; Line++) {

        // Print line of face, face by face
        for (int Face = 0; Face < Count; Face++) std::wcout << Edge << Faces[DiceValues[Face]][Line] << Edge << Space;
        std::wcout << std::endl;
    }

    // Draw the cubes bottoms
    for (int Cube = 0; Cube < Count; Cube++) std::wcout << CubeBottom << Space;
}

void PrintQR() {
    GetConsoleScreenBufferInfo(console, &screen); // Get Screen Buffer info
    // Write QR Text line by line on console center
    for (int Line = 0; Line != sizeof(QR) / sizeof(QR[0]); Line++) {
        COORD CeneterScr = { (screen.srWindow.Right - screen.srWindow.Left + 1) / 2 - sizeof(QR[Line]) / 2, (screen.srWindow.Bottom - screen.srWindow.Top + 1) / 2 - sizeof(QR) / sizeof(QR[0]) / 2 + Line};
        SetConsoleCursorPosition(console, CeneterScr);
        std::wcout << QR[Line];
    }  
}

void PrintCreator() {
    GetConsoleScreenBufferInfo(console, &screen); // Get Screen Buffer info
    // Write Creator Text line by line on console center
    for (int Line = 0; Line != sizeof(Creator) / sizeof(Creator[0]); Line++) {
        COORD CeneterScr = { (screen.srWindow.Right - screen.srWindow.Left + 1) / 2 - sizeof(Creator[Line]), (screen.srWindow.Bottom - screen.srWindow.Top + 1) / 2 - sizeof(Creator) / sizeof(Creator[0]) + Line };
        SetConsoleCursorPosition(console, CeneterScr);
        std::wcout << Creator[Line];
    }
}



int main()
{
    // Define the locale
    setlocale(LC_ALL, "en_US.UTF-8");
    fwide(stdout, 1);

    console = GetStdHandle(STD_OUTPUT_HANDLE); // Obtain the handle for the process console

    srand(time(NULL)); // Initialize random seed

    // Set Console Cursor Info
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = 0;
    lpCursor.dwSize = 100;

    while (1) {// Run indefinetrly
        // Declare Vars
        int Count;
        int* DiceValues;
        int Sum = 0;


        SetConsoleTitleW(Texts[0][Lang].c_str()); // Set Title
        SetConsoleTextAttribute(console, Color_Cyan); // Set the color to cyan
        std::cout << Title;
        SetConsoleTextAttribute(console, Color_White);
        std::wcout << std::endl << std::endl << Texts[1][Lang]; // Get dice count
        

        //Show the cursor
        lpCursor.bVisible = 1;
        SetConsoleCursorInfo(console, &lpCursor);

        std::cin >> Count; // Read the value

        //Hide the cursor
        lpCursor.bVisible = 0;
        SetConsoleCursorInfo(console, &lpCursor);

        DiceValues = new int[Count];

        Clear();
        SetConsoleTextAttribute(console, Color_Green); // Set the color to Lime Green
        // Scroll Animation
        for (int Scroll = 0; Scroll < 25; Scroll++) {
           
            // Generate random dice values
            for (int Dados = 0; Dados != Count; Dados++) DiceValues[Dados] = rand() % 5;

            SetConsoleCursorPosition(console, topLeft);
            DrawCubes(Count, DiceValues);
            Sleep(50);
        }
        SetConsoleCursorPosition(console, topLeft);
        for (int Dados = 0; Dados != Count; Dados++) DiceValues[Dados] = rand() % 5;
        DrawCubes(Count, DiceValues); // Last draw

        for (int Dice = 0; Dice != Count; Dice++) Sum += DiceValues[Dice] + 1; // Sum all the values

        SetConsoleTextAttribute(console, Color_White); // Set the color to white

        std::wcout << std::endl << Texts[2][Lang] << Sum;
        Sleep(2000); // Wait 5 Seconds for the user to see the value
        Clear();
        SetConsoleTextAttribute(console, Color_Cyan);
        PrintCreator();
        Sleep(2000); // Wait 5 Seconds for the user to see the value
        Clear();
        SetConsoleTextAttribute(console, 7);
        PrintQR();
        Sleep(3000); // Wait 5 Seconds for the user to see QrCode
        Clear();
        if (Lang) Lang = 0;else Lang = 1; // Toggle the language
    }

}