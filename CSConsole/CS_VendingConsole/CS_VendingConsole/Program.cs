using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_VendingConsole
{
    class Program
    {
         static Machine mc;

        public static void UserRun()
        {
            UserControl uc = new UserControl(mc);

            while (true)
            {
                Console.Clear();
                uc.PrintMenu();
                ConsoleKeyInfo keyinfo = Console.ReadKey();
                Console.WriteLine();
                switch (keyinfo.Key)
                {
                    case ConsoleKey.D1:
                    case ConsoleKey.NumPad1: uc.InputMoney(); break;
                    case ConsoleKey.D2:
                    case ConsoleKey.NumPad2: uc.SelectItem(); break;
                    case ConsoleKey.D3:
                    case ConsoleKey.NumPad3: uc.OutputMoney(); break;
                    case ConsoleKey.D4:
                    case ConsoleKey.NumPad4: return;
                    default:
                        Console.Write("잘못된 메뉴 입력 ");
                        break;
                }
                Console.WriteLine("Press Any Key");
                Console.ReadKey();
            }
        }

        public static void AdminRun()
        {
            AdminControl ac = new AdminControl(mc);

            while (true)
            {
                Console.Clear();
                ac.PrintMenu();
                ConsoleKeyInfo keyinfo = Console.ReadKey();
                Console.WriteLine();
                switch (keyinfo.Key)
                {
                    case ConsoleKey.D1:
                    case ConsoleKey.NumPad1: ac.InputItem(); break;//사용자 모드로 진입
                    case ConsoleKey.D2:
                    case ConsoleKey.NumPad2: ac.UpdateItemCnt(); break;
                    case ConsoleKey.D3:
                    case ConsoleKey.NumPad3: ac.UpdateItemValue(); break;
                    case ConsoleKey.D4:
                    case ConsoleKey.NumPad4: ac.DeleteItem(); break;
                    case ConsoleKey.D0:
                    case ConsoleKey.NumPad0: return;
                    default:
                        Console.Write("잘못된 메뉴 입력 ");
                        break;
                }
                Console.WriteLine("Press Any Key");
                Console.ReadKey();
            }
        }

        public static void PrintMainMenu()
        {
            Console.WriteLine("====================================");
            Console.WriteLine("[1] 사용자 [2] 관리자 [0] 종료");
            Console.WriteLine("====================================");
            Console.Write("메뉴 선택 : ");
        }

        static void Main(string[] args)
        {
           mc = new Machine();

            while(true)
            {
                Console.Clear();
                PrintMainMenu();
                ConsoleKeyInfo keyinfo = Console.ReadKey();
                Console.WriteLine();
                try
                {
                    switch (keyinfo.Key)
                    {
                        case ConsoleKey.D1:
                        case ConsoleKey.NumPad1: UserRun(); break;
                        case ConsoleKey.D2:
                        case ConsoleKey.NumPad2: AdminRun(); break;
                        case ConsoleKey.D0:
                        case ConsoleKey.NumPad0: return;
                        default:
                            Console.Write("잘못된 메뉴 입력 ");
                            break;
                    }
                }

                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                    Console.WriteLine("Press Any Key");
                    Console.ReadKey();
                }
                
            }
        }
    }
}
