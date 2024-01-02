#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <algorithm>

int GameplayLogic(int skor);
void MenuGame();
int OutroGame(int skor);

int NewGame()
{
    // Set the default score for a new game
    int newScore = 0;

    // Debug: Print information about starting a new game
    // printf("Starting a new game. Initial Score: %d\n", newScore);

    return newScore;
}

int LoadGame()
{
    int lastScore = 0; // Initialize to a default value
    FILE *file = fopen("History.txt", "r");

    if (file == NULL)
    {
        // Handle the case when the file is missing
        // printf("File is missing\n");
    }
    else
    {
        char line[100]; // Adjust the size according to your needs

        // Read lines until the end of the file
        while (fgets(line, sizeof(line), file) != NULL)
        {
            // Debug: Print the line read from the file
            // printf("Read line: %s", line);

            // Check if the line contains the expected format
            if (sscanf(line, "Terakhir Bermain: %*[^,], Skor: %d", &lastScore) == 0)
            {
                // Debug: Print the last score found
                // printf("Last Score: %d\n", lastScore);
                // Close the file and return the found score
                fclose(file);
                return lastScore;
            }
        }

        // Handle the case when the score is not found in the file
        // printf("Score not found in the file\n");

        // Close the file
        fclose(file);
    }

    return lastScore;
}

