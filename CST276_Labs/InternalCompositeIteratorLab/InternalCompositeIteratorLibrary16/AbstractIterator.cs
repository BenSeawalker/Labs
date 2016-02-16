﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public interface AbstractIterator
    {
        void First();

        void Next();

        bool IsDone();

        CompanyComponent CurrentItem();

    }
}
