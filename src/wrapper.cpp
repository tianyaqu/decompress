#include "decompress.h"
#include "list_builder.h"
#include <iostream>
#include <Rcpp.h>

using namespace Rcpp;


//' @param market market name 
//' @export

// [[Rcpp::export]]
DataFrame R_decompress(std::string market, RawVector data)
{
    unsigned len = 0;
    struct Tick* result = 0;
    
    unsigned char* _data = &data[0];
    //unsigned char* _data = (unsigned char*)compressed;
    
    int ret = decompress(market.c_str(), _data, &result,&len);
    free(compressed);
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
        
        unsigned int i = 0;
        for(;i < len;i++)
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
          .add("day", day).add("updatetime", updatetime).add("millsec",mill).add("id",id)
          .add("open",open).add("close",close).add("high",high).add("low",low).add("volume",volume).add("turnover",turnover)
          .add("last",last).add("average",ave).add("preclose",preclose).add("askprice1",askp1).add("askprice2",askp2)
          .add("askprice3",askp3).add("askprice4",askp4).add("askprice5",askp5).add("askvolume1",askv1).add("askvolume2",askv2)
          .add("askvolume3",askv3).add("askvolume4",askv4).add("askvolume5",askv5).add("bidprice1",bidp1).add("bidprice2",bidp2)
          .add("bidprice3",bidp3).add("bidprice4",bidp4).add("bidprice5",bidp5).add("bidvolume1",bidv1).add("bidvolume2",bidv2)
          .add("bidvolume3",bidv3).add("bidvolume4",bidv4).add("bidvolume5",bidv5).add("upper",upper).add("lower",lower)
          .add("openinterest",openinterest).add("preopeninterest",preopeninterest).add("presettle",presettle).add("settle",settle);        
        
    }
}

#if 0
DataFrame R_GetBar(std::string ip,int port,std::string market, std::string contract_id, std::string type, unsigned start, unsigned end, int limit)
{
    struct Bar* result = 0;
    unsigned len = 0;
    int ret = m_GetBar(&result,&len,ip.c_str(),port,market.c_str(),contract_id.c_str(), type.c_str(), start, end, limit);
    
    Rcpp::CharacterVector id(len);
    NumericVector ts(len);
    NumericVector open(len);
    NumericVector close(len);
    NumericVector high(len);
    NumericVector low(len);
    //overflow defence
    NumericVector volume(len);
    NumericVector turnover(len);
    unsigned i = 0;
    for(;i < len;i++)
    {
      ts[i] = result[i].Timestamp;
      id[i] = result[i].InstrumentID;
      open[i] = result[i].Open;
      close[i] = result[i].Close;
      high[i] = result[i].High;
      low[i] = result[i].Low;
      volume[i] = result[i].Volume;
      turnover[i] = result[i].Turnover;
      //std::cout<<ts[i]<<" "<<id[i]<<" "<<open[i]<<"\n";
    }
    
    m_FreeMem(result);
    
    return DataFrame::create(Named("timestamp")=ts,Named("id")=id,\
      Named("open")=open,Named("close")=close,\
      Named("high")=high,Named("low")=low,\
      Named("volume")=volume,Named("turnover")=turnover);
}


DataFrame R_GetTicks(std::string ip,int port,std::string c_market,std::string contractId, unsigned start, unsigned end, int limit)
{
    struct Tick* result = 0;
    unsigned len = 0,i = 0;
    int ret = m_GetTicks(&result,&len,ip.c_str(),port,c_market.c_str(),contractId.c_str(), start, end, limit);
    Rcpp::CharacterVector id(len);
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
     
    for(;i < len;i++)
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
    
    m_FreeMem(result);
    
    return ListBuilder()
      .add("day", day).add("updatetime", updatetime).add("millsec",mill).add("id",id)
      .add("open",open).add("close",close).add("high",high).add("low",low).add("volume",volume).add("turnover",turnover)
      .add("last",last).add("average",ave).add("preclose",preclose).add("askprice1",askp1).add("askprice2",askp2)
      .add("askprice3",askp3).add("askprice4",askp4).add("askprice5",askp5).add("askvolume1",askv1).add("askvolume2",askv2)
      .add("askvolume3",askv3).add("askvolume4",askv4).add("askvolume5",askv5).add("bidprice1",bidp1).add("bidprice2",bidp2)
      .add("bidprice3",bidp3).add("bidprice4",bidp4).add("bidprice5",bidp5).add("bidvolume1",bidv1).add("bidvolume2",bidv2)
      .add("bidvolume3",bidv3).add("bidvolume4",bidv4).add("bidvolume5",bidv5).add("upper",upper).add("lower",lower)
      .add("openinterest",openinterest).add("preopeninterest",preopeninterest).add("presettle",presettle).add("settle",settle);
}


double R_GetHistoricalValue(std::string ip,int port,std::string market, std::string contractId, std::string type, std::string filter, std::string mode, unsigned start, unsigned end, int limit)
{
    double r = 0;
    int ret =  m_GetHistoricalValue(&r,ip.c_str(),port,market.c_str(), contractId.c_str(), type.c_str(), filter.c_str(), mode.c_str(), start, end, limit);
    return r;
}
#endif