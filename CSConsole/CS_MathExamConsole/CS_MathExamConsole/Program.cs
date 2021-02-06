using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_MathExamConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Control con = new Control();

            con.GenerateExam();
            con.SolveExam();
            con.ExamResult();
        }
    }
}
