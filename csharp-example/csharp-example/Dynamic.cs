using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Text;

namespace csharp_example
{
    class Dynamic
    {
        public Dynamic()
        {
            dynamic dyna = 1;
            Console.WriteLine($"dyna = 1: {dyna.GetType()}");
            dyna = 'a';
            Console.WriteLine($"dyna = 'a': {dyna.GetType()}");

            dynamic person = new ExpandoObject();
            person.Name = "홍길동";
            person.Age = 20;
            person.Display = (Action)(() => { Console.WriteLine($"{person.Name} ({person.Age}세 / 무직)"); });
            person.SetAge = (Action<int>)((age) =>
            {
                person.Age = age;
                if (person.AgeChanged != null)
                    person.AgeChanged(person, EventArgs.Empty);
            });
            person.AgeChanged = null;
            person.AgeChanged += new EventHandler(OnAgeChanged);

            // ExpandoObject -> IDictionary
            var dict = (IDictionary<string, object>)person;

            foreach (var d in dict)
                Console.WriteLine($"{d.Key} {d.Value}");

            // test
            person.Display();
            person.SetAge(21);
            person.Display();
        }

        private void OnAgeChanged(object sender, EventArgs e)
        {
            Console.WriteLine("나이가 바뀌었습니다.");
        }
    }
}
