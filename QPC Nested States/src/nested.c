#include "qpc.h"
#include "nested.h"

#include "safe_std.h" /* portable "safe" <stdio.h>/<string.h> facilities */
#include <stdlib.h>


typedef struct
{
    /* protected: */
    QHsm super;

    /* private state histories */
} State;


static QState State_initial(State *const me, void const *const par);
static QState State_s(State *const me, QEvt const *const e);
static QState State_s1(State *const me, QEvt const *const e);
static QState State_s11(State *const me, QEvt const *const e);

 static State l_state;

 QHsm * const state = &l_state.super;


void State_ctor(void) {
    State *me = &l_state;
    QHsm_ctor(&me->super, Q_STATE_CAST(&State_initial));
}

static QState State_initial(State * const me, void const * const par) {
    PRINTF_S("%s", "top-init;");
    (void)par;
    return Q_TRAN(&State_s);
}

static QState State_s(State *const me, QEvt const *const e) {
QState status_;
    switch(e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s", "s-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        case Q_EXIT_SIG: {
            PRINTF_S("%s", "s-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        case Q_INIT_SIG: {
            PRINTF_S("%s", "s1-INIT;");
            status_ = Q_TRAN(&State_s1);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

static QState State_s1(State * const me, QEvt const * const e) {
    QState status_;
    switch(e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s", "s1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        case Q_EXIT_SIG: {
            PRINTF_S("%s", "s1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        case Q_INIT_SIG: {
            PRINTF_S("%s", "s11-INIT;");
            status_ = Q_TRAN(&State_s11);
            break;
        }

        case NEXT_SIG: {
            PRINTF_S("%s", "s1;");
            status_ = Q_TRAN(&State_s11);
            break;
        }
        default: {
            status_ = Q_SUPER(&State_s);
            break;
        }
    }
    return status_;
}

static QState State_s11(State *const me, QEvt const *const e) {
    QState status_;
    switch(e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s", "s11-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        case Q_EXIT_SIG: {
            PRINTF_S("%s", "s11-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
       
        default: {
            status_ = Q_SUPER(&State_s1);
            break;
        }
    }
    return status_;
}