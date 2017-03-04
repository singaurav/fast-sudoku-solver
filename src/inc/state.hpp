#ifndef STATE_INCLUDED
#define STATE_INCLUDED

struct StateNode {
    BitBoard81 state;
    int digit;
    StateNode *next;

    StateNode() { next = nullptr; }

    StateNode(const BitBoard81 &mask, int d) {
        digit = d;
        state = mask;
        next = nullptr;
    }
};

struct StateList {
    StateNode *beg;
    StateNode *end;
    int size;

    StateList() {
        beg = end = nullptr;
        size = 0;
    }

    void add_state_node(StateNode *node) {
        if (size < 1) {
            beg = end = node;
            size = 1;
        } else {
            end->next = node;
            end = node;
            size += 1;
        }
    }

    void add_state_list(StateList *other) {
        if (other->size > 0) {
            if (size < 1) {
                beg = other->beg;
                end = other->end;
                size = other->size;
            } else {
                end->next = other->beg;
                end = other->end;
                size += other->size;
            }
        }

        other->beg = nullptr;
        other->end = nullptr;
        other->size = 0;
    }

    void reset() {
        StateNode *it = beg;

        while (it != nullptr) {
            StateNode *next = it->next;
            delete it;
            it = next;
        }

        beg = end = nullptr;
        size = 0;
    }
};

struct StateListPartitioned {
    StateList *parts[DIGIT_COUNT];

    StateListPartitioned() {
        for (int i = 0; i < DIGIT_COUNT; ++i) {
            parts[i] = new StateList();
        }
    }

    void set_first_part(StateList *list) { parts[0]->add_state_list(list); }

    void reset() {
        for (int i = 0; i < DIGIT_COUNT; ++i) {
            parts[i]->reset();
            delete parts[i];
        }
    }
};

struct SolveOutput {
    int sol_count;
    int nodes_searched;
};

inline void flip_min_size_part(StateListPartitioned lists[], int beg_index) {
    int min_size_index = -1;
    int min_size = 100000;

    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        if (lists[index].parts[0]->size < min_size) {
            min_size = lists[index].parts[0]->size;
            min_size_index = index;
        }
    }

    if (min_size_index != beg_index) {
        StateListPartitioned t = lists[min_size_index];
        lists[min_size_index] = lists[beg_index];
        lists[beg_index] = t;
    }
}

inline bool conflict(const BitBoard81 &a, const BitBoard81 &b) {
    return (a.bits27[0] & b.bits27[0]) || (a.bits27[1] & b.bits27[1]) ||
           (a.bits27[2] & b.bits27[2]);
}

inline void partition(StateNode *node, StateListPartitioned lists[],
                      int beg_index) {
    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        if (lists[index].parts[0]->size > 0) {
            StateNode *it1 = lists[index].parts[0]->beg;
            StateNode *it2 = it1->next;

            while (it2 != nullptr) {
                if (conflict(node->state, it2->state)) {
                    it1->next = it2->next;
                    it2->next = nullptr;
                    lists[index].parts[beg_index]->add_state_node(it2);
                    it2 = it1->next;
                    lists[index].parts[0]->size -= 1;
                } else {
                    it1 = it2;
                    it2 = it2->next;
                }
            }

            lists[index].parts[0]->end = it1;

            if (conflict(node->state, lists[index].parts[0]->beg->state)) {
                StateNode *new_beg = lists[index].parts[0]->beg->next;
                lists[index].parts[0]->beg->next = nullptr;
                lists[index].parts[beg_index]->add_state_node(
                    lists[index].parts[0]->beg);
                lists[index].parts[0]->beg = new_beg;

                if (new_beg == nullptr) {
                    lists[index].parts[0]->end = nullptr;
                }

                lists[index].parts[0]->size -= 1;
            }
        }
    }
}

inline void attach(StateListPartitioned lists[], int beg_index) {
    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        lists[index].parts[0]->add_state_list(lists[index].parts[beg_index]);
    }
}

#endif // #ifndef STATE_INCLUDED
