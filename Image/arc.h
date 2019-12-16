#include "noeud.h"
#ifndef ARC
#define ARC
    class Arc
    {
    private:
        Noeud* predecessor;
        Noeud *successor;
        int flowValue;
        int flowCapacity;

    public:
        Arc(Noeud* predecessor, Noeud* successor, int flowValue, int flowCapacity);
        ~Arc();
        void incrementFlowValue(int newFlow);
        void decrementFlowCapacity(int newFlow);
        bool fullFlow();
        
    };

#endif