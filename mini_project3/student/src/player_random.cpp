#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
//#include <unordered_set>

using namespace std;
// using State = vector<int>; // x, y, val

const int SIZE = 15;

/*struct Point
{
    int x, y;
    Point() : Point(0, 0) {}
    Point(float x, float y) : x(x), y(y) {}
    bool operator==(const Point &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Point &rhs) const
    {
        return !operator==(rhs);
    }
    Point operator+(const Point &rhs) const
    {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
};*/

struct Node
{
    int x;
    int y;

    std::array<std::array<int, SIZE>, SIZE> nowboard;
};

int countpoint(std::array<std::array<int, SIZE>, SIZE> now, int people);
bool is_spot_on_board(int x, int y);
// int same1(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map);
int same2(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map);
int same3(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map);
Node *nextstep(int person, int x, int y, Node *hi);
vector<Node *> newnextstep(int person, Node *hi, vector<Node *> next);

enum SPOT_STATE
{
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

int player, enemy;
std::array<std::array<int, SIZE>, SIZE> board;
// std::array<std::array<int, SIZE>, SIZE> point;

int three = 0;

int countpoint(std::array<std::array<int, SIZE>, SIZE> now, int person)
{
    int point = 0;
    int onetime = 0;
    int ratio = 5;

    person = player;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            three = 0;
            onetime = 0;

            if (now[i][j] == player)
            {
                onetime += same2(person, i, j, 1, 1, now);
                onetime += same2(person, i, j, 1, 0, now);
                onetime += same2(person, i, j, 1, -1, now);
                onetime += same2(person, i, j, 0, -1, now);

                if (three >= 2)
                {
                    onetime *= 2;
                }

                point += onetime;
            }
            else if (now[i][j] == 3 - player)
            {
                onetime += (same2(3 - person, i, j, 1, 1, now) * ratio);
                onetime += (same2(3 - person, i, j, 1, 0, now) * ratio);
                onetime += (same2(3 - person, i, j, 1, -1, now) * ratio);
                onetime += (same2(3 - person, i, j, 0, -1, now) * ratio);

                if (three >= 2)
                {
                    onetime *= 2;
                }

                point -= onetime;
            }
            /*else if (now[i][j] == 0)
            {
                onetime += (same2(0, i, j, 1, 1, now));
                onetime += (same2(0, i, j, 1, 0, now));
                onetime += (same2(0, i, j, 1, -1, now));
                onetime += (same2(0, i, j, 0, -1, now));
                onetime += (same2(0, i, j, -1, -1, now));
                onetime += (same2(0, i, j, -1, 0, now));
                onetime += (same2(0, i, j, -1, 1, now));
                onetime += (same2(0, i, j, 0, 1, now));

                point += onetime * 1000;
            }*/
        }
    }

    return point;
}

