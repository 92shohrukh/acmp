/*
http://acmp.ru/index.asp?main=task&id_task=234
Мальчику Васе очень нравится известная игра "Сапер" ("Minesweeper").

В "Сапер" играет один человек. Игра идет на клетчатом поле (далее будем называть его картой) N×M (N строк, M столбцов). В K клетках поля стоят мины, в остальных клетках записано либо число от 1 до 8 — количество мин в соседних клетках, либо ничего не написано, если в соседних клетках мин нет. Клетки являются соседними, если они имеют хотя бы одну общую точку, в одной клетке не может стоять более одной мины. Изначально все клетки поля закрыты. Игрок за один ход может открыть какую-нибудь клетку. Если в открытой им клетке оказывается мина — он проигрывает, иначе игроку показывается число, которое стоит в этой клетке, и игра продолжается. Цель игры — открыть все клетки, в которых нет мин.

У Васи на компьютере есть эта игра, но ему кажется, что все карты, которые в ней есть, некрасивые и неинтересные. Поэтому он решил нарисовать свои. Однако фантазия у него богатая, а времени мало, и он хочет успеть нарисовать как можно больше карт. Поэтому он просто выбирает N, M и K и расставляет мины на поле, после чего все остальные клетки могут быть однозначно определены. Однако на определение остальных клеток он не хочет тратить свое драгоценное время. Помогите ему!

По заданным N, M, K и координатам мин восстановите полную карту.

Входные данные
В первой строке входного файла INPUT.TXT содержатся числа N, M и K (1 ≤ N ≤ 200, 1 ≤ M ≤ 200, 0 ≤ K ≤ N×M). Далее идут K строк, в каждой из которых содержится по два числа, задающих координаты мин. Первое число в каждой строке задает номер строки клетки, где находится мина, второе число — номер столбца. Левая верхняя клетка поля имеет координаты (1,1), правая нижняя — координаты (N,M).

Выходные данные
Выходной файл OUTPUT.TXT должен содержать N строк по M символов — соответствующие строки карты. j-й символ i-й строки должен содержать символ ‘*‘ (звездочка) если в клетке (i,j) стоит мина, цифру от 1 до 8, если в этой клетке стоит соответствующее число, либо ‘.‘ (точка), если клетка (i,j) пустая.
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
class field
{
   private:
      int n,m,k; //row, col, the num of mines
      char** mas;
   public:
      field(int row, int col, int k, char x);
 
      void add_mine(int i, int j)
         { mas[i][j]=':'; define_cells(i,j); return; }
 
      void define_cells(int i, int j);
      void print_field(ofstream* out);
};
 
field::field(int row, int col, int kk, char x)
{
   int i,j;
   mas=(char**)malloc((row+2)*sizeof(char*));
   for(i=0; i<(row+2); i++)
   {
      mas[i]=(char*)malloc((col+2)*sizeof(char));
   }
 
   for (i=0; i<row+2; i++)
   {
      for (j=0; j<col+2; j++)
      {
         mas[i][j]=x; //'0'=='.'
      }
   }
   n=row; m=col; k=kk;
}
 
void field::define_cells(int i, int j)
{
   (int)mas[i-1][j-1]++;
   (int)mas[i-1][j]++;
   (int)mas[i-1][j+1]++;
   (int)mas[i][j-1]++;
   (int)mas[i][j+1]++;
   (int)mas[i+1][j-1]++;
   (int)mas[i+1][j]++;
   (int)mas[i+1][j+1]++;
   return;
}
 
void field::print_field(ofstream* out)
{
   int i,j;
   for (i=1; i<=n; i++)
   {
      for (j=1; j<=m; j++)
      {
         if (mas[i][j]>'9') *out<<"*";
         else if (mas[i][j]=='0') *out<<".";
         else *out<<mas[i][j]<<"";
      }
      *out<<"\n";
   }
   return;
}
 
int main()
{
   ifstream fin("INPUT.txt");
   ofstream fout("OUTPUT.txt");
   //cout<<(char)(65);
   int n,m,k,i,j,t;
   fin>>n>>m>>k;
   field F=field(n,m,k,'0');
   for (t=1; t<=k; t++)
   {
      fin>>i>>j;
      F.add_mine(i,j);
   }
   F.print_field(&fout);
   fin.close();
   fout.close();
   return 0;
}