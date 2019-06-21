#include "PEMS.h"

/**************************************************************************/
/* Global                                                                 */
/**************************************************************************/

time_t t = time(0);   // get time now
struct tm * now = localtime( & t );
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//declaration for cursor , row and column (gotoXY)
COORD CursorPosition;
int SelDay = 0, SelMon = 0, SelYear = 0;
string title;
string describe;
string etime;
string location;
string nameEvent[10]={"01","02","03","04","05","06","07","08","09","10"};
char add[10];
int st;
int ThisDay ;
int MarkMonth[50];
int MarkDay[50];
int MarkYear[50];


/**************************************************************************/
/* Function Declaration                                                   */
/**************************************************************************/
void gotoXY(int,int);
void ChangeCursorStatus(bool);
void ViewAnotherMonth();
void clearScreen();
int searchEvent();
int showMenu(int, int, int);
void getView(int,int,int,int,int);
int getAdd(int,int,int,int);
int getEdit(int);
int getDelete();
/**************************************************************************/
/* Class Declaration                                                      */
/**************************************************************************/
class Calendar
{
    int startday;
    int DaysInMon = 0;
public:
    void printCalendar(int mon, int year)
    {
    /**************************************************************************/
    /* calculates the first day of the given month                            */
    /**************************************************************************/
        int Fday = 1;
        int y = year - (mon < 3);
        static int i[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        startday = (y + y/4 - y/100 + y/400 + i[mon-1] + Fday) % 7;


    /**************************************************************************/
    /* returns the number of days in the given month                          */
    /**************************************************************************/

        if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
        {
            DaysInMon = 30;
        }
        else if (mon == 02)
        {
            bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

            if (leapyear == false)
				DaysInMon = 28;
            else
				DaysInMon = 29;
        }
        else
        {
             DaysInMon = 31;
        }

    /**************************************************************************/
    /* prints out the body of the calendar                                    */
    /**************************************************************************/
        int pointer = 0;
        bool ascii = true;
        int k = 0;
        long int todayDate = (now->tm_mon+1)+(now->tm_year + 1900);
        int MonYear = (now->tm_mon+1)+(now->tm_year + 1900) ;
        long int  today = mon + year;
        int tmon ,tyr;
        int wrong ,specificMonth , specificYear , show ,NotHere =1 ,thd;
        string result ;

        do
        {
            int sd ,space;
            int day[31] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
            if ( startday == 0){space = 4;}
            if ( startday == 1){space = 9;}
            if ( startday == 2){space = 14;}
            if ( startday == 3){space = 19;}
            if ( startday == 4){space = 24;}
            if ( startday == 5){space = 29;}
            if ( startday == 6){space = 34;}


            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            string MON[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
            gotoXY(32,2);cout << MON[mon - 1] ;
            gotoXY(43,2);cout << year ;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoXY(19,3);  cout<< "|_______________________________________|";// sunday = 4
            gotoXY(19,4);  cout<< "|                                       |";// monday = 9
            gotoXY(19,5);  cout<< "|                                       |";// tuesday = 14
            gotoXY(19,6);  cout<< "|    S    M    T    W    T    F    S    |";// wednesday = 19
            gotoXY(19,7);  cout<< "|                                       |";//  thursday = 24
            gotoXY(19,8);  cout<< "|_______________________________________|";// friday = 29
            gotoXY(19,9);  cout<< "|                                       |";// sat = 34
            gotoXY(19,10); cout<< "|                                       |";
            gotoXY(19,11); cout<< "|                                       |";
            gotoXY(19,12); cout<< "|                                       |";
            gotoXY(19,13); cout<< "|                                       |";
            gotoXY(19,14); cout<< "|                                       |";
            gotoXY(19,15); cout<< "|                                       |";
            gotoXY(19,16); cout<< "|                                       |";
            gotoXY(19,17); cout<< "|                                       |";
            gotoXY(19,18); cout<< "|                                       |";
            gotoXY(19,19); cout<< "|                                       |";
            gotoXY(19,20); cout<< "|                                       |";
            gotoXY(19,21); cout<< "|                                       |";
            gotoXY(19,22); cout<< "|_______________________________________|";

            int printl = space -1 ;
            gotoXY(18,11);
            while (space > 0)
            {
                if ( space == printl ){cout << "|";}
                else{cout <<" " ;}
                space = space - 1;
            }

            sd = startday;
    /**************************************************************************/
    /* prints out the days of the month                                       */
    /**************************************************************************/
        for( int j = 0 ; j <DaysInMon ; j++)
        {
            if ( j == pointer && day[j] != now -> tm_mday && today != todayDate  && sd != 6 ) // 1normal with .. bgcolor
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                        cout  << setw(3) << day[j] << "* " ;
                        sd = sd + 1;
                        NotHere = 0;
                        break;
                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                 cout  << setw(3) << day[j] << "  " ;
                 sd = sd + 1;
                }

            }
            else if (j == pointer && day[j] != now->tm_mday && today != todayDate && sd == 6 )
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                        cout << setw(3) << day[j] << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                        sd = 0;
                        cout << "                   |  ";
                        NotHere = 0;
                        break;


                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                    sd = 0;
                    cout << "                   |  ";
                }

            }
            else if (j != pointer && day[j] != now->tm_mday && today != todayDate && sd == 6 )
            {
                 thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j];
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                        sd = 0;
                        cout <<  "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                    sd = 0;
                    cout <<  "                   |  ";
                }

            }
            else if (j != pointer && day[j] != now->tm_mday && today != todayDate && sd != 6 )
            {
                  thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere == 1 )
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    sd = sd + 1;
                }

            }
            else if (j == pointer && day[j] == now->tm_mday && today != todayDate && sd == 6 )
            {
                 thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                        cout << setw(3) << day[j] << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                        sd = 0;
                        cout << "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                    sd = 0;
                    cout << "                   |  ";
                }

            }
            else if (j == pointer && day[j] == now->tm_mday && today != todayDate && sd != 6 )
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                        cout  << setw(3) << day[j] << "* " ;
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                    cout  << setw(3) << day[j] << "  " ;
                    sd = sd + 1;
                }

            }
            else if (j != pointer && day[j] == now->tm_mday && today != todayDate && sd == 6 )
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                        sd = 0;
                        cout <<  "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                    sd = 0;
                    cout <<  "                   |  ";
                }

            }
            else if (j != pointer && day[j] == now->tm_mday && today != todayDate && sd != 6 )
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    sd = sd + 1;
                }

            }
            else if (j == pointer && day[j] != now->tm_mday && today == todayDate && sd == 6 ) //*5
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                        cout << setw(3) << day[j] << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                        sd = 0;
                        cout << "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                    sd = 0;
                    cout << "                   |  ";
                }

            }
            else if (j == pointer && day[j] != now->tm_mday && today == todayDate && sd != 6 )
            {
                 thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                         cout  << setw(3) << day[j] << "* " ;
                         sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                     cout  << setw(3) << day[j] << "  " ;
                     sd = sd + 1;
                }

            }
            else if (j == pointer && day[j] == now->tm_mday && today == todayDate && sd != 6 )//*2
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                        cout  << setw(3) << day[j] << "* " ;
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
                    cout  << setw(3) << day[j] << "  " ;
                    sd = sd + 1;
                }

            }
            else if (j == pointer && day[j] == now->tm_mday && today == todayDate && sd == 6 )//*1
            {
                  thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                        cout << setw(3) << day[j] << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                        sd = 0;
                        cout << "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , BACKGROUND_INTENSITY);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                    sd = 0;
                    cout << "                   |  ";
                }

            }
            else if ( j != pointer && day[j] == now->tm_mday && today == todayDate && sd != 6) //*4
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                        cout << setw(3) << day[j];
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if (NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    cout << setw(3) << day[j] << "  ";
                    sd = sd + 1;
                }

            }
            else if ( j != pointer && day[j] != now->tm_mday && today == todayDate && sd != 6)// *6
            {
                 thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                fstream MarkDate ;
                MarkDate.open("Date.txt",ios::out|ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        sd = sd + 1;
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    sd = sd + 1;
                }

            }
            else if ( j != pointer && day[j] == now->tm_mday && today == todayDate && sd == 6)// *3
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                        sd = 0;
                        cout <<  "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

                    sd = 0;
                    cout <<  "                   |  ";

                }

            }
            else if ( j != pointer && day[j] != now->tm_mday && today == todayDate && sd == 6)// *7
            {
                thd = day[j];
                int ThisDate = (thd*1000000)+(mon*10000)+(year);
                ifstream MarkDate ;
                MarkDate.open("Date.txt",ios::in);
                while(MarkDate>>ThisDay)
                {
                    if( ThisDay == ThisDate)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cout << setw(3) << day[j] ;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                        cout << "* ";
                        cout << endl<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                        sd = 0;
                        cout <<  "                   |  ";
                        NotHere = 0;
                        break;

                    }
                    else
                    {
                        NotHere =1;
                    }
                }
                MarkDate.close();
                if(NotHere ==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(3) << day[j] << "  ";
                    cout << endl<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
                    sd = 0;
                    cout <<  "                   |  ";
                }

            }
        }//-----------------------------end for loop-------------------------------------------------------------------
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            gotoXY(2,24);cout << "----------------------------------------------------------------------------";
            gotoXY(4,26);cout << "\t[  S  ] to SEARCH ";
            gotoXY(4,27);cout << "\t[  V  ] to VIEW another Calendar ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
            gotoXY(4,28);cout << "\t[ ESC ] to EXIT ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            gotoXY(2,30);cout << "----------------------------------------------------------------------------";
            k =getch();
            if ( k == 75) // left
            {
                pointer -= 1;
                if(pointer < 0){pointer = DaysInMon - 1;}
                wrong = 0;
            }
            else if ( k == 77 )// right
            {
                pointer += 1;
                if (pointer > DaysInMon -1){pointer = 0;}
                wrong = 0;
            }
            if ( k == 115 || k == 83) // button S/s
            {
                searchEvent();
            }
            else if ( k == 86 || k == 118)//button V/v
            {
                ViewAnotherMonth();
            }

            else if ( k == 13) // enter
            {
                SelDay = pointer + 1;
                SelMon = mon;
                SelYear = year;
                st = showMenu(SelDay, SelMon, SelYear);
            }
            else if ( k == 27) // esc
            {
                exit(0);
            }
            else
            {
                if(!(k ==224))
                wrong = 1;
            }

        }while(true);

    }

};