void BentukMobil(int x, int y, float kecilin, float rotation, int KursorY)
{
    setcolor(LIGHTCYAN);

    int AcuanKursorY = KursorY - (y + 600 * kecilin); // Acuan cursor y saat mobil digerakkan
    y += AcuanKursorY;

    arc(x + 250 * kecilin, y + 600 * kecilin, rotation, rotation + 130, 60 * kecilin); // efek gerak ban kiri
    arc(x + 750 * kecilin, y + 600 * kecilin, rotation, rotation + 130, 60 * kecilin); // efek gerak ban kanan

    circle(x + 250 * kecilin, y + 600 * kecilin, 75 * kecilin);                       // ban kiri lapisan 4 (Terluar)
    circle(x + 250 * kecilin, y + 600 * kecilin, 50 * kecilin);                       // ban kiri lapisan 3
    circle(x + 250 * kecilin, y + 600 * kecilin, 40 * kecilin);                       // ban kiri lapisan 2
    circle(x + 250 * kecilin, y + 600 * kecilin, 15 * kecilin);                       // ban kiri lapisan 1
    arc(x + 250 * kecilin, y + 600 * kecilin, 0 * kecilin, 180, 100 * kecilin);       // tutup ban kiri
    line(x + 150 * kecilin, y + 590 * kecilin, x + 175 * kecilin, y + 590 * kecilin); // garis horizontal ban kiri (kiri)
    line(x + 325 * kecilin, y + 590 * kecilin, x + 350 * kecilin, y + 590 * kecilin); // garis horizontal ban kiri (kanan)

    circle(x + 750 * kecilin, y + 600 * kecilin, 75 * kecilin);                       // ban kanan lapisan 4 (Terluar)
    circle(x + 750 * kecilin, y + 600 * kecilin, 50 * kecilin);                       // ban kanan lapisan 3
    circle(x + 750 * kecilin, y + 600 * kecilin, 40 * kecilin);                       // ban kanan lapisan 2
    circle(x + 750 * kecilin, y + 600 * kecilin, 15 * kecilin);                       // ban kanan lapisan 1
    arc(x + 750 * kecilin, y + 600 * kecilin, 0 * kecilin, 180, 100 * kecilin);       // tutup ban kanan
    line(x + 650 * kecilin, y + 590 * kecilin, x + 675 * kecilin, y + 590 * kecilin); // garis horizontal ban kanan (kiri)
    line(x + 825 * kecilin, y + 590 * kecilin, x + 850 * kecilin, y + 590 * kecilin); // garis horizontal ban kanan (kanan)

    line(x + 350 * kecilin, y + 600 * kecilin, x + 650 * kecilin, y + 600 * kecilin); // garis horizontal tutup ban kiri dan kanan (angka bawah)
    line(x + 135 * kecilin, y + 600 * kecilin, x + 150 * kecilin, y + 600 * kecilin); // garis horizontal tutup ban kiri (rangka bawah)
    line(x + 850 * kecilin, y + 600 * kecilin, x + 880 * kecilin, y + 600 * kecilin); // garis horizontal tutup ban kanan (rangka bawah)

    line(x + 105 * kecilin, y + 450 * kecilin, x + 105 * kecilin, y + 570 * kecilin); // garis vertikal kiri ban kiri (rangka tengah)
    arc(x + 305 * kecilin, y + 795 * kecilin, 90, 120, 400 * kecilin);                // tutup kap mobil (rangka tengah)
    line(x + 305 * kecilin, y + 395 * kecilin, x + 750 * kecilin, y + 395 * kecilin); // garis horizontal bawah kaca (rangka tengah)
    arc(x + 750 * kecilin, y + 570 * kecilin, 0, 90, 175 * kecilin);                  // tutup bagasi mobil (rangka tengah)

    line(x + 305 * kecilin, y + 395 * kecilin, x + 400 * kecilin, y + 250 * kecilin); // garis miring keatas (rangka atas)
    line(x + 400 * kecilin, y + 250 * kecilin, x + 675 * kecilin, y + 250 * kecilin); // garis horizontal (rangka atas)
    line(x + 675 * kecilin, y + 250 * kecilin, x + 750 * kecilin, y + 395 * kecilin); // garis miring kebawah (rangka atas)
    line(x + 355 * kecilin, y + 355 * kecilin, x + 410 * kecilin, y + 275 * kecilin); // garis miring keatas bagian dalam (rangka atas)
    line(x + 410 * kecilin, y + 275 * kecilin, x + 665 * kecilin, y + 275 * kecilin); // garis horizontal bagian dalam (rangka atas)
    line(x + 665 * kecilin, y + 275 * kecilin, x + 725 * kecilin, y + 395 * kecilin); // garis miring kebawah bagian dalam (rangka atas)
    line(x + 535 * kecilin, y + 275 * kecilin, x + 535 * kecilin, y + 395 * kecilin); // garis vertikal bagian dalam (rangka atas) kiri
    line(x + 565 * kecilin, y + 275 * kecilin, x + 565 * kecilin, y + 395 * kecilin); // garis vertikal bagian dalam (rangka atas) tengah
    line(x + 550 * kecilin, y + 275 * kecilin, x + 550 * kecilin, y + 395 * kecilin); // garis vertikal bagian dalam (rangka atas) kanan

    rectangle(x + 90 * kecilin, y + 570 * kecilin, x + 135 * kecilin, y + 610 * kecilin);  // kotak ban kiri
    rectangle(x + 90 * kecilin, y + 475 * kecilin, x + 105 * kecilin, y + 525 * kecilin);  // kotak lampu depan mobil
    rectangle(x + 330 * kecilin, y + 355 * kecilin, x + 355 * kecilin, y + 415 * kecilin); // kotak spion mobil
    rectangle(x + 490 * kecilin, y + 415 * kecilin, x + 535 * kecilin, y + 425 * kecilin); // kotak handle pintu mobil
    rectangle(x + 880 * kecilin, y + 570 * kecilin, x + 945 * kecilin, y + 610 * kecilin); // kotak ban kanan
}

const int MAX_MARKAJALAN = 7;

struct MarkaJalan
{
    int x1, y1, x2, y2;
};

void InisialisasiMarkaJalan(MarkaJalan markaJalan[], int startY1, int endY2)
{
    for (int i = 0; i < MAX_MARKAJALAN; ++i)
    {
        markaJalan[i].x1 = i * 200;
        markaJalan[i].y1 = startY1;
        markaJalan[i].x2 = markaJalan[i].x1 + 100;
        markaJalan[i].y2 = endY2;
    }
}

void BentukMarkaJalan(MarkaJalan markaJalan[], int KecepatanMarka)
{
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(WHITE);

    for (int i = 0; i < MAX_MARKAJALAN; ++i)
    {
        bar(markaJalan[i].x1, markaJalan[i].y1, markaJalan[i].x2, markaJalan[i].y2); // Use bar for filled rectangle

        markaJalan[i].x1 += KecepatanMarka;
        markaJalan[i].x2 += KecepatanMarka;

        if (markaJalan[i].x2 >= 1380)
        {
            markaJalan[i].x1 = -100;
            markaJalan[i].x2 = markaJalan[i].x1 + 100;
        }
    }
}

