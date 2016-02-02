using System;
using System.Collections.Generic;
using System.Text;

namespace CSharpConsoleClockObserver
{
    public class SecondClock : Clock, IDisposable
    {
        Ticker _ticker;

        public SecondClock(int originalColumn, int originalRow, ConsoleColor? color, Ticker ticker)
            : base(originalColumn, originalRow, color)
        {
            _ticker = ticker;
            _ticker.OnSecondsTick += Second;
        }

        public void Dispose()
        {
            _ticker.OnSecondsTick -= Second;
        }

        private void Second()
        {
            DateTime dt = DateTime.Now;

            WriteAt(dt.Hour, 0, 0, 2);
            WriteAt(":", 2, 0);
            WriteAt(dt.Minute, 3, 0, 2);
            WriteAt(":", 5, 0);
            WriteAt(dt.Second, 6, 0, 2);
        }
    }

    public class HundredthSecondClock : Clock, IDisposable
    {
        Ticker _ticker;

        public HundredthSecondClock(int originalColumn, int originalRow, ConsoleColor? color, Ticker ticker)
            : base(originalColumn, originalRow, color)
        {
            _ticker = ticker;
            _ticker.OnHundredthsTick += HundredthSecond;
        }

        public void Dispose()
        {
            _ticker.OnHundredthsTick -= HundredthSecond;
        }

        public void HundredthSecond()
        {
            DateTime dt = DateTime.Now;

            WriteAt(dt.Hour, 0, 0, 2);
            WriteAt(":", 2, 0);
            WriteAt(dt.Minute, 3, 0, 2);
            WriteAt(":", 5, 0);
            WriteAt(dt.Second, 6, 0, 2);
            WriteAt(".", 8, 0);
            WriteAt(dt.Millisecond / 10, 9, 0, 2);
        }
    }

    public class TenthSecondClock : Clock, IDisposable
    {
        Ticker _ticker;

        public TenthSecondClock(int originalColumn, int originalRow, ConsoleColor? color, Ticker ticker)
            : base(originalColumn, originalRow, color)
        {
            _ticker = ticker;
            _ticker.OnTenthsTick += TenthSecond;
        }

        public void TenthSecond()
        {
            DateTime dt = DateTime.Now;

            WriteAt(dt.Hour, 0, 0, 2);
            WriteAt(":", 2, 0);
            WriteAt(dt.Minute, 3, 0, 2);
            WriteAt(":", 5, 0);
            WriteAt(dt.Second, 6, 0, 2);
            WriteAt(".", 8, 0);
            WriteAt(dt.Millisecond / 100, 9, 0, 1);
        }

        public void Dispose()
        {
            _ticker.OnTenthsTick -= TenthSecond;
        }
    }
}
