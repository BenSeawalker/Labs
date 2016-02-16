using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class CompanyComposite : CompanyComponent
    {
        string _name;
        string _description;
        List<CompanyComponent> _employees;

       
        public CompanyComposite(string name = "", string description = "")
        {
            _name = name;
            _description = description;
            _employees = new List<CompanyComponent>();
        }

        public override void Add(CompanyComponent component)
        {
            _employees.Add(component);
        }

        public override void Remove(CompanyComponent component)
        {
            _employees.Remove(component);
        }

        public override List<CompanyComponent> GetCompanyComponents()
        {
            return _employees;
        }

        public override AbstractIterator CreateIterator()
        {
            return new InternalReturnAllIterator(this);
        }

        public override string GetName()
        {
            return _name;
        }

        public override void Display()
        {
            Console.WriteLine("\n\nCompany Name:\t{0}\nDescription:\t{1}\n", _name, _description);

            AbstractIterator it = CreateIterator();
            for (it.First(); !it.IsDone(); it.Next())
                it.CurrentItem().Display();
        }
    }
}
