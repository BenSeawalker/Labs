using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodDemo
{
    interface IReportOutputStrategy
    {
        void OutputTitle(string title);
        void OutputHeadings(string[] headings);
        void OutputRow(object[] row);
        void OutputFooter(string footer);

    }
}
