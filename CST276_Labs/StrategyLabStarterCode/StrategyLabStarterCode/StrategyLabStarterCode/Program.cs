using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using StockReportStrategies;

namespace StrategyLabStarterCode
{
    class Program
    {
        private static void ReportTradingDays(StockMarket tradingDays, IFilterStrategy strategy)
        {
            foreach (TradingDay day in tradingDays.GetTradingDays())
            {
                if (strategy.FilterStrategy(day))
                    Console.WriteLine(day.ToString());
            }
        }

        static void Main(string[] args)
        {
            StockMarket tradingDays = new StockMarket(@"..\..\stockData.csv");
            HighDailySwing highDailySwing = new HighDailySwing();
            HighVolume highVolume = new HighVolume();

            ReportTradingDays(tradingDays, highDailySwing);
            //ReportTradingDays(tradingDays, highVolume);
        }        
    }
}
