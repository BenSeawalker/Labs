using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Principal;

namespace TemplateMethodDemo
{
    class FileReport
    {
        string dirname;

        public FileReport(string dir)
        {
            dirname = dir;
        }

        public void ProduceReport()
        {
            Console.WriteLine("Report on director {0} ", dirname);

            Console.WriteLine("Filename, Size, Last Modified");

            DirectoryInfo dir = new DirectoryInfo(dirname);

            foreach (FileInfo file in dir.GetFiles())
            {
                Console.Write(file.Name);
                Console.Write(", ");
                Console.Write(file.Length);
                Console.Write(", ");
                Console.Write(file.LastWriteTime);
                Console.WriteLine();
            }

            Console.WriteLine("Report ran on {0} by {1} ", DateTime.Now, WindowsIdentity.GetCurrent().Name);
        }
    }
}