const int MAX_OBSBOX = 7;

struct ObsBox
{
    int x, y, width, height;
};

void BentukObsBox(struct ObsBox obsBox[MAX_OBSBOX], int gelombang, int KecepatanObsBox)
{
    setfillstyle(SOLID_FILL, BROWN);
    setcolor(BROWN);

    int width = 50;
    int height = 50;

    for (int i = 0; i < gelombang; ++i)
    {
        obsBox[i].x += KecepatanObsBox;

        if (obsBox[i].x > 1280)
        {
            obsBox[i].x = 0;
            obsBox[i].y = 250 + rand() % 500;
        }

        // Pastikan y berada di dalam rentang 250-750
        obsBox[i].y = obsBox[i].y < 250 ? 250 : (obsBox[i].y > 750 ? 750 : obsBox[i].y);

        rectangle(obsBox[i].x - width / 2, obsBox[i].y - height / 2, obsBox[i].x + width / 2, obsBox[i].y + height / 2);
        floodfill(obsBox[i].x, obsBox[i].y, BROWN);
    }
}

int BentukSkor(clock_t &WaktuMulai, int skor)
{
    clock_t WaktuSekarang = clock();
    int WaktuBerlalu = (WaktuSekarang - WaktuMulai) / CLOCKS_PER_SEC;
    int targetSkor = WaktuBerlalu * 1 + skor;  // Consider current score
    int SelisihSkor = targetSkor - skor;
    int EfekCepat = 1;  // Adjust this value for faster increase

    if (SelisihSkor > 0)
    {
        if (1 > SelisihSkor / EfekCepat)
        {
            skor += 1;
        }
        else
        {
            skor += SelisihSkor / EfekCepat;
        }
    }

    return skor;
}



void RiwayatGame(int skor)
{
    FILE *TxtFile = fopen("Carvole\\History.txt", "a"); // Open the file for writing
    if (TxtFile != NULL)
    {
        clock_t WaktuSekarang = clock();
        struct tm *WaktuLokal = localtime(&WaktuSekarang);
        char HistoriWaktu[100];
        strftime(HistoriWaktu, sizeof(HistoriWaktu), "%Y-%m-%d %H:%M:%S", WaktuLokal);

        fprintf(TxtFile, "Terakhir Bermain: %s, Skor: %d\n", HistoriWaktu, skor);

        fclose(TxtFile);
    }
    else
    {
        fprintf(stderr, "Error opening file: skor_history.txt\n");
    }
}
bool CekKlik(int x, int y, int left, int top, int right, int bottom)
{
    return (x >= left && x <= right && y >= top && y <= bottom);
}

int OutroGame(int skor)
{
    int gd = DETECT, gm;
    char path[] = "";

    initwindow(1280, 1000);
    int skorO = 0;
    while (!kbhit())
    {
        cleardevice();
        if (ismouseclick(WM_MOUSEMOVE))
        {
            int mouseY = mousey();
            int mouseX = mousex();
            char coordText1[20];
            char coordText2[20];
            sprintf(coordText1, "Mouse Y: %d", mouseY);
            sprintf(coordText2, "Mouse X: %d", mouseX);
            settextstyle(COMPLEX_FONT, 0, 2);
            settextstyle(COMPLEX_FONT, 0, 2);
            outtextxy(10, 10, coordText1);
            outtextxy(10, 30, coordText2);
        }

        char skorText[20];
        sprintf(skorText, "Skor: %d", skor);
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 6);
        outtextxy(520, 250, skorText);

        char Text1Screen4[20] = "";
        sprintf(Text1Screen4, "PLAY AGAIN");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(360, 415, Text1Screen4);
        rectangle(350, 400, 630, 465);

        char Text2Screen4[20] = "";
        sprintf(Text2Screen4, "SAVE GAME");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(705, 415, Text2Screen4);
        rectangle(690, 400, 950, 465);

        char Text3Screen4[20] = "";
        sprintf(Text3Screen4, "BACK MENU");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(370, 550, Text3Screen4);
        rectangle(350, 535, 630, 605);

        char Text4Screen4[20] = "";
        sprintf(Text4Screen4, "EXIT GAME");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(705, 550, Text4Screen4);
        rectangle(690, 535, 950, 605);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (CekKlik(x, y, 350, 400, 630, 465))
            {
                closegraph();
                int skor = NewGame();
                GameplayLogic(skor);
                break;
            }
            if (CekKlik(x, y, 690, 400, 950, 465))
            {
                // printf("skor %d", skor);
                RiwayatGame(skor);
            }
            if (CekKlik(x, y, 350, 535, 630, 605))
            {
                closegraph();
                MenuGame();
                break;
            }
            if (CekKlik(x, y, 690, 535, 950, 605))
            {
                exit(0);
            }
        }
        delay(50);
    }
    return skor;
}

