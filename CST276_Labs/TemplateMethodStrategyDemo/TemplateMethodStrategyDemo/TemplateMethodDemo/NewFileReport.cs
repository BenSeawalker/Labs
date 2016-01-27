using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Security.Principal;

namespace TemplateMethodDemo
{
    class NewFileReport:ReportTemplate
    {
        private string dirname;

        public NewFileReport(string dir)
        {
            dirname = dir;
        }
        protected override string GetTitle()
        {
            return string.Format("File Report on Directory {0}", dirname);
        }

        protected override string[] GetColumnNames()
        {
           string[] ColumnNames = new string[] { "FileName", "Size", "LastModified" };
           return ColumnNames;
        }

        protected override List<object[]> GetRows()
        {
            List<object[]> rows = new List<object[]>();

            foreach (FileInfo file in new DirectoryInfo(dirname).GetFiles())
            {
                object[] row = new object[] { file.Name, file.Length, file.LastWriteTime };
                rows.Add(row);
            }

            return rows;
        }

        protected override string GetFooter()
        {
            return string.Format("Report ran on {0} by {1} ", DateTime.Now, WindowsIdentity.GetCurrent().Name);
        }
    }
}
