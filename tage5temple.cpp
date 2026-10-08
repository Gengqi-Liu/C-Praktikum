#ifndef POSESTIMATION_H
#define POSESTIMATION_H


class PosEstimation
{
private:

    // x[0] = x-Koordinate
    // x[1] = y-Koordinate
    // x[2] = Raumrichtung
    double m_dX[3];

    // Mittlere Geschwindigkeit des vorherigen Zeitschritts
    double m_dVelAverage;


public:

    PosEstimation();

    // Alles auf Null zurücksetzen
    void Reset();

    // Neue Position berechnen
    void PredictPosition(double dSpeedR,
                         double dSpeedL,
                         double dTimestep);

    // Adresse des Positionsarrays zurückgeben
    double* GetPosition();
};

#endif

//....................................................................................................................

#include "PosEstimation.h"
#include <cmath>


PosEstimation::PosEstimation()
{
    Reset();
}


void PosEstimation::Reset()
{
    m_dX[0] = 0.0;
    m_dX[1] = 0.0;
    m_dX[2] = 0.0;

    m_dVelAverage = 0.0;
}


void PosEstimation::PredictPosition(double dSpeedR,
                                    double dSpeedL,
                                    double dTimestep)
{
    // 1. x-Koordinate berechnen
    // Wichtig: alte mittlere Geschwindigkeit
    // und alten Winkel verwenden
    m_dX[0] =
        m_dX[0]
        + m_dVelAverage
        * dTimestep
        * cos(m_dX[2]);


    // 2. y-Koordinate berechnen
    m_dX[1] =
        m_dX[1]
        + m_dVelAverage
        * dTimestep
        * sin(m_dX[2]);


    // 3. Raumrichtung berechnen
    // Spurbreite B = 0.23 m
    m_dX[2] =
        m_dX[2]
        + dTimestep
        * ((dSpeedR - dSpeedL) / 0.23);


    // 4. Winkel zunächst auf ]-2*pi, 2*pi[ begrenzen
    m_dX[2] = fmod(m_dX[2], 2.0 * M_PI);


    // 5. Winkel auf ]-pi, pi] begrenzen
    if (m_dX[2] > M_PI)
    {
        m_dX[2] -= 2.0 * M_PI;
    }

    if (m_dX[2] <= -M_PI)
    {
        m_dX[2] += 2.0 * M_PI;
    }


    // 6. Neue mittlere Geschwindigkeit berechnen
    // Diese wird im nächsten Zeitschritt verwendet
    m_dVelAverage =
        (dSpeedR + dSpeedL) / 2.0;
}


double* PosEstimation::GetPosition()
{
    return m_dX;
}


//....................................................................................................................

#include <iostream>
#include <fstream>

#include "PosEstimation.h"


int main()
{
    PosEstimation pos;

    std::ifstream datei("PosEstimationInput.txt");

    if (!datei.is_open())
    {
        std::cout << "Datei konnte nicht geoeffnet werden."
                  << std::endl;

        return 1;
    }


    double dSpeedR;
    double dSpeedL;
    double dTimestep;


    while (datei >> dSpeedR >> dSpeedL >> dTimestep)
    {
        pos.PredictPosition(
            dSpeedR,
            dSpeedL,
            dTimestep
        );


        double* pPosition = pos.GetPosition();


        std::cout
            << pPosition[0] << "\t"
            << pPosition[1] << "\t"
            << pPosition[2] << std::endl;
    }


    datei.close();

    return 0;
}

//.........................................................................
#ifndef MANEUVER_H
#define MANEUVER_H


#include <list>
#include <string>


class Maneuver
{
private:

    // Ein Punkt der Koordinatenliste
    struct Coord
    {
        double dX;
        double dY;
        double dSpeed;

        Coord(double x, double y, double speed)
        {
            dX = x;
            dY = y;
            dSpeed = speed;
        }
    };


    // Koordinatenliste
    std::list<Coord> m_CoordList;


    // Iterator auf aktuellen Sollpunkt
    std::list<Coord>::iterator m_iter;


    // Läuft momentan ein Manöver?
    bool m_bIsRunning;


    // Wunschgeschwindigkeit
    // [0] = rechts
    // [1] = links
    double m_adWishSpeed[2];


    // Maximale Geschwindigkeit
    double m_dMaxSpeed;


    // Erlaubte Positionsabweichung
    double m_dPosDifference;


public:

    Maneuver();


    // Koordinatenlisten erzeugen
    void CalcCircle(double dRadius,
                    double dSpeed,
                    double dTimestep);