int same1(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map)
{
    int a = 0;
    int e = 0;
    int out = 0;
    int point = 0;

    // test place
    if (is_spot_on_board(x - mx, y - my) && map[x - mx][y - my] != 0)
    {
        people = map[x - mx][y - my];
    }
    else if (!is_spot_on_board(x - mx, y - my))
    {
        out++;
    }
    x += mx;
    y += my;
    if (people == 0)
    {
        if (is_spot_on_board(x, y) && map[x][y] != 0)
        {
            people = map[x][y];

            x += mx;
            y += my;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (is_spot_on_board(x, y) && map[x][y] != people)
        {
            people = map[x][y];

            e++;

            x += mx;
            y += my;
        }
        else if (is_spot_on_board(x, y) && map[x][y] == people)
        {
            x += mx;
            y += my;
        }
        else
        {
            return 0;
        }
    }
    while (is_spot_on_board(x, y) && map[x][y] == people)
    {
        x += mx;
        y += my;

        a++;
    }
    if (is_spot_on_board(x, y) && map[x][y] == 3 - people)
    {
        e++;
    }
    else if (!is_spot_on_board(x, y))
    {
        out++;
    }

    point = max(a - e - out, 0);

    if (people != player)
    {
        point *= -1;
    }

    return point;
}

int same2(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map)
{
    int a = 0;
    int e = 0;
    int out = 0;
    int point = 0;

    // test place
    if (is_spot_on_board(x - mx, y - my) && map[x - mx][y - my] == people) // not head
    {
        return 0;
    }
    else if (is_spot_on_board(x - mx, y - my) && map[x - mx][y - my] == 3 - people)
    {
        e++;
    }
    else if (!is_spot_on_board(x - mx, y - my))
    {
        out++;
        e++;
    }
    while (is_spot_on_board(x, y) && map[x][y] == people)
    {
        x += mx;
        y += my;

        a++;
    }
    if (is_spot_on_board(x, y) && map[x][y] == 3 - people)
    {
        e++;
    }
    else if (!is_spot_on_board(x, y) && a < 5)
    {
        out++;
        e++;
    }

    // test point
    if (a == 1 && e == 0)
    {
        point = 10;

        if (is_spot_on_board(x + mx, y + my) && map[x + mx][y + my] == people)
        {
            point = 90;
        }
        else if (is_spot_on_board(x - mx * 3, y - my * 3) && map[x - mx * 3][y - my * 3] == people)
        {
            point = 90;
        }
    }
    else if (a == 1 && e == 1)
    {
        point = 6;
    }
    else if (a == 1 && e == 2)
    {
        point = 2;
    }
    else if (a == 2 && e == 0)
    {
        point = 100;

        three += 1;

        if (is_spot_on_board(x + mx, y + my) && map[x + mx][y + my] == people)
        {
            point = 900;

            // three += 1;
        }
        else if (is_spot_on_board(x - mx * 4, y - my * 4) && map[x - mx * 4][y - my * 4] == people)
        {
            point = 900;

            // three += 1;
        }
    }
    else if (a == 2 && e == 1)
    {
        point = 30;
    }
    else if (a == 2 && e == 2)
    {
        point = 10;
    }
    else if (a == 3 && e == 0)
    {
        point = 1000;

        three += 1;

        if (is_spot_on_board(x + mx, y + my) && map[x + mx][y + my] == people)
        {
            point = 9000;
        }
        else if (is_spot_on_board(x - mx * 5, y - my * 5) && map[x - mx * 5][y - my * 5] == people)
        {
            point = 9000;
        }
    }
    else if (a == 3 && e == 1)
    {
        point = 400;

        if (is_spot_on_board(x + mx, y + my) && map[x][y] == 0 && map[x + mx][y + my] == people)
        {
            point = 6000;
        }
        else if (is_spot_on_board(x - mx * 5, y - my * 5) && map[x - mx * 4][y - my * 4] == 0 && map[x - mx * 5][y - my * 5] == people)
        {
            point = 6000;
        }
    }
    else if (a == 3 && e == 2)
    {
        point = 250;
    }
    else if (a == 4 && e == 0)
    {
        point = 10000;
    }
    else if (a == 4 && e == 1)
    {
        point = 7000;
    }
    else if (a == 4 && e == 2)
    {
        point = 2000;
    }
    else if (a >= 5)
    {
        point = 1000000;
    }

    if (out == 1)
    {
        point *= 0.7;
    }
    else if ((out == 1 && e == 1) || out == 2)
    {
        point *= 0.1;
    }

    return point;
}

int five = 0;
int four = 0;
int four1 = 0;
int tthree = 0;
int five_e = 0;
int four_e = 0;
int four1_e = 0;
int tthree_e = 0;

int same3(int people, int x, int y, int mx, int my, std::array<std::array<int, SIZE>, SIZE> map)
{
    int a = 0;
    int b = 0;
    int e = 0;
    int out = 0;
    int point = 0;

    // test place
    if (is_spot_on_board(x - mx, y - my) && map[x - mx][y - my] == people) // not head
    {
        return 0;
    }
    else if (is_spot_on_board(x - mx, y - my) && map[x - mx][y - my] == 3 - people)
    {
        e++;
    }
    else if (!is_spot_on_board(x - mx, y - my))
    {
        out++;
        e++;
    }
    while (is_spot_on_board(x, y) && map[x][y] == people)
    {
        x += mx;
        y += my;

        a++;
    }
    if (is_spot_on_board(x, y) && map[x][y] == 3 - people)
    {
        e++;
    }
    else if (!is_spot_on_board(x, y) && map[x][y] == 0)
    {
        x += mx;
        y += my;

        while (is_spot_on_board(x, y) && map[x][y] == people)
        {
            x += mx;
            y += my;

            b++;
        }

        if (is_spot_on_board(x, y) && map[x][y] == 3 - people)
        {
            e++;
        }
        else if (!is_spot_on_board(x, y) && a < 5)
        {
            out++;
            e++;
        }
    }
    else if (!is_spot_on_board(x, y) && a < 5)
    {
        out++;
        e++;
    }

    // test point
    if (a == 5)
    {
        // point = 1000000;

        if (people == player)
        {
            five++;
        }
        else
        {
            five_e++;
        }
    }
    else if (a == 4 && e == 0)
    {
        // point = 900000;
        if (people == player)
        {
            four++;
        }
        else
        {
            four_e++;
        }
    }
    else if (a == 4 && e == 1)
    {
        point = 800000;
        if (people == player)
        {
            four1++;
        }
        else
        {
            four1_e++;
        }
    }
    else if (a == 3 && b == 1 && e == 0)
    {
        point = 800000;
        if (people == player)
        {
            four1++;
        }
        else
        {
            four1_e++;
        }
    }
    else if (a == 1 && b == 3 && e == 0)
    {
        point = 800000;
        if (people == player)
        {
            four1++;
        }
        else
        {
            four1_e++;
        }
    }
    else if (a == 2 && b == 2 && e == 0)
    {
        point = 800000;
        if (people == player)
        {
            four1++;
        }
        else
        {
            four1_e++;
        }
    }
    else if (a == 3 && e == 0)
    {
        if (tthree >= 2)
        {
            point = 700000;
        }
        else
        {
            point = 0;
        }

        if (people == player)
        {
            tthree++;
        }
        else
        {
            tthree_e++;
        }
    }
    else if (a == 2 && b == 1 && e == 0)
    {
        if (tthree >= 2)
        {
            point = 700000;
        }
        else
        {
            point = 0;
        }

        if (people == player)
        {
            tthree++;
        }
        else
        {
            tthree_e++;
        }
    }
    else if (a == 1 && b == 2 && e == 0)
    {
        if (tthree >= 2)
        {
            point = 700000;
        }
        else
        {
            point = 0;
        }

        if (people == player)
        {
            tthree++;
        }
        else
        {
            tthree_e++;
        }
    }

    return 0;
}

bool is_spot_on_board(int x, int y)
{
    return 0 <= x && x < 15 && 0 <= y && y < 15;
}
/*
Node *nextstep(int person, int x, int y, Node *hi)
{
    for (int i = x - 2; i <= x + 2; i++)
    {
        for (int j = y - 2; j <= y + 2; j++)
        {
            if (is_spot_on_board(i, j) && (hi->nowboard)[i][j] == 0)
            {
                Node *temp = new Node;
                temp->level = hi->level + 1;
                temp->x = i;
                temp->y = j;
                temp->min = 0;
                temp->max = 0;
                temp->nowboard = hi->nowboard;
                (temp->nowboard)[i][j] = person;
                temp->point = countpoint(temp->nowboard);

                (hi->next).push_back(temp);
            }
        }
    }

    return hi;
}*/

vector<Node *> newnextstep(int level, int person, Node *hi, vector<Node *> next) // count next steps
{
    vector<vector<int>> nownum;
    std::array<std::array<int, SIZE>, SIZE> check = hi->nowboard;

    if (level <= 4)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if ((hi->nowboard)[i][j] != 0)
                {
                    vector<int> temp = {i, j};

                    nownum.push_back(temp);
                }
            }
        }
    }
    else
    {
        nownum.push_back({hi->x, hi->y});
    }

    int range = 2;

    next.clear();

    for (vector<int> good : nownum)
    {
        for (int i = good[0] - range; i <= good[0] + range; i++)
        {
            for (int j = good[1] - range; j <= good[1] + range; j++)
            {
                if (is_spot_on_board(i, j) && check[i][j] == 0)
                {
                    Node *temp = new Node;

                    temp->x = i;
                    temp->y = j;
                    temp->nowboard = hi->nowboard;
                    (temp->nowboard)[i][j] = person;

                    //(hi->next).push_back(temp);
                    next.push_back(temp);

                    check[i][j] = -1;
                }
            }
        }
    }
    return next;
}

