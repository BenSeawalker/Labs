using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodDemo
{
    class ConsoleOutputStrategy:IReportOutputStrategy
    {
        public void OutputTitle(string title)
        {
            Console.WriteLine(title);
        }

        public void OutputHeadings(string[] headings)
        {
            bool first = true;
            foreach (string column in headings)
            {
                if (first)
                {
                    Console.Write(column);
                    first = false;
                }
                else                 
                {
                    Console.Write(", {0} ", column);
                }                
            }
            Console.WriteLine();
        }

        public void OutputRow(object[] row)
        {
            Console.WriteLine(row.Aggregate((accumstr, nextstr) => accumstr.ToString() + 
                ", " + nextstr.ToString()).ToString());
        }

        public void OutputFooter(string footer)
        {
            Console.WriteLine(footer);
        }
    }
}
