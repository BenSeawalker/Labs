using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using TemplateAccounts;

namespace TemplateLabStarterCode
{
    class Program
    {
        private static void PrintAccountForecasts(List<AccountTemplate> accounts)
        {
            foreach (AccountTemplate account in accounts)
            {
                account.SetDeposit(5000);
            }

            for (int nYear = 1; nYear <= 10; nYear++)
            {
                Console.WriteLine("Year {0} ", nYear);
                foreach (AccountTemplate account in accounts)
                {
                    account.PayYearlyInterest();
                    Console.WriteLine("{0} {1:C} ",account.GetType().Name,  account.GetBalance());
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            List<AccountTemplate> accounts = new List<AccountTemplate>();

            accounts.Add(new ClassicAccount());
            accounts.Add(new TaxFreeSavingsAccount());
            accounts.Add(new VariableInterestAccount());
            PrintAccountForecasts(accounts);
        }

        
    }
}
