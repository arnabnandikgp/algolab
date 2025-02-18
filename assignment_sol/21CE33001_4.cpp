#include <iostream>

using namespace std;

// vc votecount for each party
// pp party pointer
// vr vote remaining
// tot_p total number of parties

void print(int *coalition, int v, int *vc, int p, int siz_col)
{
    int sum = 0;
    int tot_sum = 0;
    for (int i = 0; i < siz_col; i++)
    {
        if (coalition[i] >= 0)
        {
            sum += vc[coalition[i] - 1];
        }
    }
    for (int i = 0; i < p; i++)
    {
        tot_sum += vc[i];
    }
    if (sum >= (v + 2) / 2 && tot_sum == v)
    {
        for (int i = 0; i < p; i++)
        {
            cout << i + 1 << ":" << vc[i] << "  ";
        }
        cout << "  Total votes for the coalition:" << sum << "\n";
    }
}
void vote_dist(int *coalition, int *vc, int pp, int vr, int v, int tot_p, int siz_col)
{
    if ((pp >= tot_p) || vr == 0)
    {
        print(coalition, v, vc, tot_p, siz_col);
        return;
    }
    int *nvc = new int[tot_p];
    for (int i = 0; i < tot_p; i++)
    {
        nvc[i] = vc[i];
    }
    vc[pp]++;
    vote_dist(coalition, vc, pp, vr - 1, v, tot_p, siz_col);
    vote_dist(coalition, nvc, pp + 1, vr, v, tot_p, siz_col);
}
// vc should be initialized to zero
int main()
{
    int v, p;
    cout << "#Voters: ";
    cin >> v;
    cout << "#Parties: ";
    cin >> p;

    cout << "Coalition: ";
    cout << "\n";
    int *coalition = new int[p];
    int siz = 0;
    for (int i = 0; i < p; i++)
    {
        int inp;
        cin >> inp;
        if (inp != -1)
        {
            coalition[i] = inp;
            siz++;
        }
        else
        {
            break;
        }
    }
    int siz_col = siz;
    cout << "\n";

    int *vc = new int[p];
    for (int i = 0; i < p; i++)
    {
        vc[i] = 0;
    }
    vote_dist(coalition, vc, 0, v, v, p, siz_col);

    return 0;
}