#include "qpc.h"
#include "safe_std.h"
#include <stdlib.h> // for exit()

Q_DEFINE_THIS_FILE


typedef struct {
    QHsm super;  /* inhertits QHsm */
 
} States;
extern States States_inst;

static QState States_initial(States * const me, void const * const par);
static QState States_One(States * const me, QEvt const * const e);

QHsm * const states = &States_inst.super;

static void States_ctor(void) {
    States *me = &States_inst;
    QHsm_ctor(&me->super, Q_STATE_CAST(&States_initial));
}

int main () {
    QF_init();
    QF_onStartup();
    States_ctor();
    QHSM_INIT(states, (void *)0, 0U);
    QEvt e;
    e.sig = Q_ENTRY_SIG;
    QHSM_DISPATCH(states, &e, 0U);
    printf("Press ENTER key to Continue\n");  
    getchar(); 
    return 0;
}

void Q_onAssert(char const * const module, int loc) {
    FPRINTF_S(stderr, "Assertion failed in %s:%d", module, loc);
    exit(-1);
}

void QF_onStartup(void) {
    QF_consoleSetup();
}
void QF_onCleanup(void) {
         QF_consoleCleanup();
}
void QF_onClockTick(void) {}



States States_inst;

static QState States_initial(States * const me, void const * const par) {
    (void)par; // unused transition parameter
    PRINTF_S("%s\n", "Initial State");
    return Q_TRAN(&States_One);
}

static QState States_One(States * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s\n", "In State One");
            status_ = Q_HANDLED();
            break;
        }
        default: {
            PRINTF_S("%s\n", "Default: State One");
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}