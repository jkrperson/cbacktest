#ifndef _DATA_HANDLER_H
#define _DATA_HANDLER_H

#include "event.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <time.h>
#include "csv.h"

struct StockInfo{
    std::time_t datetime;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adj_close;
};

class DataHandler{

    public:
        DataHandler(){};
        virtual ~DataHandler(){};

        virtual StockInfo get_latest_bar() = 0;
        
        virtual std::vector<StockInfo> get_latest_bars(int N) = 0;
        
        virtual std::time_t get_latest_bar_datetime() = 0;
        
        virtual std::vector<double> get_latest_bars_values(std::string val_type) = 0;
        virtual std::vector<double> get_latest_bars_values(std::string val_type, int N) = 0;

        virtual void update_bars() = 0;
};

class CSVDataHandler: public DataHandler{

    public:
        CSVDataHandler(): DataHandler(){};
        CSVDataHandler(std::list<Event*> _events, std::string _csv_dir);

        virtual ~CSVDataHandler(){};

        StockInfo get_latest_bar();

        std::vector<StockInfo> get_latest_bars(int N);

        std::time_t get_latest_bar_datetime();
        
        std::vector<double> get_latest_bars_values(std::string val_type);
        std::vector<double> get_latest_bars_values(std::string val_type, int N);

        void update_bars();

    private:
        std::list<Event*> events;
        std::string csv_dir;
        
        // A PROPER DATA CLASS CAN MAKE THIS BETTER

        std::list<std::time_t> stocktime;
        std::map<std::string, std::list<double>> stockdata;
        std::list<StockInfo> row_stockdata;

        std::vector<std::time_t> latest_stocktime;
        std::map<std::string, std::vector<double>> latest_stockdata;
        std::vector<StockInfo> latest_row_stockdata;

        bool continue_backtest = true;
        
        void _open_csv_file();
};

#include "datahandler.cpp"

#endif