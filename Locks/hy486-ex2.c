#define EMPTY 1 
#define WAITING 2
#define BUSY 3
#define CAPACITY 100;

<T, state> exchanger[CAPACITY];
//Each element of exchanger[] is initially <null, EMPTY>.

state = {EMPTY, WAITING, BUSY}

//Locks implemented with mutex lock
shared Lock exchangeLock;
shared Lock stackLock;

T visit(T value, int range, long duration) {
    int el = randomnumber(range);
    return (exchange(exchanger[el], value, duration));
}

T exchange(shared <T, int> slot, T myitem, long timeout) {
    long timeBound = getnanos() + timeout;
    while (TRUE) {
		// if it is time for timeout, leave the exchanger
        if (getnanos() > timeBound) return TIMEOUT; //linearization * 
        lock(exchangeLock);
        <youritem, state> = slot;
        switch (state) {
            case EMPTY: // try to place your item in the slot and set state to WAITING
                slot = <myitem, WAITING>;
                unlock(exchangeLock);
                while (getnanos() < TimeBound) { // spin until it is time for timeout					
                    <youritem, state> = slot; // read slot
                    if (state == BUSY) {
                        slot = <null, EMPTY>; // if the exchange is complete
                        return youritem;
                    } // return the other process’s item
                }
                // if no other thread shows up
                if (slot == myitem) { //linearization *
                    slot = <null, EMPTY>
                    return TIMEOUT
                } else {
                    lock(exchangeLock);

                    <youritem, state> = slot;
                    slot = <null, EMPTY>;

                    unlock(exchangeLock);
                    return youritem;
                }
            case WAITING: // some thread is waiting and slot contains its item
                slot = <myitem, BUSY>; //linearization *
                unlock(exchangeLock);
                return youritem; // and return the item of the other process
            case BUSY: // two other threads are currently using the slot
                break; // the process must retry
        } // switch
    }
}

void push(T x) {
    int range;
    long duration;
    NODE *nd = newcell(NODE);
    nd->value = x;

    // try to use the elimination array, instead of backing-off
    range = CalculateRange(); // choose the range parameter
    duration = CalculateDuration(); // choose the duration parameter
    otherValue = visit(x, range, duration); // call visit with input value as argument
    if (otherValue == NULL) { // check whether the value was exchanged with a pop() method
        RecordSuccess(); // if yes, record success
        return;
    } else if (otherValue == TIMEOUT) // otherwise,
        RecordFailure(); // record failure

    lock(stackLock);

    NODE * oldTop = TOP;
    nd->next = oldTop;
    Top = nd; //linearization point *

    unlock(stackLock);
}

T pop(void) {
    range = CalculateRange(); // choose the range parameter
    duration = CalculateDuration(); // choose the duration parameter
    otherValue = visit(NULL, range, duration); // call visit with input value as argument
    if (otherValue != NULL) { // check whether the value was exchanged with a push() method
        RecordSuccess(); // if yes, record success
        return otherValue;
    } else if (otherValue == TIMEOUT) // otherwise,
        RecordFailure(); // record failure

    lock(stackLock);

    NODE *oldTop = Top;
    if (oldTop == NULL) {
        unlock(stackLock);
        return EMPTY_STACK;
    }
    Top = oldTop->next; //linearization *
    unlock(stackLock);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



C5) ean to lock einai starvetion free tote den mporoume na exoum starvetion.
	Se kathe anakuklwsh tis while oso argei kai na einai mia diergasia logo tou elegxou pou kanoume
	gia to timeoute kapoia stigmh tha epistrepsei apo tin exchange kai stin sunexeia tha ginei instert sto stack.