using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_VendingConsole
{
    class Machine
    {
        List<Item> itemlist;
        int money;

        
        //생성자
        public Machine()
        {
            money = 0;
            itemlist = new List<Item>();
        }


        //금액 투입
        public void InputMoney(int money)
        {
            this.money += money;
        }

        //아이템 선택
        public void SelectItem(int idx)
        {
            if (itemlist[idx].Cnt >= 1 && itemlist[idx].Value <= this.money)
            {
                itemlist[idx].Cnt--;
                this.money -= itemlist[idx].Value;
            }
            else
            {
                Console.WriteLine("수량이 부족하거나 잔액이 부족합니다");
                return;
            }
        }

        //금액 반환
        public void OutputMoney()
        {
            //현재 money가 얼마인지 출력하세요 :( 100원이 반환되었습니다.");
            //money를 0으로 초기화 하세요;
            Console.Write("{0}원이 반환되었습니다.", money);
            money = 0;
        }

        //아이템 추가
        public void InputItem(string name, int value, int cnt)
        {
            //인자로 넘어온 이름, 가격, 수량을 토대로
            //    중요! 이름이 중복되는게 있을경우 return;
            //List에 삽입 하세요;

            for (int i = 0; i < itemlist.Count; i++)
            {
                Item temp = itemlist[i];
                if (temp.Name.Equals(name))
                    return;
            }

            Item item = new Item()
            {
                Name = name,
                Value = value,
                Cnt = cnt
            };

            itemlist.Add(item);
        }

        //아이템 수량 수정
        public void UpdateItemCnt(int idx, int cnt)
        {
            if (idx < itemlist.Count && idx >= 0)
                itemlist[idx].Cnt += cnt;
            else
                Console.WriteLine("유효하지 않은 인덱스입니다.");
        }

        //아이템 가격 수정
        public void UpdateItemValue(int idx, int value)
        {
            if (idx < itemlist.Count && idx >= 0)
                itemlist[idx].Value = value;
            else
                Console.WriteLine("유효하지 않은 인덱스입니다.");
        }

        //아이템 삭제
        public void DeleteItem(int idx)
        {
            if (idx < itemlist.Count && idx >= 0)
                itemlist.RemoveAt(idx);
            else
                Console.WriteLine("유효하지 않은 인덱스입니다.");
        }

        //아이템 리스트 획득
        public List<Item> GetItemList()
        {
            return itemlist;
        }

        //현재 투입금액 획득
        public int GetBalance()
        {
            return money;
        }
    }
}
