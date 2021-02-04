using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_VendingConsole
{
    class UserControl
    {
        Machine mc;

        public UserControl(Machine mc)
        {
            this.mc = mc;
        }

        //경환 형님 : 금액 투입
        public void InputMoney()
        {
            Console.Write("금액을 입력하세요 : ");
            int money = int.Parse(Console.ReadLine());
            if (money < 0)
            {
                Console.WriteLine("다시 입력하세요");
                return;
            }
            mc.InputMoney(money);
        }

        //택진 : 아이템 선택
        public void SelectItem()
        {
            Console.Write("선택할 아이템 인덱스 입력 : ");
            int idx = int.Parse(Console.ReadLine());
            if (!(idx < mc.GetItemList().Count && idx >= 0))
            {
                Console.WriteLine("유효하지 않은 인덱스입니다.");
                return;
            }

            mc.SelectItem(idx);
        }

        //유수 : 금액 반환
        public void OutputMoney()
        {
            mc.OutputMoney();
        }


        //태현 : 메뉴 출력
        public void PrintMenu()
        {
            Viewer.PrintItemInfo(mc.GetItemList());
            Console.WriteLine("====================================");
            Viewer.PrintBalanceInfo(mc.GetBalance());
            Console.WriteLine("====================================");
            Console.WriteLine("[1] 금액 투입 [2] 아이템 선택");
            Console.WriteLine("[3] 금액 반환 [4] 사용자 모드 종료");
            Console.WriteLine("====================================");
            Console.Write("메뉴입력 : ");
        }
    }
}