    void CalcEight(double dRadius,
                   double dSpeed,
                   double dTimestep);


    // Liste in Datei schreiben
    void LogList(std::string sDatei);


    // Kontrollmethoden
    bool isRunning();

    void Start();

    void Stop();

    void Proceed();


    // Wunschgeschwindigkeiten berechnen
    void CalcManeuverSpeed(double dX,
                           double dY,
                           double dW);


    // Wunschgeschwindigkeiten zurückgeben
    double* GetManeuverSpeed();
};


#endif
//...............................................................
#include "Maneuver.h"

#include <cmath>
#include <fstream>


Maneuver::Maneuver()
{
    m_bIsRunning = false;

    m_adWishSpeed[0] = 0.0;
    m_adWishSpeed[1] = 0.0;

    // Maximale Geschwindigkeit laut Skript
    m_dMaxSpeed = 0.5;

    // 2 cm Positionsabweichung
    m_dPosDifference = 0.02;
}



// ==================================================
// Kreis erzeugen
// ==================================================

void Maneuver::CalcCircle(double dRadius,
                          double dSpeed,
                          double dTimestep)
{
    // Alte Liste löschen
    m_CoordList.clear();


    // Vorgegebene for-Schleife aus dem Skript
    for (int counter = 1;
         counter <
         (int)((2.0 * M_PI)
         / ((dSpeed / dRadius) * dTimestep));
         counter++)
    {
        double dX =
            dRadius
            * sin(counter
            * (dSpeed / dRadius)
            * dTimestep);


        double dY =
            dRadius
            * (1.0
            - cos(counter
            * (dSpeed / dRadius)
            * dTimestep));


        // Punkt in Liste speichern
        m_CoordList.push_back(
            Coord(dX, dY, dSpeed)
        );
    }
}



// ==================================================
// Acht erzeugen
// ==================================================

void Maneuver::CalcEight(double dRadius,
                         double dSpeed,
                         double dTimestep)
{
    // Alte Liste löschen
    m_CoordList.clear();


    // ----------------------------------------------
    // Erster Teilkreis
    // ----------------------------------------------

    for (int counter = 1;
         counter <
         (int)((2.0 * M_PI)
         / ((dSpeed / dRadius) * dTimestep));
         counter++)
    {
        double dX =
            dRadius
            * sin(counter
            * (dSpeed / dRadius)
            * dTimestep);


        double dY =
            dRadius
            * (1.0
            - cos(counter
            * (dSpeed / dRadius)
            * dTimestep));


        m_CoordList.push_back(
            Coord(dX, dY, dSpeed)
        );
    }


    // ----------------------------------------------
    // Zweiter Teilkreis
    // ----------------------------------------------

    for (int counter = 1;
         counter <
         (int)((2.0 * M_PI)
         / ((dSpeed / dRadius) * dTimestep));
         counter++)
    {
        double dX =
            dRadius
            * sin(counter
            * (dSpeed / dRadius)
            * dTimestep);


        double dY =
            (-dRadius)
            * (1.0
            - cos(counter
            * (dSpeed / dRadius)
            * dTimestep));


        m_CoordList.push_back(
            Coord(dX, dY, dSpeed)
        );
    }
}



// ==================================================
// Koordinatenliste speichern
// ==================================================

void Maneuver::LogList(std::string sDatei)
{
    std::ofstream datei(sDatei);


    for (std::list<Coord>::iterator iter =
             m_CoordList.begin();
         iter != m_CoordList.end();
         iter++)
    {
        datei
            << iter->dX << "\t"
            << iter->dY << std::endl;
    }


    datei.close();
}



// ==================================================
// Kontrollmethoden
// ==================================================

bool Maneuver::isRunning()
{
    return m_bIsRunning;
}


void Maneuver::Start()
{
    // Wieder am Anfang beginnen
    m_iter = m_CoordList.begin();

    m_bIsRunning = true;
}


void Maneuver::Stop()
{
    m_bIsRunning = false;

    m_adWishSpeed[0] = 0.0;
    m_adWishSpeed[1] = 0.0;
}


void Maneuver::Proceed()
{
    // Iterator NICHT zurücksetzen
    m_bIsRunning = true;
}



// ==================================================
// Geschwindigkeit für das Manöver berechnen
// ==================================================

