using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class InternalReturnAllIterator : AbstractIterator
    {
        CompanyComponent _inner;
        int _index;

        public InternalReturnAllIterator(CompanyComponent inner)
        {
            _inner = inner;
        }

        public void First()
        {
            _index = 0;
        }

        public void Next()
        {
            ++_index;
        }

        public bool IsDone()
        {
            return (_index >= _inner.GetCompanyComponents().Count);
        }

        public CompanyComponent CurrentItem()
        {
            if (IsDone())
                throw new System.IndexOutOfRangeException("Iterator index out of bounds!");

            return _inner.GetCompanyComponents()[_index];
        }
    }
}
