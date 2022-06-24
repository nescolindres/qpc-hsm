#include "qpc.h"
#include "states.h"

#include "safe_std.h" /* portable "safe" <stdio.h>/<string.h> facilities */
#include <stdlib.h>

typedef struct {
/* protected: */
    QHsm super;

/* private state histories */
} States;

/* protected: */
static QState States_initial(States * const me, void const * const par);
static QState States_one(States * const me, QEvt const * const e);
static QState States_two(States * const me, QEvt const * const e);
static QState States_three(States * const me, QEvt const * const e);
static QState States_final(States * const me, QEvt const * const e);

static States l_states;

QHsm * const states = &l_states.super;

void States_ctor(void) {
    States *me = &l_states;
    QHsm_ctor(&me->super, Q_STATE_CAST(&States_initial));
}

static QState States_initial(States * const me, void const * const par) {
    (void)par;
    return Q_TRAN(&States_one);
}

static QState States_one (States * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s", "In state one\n");
            status_ = Q_HANDLED();
            break;
        }

        case Q_INIT_SIG: { 
            status_ = Q_HANDLED();
            break;
        }

        case NEXT_SIG: {
            PRINTF_S("%s", "Transisitioning to next state\n");
            status_ = Q_TRAN(&States_two);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

static QState States_two (States * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        PRINTF_S("%s", "In State Two\n");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        status_ = Q_HANDLED();
        break;
    }

    case NEXT_SIG: {
        PRINTF_S("%s", "Transitioning to next state\n");
        status_ = Q_TRAN(&States_three);
        break;
    }

    default: {
        status_ = Q_SUPER(&QHsm_top);
        break;
    }
        
    }
    return status_;
}

static QState States_three (States * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig)
    {
    
    case Q_ENTRY_SIG: {
        PRINTF_S("%s", "In State Three\n");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        status_ = Q_HANDLED();
        break;
    }

    case NEXT_SIG: {
        PRINTF_S("%s", "Exiting Program\n");
        status_ = Q_TRAN(&States_final);
        break;
    }

    default: {
        status_ = Q_SUPER(&QHsm_top);
        break;
    }
        
    }
    return status_;
    
}

static QState States_final (States * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig)
    {
    case Q_ENTRY_SIG: {
        PRINTF_S("\n%s\n", "Goodbye");
        QF_onCleanup();
        exit(0);
        status_ = Q_HANDLED();
        break;
    }

    default: {
        status_ = Q_SUPER(&QHsm_top);
        break;
    }
    }
    return status_;
}