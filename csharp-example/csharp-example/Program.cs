using System;

namespace csharp_example
{
    class Program
    {
        static void Main(string[] args)
        {
            // 시험용 계좌
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

            // 
        }
    }
}
