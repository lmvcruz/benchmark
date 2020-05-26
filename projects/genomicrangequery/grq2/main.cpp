#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "stlaux/vecaux.h"
#include "benchmarklib/benchmarklib.h"

using namespace std;

static int recCount = 0;

class DoubleKeyMap
{
public:
    DoubleKeyMap() = default;

    void set(int k1, int k2, int v)
    {
        m_map[pair<int,int>(k1,k2)] = v;
    }

    int get(int k1, int k2) {
        return m_map[pair<int,int>(k1,k2)];
    }

    bool contains(int k1, int k2) {
        pair<int,int> key(k1,k2);
        return (m_map.find(key)!=m_map.end());
    }

private:
    map<pair<int,int>, int> m_map;
};

int recSolution(DoubleKeyMap &map, vector<int> &vec, int p, int q, int c)
{
    recCount++;
    if (c==p) return vec[p];
    if (map.contains(p,c)) return map.get(p,c);
    //
    int pc1;
    if (!map.contains(p,c-1)) {
        pc1 =  recSolution(map, vec, p, q, c-1);
        map.set(p, c-1, pc1);
    }
    else {
        pc1 = map.get(p,c-1);
    }
    int v = min(vec[c], pc1);
    map.set(p,c,v);
    return v;
}

vector<int> solution(vector<int> &vec, vector<int> &p, vector<int> &q)
{
    DoubleKeyMap map;
    vector<int> sol;
    sol.resize(p.size());
    for (unsigned int i=0; i<p.size(); i++) {
        sol[i] = recSolution(map, vec, p[i], q[i], q[i]);
    }
    return sol;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Benchmark");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("vec", QCoreApplication::translate("main", "...."));
    parser.addPositionalArgument("p", QCoreApplication::translate("main", "...."));
    parser.addPositionalArgument("q", QCoreApplication::translate("main", "....."));

    parser.process(app);
    QStringList args = parser.positionalArguments();
    //
    vector<int> vec = string2vecint(args[0]);
    vector<int> p = string2vecint(args[1]);
    vector<int> q = string2vecint(args[2]);
    vector<int> sol = solution(vec, p, q);
    showVector(sol);
    //
    return 0;
}
