
//...............
//h
//...............

#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

class KeyboardControl
{
private:
    // [0] = rechter Motor
    // [1] = linker Motor
    double m_dSollGeschwindigkeit[2];

    // [0] = rechter Motor
    // [1] = linker Motor
    double m_dIstGeschwindigkeit[2];

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

KeyboardControl::KeyboardControl()
{
    m_dSollGeschwindigkeit[0] = 0.0;
    m_dSollGeschwindigkeit[1] = 0.0;

    m_dIstGeschwindigkeit[0] = 0.0;
    m_dIstGeschwindigkeit[1] = 0.0;
}

void KeyboardControl::Communicate()
{
}

void KeyboardControl::Step()
{
}

//...............
//main
//...............
#include "KeyboardControl.h"

int main()
{
    KeyboardControl control;

    control.Communicate();
    control.Step();

    return 0;
}