void Maneuver::CalcManeuverSpeed(double dX,
                                 double dY,
                                 double dW)
{
    // Sicherheit: leere Liste
    if (m_CoordList.empty())
    {
        Stop();
        return;
    }


    // Sicherheit: Ende bereits erreicht
    if (m_iter == m_CoordList.end())
    {
        Stop();
        return;
    }


    // ==============================================
    // 1. Positionsvergleich
    // ==============================================

    double dDeltaX = m_iter->dX - dX;
    double dDeltaY = m_iter->dY - dY;


    double dDistance =
        sqrt(dDeltaX * dDeltaX
           + dDeltaY * dDeltaY);


    // Sollpunkt mit ausreichender Genauigkeit erreicht
    if (dDistance <= m_dPosDifference)
    {
        m_iter++;
    }



    // ==============================================
    // 2. Ende der Liste überprüfen
    // ==============================================

    if (m_iter == m_CoordList.end())
    {
        m_adWishSpeed[0] = 0.0;
        m_adWishSpeed[1] = 0.0;

        Stop();

        return;
    }



    // ==============================================
    // 3. Winkel zwischen Soll- und Istposition
    // ==============================================

    double dPhi =
        atan2(
            m_iter->dY - dY,
            m_iter->dX - dX
        );



    // ==============================================
    // 4. Winkeldifferenz
    // ==============================================

    double dDeltaPhi = dPhi - dW;



    // ==============================================
    // 5. Winkeldifferenz auf ]-pi, pi] begrenzen
    // ==============================================

    if (dDeltaPhi <= -M_PI)
    {
        dDeltaPhi += 2.0 * M_PI;
    }

    if (dDeltaPhi > M_PI)
    {
        dDeltaPhi -= 2.0 * M_PI;
    }



    // ==============================================
    // 6. Rotationsanteil
    //
    // Faktor = 2 m/(s rad)
    // ==============================================

    double dRot = 2.0 * dDeltaPhi;


    // Auf [-0.5, 0.5] begrenzen
    if (dRot > m_dMaxSpeed)
    {
        dRot = m_dMaxSpeed;
    }

    if (dRot < -m_dMaxSpeed)
    {
        dRot = -m_dMaxSpeed;
    }



    // ==============================================
    // 7. Translationsanteil
    // ==============================================

    double dTra = m_iter->dSpeed;



    // ==============================================
    // 8. Geschwindigkeitsanteile überprüfen
    //
    // Rotationsanteil muss erhalten bleiben.
    // Falls notwendig wird Translation reduziert.
    // ==============================================

    if (dTra * dRot > 0.0)
    {
        if (dTra + dRot > m_dMaxSpeed)
        {
            dTra = m_dMaxSpeed - dRot;
        }

        if (dTra + dRot < -m_dMaxSpeed)
        {
            dTra = -m_dMaxSpeed - dRot;
        }
    }
    else
    {
        if (dTra - dRot > m_dMaxSpeed)
        {
            dTra = m_dMaxSpeed + dRot;
        }

        if (dTra - dRot < -m_dMaxSpeed)
        {
            dTra = -m_dMaxSpeed + dRot;
        }
    }



    // ==============================================
    // 9. Geschwindigkeiten summieren
    // ==============================================

    // rechts
    m_adWishSpeed[0] = dTra + dRot;

    // links
    m_adWishSpeed[1] = dTra - dRot;



    // Zusätzliche Begrenzung auf Maximalbetrag 0.5
    if (m_adWishSpeed[0] > m_dMaxSpeed)
        m_adWishSpeed[0] = m_dMaxSpeed;

    if (m_adWishSpeed[0] < -m_dMaxSpeed)
        m_adWishSpeed[0] = -m_dMaxSpeed;

    if (m_adWishSpeed[1] > m_dMaxSpeed)
        m_adWishSpeed[1] = m_dMaxSpeed;

    if (m_adWishSpeed[1] < -m_dMaxSpeed)
        m_adWishSpeed[1] = -m_dMaxSpeed;
}



double* Maneuver::GetManeuverSpeed()
{
    return m_adWishSpeed;
}

//......................................................................

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H


class PIDController
{
private:

    double m_dKp;
    double m_dKi;
    double m_dKd;
    double m_dTa;

    double m_dEsum;
    double m_deold;
    double m_dU;


public:

    PIDController(double Kp,
                  double Ki,
                  double Kd,
                  double Ta);

    void calculateU(double w, double y);

    double GetU();
};


#endif

//...............................................................................
#include "PIDController.h"


