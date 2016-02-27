using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class CompanyComponent
    {
        public virtual void Add(CompanyComponent component)
        {
            throw new System.NotImplementedException();
        }

        public virtual void Remove(CompanyComponent component)
        {
            throw new System.NotImplementedException();
        }

        public virtual List<CompanyComponent> GetCompanyComponents()
        {
            throw new System.NotImplementedException();
        }

        public virtual AbstractIterator CreateIterator()
        {
            throw new System.NotImplementedException();
        }

        public virtual string GetName()
        {
            throw new System.NotImplementedException();
        }

        public virtual void Display()
        {
            throw new System.NotImplementedException();
        }

        public virtual void DisplayNode()
        {
            throw new System.NotImplementedException();
        }

        public virtual void Accept(IVisitor visitor)
        {
            throw new System.NotImplementedException();
        }
    }
}
