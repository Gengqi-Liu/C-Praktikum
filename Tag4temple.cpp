#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H


class PIDController
{
private:

    // Verstärkungsfaktoren
    double m_dKp;
    double m_dKi;
    double m_dKd;

    // Abtastzeit
    double m_dTa;

    // Summe der Regelabweichungen
    double m_dEsum;

    // Regelabweichung des vorherigen Zeitschritts
    double m_deold;

    // Stellgröße
    double m_dU;


public:

    // Konstruktor
    PIDController(double Kp,
                  double Ki,
                  double Kd,
                  double Ta);

    // Berechnung der Stellgröße
    void calculateU(double w, double y);

    // Stellgröße zurückgeben
    double GetU();
};


#endif

//PID

#include "PIDController.h"


PIDController::PIDController(double Kp,
                             double Ki,
                             double Kd,
                             double Ta)
{
    // Reglerparameter speichern
    m_dKp = Kp;
    m_dKi = Ki;
    m_dKd = Kd;
    m_dTa = Ta;

    // Anfangswerte
    m_dEsum = 0.0;
    m_deold = 0.0;
    m_dU = 0.0;
}


void PIDController::calculateU(double w, double y)
{
    // Regelabweichung
    double e;

    // e(k) = Sollwert - Istwert
    e = w - y;

    // E(k) = E(k-1) + e(k)
    m_dEsum = m_dEsum + e;

    // PID-Regelalgorithmus
    m_dU =
        m_dKp * e
        + m_dKi * m_dTa * m_dEsum
        + m_dKd * (e - m_deold) / m_dTa;

    // Fehler für nächsten Zeitschritt speichern
    m_deold = e;
}


double PIDController::GetU()
{
    return m_dU;
}
//...............
//h
//...............

#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H


#include "InterfaceSIM.h"
#include "PIDController.h"


class KeyboardControl
{
private:

    // Sollgeschwindigkeit
    // [0] = rechter Motor
    // [1] = linker Motor
    double m_dSollGeschwindigkeit[2];


    // Istgeschwindigkeit
    // [0] = rechter Motor
    // [1] = linker Motor
    double m_dIstGeschwindigkeit[2];


    // Signallängen
    // [0] = rechter Motor
    // [1] = linker Motor
    int m_iMicros[2];


    // Schnittstelle zur Simulation
    InterfaceSIM m_Interface;


    // PID-Regler
    // Ein Regler für jeden Motor
    PIDController m_ReglerRechts;
    PIDController m_ReglerLinks;


public:

    // Konstruktor
    KeyboardControl();


    // Kommunikation mit Tastatur
    void Communicate();


    // Kommunikation mit Simulation
    void Step();


    // Pointer für Parallelisierung
    static KeyboardControl* transferPointer;


    // Transferfunktion für Parallelisierung
    static void transferFunction();
};


#endif

//...............
//cpp
//...............
#include "KeyboardControl.h"

#include <iostream>
#include <ncurses.h>
#include <signal.h>


// Statischen Pointer definieren
KeyboardControl* KeyboardControl::transferPointer;


// Konstruktor
//
// Die beiden PID-Regler werden laut Skript
// über die Initialisierungsliste initialisiert.
//
// Kp = 500.0
// Ki = 1850.0
// Kd = 0.0
// Ta = 0.04
KeyboardControl::KeyboardControl()
    : m_ReglerRechts(500.0, 1850.0, 0.0, 0.04),
      m_ReglerLinks(500.0, 1850.0, 0.0, 0.04)
{
    // Anfangswert der Sollgeschwindigkeit
    m_dSollGeschwindigkeit[0] = 0.0;
    m_dSollGeschwindigkeit[1] = 0.0;


    // Anfangswert der Istgeschwindigkeit
    m_dIstGeschwindigkeit[0] = 0.0;
    m_dIstGeschwindigkeit[1] = 0.0;


    // Nulllage des Servosignals
    m_iMicros[0] = 1500;
    m_iMicros[1] = 1500;


    // Pointer zeigt auf das aktuelle Objekt
    transferPointer = this;


    // InterfaceSIM initialisieren
    //
    // Zeitschrittlänge = 0.04 s
    // transferFunction wird zyklisch aufgerufen
    m_Interface.Initialize(0.04, transferFunction);
}



// --------------------------------------------------
// transferFunction
// --------------------------------------------------

void KeyboardControl::transferFunction()
{
    // Step() über transferPointer aufrufen
    transferPointer->Step();
}



// --------------------------------------------------
// Communicate
// --------------------------------------------------

