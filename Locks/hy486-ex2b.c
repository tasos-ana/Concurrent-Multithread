//Locks implemented with mutex lock
shared Lock stackLock;

void push(T x) {
    int range;
    long duration;

    NODE *nd = newcell(NODE);
    nd->value = x;

    while (TRUE) {
        if (trypush(nd)) return;
        else {
            range = CalculateRange();
            duration = CalculateDuration();
            otherValue = visit(x, range, duration);
            if (otherValue == NULL) {
                RecordSuccess();
                return;
            } else if (otherValue == TIMEOUT) {
                RecordFailure();
            }
        }
    }
}

T pop(void) {
    NODE *returnNode;
    while (TRUE) {
        returnNode = TryPop(); // try to pop
        if (returnNode == EMPTY_STACK) // if stack is empty, return EMPTY_CODE
            return EMPTY_STACK;
        if (returnNode != NULL) // if tryPop() was successful, return the poped value
            return returnNode->value;
        range = CalculateRange(); // choose the range parameter
        duration = CalculateDuration(); // choose the duration parameter
        otherValue = visit(NULL, range, duration); // call visit with input value as argument
        if (otherValue != NULL) { // check whether the value was exchanged with a push() method
            RecordSuccess(); // if yes, record success
            return otherValue;
        } else if (otherValue == TIMEOUT) // otherwise,
            RecordFailure(); // record failure
    }
}

boolean TryPush(NODE *n) {
    lock(stackLock);

    NODE * oldTop = TOP;
    n->next = oldTop;
    Top = n;

    unlock(stackLock);
    return True;
}

NODE *TryPop(void) {
    lock(stackLock);

    NODE *oldTop = Top;
    NODE * newTop;
    if (oldTop == NULL)
        return EMPTY_STACK;
    Top = oldTop->next;

    unlock(stackLock);
    return oldTop;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define EMPTY 1 
#define WAITING 2
#define BUSY 3
#define CAPACITY 100;

<T, state, exchangeLock> exchanger[CAPACITY];
//Each element of exchanger[] is initially <null, EMPTY>.

state = {EMPTY, WAITING, BUSY}

T visit(T value, int range, long duration) {
    int el = randomnumber(range);
    return (exchange(exchanger[el], value, duration));
}

T exchange(shared <T, int> slot, T myitem, long timeout, int index) {
    long timeBound = getnanos() + timeout;
    while (TRUE) {
        if (getnanos() > timeBound) return TIMEOUT; // if it is time for timeout, leave the exchanger
        lock(slot.exchangeLock);
        <youritem, state> = slot;
        switch (state) {
            case EMPTY: // try to place your item in the slot and set state to WAITING
                slot = <myitem, WAITING>;
                unlock(slot.exchangeLock);
                while (getnanos() < TimeBound) { // spin until it is time for timeout					
                    <youritem, state> = slot; // read slot
                    if (state == BUSY) {
                        slot = <null, EMPTY>; // if the exchange is complete
                        return youritem;
                    } // return the other process’s item
                }
                // if no other thread shows up
                if (slot == myitem) {
                    return TIMEOUT
                } else {
                    lock(slot.exchangeLock);

                    <youritem, state> = slot;
                    slot = <null, EMPTY>;

                    unlock(slot.exchangeLock);
                    return youritem;
                }
            case WAITING: // some thread is waiting and slot contains its item
                slot = <myitem, BUSY>;
                unlock(slot.exchangeLock);
                return youritem; // and return the item of the other process
            case BUSY: // two other threads are currently using the slot
                break; // the process must retry
        } // switch
    }
}