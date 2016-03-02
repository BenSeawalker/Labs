using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using SpreadSheet;
using Decorator;
using System.Threading;


namespace CommandLogging
{
    class Program
    {
        private static void UpdateSpreadSheet(ISpreadSheet spreadsheet)
        {
            int cellnum = 0;
            for (int nRow = 0; nRow < spreadsheet.NumberOfRows; nRow++)
            {
                for (int nCol = 0; nCol < spreadsheet.NumberOfColumns; nCol++)
                {
                    Console.Write("{0} ", cellnum);
                    spreadsheet.SetValue(nRow, nCol, cellnum);
                    cellnum++;

                    //Could do but performance hit
                    //spreadsheet.Save("Calcspreadsheet.bin");
                    //Thread.Sleep(100);
                }
            }
            Console.WriteLine();
        }

        private static void ValidateSheet(ISpreadSheet spreadsheet)
        {
            int cellnum = 0;

            Console.WriteLine("Validating spreadsheet");

            for (int nRow = 0; nRow < spreadsheet.NumberOfRows; nRow++)
            {
                for (int nCol = 0; nCol < spreadsheet.NumberOfColumns; nCol++)
                    Debug.Assert(spreadsheet.GetValue(nRow, nCol) == cellnum++, "Not the correct value");
            }

            Console.WriteLine("Finished validating spreadsheet");
        }

        private static void SuperSafeSpreadSheet()
        {
            ISpreadSheet Calcspreadsheet = new SimpleSpreadsheet("Calc");

            SpreadSheetCommandLogDecorator safesheet =
                new SpreadSheetCommandLogDecorator(Calcspreadsheet);

            safesheet.Save("Calcspreadsheet.bin");
            //update the spreadsheet
            UpdateSpreadSheet(safesheet);

            //what if this doesn't happen
            safesheet.Save("Calcspreadsheet.bin");

            //lose it and reload
            safesheet = null;

            Calcspreadsheet = SimpleSpreadsheet.Load("Calcspreadsheet.bin");

            safesheet =
                new SpreadSheetCommandLogDecorator(Calcspreadsheet);

            safesheet.Restore();

            //validate the values are correct
            ValidateSheet(safesheet);
        }

        private static void BatchSpreadSheet()
        {
            ISpreadSheet Calcspreadsheet = new SimpleSpreadsheet("Calc");

            SpreadSheetBatchCommandDecorator batchsheet =
                new SpreadSheetBatchCommandDecorator(Calcspreadsheet);
            
            //update the spreadsheet
            UpdateSpreadSheet(batchsheet);

            //validate the values are correct
            ValidateSheet(batchsheet);
        }

        static void Main(string[] args)
        {
            //ISpreadSheet Calcspreadsheet = new SimpleSpreadsheet("Calc");

            //Calcspreadsheet.Save("Calcspreadsheet.bin");

            //UpdateSpreadSheet(Calcspreadsheet);

            //////what if this doesn't happen
            //Calcspreadsheet.Save("Calcspreadsheet.bin");

            //Calcspreadsheet = null;
            //Calcspreadsheet = SimpleSpreadsheet.Load("Calcspreadsheet.bin");

            //ValidateSheet(Calcspreadsheet);

            //SuperSafeSpreadSheet();

            BatchSpreadSheet();
        }
    }
}
