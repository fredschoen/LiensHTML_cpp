//============================================================================
// Name        : ParseVCard.cpp
// Author      : F SCHOEN
// Version     : 41212a
// Copyright   : F SCHOEN
// Description : conversion aller et retour Vcf/Csv
//============================================================================
// fonctions:
// void fTxtVersHtml(void)
//============================================================================

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;

string nomFicEntree="";
string nomFicSortie="";

string nom1="liensHTML";

string texteCherche="";

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

	// 1ère ligne = texteCherche
	getline(ficEntree, texteCherche); 
	
	//suite
	string libelle="";
	int pos=0;
	
	while(getline(ficEntree, ligneEntree)) {

		pos = ligneEntree.find(texteCherche);
		cout << pos << endl;
		if (pos < 0 ) {
			ficSortie	<< ligneEntree << "<br>" << endl;
		}
		else {
			libelle = ligneEntree.substr(pos+ texteCherche.length(), ligneEntree.length());
			ficSortie	<< "<a href='"<< ligneEntree  << "' target='fenetre F1'>" << libelle << "</a>" << "<br>" << endl;
	}
		cout << "fTxtVersHtml, ligneEntree=" << ligneEntree << endl;
	}

	cout << "fTxtVersHtml, nomFicEntree=" << nomFicEntree << " nomFicSortie=" << nomFicSortie << " : OK !!!!!!!!!" << endl;
	ficSortie	<< "</body>"<< endl;
	ficSortie	<< "</html>"<< endl;

	ficEntree.close();
	ficSortie.close();
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
