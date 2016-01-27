using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethodDemo
{
    class Program
    {
        private static void OutputReport(ReportTemplate report, IReportOutputStrategy strategy)
        {
            report.ProduceReport(strategy);
        }
        
        static void Main(string[] args)
        {

            //FileReport report = new FileReport(@"c:\");
            //ReportTemplate report = new NewFileReport(@"c:\");
            ReportTemplate report = new DirectoryReport(@"c:\");
            IReportOutputStrategy strategy = new ConsoleOutputStrategy();
            //IReportOutputStrategy strategy = new HTMLOutputReportStrategy("HTMLReport.html");
            OutputReport(report, strategy);
        }
    }
}
