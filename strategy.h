#ifndef _STRATEGY_H
#define _STRATEGY_H

class Strategy{

    public:
        Strategy();
        virtual ~Strategy();

        virtual calculate_signals(){} = 0;
};

#endif