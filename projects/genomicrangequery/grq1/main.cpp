#include <iostream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "stlaux/vecaux.h"
#include "benchmarklib/benchmarklib.h"

using namespace std;

vector<int> solution(vector<int> &vec, vector<int> &P, vector<int> &Q)
{
    vector<int> sol;
    sol.resize(P.size());
    for (unsigned int i=0; i<P.size(); i++) {
        int mv = 5;
        for (int j=P[i]; j<=Q[i]; j++) {
            mv = min(mv, vec[j]);
        }
        sol[i] = mv;
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