int GameplayLogic(int skor)
{
    int gd = DETECT, gm;
    char path[] = "";
    int width = 1280;
    int height = 1000;
    float kecilin = 0.5;
    initwindow(width, height);

    srand((unsigned)time(NULL));
    struct ObsBox obsBox[MAX_OBSBOX];

    MarkaJalan markaJalan1[MAX_MARKAJALAN];
    MarkaJalan markaJalan2[MAX_MARKAJALAN];
    MarkaJalan markaJalan3[MAX_MARKAJALAN];
    MarkaJalan markaJalan4[MAX_MARKAJALAN];
    MarkaJalan markaJalan5[MAX_MARKAJALAN];

    int KecepatanMarka = 10;

    InisialisasiMarkaJalan(markaJalan1, 295, 305);
    InisialisasiMarkaJalan(markaJalan2, 395, 405);
    InisialisasiMarkaJalan(markaJalan3, 495, 505);
    InisialisasiMarkaJalan(markaJalan4, 595, 605);
    InisialisasiMarkaJalan(markaJalan5, 695, 705);

    int KecepatanObsBox = 20;

    int x = 615;
    int y = 0;
    float PutaranBan = 0;

    clock_t WaktuMulai = clock();

    while (!kbhit())
    {
        cleardevice();
        // Draw lanes
        setcolor(WHITE);
        line(0, 200, width, 200);
        line(0, 800, width, 800);

        BentukMarkaJalan(markaJalan1, KecepatanMarka);
        BentukMarkaJalan(markaJalan2, KecepatanMarka);
        BentukMarkaJalan(markaJalan3, KecepatanMarka);
        BentukMarkaJalan(markaJalan4, KecepatanMarka);
        BentukMarkaJalan(markaJalan5, KecepatanMarka);

        int gelombang = rand() % MAX_OBSBOX + 1;
        BentukObsBox(obsBox, gelombang, KecepatanObsBox);

        skor = BentukSkor(WaktuMulai, skor);

        char skorText[20];
        sprintf(skorText, "skor: %d", skor);
        setcolor(WHITE);
        settextstyle(8, 0, 3);
        outtextxy(600, 10, skorText);

        if (ismouseclick(WM_MOUSEMOVE))
        {
            int mouseY = mousey();
            int mouseX = mousex();
            y = mouseY;
            int titikAcuanX = x + 250 * kecilin;
            int KursorY = mouseY;
            if (mouseY < 250)
            {
                mouseY = 250;
            }
            else if (mouseY > 750)
            {
                mouseY = 750;
            }
            char coordText1[20];
            char coordText2[20];
            sprintf(coordText1, "Mouse Y: %d", mouseY);
            sprintf(coordText2, "Mouse X: %d", mouseX);
            settextstyle(8, 0, 2);
            outtextxy(10, 10, coordText1);
            settextstyle(8, 0, 2);
            outtextxy(10, 30, coordText2);
            PutaranBan += 5;

            BentukMobil(x + 250 * kecilin, y + 600 * kecilin, kecilin, PutaranBan, mouseY);
            // printf("Koor Mobil: (%d, %d, %d, %d)\n", x, y, titikAcuanX, KursorY);

            // printf("Koor Box: (%d, %d)\n", obsBox[0].x, obsBox[0].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[1].x, obsBox[1].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[2].x, obsBox[2].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[3].x, obsBox[3].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[4].x, obsBox[4].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[5].x, obsBox[5].y);
            // printf("Koor Box: (%d, %d)\n", obsBox[6].x, obsBox[6].y);

            int BatasNabrakX = 5;
            int BatasNabrakY = 25;

            bool MobilNabrak = false;

            for (int i = 0; i < MAX_OBSBOX; ++i)
            {
                if (abs(obsBox[i].x - 755) == BatasNabrakX && abs(obsBox[i].y - y) <= BatasNabrakY)
                {
                    MobilNabrak = true;
                }
            }

            if (MobilNabrak)
            {
                // printf("Nabrak!\n");
                closegraph();
                break;
            }

            delay(50);
        }
    }
    return OutroGame(skor);
}

