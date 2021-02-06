using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_MathExamConsole
{
    class Control
    {
        List<Calc> calclist = new List<Calc>();

        public void GenerateExam()
        {
            Calc temp = null;
            Random ran = new Random();
            //int num = ran.Next(0, 10);//0~9범위
            int cal = 0;
            int val1 = 0;
            int val2 = 0;


            for (int i = 0; i < 10; i++)
            {
                cal = ran.Next(0, 5);
                val1 = ran.Next(0, 10);
                val2 = ran.Next(0, 10);
                switch (cal)
                {
                    case 1: temp = new Add(val1, val2); break;
                    case 2: temp = new Sub(val1, val2); break;
                    case 3: temp = new Mul(val1, val2); break;
                    case 4: temp = new Div(val1, val2); break;
                }
                temp.calDel = ResultPrint;
                calclist.Add(temp);
            }
        }

        public void SolveExam()
        {
            for(int i = 0; i < calclist.Count; i++)
            {
                Calc calc = calclist[i];

                calc.Print();

                float ret = float.Parse(Console.ReadLine());

                calc.Exam(ret);
            }
        }

        public void ResultPrint(string str)
        {
            Console.WriteLine(str);
        }

        public void ExamResult()
        {
            Console.WriteLine(Calc.GetScore().ToString() + "점 입니다!");
        }
    }
}