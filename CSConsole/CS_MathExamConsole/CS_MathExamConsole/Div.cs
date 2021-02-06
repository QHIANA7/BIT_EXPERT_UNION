using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_MathExamConsole
{
    class Div : Calc
    {
        public Div(int value1, int value2):base(value1,value2)
        { Cal(); }

        public override void Cal()
        {
            Result = (float)Num1 / (float)Num2;
        }

        public override void Exam(float f)
        {
            if (Result == f)
            {
                base.calDel(string.Format("정답 - 사용자입력 : {0} , 정답 : {1}", f, Result));
                Calc.score += 10;
            }
            else
            {
                base.calDel(string.Format("오답 - 사용자입력 : {0} , 정답 : {1}",f, Result));
            }
        }

        public override void Print()
        {
            Console.Write("{0} / {1} = ", Num1, Num2);
        }
    }
}
