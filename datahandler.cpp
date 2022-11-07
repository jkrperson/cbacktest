#include "datahandler.h"

CSVDataHandler::CSVDataHandler(std::list<Event*> _events, std::string _csv_dir){
    events = _events;
    csv_dir = _csv_dir;

    stockdata["open"] = std::list<double>();
    stockdata["high"] = std::list<double>();
    stockdata["low"] = std::list<double>();
    stockdata["close"] = std::list<double>();
    stockdata["adj_close"] = std::list<double>();
    stockdata["volume"] = std::list<double>();

    latest_stockdata["open"] = std::vector<double>();
    latest_stockdata["high"] = std::vector<double>();
    latest_stockdata["low"] = std::vector<double>();
    latest_stockdata["close"] = std::vector<double>();
    latest_stockdata["adj_close"] = std::vector<double>();
    latest_stockdata["volume"] = std::vector<double>();


    _open_csv_file();

    update_bars();
}

void CSVDataHandler::_open_csv_file(){
    io::CSVReader<7> in(csv_dir);
    in.read_header(io::ignore_extra_column, "Date","Open","High","Low","Close","Adj Close","Volume");
    
    std::string date; double open; double high; double low; double close; double volume; double adj_close;

    while(in.read_row(date, open, high, low, close, adj_close, volume)){
        struct std::tm tm;
        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%F"); // or just %T in this case
        std::time_t time = mktime(&tm);

        
        StockInfo si = {time, open, high, low, close, volume, adj_close};
        row_stockdata.push_back(si);

        
        stocktime.push_back(time);
        stockdata["open"].push_back(open);
        stockdata["high"].push_back(high);
        stockdata["low"].push_back(low);
        stockdata["close"].push_back(close);
        stockdata["adj_close"].push_back(adj_close);
        stockdata["volume"].push_back(volume);
    }
}

StockInfo CSVDataHandler::get_latest_bar(){

    return latest_row_stockdata[latest_row_stockdata.size()-1];
}

std::vector<StockInfo> CSVDataHandler::get_latest_bars(int N){
    if(N > latest_row_stockdata.size()-1) N = 0;
    else N = latest_row_stockdata.size()-1-N;

    auto begin = latest_row_stockdata.begin() + N;
    auto end = latest_row_stockdata.end();
    std::vector<StockInfo> vec(begin, end);
    return vec;
}

std::vector<double> CSVDataHandler::get_latest_bars_values(std::string val_type){
    return latest_stockdata[val_type]; 
}

std::time_t CSVDataHandler::get_latest_bar_datetime(){
    return latest_stocktime[latest_stocktime.size()-1];
}

std::vector<double> CSVDataHandler::get_latest_bars_values(std::string val_type, int N){
    std::vector<double> data = latest_stockdata[val_type];
    if(N > stockdata.size()-1) N = 0;
    else N = data.size()-1-N;

    auto begin = data.begin() + N;
    auto end = data.end();
    std::vector<double> vec(begin, end);
    return vec;
}

void CSVDataHandler::update_bars(){
    latest_stocktime.push_back(stocktime.front());
    stocktime.pop_front();

    latest_stockdata["open"].push_back(stockdata["open"].front());
    latest_stockdata["high"].push_back(stockdata["high"].front());
    latest_stockdata["low"].push_back(stockdata["low"].front());
    latest_stockdata["close"].push_back(stockdata["close"].front());
    latest_stockdata["adj_close"].push_back(stockdata["adj_close"].front());
    latest_stockdata["volume"].push_back(stockdata["volume"].front());

    stockdata["open"].pop_front();
    stockdata["high"].pop_front();
    stockdata["low"].pop_front();
    stockdata["close"].pop_front();
    stockdata["adj_close"].pop_front();
    stockdata["volume"].pop_front();

    latest_row_stockdata.push_back(row_stockdata.front());
    row_stockdata.pop_front();
}

int main(){
    CSVDataHandler x(std::list<Event*>(), "GOOG.csv");
    
    std::cout<<x.get_latest_bar().volume<<std::endl;
    return 0;
}