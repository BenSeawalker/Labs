using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class CompositeVisitor : IVisitor
    {
        public CompositeVisitor(CompanyComponent component)
        {
            component.Accept(this);
        }

        public void Visit(CompanyComposite composite)
        {
            composite.DisplayNode();
        }

        public void Visit(Employee employee)
        {}
    }
}
