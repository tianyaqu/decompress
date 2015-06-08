#include "decompress.h"
#include "list_builder.h"
#include <iostream>
#include <Rcpp.h>

using namespace Rcpp;

//' @param market market name 
//' @param data compressed data
//' @export 

// [[Rcpp::export]]
DataFrame R_decompress(std::string market, RawVector data)
{
    unsigned len = 0;
    struct Tick* result = 0;
    
    unsigned char* _data = &data[0];
    
    int ret = decompress(market.c_str(), _data, &result,&len);
    if (ret == 0 && len > 0)
    {
        CharacterVector id(len);
        NumericVector day(len);
        NumericVector updatetime(len);
        NumericVector mill(len);
        NumericVector open(len);
        NumericVector close(len);
        NumericVector high(len);
        NumericVector low(len);
        //overflow defence
        NumericVector volume(len);
        NumericVector turnover(len);
        NumericVector last(len);
        NumericVector ave(len);
        NumericVector preclose(len);
        
        NumericVector askp1(len);
        NumericVector askp2(len);
        NumericVector askp3(len);
        NumericVector askp4(len);
        NumericVector askp5(len);
    
        NumericVector askv1(len);
        NumericVector askv2(len);
        NumericVector askv3(len);
        NumericVector askv4(len);
        NumericVector askv5(len);
        
        NumericVector bidp1(len);
        NumericVector bidp2(len);
        NumericVector bidp3(len);
        NumericVector bidp4(len);
        NumericVector bidp5(len);
        
        NumericVector bidv1(len);
        NumericVector bidv2(len);
        NumericVector bidv3(len);
        NumericVector bidv4(len);
        NumericVector bidv5(len);
        NumericVector upper(len);
        NumericVector lower(len);
        NumericVector openinterest(len);
        NumericVector preopeninterest(len);
        NumericVector presettle(len);
        NumericVector settle(len);
        
        for(unsigned int i = 0;i < len;i++)
        {
          day[i] = result[i].ActionDay;      
          updatetime[i] = result[i].UpdateTime;
          mill[i] = result[i].UpdateMillisec;
          
          id[i] = result[i].InstrumentID;
          open[i] = result[i].OpenPrice;
          close[i] = result[i].ClosePrice;
          high[i] = result[i].HighestPrice;
          low[i] = result[i].LowestPrice;
          volume[i] = result[i].Volume;
          turnover[i] = result[i].Turnover; 

          last[i]  = result[i].LastPrice;
          ave[i] = result[i].AveragePrice;
          preclose[i] = result[i].PreClosePrice;
          
          askp1[i] = result[i].AskPrice1;
          askp2[i] = result[i].AskPrice2;
          askp3[i] = result[i].AskPrice3;
          askp4[i] = result[i].AskPrice4;
          askp5[i] = result[i].AskPrice5;
          
          askv1[i] = result[i].AskVolume1;
          askv2[i] = result[i].AskVolume2;
          askv3[i] = result[i].AskVolume3;
          askv4[i] = result[i].AskVolume4;
          askv5[i] = result[i].AskVolume5;
          
          bidp1[i] = result[i].BidPrice1;
          bidp2[i] = result[i].BidPrice2;
          bidp3[i] = result[i].BidPrice3;
          bidp4[i] = result[i].BidPrice4;
          bidp5[i] = result[i].BidPrice5;
          
          bidv1[i] = result[i].BidVolume1;
          bidv2[i] = result[i].BidVolume2;
          bidv3[i] = result[i].BidVolume3;
          bidv4[i] = result[i].BidVolume4;
          bidv5[i] = result[i].BidVolume5;
          
          upper[i] = result[i].UpperLimitPrice;
          lower[i] = result[i].LowerLimitPrice;
          openinterest[i] = result[i].OpenInterest;
          preopeninterest[i] = result[i].PreOpenInterest;
          presettle[i] = result[i].PreSettlementPrice;
          settle[i] = result[i].SettlementPrice;      
        }
    
        free_mem(result);
    
        return ListBuilder()
          .add("day", day).add("updatetime", updatetime).add("millsec",mill).add("instrument",id)
          .add("Open",open).add("Close",close).add("High",high).add("Low",low).add("Volume",volume).add("Turnover",turnover)
          .add("Last",last).add("Average",ave).add("Preclose",preclose).add("Askprice1",askp1).add("Askprice2",askp2)
          .add("Askprice3",askp3).add("Askprice4",askp4).add("Askprice5",askp5).add("Askvolume1",askv1).add("Askvolume2",askv2)
          .add("Askvolume3",askv3).add("Askvolume4",askv4).add("Askvolume5",askv5).add("Bidprice1",bidp1).add("Bidprice2",bidp2)
          .add("Bidprice3",bidp3).add("Bidprice4",bidp4).add("Bidprice5",bidp5).add("Bidvolume1",bidv1).add("Bidvolume2",bidv2)
          .add("Bidvolume3",bidv3).add("Bidvolume4",bidv4).add("Bidvolume5",bidv5).add("Upper",upper).add("Lower",lower)
          .add("Openinterest",openinterest).add("Preopeninterest",preopeninterest).add("Presettle",presettle).add("Settle",settle);        
        
    }
}