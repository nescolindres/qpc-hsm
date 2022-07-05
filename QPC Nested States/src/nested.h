#ifndef NESTED_H
#define NESTED_H


enum TransitionSignals {
    NEXT_SIG = Q_USER_SIG,
    TERMINATE_SIG
};

extern QHsm * const state;

void State_ctor(void);

#endif