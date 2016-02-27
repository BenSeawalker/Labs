using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    internal class InternalReturnAllIterator : AbstractIterator
    {
        CompanyComponent inner;
        int current;

        public InternalReturnAllIterator(CompanyComponent component)
        {
            inner = component;
            current = 0;
        }

        public void First()
        {
            current = 0;
        }

        public void MoveNext()
        {
            ++current;
        }

        public bool IsDone()
        {
            return (current >= inner.GetCompanyComponents().Count);
        }

        public CompanyComponent GetCurrent()
        {
            if (IsDone())
                throw new System.IndexOutOfRangeException("Iterator index out of bounds!");

            return inner.GetCompanyComponents()[current];
        }
    }
}