main()
{
    ChangeCursorStatus(false);
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    Calendar cal;
    cal.printCalendar(month, year);

}

/**************************************************************************/
/* Function Definition                                                    */
/**************************************************************************/
void ViewAnotherMonth()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    int specificMonth = 0, specificYear = 0;
    gotoXY(10,32);cout << "Enter Month <MM>   : ";
    gotoXY(31,32);cin >> specificMonth;
    gotoXY(10,33);cout << "Enter Year  <YYYY> : ";
    gotoXY(31,33);cin >> specificYear;
    if( specificMonth > 0 && specificMonth <13 && specificYear > 0 && specificYear < 10000 )
    {
        system("cls");
        Calendar cal;
        cal.printCalendar(specificMonth, specificYear);
    }
    else if ( specificMonth < 0 || specificMonth > 12 || specificYear < 0 || specificYear > 10000)
    {
        cin.clear();
        cin.ignore(999,'\n');

        gotoXY(20,35);cout << "ERROR !";
        Sleep(1000);
        system("cls");
    }
    else
    {
        if(!(cin>>specificMonth && cin>>specificYear))
        {
            cin.clear();
            cin.ignore(999,'\n');

            gotoXY(20,36);cout << "\tInvalid Input !";
            Sleep(1000);
            system("cls");

        }
    }
}
void ChangeCursorStatus(bool Visible)
{
	CONSOLE_CURSOR_INFO *c=new CONSOLE_CURSOR_INFO;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible)
	{
		c->bVisible=TRUE;
		c->dwSize=0;//(0) is invild so the default value is set
	}
	else
	{
		c->bVisible=FALSE;
		c->dwSize=1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h,c);
}
void gotoXY(int x, int y)
{
    CursorPosition.X = x; // Locates column
    CursorPosition.Y = y; // Locates Row
    SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}
