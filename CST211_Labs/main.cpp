#include <QCoreApplication>

#include <QDebug>

#include "doublelinkedlist.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    
    try
    {
        DoubleLinkedList<int> l1;
        l1.Append(2);
        l1.InsertAfter(3, 2);
        l1.Prepend(1);
        l1.InsertBefore(0, 1);
        
        DoubleLinkedList<int> l2(l1);
        l2.Append(6);
        l2.InsertAfter(5, 3);
        l2.InsertBefore(4, 5);
        
        qDebug() << l1.First();
        qDebug() << l1.Last() << '\n';
        
        qDebug() << l2.First();
        qDebug() << l2.Last() << '\n';
    }
    catch (const char * e)
    {
        qDebug() << e << '\n';
    }
    
    
    
    return a.exec();
}

