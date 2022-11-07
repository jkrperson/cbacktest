#ifndef _EVENT_H
#define _EVENT_H
#include <string>
#include <iostream>

class Event{
    const std::string e_type;

    public:
        Event(){};
        Event(std::string e) : e_type{e} {};
        virtual ~Event(){};

        const std::string get_type() const{return e_type;}
};

class MarketEvent: public Event{
    public:
        MarketEvent(): Event{std::string("MARKET")}{};
        virtual ~MarketEvent(){};
};

class SignalEvent: public Event{
    public:
        SignalEvent(): Event{std::string("SIGNAL")}{};
        SignalEvent(int _strategy_id, std::string _symbol, int _datetime, std::string _signal_type, int _strength): 
            strategy_id{_strategy_id}, symbol{_symbol}, datetime{_datetime}, signal_type{_signal_type}, strength{_strength}{};

        virtual ~SignalEvent(){};
    private:
        int strategy_id;
        std::string symbol;
        int datetime;
        std::string signal_type;
        int strength;
};

class OrderEvent: public Event{
    
    public:
        OrderEvent(): Event{std::string("ORDER")}{};
        OrderEvent(std::string _symbol, std::string _order_type, int _quantity, std::string _direction):
            symbol{_symbol}, order_type{_order_type}, quantity{_quantity}, direction{_direction} {};

        virtual ~OrderEvent(){};

        void print_order(){
            std::cout<<"Order: Symbol="<<symbol<<", Type="<<order_type<<", Quantity="<<quantity<<", Direction="<<direction<<std::endl;
        };

    private:
        std::string symbol;
        std::string order_type;
        int quantity;
        std::string direction;
};

class FillEvent: public Event{

    public:
        FillEvent(): Event{std::string("FILL")}{};
        FillEvent(int _timeindex, std::string _symbol, std::string _exchange, int _quantity, std::string _direction, int _fill_cost, int _commission):
            timeindex{_timeindex}, symbol{_symbol}, exchange{_exchange}, quantity{_quantity}, direction{_direction}, fill_cost{_fill_cost}, commission{_commission}{};

    private:
        int timeindex;
        std::string symbol;
        std::string exchange;
        int quantity;
        std::string direction;
        int fill_cost;
        int commission;

};

#endif