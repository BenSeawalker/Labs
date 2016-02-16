using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmployeeCollection2016
{
    public class InternalReturnAllIterator : AbstractIterator
    {
        Company _inner;
        int _index;

        public InternalReturnAllIterator(Company inner)
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
            return (_index >= _inner.Employees.Count);
        }

        public Employee CurrentItem()
        {
            if (IsDone())
                throw new System.IndexOutOfRangeException("Iterator index out of bounds!");

            return _inner.Employees[_index];
        }
    }
}
