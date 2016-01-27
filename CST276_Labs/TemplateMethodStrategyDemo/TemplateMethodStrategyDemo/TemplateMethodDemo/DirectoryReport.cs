using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Principal;
using System.IO;

namespace TemplateMethodDemo
{
    class DirectoryReport:ReportTemplate
    {
        private string dir;
        public DirectoryReport(string directory)
        {
            dir = directory;
        }
        protected override string GetTitle()
        {
            return string.Format("Directory Report on Directory {0} ", dir);
        }

        protected override string[] GetColumnNames()
        {
            string[] ColumnNames = new string[] { "DirectoryName ", "LastModified " };
            return ColumnNames;
        }

        protected override List<object[]> GetRows()
        {
           
            List<object[]> rows = new List<object[]>();

            foreach (DirectoryInfo directory in new DirectoryInfo(dir).GetDirectories())
            {
                object[] row = new object[] { directory.Name, directory.LastWriteTime };                
                rows.Add(row);
            }
            return rows;

        }

        protected override string GetFooter()
        {
            return string.Format("Report ran {0} by {1}", DateTime.Now,
                  WindowsIdentity.GetCurrent().Name);
        }
    }
}
