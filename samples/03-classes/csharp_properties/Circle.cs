using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_properties
{
    internal class Circle
    {
        private double _radius = 0;
        public double Radius
        {
            get { return _radius; }
            set
            {
                if (value < 0) throw new ArgumentException("Radius must not be negative");
                _radius = value;
            }
        }

        // Свойство Area вычисляется, используя Radius
        public double Area
        {
            get { return Radius * Radius * Math.PI; }
        }

        public Circle(double radius)
        {
            _radius = radius;
        }
    }
}