PIDController::PIDController(double Kp,
                             double Ki,
                             double Kd,
                             double Ta)
{
    m_dKp = Kp;
    m_dKi = Ki;
    m_dKd = Kd;
    m_dTa = Ta;

    m_dEsum = 0.0;
    m_deold = 0.0;
    m_dU = 0.0;
}


void PIDController::calculateU(double w, double y)
{
    double e;

    e = w - y;

    m_dEsum = m_dEsum + e;

    m_dU =
        m_dKp * e
        + m_dKi * m_dTa * m_dEsum
        + m_dKd * (e - m_deold) / m_dTa;

    m_deold = e;
}


double PIDController::GetU()
{
    return m_dU;
}

//..............................................................................
#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H


#include "InterfaceSIM.h"
#include "Maneuver.h"
#include "PosEstimation.h"
#include "PIDController.h"


class RobotControl
{
private:

    // Schnittstelle zur Simulation
    InterfaceSIM m_Interface;


    // Manöver
    Maneuver m_Maneuver;


    // Positionsschätzung
    PosEstimation m_PosEstimation;


    // Ein PID-Regler pro Motor
    PIDController m_MotorR;
    PIDController m_MotorL;


    // Aktuelle Istgeschwindigkeiten
    double m_dActualSpeed[2];


    // Signallängen
    int m_iMicros[2];


    // Programm aktiv?
    bool m_bIsActive;


public:

    RobotControl();


    // Parallelisierung
    static RobotControl* transferPointer;

    static void transferFunction();


    // Status des Programms
    bool isActive();


    // Zyklische Robotersteuerung
    void Step();


    // Kommunikation mit Benutzer
    void Communicate();
};


#endif

//............................................................................
#include "RobotControl.h"

#include <iostream>
#include <ncurses.h>
#include <signal.h>


// Statischen Pointer definieren
RobotControl* RobotControl::transferPointer;



// ==================================================
// Konstruktor
// ==================================================

RobotControl::RobotControl()
    : m_MotorR(500.0, 100.0, 0.0, 0.04),
      m_MotorL(500.0, 100.0, 0.0, 0.04)
{
    // Anfangsgeschwindigkeit
    m_dActualSpeed[0] = 0.0;
    m_dActualSpeed[1] = 0.0;


    // Motoren stehen
    m_iMicros[0] = 1500;
    m_iMicros[1] = 1500;


    // Programm ist zunächst aktiv
    m_bIsActive = true;


    // Interface initialisieren
    m_Interface.Initialize(
        0.04,
        transferFunction
    );


    // Pointer auf dieses Objekt setzen
    transferPointer = this;
}



// ==================================================
// transferFunction
// ==================================================

void RobotControl::transferFunction()
{
    transferPointer->Step();
}



// ==================================================
// isActive
// ==================================================

bool RobotControl::isActive()
{
    return m_bIsActive;
}



// ==================================================
// Communicate
// ==================================================

void RobotControl::Communicate()
{
    // ==============================================
    // Zuerst normale Kommunikation mit iostream
    // ==============================================

    char cAntwort;


    std::cout
        << "Soll ein neues Manoever gefahren werden? (j/n): ";

    std::cin >> cAntwort;


    // Benutzer möchte kein weiteres Manöver
    if (cAntwort != 'j')
    {
        m_bIsActive = false;

        return;
    }



    // ==============================================
    // Radius und Geschwindigkeit einlesen
    // ==============================================

    double dRadius;
    double dSpeed;

    int iManeuver;


    std::cout << "Radius [m]: ";
    std::cin >> dRadius;


    std::cout << "Geschwindigkeit [m/s]: ";
    std::cin >> dSpeed;


    std::cout
        << "Manoever waehlen:\n"
        << "1 = Kreis\n"
        << "2 = Acht\n";

    std::cin >> iManeuver;



    // ==============================================
    // Koordinatenliste erzeugen
    //
    // timestep = 0.04 s
    // ==============================================

    if (iManeuver == 1)
    {
        m_Maneuver.CalcCircle(
            dRadius,
            dSpeed,
            0.04
        );
    }
    else
    {
        m_Maneuver.CalcEight(
            dRadius,
            dSpeed,
            0.04
        );
    }



    // ==============================================
    // Positionsschätzung zurücksetzen
    // ==============================================

    m_PosEstimation.Reset();



    // ==============================================
    // ncurses starten
    // ==============================================

    initscr();

    nodelay(stdscr, TRUE);

    noecho();



    // ==============================================
    // Step-Methode starten
    // ==============================================

    sigprocmask(
        SIG_UNBLOCK,
        &m_Interface.mask,
        nullptr
    );



    int iTaste = -1;

    bool bQuit = false;



    clear();

    printw("s = Start\n");
    printw("b = Stop\n");
    printw("p = Proceed\n");
    printw("q = Quit\n");



    // ==============================================
    // Benutzersteuerung
    // ==============================================

    while (!bQuit)
    {
        iTaste = getch();


        if (iTaste != -1)
        {
            // Manöver von vorne starten
            if (iTaste == 's')
            {
                m_Maneuver.Start();

                clear();
                printw("Manoever gestartet\n");
            }


            // Manöver stoppen / pausieren
            else if (iTaste == 'b')
            {
                m_Maneuver.Stop();

                clear();
                printw("Manoever gestoppt\n");
            }


            // Unterbrochenes Manöver fortsetzen
            else if (iTaste == 'p')
            {
                m_Maneuver.Proceed();

                clear();
                printw("Manoever fortgesetzt\n");
            }


            // Programm verlassen
            else if (iTaste == 'q')
            {
                m_Maneuver.Stop();

                bQuit = true;
            }
        }
    }



    // ==============================================
    // Warten bis Roboter wirklich steht
    // ==============================================

    while (m_dActualSpeed[0] != 0.0 ||
           m_dActualSpeed[1] != 0.0)
    {
        // Step() läuft weiterhin
    }



    // ==============================================
    // Step-Methode stoppen
    // ==============================================

    sigprocmask(
        SIG_BLOCK,
        &m_Interface.mask,
        nullptr
    );



    // ncurses beenden
    endwin();
}



