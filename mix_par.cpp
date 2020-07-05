#include "mix_par.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include "QMessageBox"
using namespace std;

Mix_Par::~Mix_Par()
{/*
    for (int i = 0; i < num_teams; i++) {
        delete[] results[i];
    }
    delete[] results;

    for (int i = 0; i < capacity_tour; i++) {
        delete[] arr_pairs[i];
    }
    delete[] arr_pairs;

    delete[] arr_players;*/

    if(results)
    {
        for (int i = 0; i < num_teams; ++i) {
            delete[] results[i];
        }
        delete[] results;
    }

    if(results2)
    {
        for (int i = 0; i < num_teams; ++i) {
            delete[] results2[i];
        }
        delete[] results2;
    }

    if(teams)
    {
        delete[] teams;
    }

    if(arr_pairs)
    {
        for (int i = 0; i < capacity_tour; ++i) {
            delete[] arr_pairs[i];
        }
        delete[] arr_pairs;
    }

    if(arr_players)
    {
        delete[] arr_players;
    }
}

void Mix_Par::RotateArray(int* teams, int n)
{
    //int n = _msize(teams) / sizeof(teams[0]);
    //int n = sizeof(teams) / sizeof(teams[0]);
    //int n = 10;
    int tmp = teams[n - 1];
    for (int i = n - 1; i > 0; i--)
        teams[i] = teams[i - 1];
    teams[0] = tmp;
}

//нечетное кол-во
int** Mix_Par::GenerateRoundRobinOdd(const int num_teams)
{
    int n2 = (int)((num_teams - 1) / 2);

    results = new int*[num_teams];
    for (int i = 0; i < num_teams; i++)
    {
        results[i] = new int[num_teams];
        for (int j = 0; j < num_teams; j++)
        {
            results[i][j] = 0;
        }
    }

    //for (int i = 0; i < num_teams; i++)
    //results[i] = new int[num_teams];

    // записывается значение массива
    /*int **/teams = new int[num_teams];
    for (int i = 0; i < num_teams; i++)
        teams[i] = i;

    // составление пар
    for (int round = 0; round < num_teams; round++)
    {
        for (int i = 0; i < n2; i++)
        {
            int team1 = teams[n2 - i];
            int team2 = teams[n2 + i + 1];
            results[team1][round] = team2;
            results[team2][round] = team1;
        }

        // Выбор игрока с bye
        results[teams[0]][round] = BYE;

        // Сдвиг
        RotateArray(teams, num_teams);
    }

    return results;
}

//четное кол-во
int ** Mix_Par:: GenerateRoundRobinEven(int num_teams)
{
    // заполняются пары без одного игрока
    /*int ***/results = GenerateRoundRobinOdd(num_teams - 1);

    // Copy the results into a bigger array,
    // replacing the byes with the extra team.
    /*int ***/results2 = new int*[num_teams];
    for (int i = 0; i < num_teams; i++)
        results2[i] = new int[num_teams];
    for (int team = 0; team < num_teams - 1; team++)
    {
        for (int round = 0; round < num_teams - 1; round++)
        {
            if (results[team][round] == BYE)
            {
                // Change the bye to the new team.
                results2[team][round] = num_teams - 1;
                results2[num_teams - 1][round] = team;
            }
            else
            {
                results2[team][round] = results[team][round];
            }
        }
    }
    return results2;
}

//определяет сколько человек
int** Mix_Par::GenerateRoundRobin(int num_teams)
{
    if (num_teams % 2 == 0)
        return GenerateRoundRobinEven(num_teams);
    else
        return GenerateRoundRobinOdd(num_teams);
}

