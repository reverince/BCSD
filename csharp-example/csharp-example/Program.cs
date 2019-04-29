using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace csharp_example
{
    class Program
    {
        [Flags]
        enum Border { None = 0, Left = 1, Top = 2, Right = 4, Bottom = 8 }

        #region Functions

        static IEnumerable<int> GetPrime()  // yield
        {
            int[] primes = { 2, 3, 5, 7, 11 };
            int i = 0;
            while (i < primes.Length)
            {
                yield return primes[i];
                i++;
            }
        }

        static void AddNumAndIncrease(ref int a, ref int b, out int c)  // ref & out
        {
            c = a + b;
            a++;
            b++;
        }

        static int AddNums(params int[] nums)  // params
        {
            int sum = 0;
            foreach (var n in nums)
                sum += n;
            return sum;
        }

        static void IsBankAccount(object obj)  // is & as
        {
            BankAccount bankAccount;
            bool isAcount = obj is BankAccount;
            bankAccount = obj as BankAccount;  // null if fail
            bankAccount = (BankAccount)obj; // exception if fail
        }

        delegate int DelegateString2Int(string str);  // delegate
        static int String2Int(string str)
        {
            return int.Parse(str);
        }

        #endregion Functions

        static void Main(string[] args)
        {
#pragma warning disable  // 경고 메시지 OFF
            bool isTrue = true;  // 1bit boolean
            byte b = byte.MaxValue;  // 8bit unsigned integer
            sbyte sb = sbyte.MaxValue;  // 8bit signed integer
            short sh = short.MaxValue;  // 16bit signed integer
            ushort ush = ushort.MaxValue;  // 16bit unsigned integer
            int n = int.MaxValue;  // 32bit signed integer
            uint un = uint.MaxValue;  // 32bit unsigned integer
            long ld = 1024L;  // 64bit signed integer
            ulong uld = 1024UL;  // 64bit unsigned integer
            float f = 10.24F;  // 32bit floating point
            double lf = 10.24D;  // 64bit floating point
            decimal dec = 10.24M;  // 128bit decimal
            char c = 'a';  // 16bit unicode
            string s = string.Empty;  // unicode string

            int[,,] cubes = { };  // 다차원 배열
            object obj = cubes;  // contains any type
#pragma warning restore

            StringBuilder stringbuilder = new StringBuilder();
            for (int i = 0; i < 10; i++)
                stringbuilder.Append(i.ToString());
            string strBuilt = stringbuilder.ToString();
            Console.WriteLine($"StringBuilder: {strBuilt}");

            Border border = Border.Left | Border.Top;
            Console.WriteLine($"Border.Top: {border.HasFlag(Border.Top)}");

            int? nq = null;  // Nullable<int>
            int num = nq ?? -1;
            Console.WriteLine($"num is -1 if nq is null: {num}");

            Console.Write("GetPrime: ");
            foreach (int p in GetPrime())
                Console.Write($"{p} ");
            Console.WriteLine();

            int nA = 2, nB = 3;
            AddNumAndIncrease(ref nA, ref nB, out int nC);  // 인라인 변수 선언
            Console.WriteLine($"AddNumAndIncrease: nA: {nA}, nB: {nB}, nC: {nC}");

            Console.WriteLine($"AddNums(2, 3, 5, 7): {AddNums(2, 3, 5, 7)}");

            DelegateString2Int ds2i = new DelegateString2Int(String2Int);
            Console.WriteLine($"Delegate string to int: {ds2i("2357")}");

            var people = new[]
            {  // 읽기 전용 익명 타입
                new { Name="Lee", Age=33, Phone="000-111-1111" },
                new { Name="Kim", Age=25, Phone="000-222-2222" },
                new { Name="Park", Age=37, Phone="000-333-3333" }
            };
            // 람다식과 LINQ
            var query = people.Where(p => p.Age >= 30).Select(p => new { p.Name, p.Age });
            foreach (var p in query)
                Console.WriteLine(p);

            // Extension.cs에 정의된 확장 메소드
            Console.WriteLine($"\"Hello\".Has('e'): {"Hello".Has('e')}");

            // dynamic 기능 테스트
            Dynamic dynamic = new Dynamic();

            // 이하 클래스 관련

            var account = new BankAccount("앨리스", 1000);
            Console.WriteLine($"어서오세요, {account.Owner} 씨! 당신의 계좌 #{account.Number}의 잔액은 ${account.Balance}입니다.");

            account.Withdrawal(5, DateTime.Now, "햄버거");
            Console.WriteLine(account.Balance);
            account.Deposit(1, DateTime.Now, "오다 주웠다");
            Console.WriteLine(account.Balance);

            Console.WriteLine(account.GetAccountHistory());

            // 음수 잔액 계좌 생성
            try
            {
                var invalidAccount = new BankAccount("밥", -100);
            }
            catch (ArgumentOutOfRangeException e)
            {
                Console.WriteLine("계좌 생성 오류 발생");
                Console.WriteLine(e.ToString());
            }

        }
    }
}
