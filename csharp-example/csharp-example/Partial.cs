using System;
using System.Collections.Generic;
using System.Text;

namespace csharp_example
{
    partial class Partial  // 여러 곳에서 선언 가능한 partial 클래스
    {
        partial void Do();
    }

    partial class Partial
    {
        partial void Do()  // partial 메소드 (오직 private void만)
        {
            throw new NotImplementedException();
        }
    }
}
