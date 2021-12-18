#include "keypad.h"
#include "lcd.h"
#include "ssd.h"
#include "adc.h"
#include "led.h"
#include <pic18f4520.h>

#define L_L1 0x80
#define L_L2 0xC0
#define L_CLR 0x01

unsigned int oldValue;
unsigned char tecla;
char enable = 0;
long int studyTime = 54000, breakTime = 18000, bigBreak = 90000, time = 0, reset = 1;
long int totalStudied = 0, totalBreak = 0, studyGoal = 0, oldStudyGoal = 0;

void instructions();
void verifyGoal();

void operate(unsigned char op)
{
    switch (op)
    {
    case 'U':
        if (reset % 2 == 0)
        {
            breakTime += 60;
            time = breakTime;
        }
        else if (reset == 8)
        {
            bigBreak += 60;
            time = bigBreak;
        }
        else
        {
            studyTime += 60;
            time = studyTime;
        }
        break;

    case 'D':
        if (reset % 2 == 0)
        {
            breakTime -= 60;
            time = breakTime;
        }
        else if (reset == 8)
        {
            bigBreak -= 60;
            time = bigBreak;
        }
        else
        {
            studyTime -= 60;
            time = studyTime;
        }
        break;

    case 'S':
        if (reset % 2 == 0)
        {
            lcdCommand(L_CLR);
            lcdString("Hora do descanso!");
        }
        else if (studyGoal != 0)
        {
            lcdCommand(L_CLR);
            lcdString("Atual meta:");
            lcdCommand(L_L2);
            lcdNumber(studyGoal);
            lcdString(" minutos");
            enable = 0;
        }
        for (time; time > 0; time--)
        {
            ssdDigit(((time / 3600) % 24) / 10, 0);
            ssdDigit(((time / 3600) % 24) % 10, 1);
            ssdDigit((time / 600) % 6, 2);
            ssdDigit((time / 60) % 10, 3);
            if (reset % 2 != 0)
            {
                totalStudied++;
            }
            else
            {
                totalBreak++;
            }
            ssdUpdate();
            for (int tempo = 0; tempo < 500; tempo++)
                ; // +- 10ms
        }
        reset++;
        verifyGoal();
        lcdCommand(L_CLR);
        lcdString("Tempo de estudo:");
        lcdCommand(L_L2);
        lcdNumber(totalStudied / 3600);
        lcdString(" minutos");
        break;

    case 'L':
        lcdCommand(L_CLR);
        enable = 1;
        break;

    case 's':
        reset++;
        break;
    }
}

void LeTeclado(void)
{
    if (kpRead() != oldValue)
    {
        oldValue = kpRead();
        tecla = kpReadKey();
        if (reset % 2 == 0)
        {
            time = breakTime;
        }
        else if (reset == 8)
        {
            time = bigBreak;
            reset = 0;
        }
        else
        {
            time = studyTime;
        }
        operate(tecla);
    }
}

void SetaMeta(void)
{
    studyGoal = adcRead(0);
    if (studyGoal != oldStudyGoal)
    {
        oldStudyGoal = studyGoal;
        lcdCommand(L_L1);
        lcdString("Atual meta:");
        lcdCommand(L_L2);
        lcdNumber(studyGoal);
        lcdString(" minutos");
        for (int i = 0; i < 8; i++)
        {
            DesligarLed(i);
        }
    }
}

void verifyGoal()
{
    if (studyGoal != 0)
    {
        int test = (totalStudied * 100) / (studyGoal * 3600);
        int j = 0;

        if (test > 87)
        {
            j = 8;
        }
        else if (test >= 75)
        {
            j = 7;
        }
        else if (test >= 62)
        {
            j = 6;
        }
        else if (test >= 50)
        {
            j = 5;
        }
        else if (test >= 37)
        {
            j = 4;
        }
        else if (test >= 25)
        {
            j = 3;
        }
        else if (test >= 12)
        {
            j = 2;
        }
        else
        {
            j = 1;
        }

        for (int i = 0; i < j; i++)
        {
            LigarLed(i);
        }
    }
}

void main(void)
{
    char slot;

    lcdInit();
    kpInit();
    ssdInit();
    ConfiguraLed();
    adcInit();

    // inicializa��es
    for (;;)
    {
        switch (slot)
        {
        case 0:
            LeTeclado();
            slot = 1;
            break;
        case 1:
            kpDebounce();
            slot = 2;
            break;
        case 2:
            if (enable == 1)
            {
                SetaMeta();
            }
            slot = 0;
            break;
        default:
            slot = 0;
            break;
        }
        ssdDigit(((time / 3600) % 24) / 10, 0);
        ssdDigit(((time / 3600) % 24) % 10, 1);
        ssdDigit((time / 600) % 6, 2);
        ssdDigit((time / 60) % 10, 3);
        ssdUpdate();
    }
}
