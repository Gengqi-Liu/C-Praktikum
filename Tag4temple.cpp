
//...............
//h
//...............

#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include "InterfaceSIM.h"

class KeyboardControl
{
private:
    // Sollgeschwindigkeit
    // [0] = rechts
    // [1] = links
    double m_dSollGeschwindigkeit[2];

    // Istgeschwindigkeit
    // [0] = rechts
    // [1] = links
    double m_dIstGeschwindigkeit[2];

    // Signallängen für die Simulation
    // [0] = rechts
    // [1] = links
    int m_iMicros[2];

    // Schnittstelle zur Simulation
    InterfaceSIM m_Interface;

public:
    KeyboardControl();

    void Communicate();
    void Step();
};

#endif

//...............
//cpp
//...............
#include "KeyboardControl.h"

#include <iostream>
#include <ncurses.h>


// Konstruktor
KeyboardControl::KeyboardControl()
{
    // Anfangs soll der Roboter stehen
    m_dSollGeschwindigkeit[0] = 0.0;
    m_dSollGeschwindigkeit[1] = 0.0;

    m_dIstGeschwindigkeit[0] = 0.0;
    m_dIstGeschwindigkeit[1] = 0.0;

    // Nulllage des Signals = 1500 µs
    m_iMicros[0] = 1500;
    m_iMicros[1] = 1500;

    // InterfaceSIM initialisieren
    // Zeitschrittlänge = 0.04 s
    // Zweites Argument wird erst in 2.7 ergänzt
    m_Interface.Initialize(0.04, nullptr);
}


void KeyboardControl::Communicate()
{
    // ncurses starten
    initscr();

    // Eingaben sofort einlesen, ohne Enter
    nodelay(stdscr, TRUE);
    noecho();

    int iTaste = -1;
    bool bQuit = false;

    // Erste Schleife:
    // Tastatureingaben verarbeiten
    while (!bQuit)
    {
        iTaste = getch();

        // Nur reagieren, wenn wirklich eine Taste gedrückt wurde
        if (iTaste != -1)
        {
            // w = vorwärts
            if (iTaste == 'w')
            {
                m_dSollGeschwindigkeit[0] += 0.01;
                m_dSollGeschwindigkeit[1] += 0.01;
            }

            // s = rückwärts
            else if (iTaste == 's')
            {
                m_dSollGeschwindigkeit[0] -= 0.01;
                m_dSollGeschwindigkeit[1] -= 0.01;
            }

            // a = links drehen
            else if (iTaste == 'a')
            {
                m_dSollGeschwindigkeit[0] += 0.005;
                m_dSollGeschwindigkeit[1] -= 0.005;
            }

            // d = rechts drehen
            else if (iTaste == 'd')
            {
                m_dSollGeschwindigkeit[0] -= 0.005;
                m_dSollGeschwindigkeit[1] += 0.005;
            }

            // b = break
            else if (iTaste == 'b')
            {
                m_dSollGeschwindigkeit[0] = 0.0;
                m_dSollGeschwindigkeit[1] = 0.0;
            }

            // q = quit
            else if (iTaste == 'q')
            {
                m_dSollGeschwindigkeit[0] = 0.0;
                m_dSollGeschwindigkeit[1] = 0.0;

                bQuit = true;
            }


            // Sollgeschwindigkeit rechts begrenzen
            if (m_dSollGeschwindigkeit[0] > 0.5)
                m_dSollGeschwindigkeit[0] = 0.5;

            if (m_dSollGeschwindigkeit[0] < -0.5)
                m_dSollGeschwindigkeit[0] = -0.5;


            // Sollgeschwindigkeit links begrenzen
            if (m_dSollGeschwindigkeit[1] > 0.5)
                m_dSollGeschwindigkeit[1] = 0.5;

            if (m_dSollGeschwindigkeit[1] < -0.5)
                m_dSollGeschwindigkeit[1] = -0.5;


            // Anzeige der letzten Taste und Sollgeschwindigkeiten
            clear();

            printw("Letzte Taste: %c\n", iTaste);

            printw("Sollgeschwindigkeit rechts: %.3f m/s\n",
                   m_dSollGeschwindigkeit[0]);

            printw("Sollgeschwindigkeit links:  %.3f m/s\n",
                   m_dSollGeschwindigkeit[1]);
        }
    }


    // ncurses beenden
    endwin();

    // Nach dem Beenden noch einmal in der normalen Konsole anzeigen
    std::cout << "Letzte Taste: "
              << static_cast<char>(iTaste)
              << std::endl;

    std::cout << "Sollgeschwindigkeit rechts: "
              << m_dSollGeschwindigkeit[0]
              << " m/s"
              << std::endl;

    std::cout << "Sollgeschwindigkeit links: "
              << m_dSollGeschwindigkeit[1]
              << " m/s"
              << std::endl;
}


void KeyboardControl::Step()
{
    // GetInput() laut Skript nur EINMAL
    // zu Beginn von Step() aufrufen
    double* pdInput = m_Interface.GetInput();

    // Istgeschwindigkeiten speichern
    m_dIstGeschwindigkeit[0] = pdInput[0];
    m_dIstGeschwindigkeit[1] = pdInput[1];


    // Sollgeschwindigkeit [-0.5, +0.5]
    // in Signallänge [1000, 2000] umrechnen
    m_iMicros[0] =
        1500 + m_dSollGeschwindigkeit[0] * 1000;

    m_iMicros[1] =
        1500 + m_dSollGeschwindigkeit[1] * 1000;


    // Signallänge rechts begrenzen
    if (m_iMicros[0] > 2000)
        m_iMicros[0] = 2000;

    if (m_iMicros[0] < 1000)
        m_iMicros[0] = 1000;


    // Signallänge links begrenzen
    if (m_iMicros[1] > 2000)
        m_iMicros[1] = 2000;

    if (m_iMicros[1] < 1000)
        m_iMicros[1] = 1000;


    // Neue Stellgrößen an die Simulation senden
    m_Interface.SetOutputs(m_iMicros);
}

//...............
//main
//...............
#include "KeyboardControl.h"

int main()
{
    // Objekt der Klasse KeyboardControl erstellen
    KeyboardControl control;

    // Tastatursteuerung starten
    control.Communicate();

    return 0;
}
