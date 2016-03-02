using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SpreadSheet;

namespace Decorator
{
    public class SpreadSheetDecorator : ISpreadSheet
    {
        protected ISpreadSheet inner;

        public SpreadSheetDecorator(ISpreadSheet spreadsheet)
        {
            inner = spreadsheet;
        }
        
        public virtual int GetValue(int nRow, int nCol)
        {
            return inner.GetValue(nRow, nCol);
        }

        public virtual void SetValue(int nRow, int nCol, int value)
        {
            inner.SetValue(nRow, nCol, value);
        }

        public virtual string Name
        {
            get { return inner.Name; }
        }

        public virtual int NumberOfColumns
        {
            get { return inner.NumberOfColumns; }
        }

        public virtual int NumberOfRows
        {
            get { return inner.NumberOfRows; }
        }

        public virtual void Save(string filename)
        {
            inner.Save(filename);
        }        
    }
}
