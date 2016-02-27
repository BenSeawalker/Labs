using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Reflection;

namespace ReflectionTest
{
    class Program
    {
        static void Main(string[] args)
        {
            string assemblyName = @"..\..\..\BankAccountLibrary\bin\Debug\BankAccountLibrary.dll";
            Assembly assembly = Assembly.LoadFrom(assemblyName);

            Type[] types = assembly.GetTypes();

            Console.WriteLine("the types available in assembly {0} are:", assembly);
            Console.WriteLine("------------------------------------------------------------------");

            foreach (Type type in types)
            {
                object dInstance = Activator.CreateInstance(type);

                Console.WriteLine("The class name is: {0}", type.FullName);
                Console.WriteLine("The namespace is: {0}", type.Namespace);
                Console.WriteLine("The base type is: {0}", (type.BaseType != null) ?
                    type.BaseType.FullName : "There is no base type");
                Console.WriteLine("------------------------------------------------------------------");

                foreach (MethodInfo methodInfo in type.GetMethods(BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly))
                {
                    Console.WriteLine("The method signature is: {0}", methodInfo);

                    foreach (ParameterInfo parameter in methodInfo.GetParameters())
                    {
                        Console.WriteLine("The parameter type is: {0}, The parameter name is: {1}", parameter.ParameterType, parameter.Name);
                    }
                    

                    Console.WriteLine("Dynamically calling method {0} on {1}", methodInfo.Name, type.FullName);

                    
                    object result = -1.0;

                    if (methodInfo.GetParameters().Length == 0)
                    {
                        object[] arguments = { };

                        result = type.InvokeMember(methodInfo.Name, BindingFlags.InvokeMethod,
                            null, dInstance, arguments);
                    }
                    else if (methodInfo.GetParameters().Length == 1)
                    {
                        object[] arguments = { 5000.0 };

                        result = type.InvokeMember(methodInfo.Name, BindingFlags.InvokeMethod,
                            null, dInstance, arguments);
                    }

                    Console.WriteLine("The result is: {0:C}", result);

                    Console.WriteLine("------------------------------------------------------------------");
                }
            }
        }
    }
}