void KeyboardControl::Communicate()
{
    // ncurses starten
    initscr();

    // getch() soll nicht auf eine Eingabe warten
    nodelay(stdscr, TRUE);

    // Tasteneingaben nicht zusätzlich anzeigen
    noecho();


    int iTaste = -1;

    bool bQuit = false;


    // ----------------------------------------------
    // Parallele Ausführung von Step() starten
    // ----------------------------------------------

    sigprocmask(SIG_UNBLOCK,
                &m_Interface.mask,
                nullptr);



    // ==============================================
    // Erste Schleife:
    // Kommunikation mit dem Benutzer
    // ==============================================

    while (!bQuit)
    {
        // Taste einlesen
        iTaste = getch();


        // Nur reagieren, wenn wirklich
        // eine Taste gedrückt wurde
        if (iTaste != -1)
        {

            // --------------------------------------
            // w = vorwärts
            // --------------------------------------

            if (iTaste == 'w')
            {
                m_dSollGeschwindigkeit[0] += 0.01;
                m_dSollGeschwindigkeit[1] += 0.01;
            }


            // --------------------------------------
            // s = rückwärts
            // --------------------------------------

            else if (iTaste == 's')
            {
                m_dSollGeschwindigkeit[0] -= 0.01;
                m_dSollGeschwindigkeit[1] -= 0.01;
            }


            // --------------------------------------
            // a = links
            //
            // rechter Motor +0.005
            // linker Motor  -0.005
            // --------------------------------------

            else if (iTaste == 'a')
            {
                m_dSollGeschwindigkeit[0] += 0.005;
                m_dSollGeschwindigkeit[1] -= 0.005;
            }


            // --------------------------------------
            // d = rechts
            //
            // rechter Motor -0.005
            // linker Motor  +0.005
            // --------------------------------------

            else if (iTaste == 'd')
            {
                m_dSollGeschwindigkeit[0] -= 0.005;
                m_dSollGeschwindigkeit[1] += 0.005;
            }


            // --------------------------------------
            // b = break
            //
            // Roboter anhalten,
            // Programm aber nicht beenden
            // --------------------------------------

            else if (iTaste == 'b')
            {
                m_dSollGeschwindigkeit[0] = 0.0;
                m_dSollGeschwindigkeit[1] = 0.0;
            }


            // --------------------------------------
            // q = quit
            //
            // Roboter anhalten und
            // erste Schleife verlassen
            // --------------------------------------

            else if (iTaste == 'q')
            {
                m_dSollGeschwindigkeit[0] = 0.0;
                m_dSollGeschwindigkeit[1] = 0.0;

                bQuit = true;
            }



            // ======================================
            // Sollgeschwindigkeiten begrenzen
            //
            // Erlaubter Bereich:
            // [-0.5, +0.5] m/s
            // ======================================


            // rechter Motor

            if (m_dSollGeschwindigkeit[0] > 0.5)
            {
                m_dSollGeschwindigkeit[0] = 0.5;
            }

            if (m_dSollGeschwindigkeit[0] < -0.5)
            {
                m_dSollGeschwindigkeit[0] = -0.5;
            }


            // linker Motor

            if (m_dSollGeschwindigkeit[1] > 0.5)
            {
                m_dSollGeschwindigkeit[1] = 0.5;
            }

            if (m_dSollGeschwindigkeit[1] < -0.5)
            {
                m_dSollGeschwindigkeit[1] = -0.5;
            }



            // ======================================
            // Werte in der Konsole anzeigen
            // ======================================

            clear();


            printw(
                "Letzte Taste: %c\n",
                iTaste
            );


            printw(
                "Sollgeschwindigkeit rechts: %.3f m/s\n",
                m_dSollGeschwindigkeit[0]
            );


            printw(
                "Sollgeschwindigkeit links:  %.3f m/s\n",
                m_dSollGeschwindigkeit[1]
            );
        }
    }



    // ==============================================
    // Zweite Schleife
    //
    // Nach q warten, bis der Roboter
    // tatsächlich steht.
    //
    // Step() läuft währenddessen weiter.
    // ==============================================

    while (m_dIstGeschwindigkeit[0] != 0.0 ||
           m_dIstGeschwindigkeit[1] != 0.0)
    {
        // Warten bis Istgeschwindigkeiten = 0
    }



    // ==============================================
    // Parallele Ausführung von Step() beenden
    // ==============================================

    sigprocmask(SIG_BLOCK,
                &m_Interface.mask,
                nullptr);



    // ncurses ausschalten
    endwin();
}



// --------------------------------------------------
// Step
// --------------------------------------------------

void KeyboardControl::Step()
{
    // ==============================================
    // 1. Istgeschwindigkeit einlesen
    //
    // GetInput() darf laut Skript nur EINMAL
    // am Anfang von Step() aufgerufen werden.
    // ==============================================

    double* pdInput = m_Interface.GetInput();


    // rechte Istgeschwindigkeit
    m_dIstGeschwindigkeit[0] = pdInput[0];


    // linke Istgeschwindigkeit
    m_dIstGeschwindigkeit[1] = pdInput[1];



    // ==============================================
    // 2. PID-Regler rechter Motor
    //
    // Sollgeschwindigkeit = Führungsgröße
    // Istgeschwindigkeit  = Regelgröße
    // ==============================================

    m_ReglerRechts.calculateU(
        m_dSollGeschwindigkeit[0],
        m_dIstGeschwindigkeit[0]
    );



    // ==============================================
    // 3. PID-Regler linker Motor
    // ==============================================

    m_ReglerLinks.calculateU(
        m_dSollGeschwindigkeit[1],
        m_dIstGeschwindigkeit[1]
    );



    // ==============================================
    // 4. Stellgröße holen und um 1500 µs verschieben
    //
    // Laut Skript:
    // Servosignal = 1500 µs + u
    // ==============================================

    m_iMicros[0] =
        1500 + m_ReglerRechts.GetU();


    m_iMicros[1] =
        1500 + m_ReglerLinks.GetU();



    // ==============================================
    // 5. Signallängen begrenzen
    //
    // Erlaubter Bereich:
    // [1000 µs, 2000 µs]
    // ==============================================


    // rechter Motor

    if (m_iMicros[0] > 2000)
    {
        m_iMicros[0] = 2000;
    }

    if (m_iMicros[0] < 1000)
    {
        m_iMicros[0] = 1000;
    }


    // linker Motor

    if (m_iMicros[1] > 2000)
    {
        m_iMicros[1] = 2000;
    }

    if (m_iMicros[1] < 1000)
    {
        m_iMicros[1] = 1000;
    }



    // ==============================================
    // 6. Stellgrößen an Simulation senden
    // ==============================================

    m_Interface.SetOutputs(m_iMicros);
}

//...............
//main
//...............
#include "KeyboardControl.h"


int main()
{
    // Tastatursteuerung erstellen
    KeyboardControl control;


    // Steuerung starten
    control.Communicate();


    return 0;
}
