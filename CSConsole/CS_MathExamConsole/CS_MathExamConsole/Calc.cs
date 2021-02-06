using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_MathExamConsole
{
    public delegate void CallPrint(string str);

    abstract class Calc
    {

        protected static int score = 0;
        public int Num1 { get; private set; }
        public int Num2 { get; private set; }
        public float Result { get; protected set; }

        public CallPrint calDel = null;

        public Calc()
        {

        }

        public Calc(int value1, int value2)
        {
            Num1 = value1;
            Num2 = value2;
        }


        public abstract void Cal();

        public abstract void Print();// 이 소스는 추상화하지 않아도 괜찮았을듯 하다.

        public abstract void Exam(float f);

        public static int GetScore()
        {
            return score;
        }

    }
}
