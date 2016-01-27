using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StockReportStrategies
{
    public class HighVolume : IFilterStrategy
    {
        public bool FilterStrategy(TradingDay day)
        {
            return (day.Volume > 20000000);
        }
    }
}