int* Mix_Par::List_player(int num_teams)
{
    MainWindow m;
    QSqlQuery* query=new QSqlQuery(m.get_db());
    //query->prepare("SELECT * FROM Player_info");
    //query->exec();
    /*int* */arr_players = new int[num_teams];
    query->prepare("SELECT ID FROM Player_info");
    if( query->exec() )
    {
        query->next();
        for (int i = 0; i < num_teams; i++)
       {
            arr_players[i] = query->value(0).toInt();
            query->next();
       }
    }
    delete query; /**/
    m.connClose(); /**/
    return arr_players;
}
void Mix_Par::Sort_pairs(int num_teams)
{
    // Get the schedule.
    // int num_teams = (int)nudNumTeams.Value;
    /*int** */results = GenerateRoundRobin(num_teams);
    int pars{ 0 };
    if (num_teams % 2 == 0)
    {
        capacity_tour = num_teams - 1;
        pars =num_teams / 2;
    }
    else
    {
        capacity_tour = num_teams;
        pars = (num_teams + 1) / 2;
    }
    // Display the result.
    //string txt = "";
    //for (int round = 0; round <= results.GetUpperBound(1); round++)
    /*for (int j = 0; j <= capacity_tour - 1; j++)
    {
        cout << " " << endl;
        for (int i = 0; i<num_teams; i++)
        {
            cout << " " << results[i][j] << " ";
        }
    }
    */

    /*int** */arr_pairs = new int*[capacity_tour];
    for (int i = 0; i < capacity_tour * pars; i++ )
    {
        arr_pairs[i] = new int[3];
        for (int j =0; j < 3; j++ )
        {
            arr_pairs[i][j] = 0;
        }
    }
    int ind{0};
    for (int round = 0; round <= capacity_tour - 1; round++)
    {
        cout << " Round " << round << " " << endl;

        for (int team = 0; team < num_teams; team++)
        {
            if (results[team][round] == -1)
            {
                cout << "    " << team << " (bye)" << endl;
                arr_pairs[ind][0]=round;
                arr_pairs[ind][1]=team;
                arr_pairs[ind][2]=-1;
                ind++;

            }
            else if (team < results[team][round])
            {
                if (team == (num_teams - 1) || results[team][round] == (num_teams - 1))
                {
                    if (results[team][round] < (num_teams - 1) / 2)
                    {
                        cout << "    " << results[team][round] << " v " << team << " " << endl;
                        arr_pairs[ind][0] = round;
                        arr_pairs[ind][1] = results[team][round];
                        arr_pairs[ind][2] = team;
                    }
                    else
                    {
                        cout << "    " << team << " v " << results[team][round] << " " << endl;
                        arr_pairs[ind][0] = round;
                        arr_pairs[ind][1] = team;
                        arr_pairs[ind][2] = results[team][round];
                    }
                    ind++;
                }
                else if ((team + results[team][round]) % 2 == 0)
                {
                    if (results[team][round] < team)
                    {
                        cout << "    " << team << " v " << results[team][round] << " " << endl;
                        arr_pairs[ind][0] = round;
                        arr_pairs[ind][1] = team;
                        arr_pairs[ind][2] = results[team][round];
                    }
                    else
                    {
                        cout << "    " << results[team][round] << " v " << team << " " << endl;
                        arr_pairs[ind][0] = round;
                        arr_pairs[ind][1] = results[team][round];
                        arr_pairs[ind][2] = team;
                    }
                    ind++;
                }
                else if ((team + results[team][round]) % 2 != 0 and results[team][round] < team)
                {
                    cout << "    " << results[team][round] << " v " << team << " " << endl;
                    arr_pairs[ind][0] = round;
                    arr_pairs[ind][1] = team;
                    arr_pairs[ind][2] = results[team][round];

                    ind++;
                } else {
                    cout << "    " << team << " v " << results[team][round] << " " << endl;
                    arr_pairs[ind][0] = round;
                    arr_pairs[ind][1] = results[team][round];
                    arr_pairs[ind][2] = team;

                    ind++;
                }
            }
        }
    }

    cout << "Pochty0" << endl;
    //MainWindow q;
    //q.db.open();
    //cout<<"Pochty1"<< endl;
    //QSqlQuery* query =new QSqlQuery(q.db);

    cout << "Pochty2" << endl;
    MainWindow m;
    cout << "Pochty3" << endl;
    QSqlQuery query(m.get_db());
    try {
        cout << "Pochty4" << endl;
        //query.prepare("select * from Player_info");
        //cout << "Pochty5" << endl;
        //query.exec();
        //cout << "Pochty6" << endl;
        arr_players = new int[num_teams];

        cout << "Pochty7" << endl;
        query.prepare("SELECT ID FROM Player_info");
        if( query.exec() )
        {
            cout << "Pochty8s" << endl;
            query.next();
            for (int i = 0; i < num_teams; i++)
            {
                arr_players[i] = query.value(0).toInt();
                cout << "Pochty8s" << i <<1 << endl;
                query.next();
                cout << "Pochty8s" << i <<2 << endl;
            }
        }
    } catch(exception ex) {cout << ex.what() << endl;}

    cout<< "poojvifo " << endl;
    for (int i = 0; i < capacity_tour * pars; ++i )
    {
        try {
            //QString Number_Tours = (QString)arr_pairs[i][0];
            //QString Player_write = (QString)arr_players[arr_pairs[i][1]];
            //QString Player_black = (QString)arr_players[arr_pairs[i][2]];
            int Number_Tours = arr_pairs[i][0];
            int Player_write = arr_players[arr_pairs[i][1]];
            int Player_black = arr_players[arr_pairs[i][2]];

            query.prepare("INSERT OR REPLACE into Tours( Number_Tours,  Player_write,  Player_black,  Result_write,  Result_black)"
                                              " values (:Number_Tours, :Player_write, :Player_black, :Result_write, :Result_black)");
            query.bindValue(":Number_Tours", Number_Tours);
            query.bindValue(":Player_write", Player_write);
            query.bindValue(":Player_black", Player_black);
            query.bindValue(":Result_write", 0);
            query.bindValue(":Result_black", 0);

            if (query.exec())
            {
                QMessageBox::information(0, "Information", "Success insert into");
                cout << "iteration "<<i<<"  tour "<<Number_Tours<<": "<<Player_write<<" vs "<<Player_black<<";" << endl;
            }
            else
            {
                QMessageBox::information(0, "Information", "Error");
            }
        } catch(exception ex) {cout << ex.what() << endl;}
    }
}
