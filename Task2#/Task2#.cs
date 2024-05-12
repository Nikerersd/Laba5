using System;
using System.Collections.Generic;
using System.Linq;

public class Visitor
{
    public string Ticket { get; set; }
    public int Duration { get; set; }
}

public class ClinicQueue
{
    private int numWindows;
    private List<Queue<Visitor>> windows;
    private List<Visitor> visitors;
    private int visitorCounter = 0;

    private string GenerateTicket()
    {
        return "T" + (100 + (visitorCounter++ % 900));
    }

    public ClinicQueue(int numWindows)
    {
        this.numWindows = numWindows;
        windows = new List<Queue<Visitor>>(numWindows);
        for (int i = 0; i < numWindows; i++)
        {
            windows.Add(new Queue<Visitor>());
        }
        visitors = new List<Visitor>();
    }

    public void Enqueue(int duration)
    {
        string ticket = GenerateTicket();
        visitors.Add(new Visitor { Ticket = ticket, Duration = duration });
        Console.WriteLine(ticket);
    }

    public void Distribute()
    {
        List<int> load = new List<int>(Enumerable.Repeat(0, numWindows));

        visitors = visitors.OrderByDescending(v => v.Duration).ToList();

        foreach (Visitor v in visitors)
        {
            int minWindow = load.IndexOf(load.Min());
            load[minWindow] += v.Duration;
            windows[minWindow].Enqueue(v);
        }

        for (int i = 0; i < numWindows; i++)
        {
            Console.Write($"Окно {i + 1} (");
            int totalTime = 0;
            bool first = true;
            while (windows[i].Count > 0)
            {
                if (!first)
                    Console.Write(", ");
                first = false;
                Visitor v = windows[i].Dequeue();
                Console.Write(v.Ticket);
                totalTime += v.Duration;
            }
            Console.WriteLine($") {totalTime} минут");
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Введите кол-во окон: ");
        int numWindows = Convert.ToInt32(Console.ReadLine());
        ClinicQueue queue = new ClinicQueue(numWindows);

        string command;
        while (true)
        {
            command = Console.ReadLine();
            string[] parts = command.Split(' '); // Разделение ввода на части
            if (parts[0] == "ENQUEUE")
            {
                int duration = Convert.ToInt32(parts[1]); // Значение после команды
                queue.Enqueue(duration);
            }
            else if (parts[0] == "DISTRIBUTE")
            {
                queue.Distribute();
                break;
            }
        }
    }
}
