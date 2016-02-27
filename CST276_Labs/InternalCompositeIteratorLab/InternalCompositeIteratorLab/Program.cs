using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//using EmployeeCollection2016;
using InternalCompositeIteratorLibrary16;

namespace InternalCompositeIteratorLab
{
    class Program
    {
        //static void PrintEmployees(AbstractIterator it)
        //{
        //    for (it.First(); !it.IsDone(); it.Next())
        //    {
        //        it.CurrentItem().DisplayEmployee();
        //        Console.WriteLine();
        //    }
        //}

        static void Main(string[] args)
        {
            // PART 1
            //Company c = new Company("Valve", "An entertainment software and technology company founded in 1996");

            //c.Employees.Add(new Employee("Gabe Newell", "123455789", 1000000));
            //c.Employees.Add(new Employee("Steven Noonan", "63561541", 100000));
            //c.Employees.Add(new Employee("Mike Ambinder", "74584874", 1000));
            //c.Employees.Add(new Employee("John Guthrie", "12323156", 142134));
            //c.Employees.Add(new Employee("Emily Kent", "458468765", 10000));

            //Console.WriteLine("\n{0} Employees:\n", c.Name);
            //PrintEmployees(new InternalReturnAllIterator(c));

            //Console.WriteLine("\nFat Cats:\n");
            //PrintEmployees(new InternalFatCatsIterator(c));

            // PART 2
            CompanyComponent valve = new CompanyComposite("Valve", "An entertainment software and technology company founded in 1996");
            CompanyComponent steam = new CompanyComposite("Steam", "The leading software distribution platform");
            CompanyComponent dota = new CompanyComposite("DOTA", "MOBA game");
            CompanyComponent csgo = new CompanyComposite("CS:GO", "FPS game");
            CompanyComponent tf2 = new CompanyComposite("TF2", "TPS game");

            CompanyComponent gaben = new Employee("Gabe Newell", "123456789", 1000000);
            CompanyComponent seanj = new Employee("Sean Jenkin", "916394807", 100000);
            CompanyComponent emilyk = new Employee("Emily Kent", "458468765", 100000);

            CompanyComponent mattl = new Employee("Matt Logue", "189631892", 10000);
            CompanyComponent stevenn = new Employee("Steven Noonan", "918749128", 10000);

            CompanyComponent jessc = new Employee("Jess Cliffe", "687698129", 10000);
            CompanyComponent alfredr = new Employee("Alfred Reynolds", "576481928", 10000);

            CompanyComponent jeffb = new Employee("Jeff Ballinger", "687698129", 10000);
            CompanyComponent johnc = new Employee("John Cook", "576481928", 10000);


            // VALVE
            valve.Add(gaben);
            valve.Add(seanj);
            valve.Add(emilyk);
            valve.Add(mattl);
            valve.Add(stevenn);
            valve.Add(jessc);
            valve.Add(alfredr);
            valve.Add(jeffb);
            valve.Add(johnc);

            valve.Add(steam);

            // STEAM
            steam.Add(gaben);
            steam.Add(seanj);
            steam.Add(emilyk);

            steam.Add(dota);
            steam.Add(csgo);
            steam.Add(tf2);

            // DOTA
            dota.Add(mattl);
            dota.Add(stevenn);

            // CSGO
            csgo.Add(jessc);
            csgo.Add(alfredr);

            // TF2
            tf2.Add(jeffb);
            tf2.Add(johnc);


            //valve.Display();

            //AbstractIterator iter = new CompositeIterator(valve);
            //for (iter.First(); !iter.IsDone(); iter.MoveNext())
            //    iter.GetCurrent().DisplayNode();

            IVisitor comp_visitor = new CompositeVisitor(valve);

            //IVisitor emp_visitor = new EmployeeVisitor(valve);

            Console.WriteLine();
        }
    }
}
