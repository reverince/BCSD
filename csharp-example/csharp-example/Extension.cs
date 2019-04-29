using System;
using System.Collections.Generic;
using System.Text;

namespace csharp_example
{
    public static class Extension
    {
        // this 키워드로 확장 메소드 선언
        public static bool Has(this string str, char ch)
        {
            return str.IndexOf(ch) >= 0;
        }
    }
}
