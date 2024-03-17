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

std::wstring Creator[] = {
    L"       ~ By Goncermor ~     ",
    L"                            ",
    L" ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
    L" █ ▄▄▄▄▄ █▀▄▄     ██ ▄▄▄▄▄ █",
    L" █ █   █ █▄▀█▄██  ██ █   █ █",
    L" █ █▄▄▄█ █ ▄▀▄▀█▄ ▄█ █▄▄▄█ █",
    L" █▄▄▄▄▄▄▄█ █ █ █▄█▄█▄▄▄▄▄▄▄█",
    L" █ ▄▀▄▀█▄▄█▀██  ▄▄▄█ ▄▄█▄▄▀█",
    L" █ ▄▀ ▄▄▄▀ ▀▀▀█▀▄▀ █   ██▄▄█",
    L" █▄▄▀▀▀ ▄ ▀█▄█ ▄██▄   █ ▀▄ █",
    L" █▄▀▀██▄▄▀▄██▄ ▀ ▀ █▀▄ █▄▀▄█",
    L" █▄▄██▄█▄▄ ▄▄ ▄▀█  ▄▄▄  ▄█▀█",
    L" █ ▄▄▄▄▄ █▄  █▄▄▄▄ █▄█  ▀  █",
    L" █ █   █ █▀█▄▄▀▄▄█▄▄▄   ▀███",
    L" █ █▄▄▄█ █▀▄ ▀▀ █▀ ▀█▄▄▀▄█▄█",
    L" █▄▄▄▄▄▄▄█▄▄▄▄▄▄█▄▄██▄███▄▄█",
    L"http://profile.goncermor.com/"
};

std::wstring QR[] = {
    L"       ~ By Goncermor ~      ",
    L"                             ",
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

const std::string Texts[] = {
    "Dado++ Consola por Goncermor [DEMO] -> https://github.com/Goncermor/Dice++",
    "Digite o numero de dados",
    "Você obteve: ",

};


HANDLE console;
COORD topLeft = { 0, 0 };

void Clear() {
    // Substitute all chars in the console by " " and then go to 0,0 (A.K.A. Clear the console)
    CONSOLE_SCREEN_BUFFER_INFO screen;
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
        for (int Face = 0; Face < Count; Face++) {
            std::wcout << Edge;
            std::wcout << Faces[DiceValues[Face]][Line];
            std::wcout << Edge << Space;
        }

        std::wcout << std::endl;
    }

    // Draw the cubes bottoms
    for (int Cube = 0; Cube < Count; Cube++) std::wcout << CubeBottom << Space;
}

void PrintQR() {
    CONSOLE_SCREEN_BUFFER_INFO screen;
    GetConsoleScreenBufferInfo(console, &screen);

    for (int Line = 0; Line != sizeof(QR) / sizeof(QR[0]); Line++) {
        COORD CeneterScr = { (screen.srWindow.Right - screen.srWindow.Left + 1) / 2 - sizeof(QR[Line]) / 2, (screen.srWindow.Bottom - screen.srWindow.Top + 1) / 2 - sizeof(QR) / sizeof(QR[0]) / 2 + Line};
        SetConsoleCursorPosition(console, CeneterScr);
        std::wcout << QR[Line];
    }  
}

void PrintCreator() {
    CONSOLE_SCREEN_BUFFER_INFO screen;
    GetConsoleScreenBufferInfo(console, &screen);

    for (int Line = 0; Line != sizeof(Creator) / sizeof(Creator[0]); Line++) {
        COORD CeneterScr = { (screen.srWindow.Right - screen.srWindow.Left + 1) / 2 - sizeof(Creator[Line]) / 2, (screen.srWindow.Bottom - screen.srWindow.Top + 1) / 2 - 16 / 2 + Line };
        SetConsoleCursorPosition(console, CeneterScr);
        std::wcout << QR[Line];
    }
}



int main()
{
    // Define the locale
    setlocale(LC_ALL, "en_US.UTF-8");
    fwide(stdout, 1);

    console = GetStdHandle(STD_OUTPUT_HANDLE); // Obtain the handle for the process console

    srand(time(NULL)); // Initialize random seed

    // Disable the Console Cursor
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = 0;
    lpCursor.dwSize = 100;
   

    while (1) {// Run indefinetrly
        SetConsoleTitleA("Dice++ Console By Goncermor [DEMO] -> https://github.com/Goncermor/Dice++ Console"); // Set Title
        SetConsoleTextAttribute(console,11); // Set the color to cyan
        std::cout << Title;
        SetConsoleTextAttribute(console, 7);
        std::cout << std::endl << std::endl << "Enter number of dices: "; // Get dice count
        int Count;

        //Show the cursor
        lpCursor.bVisible = 1;
        SetConsoleCursorInfo(console, &lpCursor);

        std::cin >> Count; // Read the value

        //Hide the cursor
        lpCursor.bVisible = 0;
        SetConsoleCursorInfo(console, &lpCursor);

        // Generate random values for the dices
        int* DiceValues = new int[Count];

        Clear();
        SetConsoleTextAttribute(console, 10); // Set the color to Lime Green
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

        int Sum = 0;
        for (int Dice = 0; Dice != Count; Dice++) Sum += DiceValues[Dice] + 1; // Sum all the values

        SetConsoleTextAttribute(console, 7); // Set the color to white

        std::cout << std::endl << "You got: " << Sum;
        Sleep(5000); // Wait 5 Seconds for the user to see the value
        Clear();
        PrintQR();
        Sleep(5000); // Wait 5 Seconds for the user to see QrCode
        Clear();
    }

}