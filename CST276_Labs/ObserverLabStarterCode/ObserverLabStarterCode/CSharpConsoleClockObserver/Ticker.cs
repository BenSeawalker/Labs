using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace CSharpConsoleClockObserver
{
    public delegate void OnSecondsDelegate();
    public delegate void OnTenthsDelegate();
    public delegate void OnHundredthsDelegate();


    public class Ticker
    {
        public event OnSecondsDelegate     OnSecondsTick;
        public event OnTenthsDelegate      OnTenthsTick;
        public event OnHundredthsDelegate  OnHundredthsTick;

        private bool done;
        public bool Done
        {
            get { return done; }
            set { done = value; }
        }

        public Ticker()
        {
            OnSecondsTick += NullHandler;
            OnTenthsTick += NullHandler;
            OnHundredthsTick += NullHandler;
        }

        void NullHandler()
        {}

        public void Run()
        {
            int count = 0;
            while (!done)
            {
                Interlocked.Increment(ref count);

                OnHundredthsTick();

                if (count % 10 == 0)
                {
                    OnTenthsTick();
                }
                if (count % 100 == 0)
                {
                    OnSecondsTick();
                }
                //if (count % 6000 == 0)
                //{
                //    timer.Minute();
                //}
                //if (count % 36000 == 0)
                //{
                //    timer.Hour();
                //}
            }
            if (count % 36000 == 0)
            {
                count = 0;
            }
        }
    }
}
