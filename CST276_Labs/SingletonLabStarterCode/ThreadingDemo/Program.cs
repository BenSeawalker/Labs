using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;

using SingletonDLL2016;

namespace ThreadingDemo
{
    public class ExerciseThreads
    {
        
        public static void ThreadLogger()
        {
            for (int nIter = 0; nIter < 100; nIter++)
            {
                SingletonLogger.GetInstance().LogMsg(String.Format("Writing Message {0}", nIter));
            }            
        }
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            List<Thread> threadlist = new List<Thread>();

            Stopwatch timer = new Stopwatch();

            timer.Start();
            Console.WriteLine("Begin Logging");
            for (int nThread = 0; nThread < 5; nThread++)
            {
                threadlist.Add(new Thread(ExerciseThreads.ThreadLogger));
                threadlist[nThread].Start();
            }

            foreach (Thread t in threadlist)
            {                
                t.Join();                
            }

            SingletonLogger.GetInstance().Close();
            Console.WriteLine("Elapsed Time: {0}", timer.Elapsed);
        }
    }
}
