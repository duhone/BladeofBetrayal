using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace CR.Utility
{
    public class Singleton<T> where T : class
    {
        public static T Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (threadLock)
                    {
                        if (instance == null)
                        {
                            Type type = typeof(T);
                            ConstructorInfo constructorInfo = type.GetConstructor(
                                BindingFlags.Instance | BindingFlags.NonPublic, null, Type.EmptyTypes, null);
                            instance = (T)constructorInfo.Invoke(null);
                        }
                    }
                }
                return instance;
            }
        }
        protected Singleton()
        {
        }
        private static T instance = null;
        private static Object threadLock = new Object();
    }
}
