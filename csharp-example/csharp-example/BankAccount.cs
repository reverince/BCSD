using System;
using System.Collections.Generic;
using System.Text;

namespace csharp_example
{
    class BankAccount
    {
        private static int accountNumberSeed = 23571113;

        private List<Transaction> transactions = new List<Transaction>();

        public string Number { get; }
        public string Owner { get; set; }
        public decimal Balance {
            get
            {
                decimal balance = 0;
                foreach (var t in transactions)
                    balance += t.Amount;
                return balance;
            }
        }

        public BankAccount(string name, decimal initialBalance)
        {
            this.Number = accountNumberSeed.ToString();
            accountNumberSeed++;
            this.Owner = name;
            Deposit(initialBalance, DateTime.Now, "초기금");
        }

        public void Deposit(decimal amount, DateTime date, string note)
        {
            if (amount <= 0)
                throw new ArgumentOutOfRangeException(nameof(amount), "예금액은 양수여야 합니다.");
            var deposit = new Transaction(amount, date, note);
            transactions.Add(deposit);
        }
        public void Withdrawal(decimal amount, DateTime date, string note)
        {
            if (Balance - amount < 0)
                throw new InvalidOperationException("잔액이 부족합니다.");
            var withdrawal = new Transaction(-amount, date, note);
            transactions.Add(withdrawal);
        }
        public string GetAccountHistory()
        {
            var report = new System.Text.StringBuilder();
            report.AppendLine("날짜\t금액\t비고");
            report.AppendLine("――――――――――");
            foreach (var t in transactions)
                report.AppendLine($"{t.Date.ToShortDateString()}\t{t.Amount}\t{t.Note}");

            return report.ToString();
        }
    }
}
