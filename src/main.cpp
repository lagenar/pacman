#include "PacmanMain.h"

#include "PacmanHeuristics.h"
#include "PacmanRTAPathfinder.h"

#include "fstream"

using namespace std;


int main(int argc, char * argv[])
{
	vector<pair<HeuristicEvaluation, string> > heuristics;

	heuristics.push_back(make_pair(&h1, "Heuristica1"));
	heuristics.push_back(make_pair(&h2, "Heuristica2"));
	heuristics.push_back(make_pair(&h3, "Heuristica3"));
	heuristics.push_back(make_pair(&h4, "Heuristica4"));
	heuristics.push_back(make_pair(&h5, "Heuristica5"));
	heuristics.push_back(make_pair(&h6, "Heuristica6"));

	string filename = "";

	if (argc > 1) {
		if (argc == 2) {
			fstream file(argv[1]);
			if (file.is_open()) {
				filename = argv[1];
				cout << "Se habilitara la opcion para reproducir la solucion: " << filename << "\n\n";
			} else {
				cout << "No se pudo abrir el archivo de la solucion: " << argv[1] << "\n\n";
			}
		} else {
			cout << "Numero de argumentos incorrecto\n\n";
		}
	}

	runPacman(new PacmanRTAPathfinder(), heuristics, filename);

	return 0;
}

