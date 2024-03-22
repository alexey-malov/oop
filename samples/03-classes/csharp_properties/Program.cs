using csharp_properties;

Circle c = new(10);
c.Radius = 3;

Counter cnt = new();

Console.WriteLine("Area:" + c.Area.ToString());

Console.WriteLine("Counter:" + cnt.Value);
Console.WriteLine("Counter:" + cnt.Value);

