#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "parser.h"

using namespace std;

//max line per file
#define MAX_LINE 100000

int parse_tick(string market, string line, struct Tick* p)
{

    unsigned int num = 0;
    unsigned pre = 0;
    int ret = -1;
    struct Tick tick;
    
#ifdef __GNUC__
    snprintf(tick.ExchangeID,sizeof(tick.ExchangeID),"%s", market.c_str());
#else
    sprintf_s(tick.ExchangeID, "%s", market.c_str());
#endif

    while ((ret = line.find(',', pre)) > 0)
    {
        string element = line.substr(pre, ret - pre);
        int line_len = element.size();
        if (num == 0)
        {
            string t0 = element.substr(0, 8);
            string t1 = element.substr(8, line_len - 3 - 8);
            string t2 = element.substr(line_len - 3, 3);
            tick.ActionDay = atoi(t0.c_str());
            tick.TradingDay = tick.ActionDay;
            tick.UpdateTime = atoi(t1.c_str());
            tick.UpdateMillisec = atoi(t2.c_str());
        }
        else if (num == 1)
        {
#ifdef __GNUC__
            snprintf(tick.Symbol,sizeof(tick.Symbol),"%s", element.c_str());
            snprintf(tick.InstrumentID,sizeof(tick.InstrumentID),"%s", element.c_str());
#else
            sprintf_s(tick.Symbol, "%s", element.c_str());
            sprintf_s(tick.InstrumentID, "%s", element.c_str());
#endif
        }
        else if (num == 2)
        {
            tick.OpenPrice = atof(element.c_str());
        }
        else if (num == 3)
        {
            tick.ClosePrice = atof(element.c_str());
        }
        else if (num == 4)
        {
            tick.HighestPrice = atof(element.c_str());
        }
        else if (num == 5)
        {
            tick.LowestPrice = atof(element.c_str());
        }
        else if (num == 6)
        {
            tick.Turnover = atof(element.c_str());
        }
        else if (num == 7)
        {
            tick.Volume = atoi(element.c_str());
        }
        else if (num == 8)
        {
            tick.LastPrice = atof(element.c_str());
        }
        else if (num == 9)
        {
            tick.AveragePrice = atof(element.c_str());
        }
        else if (num == 10)
        {
            tick.PreClosePrice = atof(element.c_str());
        }
        else if (num == 11)
        {
            tick.UpperLimitPrice = atof(element.c_str());
        }
        else if (num == 12)
        {
            tick.LowerLimitPrice = atof(element.c_str());
        }
        else if (num == 13)
        {
            tick.OpenInterest = atoll(element.c_str());
        }
        else if (num == 14)
        {
            tick.PreOpenInterest = atoll(element.c_str());
        }
        else if (num == 15)
        {
            tick.PreSettlementPrice = atof(element.c_str());
        }
        else if (num == 16)
        {
            tick.SettlementPrice = atof(element.c_str());
        }
        else if (num == 17)
        {
            tick.AskPrice1 = atof(element.c_str());
        }
        else if (num == 18)
        {
            tick.AskPrice2 = atof(element.c_str());
        }
        else if (num == 19)
        {
            tick.AskPrice3 = atof(element.c_str());
        }
        else if (num == 20)
        {
            tick.AskPrice4 = atof(element.c_str());
        }
        else if (num == 21)
        {
            tick.AskPrice5 = atof(element.c_str());
        }
        else if (num == 22)
        {
            tick.AskVolume1 = atoi(element.c_str());
        }
        else if (num == 23)
        {
            tick.AskVolume2 = atoi(element.c_str());
        }
        else if (num == 24)
        {
            tick.AskVolume3 = atoi(element.c_str());
        }
        else if (num == 25)
        {
            tick.AskVolume4 = atoi(element.c_str());
        }
        else if (num == 26)
        {
            tick.AskVolume5 = atoi(element.c_str());
        }
        else if (num == 27)
        {
            tick.BidPrice1 = atof(element.c_str());
        }
        else if (num == 28)
        {
            tick.BidPrice2 = atof(element.c_str());
        }
        else if (num == 29)
        {
            tick.BidPrice3 = atof(element.c_str());
        }
        else if (num == 30)
        {
            tick.BidPrice4 = atof(element.c_str());
        }
        else if (num == 31)
        {
            tick.BidPrice5 = atof(element.c_str());
        }
        else if (num == 32)
        {
            tick.BidVolume1 = atoi(element.c_str());
        }
        else if (num == 33)
        {
            tick.BidVolume2 = atoi(element.c_str());
        }
        else if (num == 34)
        {
            tick.BidVolume3 = atoi(element.c_str());
        }
        else if (num == 35)
        {
            tick.BidVolume4 = atoi(element.c_str());
        }


        pre = ret + 1;
        num++;
    }

    string element = line.substr(pre, line.size() - pre);
    tick.BidVolume5 = atoi(element.c_str());

    memcpy(p, &tick, sizeof(struct Tick));
    return 0;
}

unsigned int append_csv2_buffer(string market, string csv, struct Tick* ptr, unsigned int ava_num)
{
    unsigned int num = 0;
    unsigned pre = 0;
    int ret = -1;

    while ((ret = csv.find('\n', pre)) > 0)
    {
        string line = csv.substr(pre, ret + 1 - pre);
        if (num < ava_num)
        {
            if (0 == parse_tick(market, line, ptr + num))
            {
                num++;
            }
        }
        else
        {
            break;
        }
        pre = ret + 1;
    }

    return num;
}

int parse_string(const char* c_market,const char* content, struct Tick** result, unsigned* len)
{
    string market(c_market);
    string file_content((const char*)content);

    *result = (struct Tick*)malloc(sizeof(struct Tick) * MAX_LINE);
    if(*result == NULL)
    {
        *len = 0;
        return -1;
    }

    int ava_num = MAX_LINE;
    *len = append_csv2_buffer(market, file_content, *result,ava_num);
    return 0;
}


void m_FreeMem(void* ptr)
{
    free(ptr);
}