using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    class ConsoleLogger : ILogger
    {
        private LogLevel logLevel;

        internal ConsoleLogger()
        {
            logLevel = LogLevel.INFO;
        }

        internal ConsoleLogger(LogLevel level)
        {
            logLevel = level;
        }

        public void Log(string text)
        {
            Console.WriteLine(text);
        }

        public void Log(LogLevel level, string text)
        {
            if (level >= logLevel)
                Console.WriteLine(text);
        }
    }
}
