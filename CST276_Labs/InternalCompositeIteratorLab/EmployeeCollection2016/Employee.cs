﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmployeeCollection2016
{
    public class Employee
    {
        string _name;
        string _ssn;
        double _salary;

        public string Name { get { return _name; } }
        public string SSN { get { return _ssn; } }
        public double Salary { get { return _salary; } }

        public Employee(string name, string ssn, double salary)
        {
            _name = name;
            _ssn = ssn;
            _salary = salary;
        }

        public void DisplayEmployee()
        {
            Console.WriteLine("Name: {0,-20} SSN: {1,-15} Salary: {2,20:C}", _name, _ssn, _salary);
        }
    }
}
