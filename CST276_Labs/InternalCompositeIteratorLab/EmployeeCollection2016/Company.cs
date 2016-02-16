using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmployeeCollection2016
{
    public class Company
    {
        string _name;
        string _description;
        List<Employee> _employees;

        public string Name { get { return _name; } }
        public string Description{ get { return _description; } }
        public List<Employee> Employees { get { return _employees; } }

       
        public Company(string name = "", string description = "")
        {
            _name = name;
            _description = description;
            _employees = new List<Employee>();
        }


    }
}
