using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_properties
{
    internal class Counter
    {
        private int _value = 0;

        // Поле _value будет увеличиваться всякий раз, когда происходит чтение свойства Value.
        // Даже, если просматривать его под отладчиком.
        // Это может вызвать удивление.
        public int Value {  get { return _value++; } }

        // Это свойство будет долго вычисляться при просмотре под отладчиком.
        public int LongCalculation
        {
            get
            {
                int sum = 0;
                for (int i = 0; i < 1000000000; ++i)
                {
                    ++sum;
                }
                return sum;
            }
        }
    }
}
