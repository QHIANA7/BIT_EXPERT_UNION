using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_VendingConsole
{
    class AdminControl
    {
        Machine mc;

        public AdminControl(Machine mc)
        {
            this.mc = mc;
        }

        //택진 : 아이템 추가
        public void InputItem()
        {
            Console.Write("추가할 아이템 이름 : ");
            string name = Console.ReadLine();
            Console.Write("추가할 아이템 가격 : ");
            int value = int.Parse(Console.ReadLine());
            if (value < 1)
            {
                Console.WriteLine("0 미만의 가격은 설정할 수 없습니다");
                return;
            }
            Console.Write("추가할 아이템 수량 : ");
            int cnt = int.Parse(Console.ReadLine());
            if (cnt < 1)
            {
                Console.WriteLine("0 미만의 수량은 설정할 수 없습니다");
                return;
            }

            mc.InputItem(name, value, cnt);
        }

        //유수 : 아이템 수량 수정
        public void UpdateItemCnt()
        {

            Console.Write("수정할 아이템 인덱스 입력 : ");
            int idx = int.Parse(Console.ReadLine());
            if (!(idx < mc.GetItemList().Count && idx >= 0))
            {
                Console.WriteLine("유효하지 않은 인덱스입니다.");
                return;
            }

            Console.Write("수정할 아이템 수량 입력 : ");
            int cnt = int.Parse(Console.ReadLine());

            if (cnt < 0)
            {
                Console.WriteLine("0 미만의 수량을 추가할 수 없습니다.");
                return;
            }
            mc.UpdateItemCnt(idx, cnt);

        }

        //태현 : 아이템 가격 수정
        public void UpdateItemValue()
        {
            Console.Write("수정할 아이템 인덱스 입력 : ");
            int idx = int.Parse(Console.ReadLine());

            if (!(idx < mc.GetItemList().Count && idx >= 0))
            {
                Console.WriteLine("유효하지 않은 인덱스입니다.");
                return;
            }

            Console.Write("수정할 아이템 가격 입력 : ");
            int value = int.Parse(Console.ReadLine());

            if (value < 1)
            {
                Console.WriteLine("0 미만의 가격은 설정할 수 없습니다.");
                return;
            }


            mc.UpdateItemValue(idx, value);
        }

        //경환형님 : 아이템 삭제
        public void DeleteItem()
        {
            Console.Write("삭제할 인덱스를 입력하세요 : ");
            int idx = int.Parse(Console.ReadLine());
            if (!(idx < mc.GetItemList().Count && idx >= 0))
            {
                Console.WriteLine("유효하지 않은 인덱스입니다.");
                return;
            }
            mc.DeleteItem(idx);
        }

        //태현 : 메뉴 출력
        public void PrintMenu()
        {
            Viewer.PrintItemInfo(mc.GetItemList());
            Console.WriteLine("====================================");
            Viewer.PrintBalanceInfo(mc.GetBalance());
            Console.WriteLine("====================================");
            Console.WriteLine("[1] 아이템 추가 [2] 아이템 수량 수정");
            Console.WriteLine("[3] 아이템 가격 수정 [4] 아이템 삭제");
            Console.WriteLine("[0] 관리자 모드 종료");
            Console.WriteLine("====================================");
            Console.Write("메뉴입력 : ");
        }
    }
}
