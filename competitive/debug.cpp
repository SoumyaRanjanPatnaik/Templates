#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <strstream>
#include <iomanip>
using namespace std;

int NUM_TESTS = 0;

class Contraints
{
public:
    enum Type
    {
        LL,
        DB
    };
    void set_type(Type t)
    {
        this->type = t;
    }
    void input_lval(stringstream &ss)
    {
        if (type == LL)
        {
            long long temp;
            ss >> temp;
            l_contraint.l = temp;
        }
        else
        {
            double temp;
            ss >> temp;
            l_contraint.f = temp;
        }
    }
    void input_rval(stringstream &ss)
    {
        if (type == LL)
        {
            long long temp;
            ss >> temp;
            r_contraint.l = temp;
        }
        else
        {
            double temp;
            ss >> temp;
            r_contraint.f = temp;
        }
    }

    Type get_type()
    {
        return type;
    }
    void set_num(long long n)
    {
        num = n;
    }
    long long get_num()
    {
        return num;
    }

    union Data
    {
        double f;
        long long l;
    };
    Data r_contraint;
    Data l_contraint;
    Contraints()
    {
        precision = 0;
        num = 0;
        l_contraint.l = 0;
        l_contraint.f = 0;
        r_contraint.l = 0;
        r_contraint.f = 0;
        type = LL;
    }
    int precision;
    long long num;

private:
    Type type;
};

void parse(stringstream &ss, string str, vector<Contraints> &v)
{
    ss.clear();
    ss.str(str);
    string word;
    ss >> word;
    Contraints curr_val;
    if (word.compare("") == 0)
    {
        return;
    }
    if (word[0] == 'i' || word[0] == 'l')
    {
        curr_val.set_type(Contraints::Type::LL);
    }
    else if (word[0] == 'd' || word[0] == 'f')
    {
        int p;
        ss >> p;
        curr_val.precision = p;
        curr_val.set_type(Contraints::Type::DB);
    }
    curr_val.input_lval(ss);
    curr_val.input_rval(ss);
    ss>>word;
    //if(word[0] = 'n') {
        
    //}
    //else {
        
    //}
    ss>>curr_val.num;
    v.push_back(curr_val);
}

void write_int_test(ofstream &fout, long long n, long long l, long long r)
{
    for (long long i = 0; i < n; i++)
    {
        long long val;
        val = l + rand() % (r - l);
        fout << val << " ";
    }
    fout << endl;
}
void write_double_test(ofstream &fout, long long n, long long l, long long r, int p)
{
    for (long long i = 0; i < n; i++)
    {
        double val;
        val = l + (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * (r - l);
        fout << setprecision(p);
        fout << val << " ";
    }
    fout << endl;
}

void write_test_lines(ofstream &fout, vector<Contraints> constraint_vec)
{
    for (auto c : constraint_vec)
    {
        if (c.get_type() == Contraints::LL)
        {
            write_int_test(fout, c.get_num(), c.l_contraint.l, c.r_contraint.l);
        }
        else
        {
            write_double_test(fout, c.get_num(), c.l_contraint.l, c.r_contraint.l, c.precision);
        }
    }
}

int main()
{
    stringstream ss;
    ifstream fin("format.txt", ios::in);
    ofstream fout("tests.txt");
    fout << fixed;
    vector<Contraints> format;
    string curr;
    fin >> curr;
    NUM_TESTS = atoi(curr.c_str());
    fout << NUM_TESTS << endl;
    while (!fin.eof())
    {
        getline(fin, curr);
        parse(ss, curr, format);
    }
    while (NUM_TESTS--)
    {
        write_test_lines(fout, format);
    }
    fin.close();
    fout.close();
}
