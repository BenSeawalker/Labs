using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace TemplateMethodDemo
{
    class HTMLOutputReportStrategy : IReportOutputStrategy
    {
        XmlTextWriter writer;

        public HTMLOutputReportStrategy(string filename)
        {
            writer = new XmlTextWriter(filename, Encoding.Unicode);
            writer.WriteStartDocument();
            writer.WriteStartElement("HTML");
        }
        
        public void OutputTitle(string title)
        {
            writer.WriteElementString("h1", title);
        }

        public void OutputHeadings(string[] columns)
        {
            writer.WriteStartElement("table");
            writer.WriteStartElement("tr");
            foreach (string column in columns)
            {
                writer.WriteElementString("th", column);
            }
            writer.WriteEndElement();
        }

        public void OutputRow(object[] row)
        {
            writer.WriteStartElement("tr");
            foreach (object column in row)
            {
                writer.WriteElementString("td", column.ToString());
            }
            writer.WriteEndElement();
        }

        public void OutputFooter(string footing)
        {
            writer.WriteEndElement();
            writer.WriteElementString("i", footing);
            writer.Close();
        }
    }
}
