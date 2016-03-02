using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SpreadSheet;
using Command;

namespace Decorator
{
    public class SpreadSheetBatchCommandDecorator : SpreadSheetDecorator
    {
        BatchInvoker invoker;

        public SpreadSheetBatchCommandDecorator(ISpreadSheet spreadsheet) : base(spreadsheet)
        {
            invoker = new BatchInvoker();
        }

        public override void SetValue(int nRow, int nCol, int value)
        {
            invoker.Execute(new SetValueCommand(inner, nRow, nCol, value));
        }
    }
}
