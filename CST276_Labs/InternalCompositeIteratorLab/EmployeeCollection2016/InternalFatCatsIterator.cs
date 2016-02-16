using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmployeeCollection2016
{
    public class InternalFatCatsIterator : AbstractIterator
    {
        Company _inner;
        int _index;

        const double _fat = 100000;

        public InternalFatCatsIterator(Company inner)
        {
            _inner = inner;
        }

        public void First()
        {
            _index = 0;
            if (!IsDone() && _inner.Employees[_index].Salary < _fat)
                Next();
        }

        public void Next()
        {
            ++_index;

            while (!IsDone() && _inner.Employees[_index].Salary < _fat)
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
