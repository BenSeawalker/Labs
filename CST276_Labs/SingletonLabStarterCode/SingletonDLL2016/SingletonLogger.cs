using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.IO;

namespace SingletonDLL2016
{
    public class SingletonLogger
    {
        // INSTANCE
        private static SingletonLogger _instance;

        // LOCKS
        private static Object _singletonLock = new Object();
        private Object _messageLock = new Object();

        // MEMBERS
        private StreamWriter streamwriter;


        // CTOR and DTOR
        private SingletonLogger(string LogFile)
        {
            streamwriter = new StreamWriter(File.Create(LogFile));
        }


        // PUBLIC METHODS
        public static SingletonLogger GetInstance()
        {
            if(_instance == null)
            {
                lock(_singletonLock)
                {
                    if (_instance == null)
                        _instance = new SingletonLogger("log.txt");
                }
            }

            return _instance;
        }

        public void LogMsg(string msg)
        {
            lock (_messageLock)
            {
                streamwriter.WriteLine("{0}  {1}", DateTime.Now, msg);
                Thread.Sleep(10);
            }
        }

        public void Close()
        {
            streamwriter.Close();
        }

        
    }
}
