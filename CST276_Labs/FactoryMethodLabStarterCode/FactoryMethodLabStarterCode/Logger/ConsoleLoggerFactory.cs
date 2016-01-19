using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public class ConsoleLoggerFactory : ILoggerFactory
    {
        public ILogger CreateLogger()
        {
            return new ConsoleLogger();
        }


        public ILogger CreateLogger(LogLevel level)
        {
            return new ConsoleLogger(level);
        }
    }
}
