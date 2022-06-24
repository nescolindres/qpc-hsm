#ifndef STATES_H
#define STATES_H

enum TransitionSignals {
    NEXT_SIG = Q_USER_SIG,
    TERMINATE_SIG
};

extern QHsm * const states;

void States_ctor(void);

#endif

