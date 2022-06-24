#include "qpc.h"
#include "states.h"

#include "safe_std.h" /* portable "safe" <stdio.h>/<string.h> facilities */
#include <stdlib.h>   /* for exit() */


Q_DEFINE_THIS_FILE

int main() {
    QF_init();
    QF_onStartup();

    PRINTF_S("%s", "Linear State Transition Press 'n' for next state\n");

    
    States_ctor();
    QHSM_INIT(states, (void *)0, 0U);

    for (;;) {
        QEvt e;
        uint8_t c;

        PRINTF_S("\n", "");
        c = (uint8_t)QF_consoleWaitForKey();
        PRINTF_S("%c: ", (c >= ' ') ? c : 'X');

        switch (c) {
            case 'n':  e.sig = NEXT_SIG;        break;
            case 0x1B: e.sig = TERMINATE_SIG;   break;
        }

        /* dispatch the event into the state machine */
        QHSM_DISPATCH(states,  &e, 0U);
    }
    QF_onCleanup();
    return 0;
}
/*..........................................................................*/
void QF_onStartup(void) {
    QF_consoleSetup();
}
/*..........................................................................*/
void QF_onCleanup(void) {
    QF_consoleCleanup();
}
/*..........................................................................*/
void QF_onClockTick(void) {
}

/*..........................................................................*/
Q_NORETURN Q_onAssert(char const * const file, int_t const line) {
    FPRINTF_S(stderr, "Assertion failed in %s, line %d", file, line);
    QF_onCleanup();
    exit(-1);
}
