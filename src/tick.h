#ifndef TICK_H
#define TICK_H 

struct Tick{
    unsigned ActionDay;
    unsigned TradingDay;
    char ExchangeID[16];
    char InstrumentID[16];
    char Symbol[16];
    unsigned UpdateMillisec;    
    unsigned UpdateTime;
    double OpenPrice;
    double ClosePrice;
    double HighestPrice;
    double LowestPrice;
    double Turnover;
    int Volume;
    double LastPrice;
    double AveragePrice;
    double PreClosePrice;
    double AskPrice1;
    double AskPrice2;
    double AskPrice3;
    double AskPrice4;
    double AskPrice5;
    int AskVolume1;
    int AskVolume2;
    int AskVolume3;
    int AskVolume4;
    int AskVolume5;
    double BidPrice1;
    double BidPrice2;
    double BidPrice3;
    double BidPrice4;
    double BidPrice5;
    int BidVolume1;
    int BidVolume2;
    int BidVolume3;
    int BidVolume4;
    int BidVolume5;
    double UpperLimitPrice;
    double LowerLimitPrice;
    unsigned long long OpenInterest;
    unsigned long long PreOpenInterest;
    double PreSettlementPrice;
    double SettlementPrice;
};

struct Bar{
    unsigned Timestamp;
    char InstrumentID[16];
    double Open;
    double Close;
    double Low;
    double High;
    unsigned long long Volume;
    double Turnover;
};

#endif