// ==================================================
// Step
// ==================================================

void RobotControl::Step()
{
    // ==============================================
    // 1. Istgeschwindigkeiten einlesen
    // ==============================================

    double* pdInput =
        m_Interface.GetInput();


    m_dActualSpeed[0] = pdInput[0];
    m_dActualSpeed[1] = pdInput[1];



    // ==============================================
    // Läuft ein Manöver?
    // ==============================================

    if (m_Maneuver.isRunning())
    {
        // ==========================================
        // 2. Positionsschätzung
        // ==========================================

        m_PosEstimation.PredictPosition(
            m_dActualSpeed[0],
            m_dActualSpeed[1],
            0.04
        );


        double* pdPosition =
            m_PosEstimation.GetPosition();



        // ==========================================
        // 3. Neue Wunschgeschwindigkeiten berechnen
        // ==========================================

        m_Maneuver.CalcManeuverSpeed(
            pdPosition[0],
            pdPosition[1],
            pdPosition[2]
        );


        double* pdWishSpeed =
            m_Maneuver.GetManeuverSpeed();



        // ==========================================
        // Falls CalcManeuverSpeed das Ende
        // des Manövers erreicht hat
        // ==========================================

        if (!m_Maneuver.isRunning())
        {
            m_iMicros[0] = 1500;
            m_iMicros[1] = 1500;
        }
        else
        {
            // ======================================
            // 4. PID-Regler
            // ======================================

            m_MotorR.calculateU(
                pdWishSpeed[0],
                m_dActualSpeed[0]
            );


            m_MotorL.calculateU(
                pdWishSpeed[1],
                m_dActualSpeed[1]
            );



            // ======================================
            // 5. Stellgröße in Signallänge umwandeln
            // ======================================

            m_iMicros[0] =
                1500 + m_MotorR.GetU();


            m_iMicros[1] =
                1500 + m_MotorL.GetU();



            // ======================================
            // 6. Bereich [1000,2000] sicherstellen
            // ======================================

            if (m_iMicros[0] > 2000)
                m_iMicros[0] = 2000;

            if (m_iMicros[0] < 1000)
                m_iMicros[0] = 1000;


            if (m_iMicros[1] > 2000)
                m_iMicros[1] = 2000;

            if (m_iMicros[1] < 1000)
                m_iMicros[1] = 1000;
        }
    }

    else
    {
        // ==========================================
        // Kein Manöver aktiv
        // → Roboter stoppen
        // ==========================================

        m_iMicros[0] = 1500;
        m_iMicros[1] = 1500;
    }



    // ==============================================
    // 7. Signallängen an Simulation senden
    // ==============================================

    m_Interface.SetOutputs(m_iMicros);
}

//......................................................................
#include "RobotControl.h"


int main()
{
    RobotControl control;


    do
    {
        control.Communicate();
    }
    while (control.isActive());


    return 0;
}