int maxpoint = 0;
int howmany = 0;

/*
Node *maketree(Node *now)
{
    if (now->level >= 2)
    {
        if (maxpoint < now->point)
        {
            maxpoint = now->point;

            remx = now->x;
            remy = now->y;
        }

        return now;
    }

    now = nextstep(2 - ((now->level - 1) % 2), now->x, now->y, now);

    for (int i = 0; i < (now->next).size(); i++)
    {
        (now->next)[i] = maketree((now->next)[i]);
    }

    return now;
}*/

int remx = 7;
int remy = 7;
vector<vector<int>> remnum;

int newmaketree(Node *now, int depth, int a, int b, int person, vector<Node *> next) // make tree
{
    // vector<Node *> nownext = next;

    if (depth == 3)
    {
        int hnum = countpoint(now->nowboard, player);

        // std::cout << (now->x) << " " << (now->y) << " " << hnum << std::endl;

        // delete now;
        return hnum;
    }

    next = newnextstep(depth, person, now, next);

    if (person == player)
    {
        int value = -20000000, back = 0;

        for (auto i : next)
        {
            back = newmaketree(i, depth - 1, a, b, 3 - person, next);

            /*five = 0;
            four = 0;
            four1 = 0;
            tthree = 0;
            five_e = 0;
            four_e = 0;
            four1_e = 0;
            tthree_e = 0;

            for (int ik = 0; ik < 15; ik++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((i->nowboard)[ik][j] == player)
                    {
                        same3(player, ik, j, 1, 1, i->nowboard);
                        same3(player, ik, j, 1, 0, i->nowboard);
                        same3(player, ik, j, 1, -1, i->nowboard);
                        same3(player, ik, j, -1, 0, i->nowboard);
                    }
                    else if((i->nowboard)[ik][j] == 3 -player)
                    {
                        same3(3-player, ik, j, 1, 1, i->nowboard);
                        same3(3-player, ik, j, 1, 0, i->nowboard);
                        same3(3-player, ik, j, 1, -1, i->nowboard);
                        same3(3-player, ik, j, -1, 0, i->nowboard);
                    }
                }
            }

            if (five > 0)
            {
                back =max(back, 1000000);
                //back = 1000000;
            }
            else if (five_e > 0)
            {
                back =max(back, -10000000);
                //back = -1000000;
            }
            else if (four_e > 0 || four1_e > 0)
            {
                back =max(back, -9000000);
                //back = 900000;
            }
            else if (four > 0 || four1 > 0)
            {
                back =max(back, 9000000);
                //back = -900000;
            }
            else if (tthree_e > 0)
            {
                back =max(back, -8000000);
                //back = -800000;
            }
            else if (tthree > 1)
            {
                back =max(back, 8000000);
                //back = 800000;
            }*/

            if (depth == 4)
            {
                 //std::cout << (i->x) << " " << (i->y) << " " << back << std::endl;
            }

            if (back > value)
            {
                value = back;

                if (depth == 4)
                {
                    remnum.clear();
                    remnum.push_back({(i->x), (i->y)});

                    //std::cout << "great" << std::endl;
                }
            }
            else if (back == value && depth == 4)
            {
                //std::cout << "same" << std::endl;
                remnum.push_back({(i->x), (i->y)});
            }

            a = max(a, value);

            if (a >= b)
            {
                 break;
            }
        }
        // delete now;
        return value;
    }
    else if (person == 3 - player)
    {
        int value = 20000000, back = 0;

        for (auto i : next)
        {
            back = newmaketree(i, depth - 1, a, b, 3 - person, next);

            /*five = 0;
            four = 0;
            four1 = 0;
            tthree = 0;
            five_e = 0;
            four_e = 0;
            four1_e = 0;
            tthree_e = 0;

            for (int ik = 0; ik < 15; ik++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((i->nowboard)[ik][j] == player)
                    {
                        same3(player, ik, j, 1, 1, i->nowboard);
                        same3(player, ik, j, 1, 0, i->nowboard);
                        same3(player, ik, j, 1, -1, i->nowboard);
                        same3(player, ik, j, -1, 0, i->nowboard);
                    }
                    else if((i->nowboard)[ik][j] == 3-player)
                    {
                        same3(3-player, ik, j, 1, 1, i->nowboard);
                        same3(3-player, ik, j, 1, 0, i->nowboard);
                        same3(3-player, ik, j, 1, -1, i->nowboard);
                        same3(3-player, ik, j, -1, 0, i->nowboard);
                    }
                }
            }

            if (five_e > 0)
            {
                back =min(back, 10000000);
                //back = 1000000;
            }
            else if (five > 0)
            {
                back =min(back, -10000000);
                //back = -1000000;
            }
            else if (four > 0 || four1 > 0)
            {
                back =min(back, -9000000);
                //back = -900000;
            }
            else if (four_e > 0 || four1_e > 0)
            {
                back =min(back, 9000000);
                //back = 900000;
            }
            else if (tthree > 0)
            {
                back =min(back, -8000000);
                //back = -800000;
            }
            else if (tthree_e > 1)
            {
                back =min(back, 8000000);
                //back = 800000;
            }*/

            value = min(value, back);
            b = min(b, value);

            if (depth == 3)
            {
                 /*std::cout  << "     " << (i->x) << " " << (i->y) << " " << back << std::endl;
                for (int ik = 0; ik < SIZE; ik++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        std::cout << (i->nowboard)[ik][j] << " ";
                    }
                    std::cout << std::endl;
                }*/
            }

            if (a >= b)
            {
                 break;
            }
        }

        // delete now;
        return value;
    }

    // delete now;
    return 0;
}

void read_board(std::ifstream &fin)
{
    fin >> player;
    // enemy = 3 - player;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            fin >> board[i][j];
        }
    }
}

void write_valid_spot(std::ofstream &fout)
{
    srand(time(NULL));

    //   Keep updating the output until getting killed.

    // while (true)
    {
        int x, y;
        vector<Node *> next;
        Node *head = new Node;

        head->x = 0;
        head->y = 0;
        head->nowboard = board;

        // remx = 7;
        // remy = 7;

        x = newmaketree(head, 4, -20000000, 20000000, player, next);

        if (remnum.size() != 0)
        {
            int r = rand() % remnum.size();
            x = remnum[r][0];
            y = remnum[r][1];
        }
        else
        {
            x = 7;
            y = 7;
        }

        // Choose a random spot.

        if (is_spot_on_board(x, y) && board[x][y] == EMPTY)
        {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
        else
        {
            while (board[x][y] != EMPTY)
            {
                x = (rand() % SIZE);
                y = (rand() % SIZE);
            }

            // x = y = 0;

            fout << x << " " << y << std::endl;
            fout.flush();
        }
    }
}

int main(int, char **argv)
{
    // std::cout << "hi" << std::endl;
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}