void MenuGame()
{
    int gd = DETECT, gm;
    char path[] = "";

    initwindow(1280, 1000);
    while (!kbhit())
    {
        cleardevice();
        if (ismouseclick(WM_MOUSEMOVE))
        {
            int mouseY = mousey();
            int mouseX = mousex();
            char coordText1[20];
            char coordText2[20];
            sprintf(coordText1, "Mouse Y: %d", mouseY);
            sprintf(coordText2, "Mouse X: %d", mouseX);
            settextstyle(COMPLEX_FONT, 0, 2);
            settextstyle(COMPLEX_FONT, 0, 2);
            outtextxy(10, 10, coordText1);
            outtextxy(10, 30, coordText2);
        }

        char TextScreen1[20] = "";
        sprintf(TextScreen1, "NEW GAME");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(380, 410, TextScreen1);
        rectangle(350, 395, 610, 465);

        char Text2Screen1[20] = "";
        sprintf(Text2Screen1, "LOAD GAME");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(705, 410, Text2Screen1);
        rectangle(690, 395, 950, 465);

        char Text3Screen1[20] = "";
        sprintf(Text3Screen1, "CHOOSE CAR");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(525, 550, Text3Screen1);
        rectangle(510, 535, 800, 605);

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (CekKlik(x, y, 350, 395, 610, 465))
            {
                closegraph();
                int skor = NewGame();
                GameplayLogic(skor);
                break;
            }

            if (CekKlik(x, y, 690, 395, 950, 465))
            {
                closegraph();
                int skor = LoadGame();
                GameplayLogic(skor);
                break;
            }
            if (CekKlik(x, y, 510, 535, 800, 605))
            {
            }
        }
        delay(50);
    }
}

void IntroGame()
{
    int gd = DETECT, gm;
    char path[] = "";

    initwindow(1280, 1000);
    while (!kbhit())
    {
        cleardevice();
        if (ismouseclick(WM_MOUSEMOVE))
        {
            int mouseY = mousey();
            int mouseX = mousex();
            char coordText1[20];
            char coordText2[20];
            sprintf(coordText1, "Mouse Y: %d", mouseY);
            sprintf(coordText2, "Mouse X: %d", mouseX);
            settextstyle(COMPLEX_FONT, 0, 2);
            settextstyle(COMPLEX_FONT, 0, 2);
            outtextxy(10, 10, coordText1);
            outtextxy(10, 30, coordText2);
        }
        char judulgame[20] = "";
        sprintf(judulgame, "CARVOLE");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 10);
        outtextxy(370, 370, judulgame);

        char TextScreen1[20] = "";
        sprintf(TextScreen1, "PLAY");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(440, 525, TextScreen1);
        rectangle(380, 520, 610, 570);

        char Text2Screen1[20] = "";
        sprintf(Text2Screen1, "EXIT");
        setcolor(WHITE);
        settextstyle(COMPLEX_FONT, 0, 5);
        outtextxy(760, 525, Text2Screen1);
        rectangle(690, 520, 920, 570);

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (CekKlik(x, y, 380, 520, 610, 570))
            {
                closegraph(); // Close the current graph before opening MenuGame
                MenuGame();
                break; // Exit the loop to stop processing the intro screen
            }
            if (CekKlik(x, y, 690, 520, 920, 570))
            {
                exit(0);
            }
        }
        delay(50);
    }
}

int main()
{
    IntroGame();
    return 0;
}
