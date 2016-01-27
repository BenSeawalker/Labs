using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace StockReportStrategies
{
    public class StockMarket
    {
        List<TradingDay> tradingDays = new List<TradingDay>();

        public StockMarket(string filename)
        {
            //the "using" statement will close the file automatically
            using (StreamReader reader = new StreamReader(filename))
            {
                // Skip header row
                reader.ReadLine();
                string dataRow = null;

                while ((dataRow = reader.ReadLine()) != null)
                {
                    tradingDays.Add(new TradingDay(dataRow));
                }
            }
        }

        /// <summary>
        /// Returns an iterator to iterate through each trading day
        /// </summary>
        /// <returns></returns>
        public IEnumerable<TradingDay> GetTradingDays()
        {
            return tradingDays;
        }
    }

}
