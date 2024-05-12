using System;
using System.Collections.Generic;
using System.Linq;

public class Item
{
    public string Name { get; set; }
    public int Quantity { get; set; }
}

public class Warehouse
{
    private Dictionary<string, List<Item>> cells = new Dictionary<string, List<Item>>();

    private const int MAX_ITEMS_PER_CELL = 10;
    private const int NUM_ZONES = 1;
    private const int NUM_SHELVES_PER_ZONE = 10;
    private const int NUM_SECTIONS_PER_SHELF = 7;
    private const int NUM_SHELVES_PER_SECTION = 4;

    public void AddItem(string itemName, int quantity, string cellAddress)
    {
        if (!cells.ContainsKey(cellAddress))
        {
            cells[cellAddress] = new List<Item>();
        }

        var items = cells[cellAddress];
        int summ = items.Sum(item => item.Quantity);

        var existingItem = items.FirstOrDefault(item => item.Name == itemName);
        if (existingItem != null)
        {
            if (summ + quantity <= MAX_ITEMS_PER_CELL)
            {
                existingItem.Quantity += quantity;
                return;
            }
            else
            {
                Console.WriteLine($"Невозможно добавить товар {itemName} в ячейку {cellAddress}. Превышен лимит в {MAX_ITEMS_PER_CELL} единиц.");
                return;
            }
        }

        if (summ + quantity <= MAX_ITEMS_PER_CELL)
        {
            items.Add(new Item { Name = itemName, Quantity = quantity });
        }
        else
        {
            Console.WriteLine($"Ячейка {cellAddress} заполнена. Невозможно добавить товар {itemName}.");
        }
    }

    public void RemoveItem(string itemName, int quantity, string cellAddress)
    {
        if (!cells.ContainsKey(cellAddress))
        {
            Console.WriteLine($"В ячейке {cellAddress} нет товара {itemName}.");
            return;
        }

        var items = cells[cellAddress];
        var existingItem = items.FirstOrDefault(item => item.Name == itemName);
        if (existingItem != null)
        {
            if (existingItem.Quantity >= quantity)
            {
                existingItem.Quantity -= quantity;
                if (existingItem.Quantity == 0)
                {
                    items.Remove(existingItem);
                }
                return;
            }
            else
            {
                Console.WriteLine($"В ячейке {cellAddress} недостаточно товара {itemName}.");
                return;
            }
        }

        Console.WriteLine($"В ячейке {cellAddress} нет товара {itemName}.");
    }

    public void GetInfo()
    {
        int totalItems = 0;
        int totalCells = NUM_ZONES * NUM_SHELVES_PER_ZONE * NUM_SECTIONS_PER_SHELF * NUM_SHELVES_PER_SECTION;
        int occupiedCells = 0;

        foreach (var cell in cells)
        {
            if (cell.Value.Any())
            {
                occupiedCells++;
                totalItems += cell.Value.Sum(item => item.Quantity);
            }
        }

        Console.WriteLine($"Общая загрузка склада: {(double)totalItems / (totalCells * MAX_ITEMS_PER_CELL) * 100}%");
        Console.WriteLine($"Загрузка зоны A: {(double)totalItems / (totalCells * MAX_ITEMS_PER_CELL) * 100}%");

        Console.WriteLine("Содержимое ячеек:");
        foreach (var cell in cells)
        {
            if (cell.Value.Any())
            {
                Console.Write($"Ячейка {cell.Key}: ");
                foreach (var item in cell.Value)
                {
                    Console.Write($"{item.Name} ({item.Quantity}), ");
                }
                Console.WriteLine();
            }
        }

        Console.WriteLine("Пустые ячейки:");
        for (int i = 0; i < NUM_ZONES; i++)
        {
            for (int j = 0; j < NUM_SHELVES_PER_ZONE; j++)
            {
                for (int k = 0; k < NUM_SECTIONS_PER_SHELF; k++)
                {
                    for (int l = 0; l < NUM_SHELVES_PER_SECTION; l++)
                    {
                        string cellAddress = $"{(char)('A' + i)}{(j + 1)}{(k + 1)}{(l + 1)}";
                        if (!cells.ContainsKey(cellAddress) || !cells[cellAddress].Any())
                        {
                            Console.Write($"{cellAddress}, ");
                        }
                    }
                }
            }
        }
        Console.WriteLine();
    }
}

class Program
{
    static void Main(string[] args)
    {
        Warehouse warehouse = new Warehouse();
        string command, itemName, cellAddress;
        int quantity;

        while (true)
        {
            Console.Write("Введите команду (ADD, REMOVE, INFO или EXIT): ");
            command = Console.ReadLine();

            if (command == "EXIT")
            {
                break;
            }
            else if (command == "ADD" || command == "REMOVE")
            {
                Console.Write("Введите название товара, количество и адрес ячейки: ");
                string input = Console.ReadLine();
                string[] inputParts = input.Split(' ');
                if (inputParts.Length == 3)
                {
                    itemName = inputParts[0];
                    quantity = int.Parse(inputParts[1]);
                    cellAddress = inputParts[2];
                    if (command == "ADD")
                    {
                        warehouse.AddItem(itemName, quantity, cellAddress);
                    }
                    else
                    {
                        warehouse.RemoveItem(itemName, quantity, cellAddress);
                    }
                }
                else
                {
                    Console.WriteLine("Некорректный ввод.");
                }
            }
            else if (command == "INFO")
            {
                warehouse.GetInfo();
            }
            else
            {
                Console.WriteLine("Неизвестная команда. Попробуйте еще раз.");
            }
        }
    }
}
