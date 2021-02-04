using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_VendingConsole
{
    class Viewer
    {
        //아이템 이름,가격,수량 출력 메소드
        public static void PrintItemInfo(List<Item> itemlist)
        {
            Console.WriteLine("{0,6} {1,10} {2,5} {3,-30}", "[인덱스]","[가격]","[수량]", "[이름]");
            for(int i = 0;  i < itemlist.Count; i++)
            {
                Item temp = itemlist[i];
                Console.WriteLine("{0,8} {1,12} {2,7}   {3,-30}", i,temp.Value,temp.Cnt, temp.Name);
            }
        }

        //잔액 출력 메소드
        public static void PrintBalanceInfo(int value)
        {
            Console.WriteLine("[현재 투입 금액] {0}원",value);
        }
    }
}
