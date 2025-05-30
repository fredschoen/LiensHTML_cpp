//============================================================================
// Name        : ParseVCard.cpp
// Author      : F SCHOEN
// Version     : 41212a
// Copyright   : F SCHOEN
// Description : conversion aller et retour Vcf/Csv
//============================================================================
// fonctions:
// void fTxtVersHtml(void)
//    la 1ère ligne conitent 'texteCherche'
//============================================================================

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;

string nomFicEntree="";
string nomFicSortie="";

string nom1="liensHTML";

string texteCherche="";
string colonne1="";
string colonne2="";

//============================================================================
void fTxtVersHtml(void) {
	//============================================================================
	std::cout << "exec fTxtVersHtml" << endl;

	cout << "nomFicEntree=[" << nomFicEntree << "]" << endl;
	cout << "nomFicSortie=[" << nomFicSortie << "]"<< endl;

	std::ifstream ficEntree (nomFicEntree); // prendre un fichier ANSI (binary ne change pas le pb UTF8)
	std::ofstream ficSortie (nomFicSortie);

	//std::ifstream ficEntree (nomFicEntree, std::ios::binary); (binary ne change pas le pb UTF8)
	string ligneEntree="";

	if  (!ficEntree){
		cout << "ERREUR: Impossible d'ouvrir ficEntree " << nomFicEntree<< endl;
		return;
	}
	if  (!ficSortie){
		cout << "ERREUR: Impossible d'ouvrir ficSortie " << nomFicSortie<< endl;
		ficEntree.close();
		return;
	}

	ficSortie	<< "<html>"<< endl;
	ficSortie	<< "<body>"<< endl;
	ficSortie	<< "<table border='1'>"<< endl;

	// la 1ère ligne conitent 'texteCherche'
	getline(ficEntree, texteCherche); 
	cout << "fTxtVersHtml, texteCherche=<" << texteCherche  << ">" << endl;
	
	//suite
	string colonne2="";
	int pos=0;
	
	while(getline(ficEntree, ligneEntree)) {

		//<<<<<<<<<colonne1 ou colonne2 <<<<<<<<<<<<<<<<<
		pos = ligneEntree.find(texteCherche);
		if (pos < 0 ) {
			//<<<<<<<<<ecrire colonne 1 memorisée et seule
			if (colonne1.length()>0){
				cout << "fTxtVersHtml, colonne1 seule=" << colonne1 <<  endl;
				ficSortie	<< "<tr>" << endl;
				ficSortie	<< "<td  colspan='2'>" << endl;
				ficSortie	<< colonne1 << endl;
				ficSortie	<< "</td>" << endl;
				ficSortie	<< "</tr>"<< endl;

			}
			//<<<<<<<<<memo colonne 1 pour le coup d'apres
			colonne1 = ligneEntree;
			cout << "fTxtVersHtml, colonne1=" << colonne1 << endl;
		}
		else {
			//<<<<<<<<<ecrire colonne 1 et colonne2 
			colonne2 = ligneEntree.substr(pos+ texteCherche.length(), ligneEntree.length());
			cout << "fTxtVersHtml, colonne2=" << colonne2 << " ; colonne1=" << colonne1 << endl;
			ficSortie	<< "<tr>" << endl;
			ficSortie	<< "<td width='400'>" << endl;
			ficSortie	<< colonne1 << endl;
			ficSortie	<< "</td>" << endl;
			ficSortie	<< "<td>" << endl;
			ficSortie	<< "<a href='" << ligneEntree  << "' target='fenetre F1'>" << colonne2 << "</a>" << "<br>" << endl;
			ficSortie	<< "</td>"<< endl;
			ficSortie	<< "</tr>"<< endl;
			//<<<<<<<<<raz colonne 
			colonne1 = "";
		}
		
	}

	ficSortie	<< "</table>"<< endl;
	ficSortie	<< "</body>"<< endl;
	ficSortie	<< "</html>"<< endl;

	ficEntree.close();
	ficSortie.close();
	cout << "fTxtVersHtml, nomFicEntree=" << nomFicEntree << " nomFicSortie=" << nomFicSortie << " : OK !!!!!!!!!" << endl;
	return;
}


//============================================================================
string fChoixNomFic() {
//============================================================================
    int val=0;
    string sNomFic="";

    cout << "choix du nom des fichiers vcf et csv'" << std::endl
			<< "1 : '" << nom1 << ".*'" << std::endl
			<< "2.autre nom " << std::endl
			<< "9.sortie " << std::endl
			;

    cin >> val;

    	if (val == 1) {
    		sNomFic=nom1;
    	} else if (val == 2) {
    	    cout << "quels autres fichiers ? " << std::endl;
    		cin >> sNomFic;
    	} else if (val == 9) {
        	sNomFic="";
    	}

	return sNomFic;

}

//============================================================================
int main(void) {
//============================================================================
    std::cout << "SALUT FRED (2024 12 12)"
			  << std::endl;

    string sNomFic = "";

    int val=0;

    while (val<9) {

    	sNomFic = fChoixNomFic();

    	if (sNomFic.length()>0) {
			cout << "1 txt->html " << sNomFic << std::endl
				 << "9.sortie" << std::endl
				 ;
			cin >> val;
    	}
    	else { // sortir
			val=9;
    	}
		string prefixeNomFichier;
		prefixeNomFichier="./data/";
    	if (val == 1) {
        	nomFicEntree= prefixeNomFichier + sNomFic+".txt";
        	nomFicSortie= prefixeNomFichier + sNomFic+".fTxtVersHtml.html";
        	fTxtVersHtml();
    	}
    }

    cout << "CIAO FRED" << endl;

    return EXIT_SUCCESS;
}