void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;

    SetConsoleCursorPosition(hOut, Position);
}
int searchEvent()
{
    system("cls");
    string Option[]={ " [1] Event Date ",
                      " [2] Event Name ",
                      " [3] Exit"} ;
    bool ascii = true;

    int key = 0, pointer = 0;
    int cp[3] = {9 , 10, 11};
    int choice;
    do
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoXY(15,4);  cout << "| ____________________________________________ |";
        gotoXY(15,5);  cout << "|                                              |";
        gotoXY(15,6);  cout << "|                  Search by                   |";
        gotoXY(15,7);  cout << "| ____________________________________________ |";
        gotoXY(15,8);  cout << "|                                              |";
        gotoXY(15,9);  cout << "|                                              |";
        gotoXY(15,10); cout << "|                                              |";
        gotoXY(15,11); cout << "|                                              |";

        for ( int i = 0 ; i < 3 ; i++)
        {
            if ( i == pointer )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                gotoXY(16,cp[i]);
                cout << Option[i] ;
                choice = i;
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
                gotoXY(16,cp[i]);
                cout << Option[i];
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
            gotoXY(15,12); cout << "| ____________________________________________ |";
            gotoXY(15,13); cout << "|                                              |";
        }
        key = getch();

        if(key == 80)// down key(acsii).
        {
            pointer += 1;
            if(pointer > 2)
            {
                pointer = 0;
            }
        }
        else if(key ==72)// up key(acsii).
        {
            pointer -= 1;
            if(pointer < 0)
            {
                pointer = 2;
            }
        }
        else if (key == 13)
        { // Enter key(acsii).
            switch(choice)
            {
                case 0 :
                {

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    gotoXY(15,18);cout << "  Date[dmmyyyy]    : ";

                    string SearchDateString;

                    gotoXY(36,18);getline(cin, SearchDateString);

                    file searchTheData;
                    int *titleArray = searchTheData.searchFile("Date.txt", SearchDateString);
                    bool foundOrNot;
                    int tit = 23 , d = 24 , l = 25 , t = 26 , n =22,pause;
                    if(titleArray[0]>0)
                    {

                        for(int i=1;i<=titleArray[0];i++)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                            gotoXY(15,n);cout << "  Event [" << i << "]";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                            gotoXY(15,tit);cout << "  Title       : ";
                            gotoXY(15,d);  cout << "  Description : ";
                            gotoXY(15,l);  cout << "  Location    : ";
                            gotoXY(15,t);  cout << "  Time        : ";

                            gotoXY(32,tit); cout << searchTheData.ReadLine("Title.txt",titleArray[i]);
                            gotoXY(32,d); cout << searchTheData.ReadLine("Description.txt",titleArray[i]);
                            gotoXY(32,l); cout << searchTheData.ReadLine("Location.txt",titleArray[i]);
                            gotoXY(32,t); cout << searchTheData.ReadLine("Time.txt",titleArray[i]);

                            n+=7;tit+=7;d+=7;l+=7;t+=7;

                        }
                        pause = t + 3;
                        gotoXY(15,pause);system("pause");
                        system("cls");
                    }
                    else {
                        gotoXY(16,22); cout << " Not found!";
                        gotoXY(16,24);system("pause");
                        system("cls");
                    }
                }
                break;
                case 1 :
                {


                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    gotoXY(15,18);cout << "  Name     : ";

                    string SearchTitleString;

                    gotoXY(33,18);getline(cin, SearchTitleString);

                    file searchTheData;
                    int *titleArray = searchTheData.searchFile("Title.txt", SearchTitleString);
                    bool foundOrNot;
                    int tit = 23 , d = 24 , l = 25 , t = 26 , n =21,pause;
                    if(titleArray[0]>0){
                        for(int i=1;i<=titleArray[0];i++){

                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                            gotoXY(15,n);cout << "  Event [" << i << "]";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                            gotoXY(15,tit);cout << "  Title       : ";
                            gotoXY(15,d);  cout << "  Description : ";
                            gotoXY(15,l);  cout << "  Location    : ";
                            gotoXY(15,t);  cout << "  Time        : ";

                            gotoXY(32,tit); cout << searchTheData.ReadLine("Title.txt",titleArray[i]);
                            gotoXY(32,d); cout << searchTheData.ReadLine("Description.txt",titleArray[i]);
                            gotoXY(32,l); cout << searchTheData.ReadLine("Location.txt",titleArray[i]);
                            gotoXY(32,t); cout << searchTheData.ReadLine("Time.txt",titleArray[i]);

                             n+=7;tit+=7;d+=7;l+=7;t+=7;

                        }
                        pause = t + 3;
                        gotoXY(15,pause);system("pause");
                        system("cls");
                    } else {
                        gotoXY(16,22); cout << " Not found!";
                        gotoXY(16,24);system("pause");
                        system("cls");
                    }
                }
                break;
                case 2 :
                {
                    cout << "\n\n\t\tLoading ....";
                    Sleep(1000);
                    system("cls");
                    return 0 ;
                }
                break;
                default :
                {
                    cout << "\n Choose AGAIN." ;
                }
            }


        }
        else
        {
            if(!(key == 224))// except up and down.
            {
                    //wrong = 1;
            }
        }




        clearScreen();
    }while(true);
}
int showMenu(int day, int mon, int year)
{
    system("cls");
    string Option[]={ " [1] View Event ",
                      " [2] Add Event ",
                      " [3] Edit Event ",
                      " [4] Delete Event ",
                      " [5] Exit " } ;
    int wrong;
    int initialNum = 0;
    int key = initialNum, theOpt = initialNum,pointer = initialNum;
    bool ascii = true;
    int ch ,choose;

    int cp[5] = { 9 , 10, 11 , 12 , 13 };
    int numEvent , name ,store;
    store = 0 ;




    do
    {
        // below this one connect from the end part there!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoXY(15,3); cout << "Selected Date: " << day << "/" << mon << "/" << year;
        gotoXY(15,4);  cout << "| ____________________________________________ |";
        gotoXY(15,5);  cout << "|                                              |";
        gotoXY(15,6);  cout << "|                   OPTION                     |";
        gotoXY(15,7);  cout << "| ____________________________________________ |";
        gotoXY(15,8);  cout << "|                                              |";
        gotoXY(15,9);  cout << "|                                              |";
        gotoXY(15,10); cout << "|                                              |";
        gotoXY(15,11); cout << "|                                              |";
        gotoXY(15,12); cout << "|                                              |";
        gotoXY(15,13); cout << "|                                              |";


        for ( int i = 0 ; i < 5 ; i++)
        {
            if ( i == pointer )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                gotoXY(16,cp[i]);
                cout << Option[i] ;
                ch = i;
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
                gotoXY(16,cp[i]);
                cout << Option[i];
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
            gotoXY(15,14); cout << "| ____________________________________________ |";
            gotoXY(15,15); cout << "|                                              |";
        }

            if(wrong == 1)
            {
                cout << "" ; // press wrong key , nothing should happen , i dunno what to put here .
            }

            key = getch();	//get option.

            if(key == 80)// down key(acsii).
            {
                pointer += 1;
                if(pointer > 4 )
                {
                    pointer = 0;
                }
                wrong = 0;
            }
            else if(key ==72)// up key(acsii).
            {
                pointer -= 1;
                if(pointer <0)
                {
                    pointer = 4;
                }
                wrong = 0;
            }
            else if (key == 13)
            { // Enter key(acsii).

                switch(ch)
                {
                    case 0 :
                    {
                        getView(numEvent,store,day, mon, year);
                    }
                    break;
                    case 1 :
                    {
                        numEvent = getAdd(store, day, mon, year);
                        store = numEvent;
                    }
                    break ;
                    case 2 :
                    {
                        name = getEdit(store) ;
                    }
                    break;
                    case 3 :
                    {
                        choose = getDelete();
                    }
                    break;
                    case 4 :
                    {
                        cout << "\n\n\n\t\tLoading ....";
                        Sleep(1000);
                        system("cls");
                        return 0 ;
                    }
                    break;
                    default :
                    {
                        cout << "\n Choose AGAIN." ;
                    }

                }

            }
            else
            {
                if(!(key == 224))// except up and down.
                {
                    wrong = 1;
                }
            }

        // below this one is like system("cls")---------------------------------------------
        clearScreen();
    }while (true );

    return store;
}
void getView(int numEvent,int store,int aday,int amon,int ayear)
{
    int key ,wrong,i=0;
    bool ascii = true;
    int idname = 1;
    int lline , exx;
    int id ;


    file viewSearchGetData;

    int DateInt = (aday*1000000)+(amon*10000)+(ayear);
    string DateString;
    stringstream stream;
    stream << DateInt;
    stream >> DateString;

    int *DateArray = viewSearchGetData.searchFile("Date.txt", DateString);
    bool foundOrNot;
    (DateArray[0]==0)?foundOrNot=false:foundOrNot=true;

    if(!foundOrNot)
    {
            system("cls");
            gotoXY(10,5);  cout << " __________________________________________________________ ";
            gotoXY(10,7);  cout << "                       E V E N T                            ";
            gotoXY(10,8);  cout << " __________________________________________________________ ";
            gotoXY(10,28); cout << " __________________________________________________________ ";
            gotoXY(13,10);cout << " NO Event is Created!";
            gotoXY(10,28); cout << " __________________________________________________________ ";
            gotoXY(10,30);cout << "[ ESC ] Exit !";

            do
            {
                key = getch();
                if (key == 27)
                {
                    system("cls");
                    break;
                }
                else
                {
                    if( !(key == 224))
                    wrong = 1 ;
                }

            }while(true);
    }else{

        system("cls");
        gotoXY(10,5);  cout << " __________________________________________________________ ";
        gotoXY(29,7);  cout << aday << " / " << amon << " / " << ayear << " " <<" E V E N T " ;
        gotoXY(10,8);  cout << " __________________________________________________________ ";

        int tit = 12 , d = 13 , l = 14 , t = 15 , n =10;

        for(int i=1;i<=DateArray[0];i++){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            gotoXY(13,n);cout << "Event [" << i << "]";

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            gotoXY(13,tit);cout << "Title       : ";
            gotoXY(13,d);  cout << "Description : ";
            gotoXY(13,l);  cout << "Location    : ";
            gotoXY(13,t);  cout << "Time        : ";

            gotoXY(27,tit); cout << viewSearchGetData.ReadLine("Title.txt",DateArray[i]);
            gotoXY(27,d); cout << viewSearchGetData.ReadLine("Description.txt",DateArray[i]);
            gotoXY(27,l); cout << viewSearchGetData.ReadLine("Location.txt",DateArray[i]);
            gotoXY(27,t); cout << viewSearchGetData.ReadLine("Time.txt",DateArray[i]);

            tit+=8 ; d+=8 ; l+=8 ; t+=8 ; n+=8;
        }

        lline = t - 5;
        exx = lline +2;
        gotoXY(10,lline); cout << " __________________________________________________________ ";
        gotoXY(10,exx);cout << "[ ESC ] Exit !";

        do
        {
            key = getch();
            if (key == 27) // esc
            {
                system("cls");
                break;
            }
            else
            {
                if(!(key == 224))
                cout << ""; // suppose is to do nothing . i dunno what to put here
            }

        }while(true);
    }
}
int getAdd(int store,int aday, int amon,int ayear)
{
    int i = 0;
    int j = 1;

    do
    {

                system("cls");
                gotoXY(10,5);  cout << " __________________________________________________________ ";
                gotoXY(10,7);  cout << "                      E V E N T                          ";
                gotoXY(10,8);  cout << " __________________________________________________________ ";
                gotoXY(10,28); cout << " __________________________________________________________ ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoXY(43,7);cout << "[ " << nameEvent[i] << " ]";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                gotoXY(13,10);cout << " Title       : ";
                gotoXY(13,14);cout << " Description : ";
                gotoXY(13,18);cout << " Location    : ";
                gotoXY(13,22);cout << " Time        : ";

                string addTitleString,addDescriptionString,addLocationString,addTimeString;

                int DateInt = (aday*1000000)+(amon*10000)+(ayear);
                string DateString;
                stringstream stream;
                stream << DateInt;
                stream >> DateString;

                gotoXY(29,10);getline(cin, addTitleString);
                gotoXY(29,14);getline(cin, addDescriptionString);
                gotoXY(29,18);getline(cin, addLocationString);
                gotoXY(29,22);getline(cin, addTimeString);

                file addMore;
                addMore.AddFile("Title.txt", addTitleString);
                addMore.AddFile("Description.txt", addDescriptionString);
                addMore.AddFile("Location.txt", addLocationString);
                addMore.AddFile("Time.txt", addTimeString);
                addMore.AddFile("Date.txt", DateString);

                i ++;
                j ++;




        store ++;

        gotoXY(10,30);cout << "  ADD another event ? <yes> :";
        cin >> add;
        cin.ignore();

        if(add[0] != 'y' && add[0] != 'Y')
        {
            system("cls");
            break;
        }

    }while( add[0] == 'Y'|| add[0] == 'y');

    return store;
}
int getEdit(int)
{
    int i = 0;
    int j = 1;

    do
    {

                system("cls");
                gotoXY(10,5);  cout << " __________________________________________________________ ";
                gotoXY(10,7);  cout << "                     E D I T                          ";
                gotoXY(10,8);  cout << " __________________________________________________________ ";
                gotoXY(10,28); cout << " __________________________________________________________ ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoXY(43,7);cout << "[ " << "Key In The Title" << " ]";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                gotoXY(13,10);cout << " Title       : ";

                string EditTitleString,EditDescriptionString,EditLocationString,EditTimeString;

                gotoXY(29,10);getline(cin, EditTitleString);

                file editSearchData;
                int *titleArray = editSearchData.searchFile("Title.txt", EditTitleString);
                bool foundOrNot;
                (titleArray[0]==1)?foundOrNot=true:foundOrNot=false;

                if(foundOrNot){
                    gotoXY(13,10);cout << " Date       : ";
                    gotoXY(13,14);cout << " Title       : ";
                    gotoXY(13,18);cout << " Description : ";
                    gotoXY(13,22);cout << " Location    : ";
                    gotoXY(13,26);cout << " Time        : ";

                    gotoXY(29,10);cout << editSearchData.ReadLine("Date.txt",titleArray[1]);
                    gotoXY(29,14);cout << editSearchData.ReadLine("Title.txt",titleArray[1]);
                    gotoXY(29,18);getline(cin, EditDescriptionString);
                    gotoXY(29,22);getline(cin, EditLocationString);
                    gotoXY(29,26);getline(cin, EditTimeString);

                    editSearchData.ModOrDelData("Title.txt", titleArray[1], EditTitleString);
                    editSearchData.ModOrDelData("Description.txt", titleArray[1], EditDescriptionString);
                    editSearchData.ModOrDelData("Location.txt", titleArray[1], EditLocationString);
                    editSearchData.ModOrDelData("Time.txt", titleArray[1], EditTimeString);
                } else {
                    system("cls");
                    gotoXY(10,5);  cout << " __________________________________________________________ ";
                    gotoXY(10,7);  cout << "                     E D I T                          ";
                    gotoXY(10,8);  cout << " __________________________________________________________ ";
                    gotoXY(10,28); cout << " __________________________________________________________ ";
                    gotoXY(17,10);cout << " Tittle Not Found !";
                    gotoXY(10,28); cout << " __________________________________________________________ ";
                    gotoXY(10,30);cout << "[ ESC ] Exit !";
                }

        gotoXY(10,30);cout << "  Edit another event ? <yes/no> :";
        cin >> add;
        cin.ignore();

        if(add[0] != 'y' && add[0] != 'Y')
        {
            system("cls");
            break;
        }

    }while( add[0] == 'Y'|| add[0] == 'y');


}
int getDelete()
{
    int i = 0;
    int j = 1;

    do
    {

                system("cls");
                gotoXY(10,5);  cout << " __________________________________________________________ ";
                gotoXY(10,7);  cout << "                  D E L E T E                         ";
                gotoXY(10,8);  cout << " __________________________________________________________ ";
                gotoXY(10,28); cout << " __________________________________________________________ ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoXY(40,7);cout << "[ " << "Key in the Title" << " ]";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                gotoXY(13,10);cout << " Title       : ";

                string DelTitleString,DelDescriptionString,DelLocationString,DelTimeString;

                gotoXY(29,10);getline(cin, DelTitleString);

                file deleteData;
                int *titleArray = deleteData.searchFile("Title.txt", DelTitleString);
                bool foundOrNot;
                (titleArray[0]==1)?foundOrNot=true:foundOrNot=false;
                if(foundOrNot){
                    deleteData.ModOrDelData("Date.txt", titleArray[1], "||Delete||");
                    deleteData.ModOrDelData("Title.txt", titleArray[1], "||Delete||");
                    deleteData.ModOrDelData("Description.txt", titleArray[1], "||Delete||");
                    deleteData.ModOrDelData("Location.txt", titleArray[1], "||Delete||");
                    deleteData.ModOrDelData("Time.txt", titleArray[1], "||Delete||");
                } else {
                    system("cls");
                    gotoXY(10,5);  cout << " __________________________________________________________ ";
                    gotoXY(10,7);  cout << "                  D e l e t e                         ";
                    gotoXY(10,8);  cout << " __________________________________________________________ ";
                    gotoXY(10,28); cout << " __________________________________________________________ ";
                    gotoXY(17,10);cout << " Tittle Not Found !";
                    gotoXY(10,28); cout << " __________________________________________________________ ";
                    gotoXY(10,30);cout << "[ ESC ] Exit !";
                }

        gotoXY(10,30);cout << "  Delete another event ? <yes/no> :";
        cin >> add;
        cin.ignore();

        if(add[0] != 'y' && add[0] != 'Y')
        {
            system("cls");
            break;
        }

    }while( add[0] == 'Y'|| add[0] == 'y');
}
