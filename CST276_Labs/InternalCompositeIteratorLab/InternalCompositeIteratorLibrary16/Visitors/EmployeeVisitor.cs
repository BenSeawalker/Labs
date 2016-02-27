using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class EmployeeVisitor : IVisitor
    {
        public EmployeeVisitor(CompanyComponent component)
        {
            component.Accept(this);
        }

        public void Visit(CompanyComposite composite)
        {
            Console.WriteLine();
        }

        public void Visit(Employee employee)
        {
            employee.DisplayNode();
        }
    }
}
