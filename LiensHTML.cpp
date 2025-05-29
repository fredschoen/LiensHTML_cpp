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
int finFic=0;

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
	ficSortie	<< "<table>"<< endl;

	// la 1ère ligne conitent 'texteCherche'
	getline(ficEntree, texteCherche); 
	cout << "fTxtVersHtml, texteCherche=<" << texteCherche  << ">" << endl;
	
	//suite
	string colonne2="";
	int pos=0;
	
	while(getline(ficEntree, ligneEntree)) {

		//<<<<<<<<<colonne1 ou colonne2 <<<<<<<<<<<<<<<<<
		pos = ligneEntree.find(texteCherche);
		cout << "colonne1: pos=" << pos << " ; ligneEntree=" << ligneEntree << endl;
		if (pos < 0 ) {
			colonne1 = ligneEntree;
			colonne2 = "";
		}
		else {
			colonne1 = "";
			colonne2 = ligneEntree.substr(pos+ texteCherche.length(), ligneEntree.length());
		}
		
		//<<<<<<<<<colonne2<<<<<<<<<<<<<<<<<
		finFic=0;
		while ((pos < 0) && (finFic == 0)) {

			if (getline(ficEntree, ligneEntree)){
				pos = ligneEntree.find(texteCherche);
				cout << "(while) pour colonne2: pos=" << pos << " ; ligneEntree=" << ligneEntree << endl;
				if (pos < 0 ) {
					//<<<<<<<<<assemblage d'une ligne "pur texte" <<<<<<<<<<<<<<<<<
					ficSortie	<< "<tr>" << endl;
					ficSortie	<< "<td>" << endl;
					ficSortie	<< colonne1 << endl; //recupéré du coup d'avant
					ficSortie	<< "</td>" << endl;
					ficSortie	<< "<td>" << endl;
					ficSortie	<< "</td>"<< endl;
					ficSortie	<< "</tr>"<< endl;
					//<<<<<<<<<et recup de la nouvelle colonne1 <<<<<<<<<<<<<<<<<
					colonne1 = ligneEntree; // pour le coup d'apès
					cout << "(while) nouvelle colonne1=" << colonne1  << endl;
				}
				else {
					//on a la colonne2
					colonne2 = ligneEntree.substr(pos+ texteCherche.length(), ligneEntree.length());
					cout << "(while) colonne2: pos=" << pos << " ; ligneEntree=" << ligneEntree << endl;
				}
			}
			else {
				pos=-1;
				finFic=1;
				cout << "(while) finFic=" << finFic << endl;
			}
		}
		
		if (!(pos < 0)) {

			//<<<<<<<<<assemblage de 2 colonnes <<<<<<<<<<<<<<<<<
			cout << "fTxtVersHtml, colonne1=" << colonne1 << " ; colonne2=" << colonne2 << endl;
			ficSortie	<< "<tr>" << endl;
			ficSortie	<< "<td>" << endl;
			ficSortie	<< colonne1 << endl;
			ficSortie	<< "</td>" << endl;
			ficSortie	<< "<td>" << endl;
			ficSortie	<< "<a href='" << ligneEntree  << "' target='fenetre F1'>" << colonne2 << "</a>" << "<br>" << endl;
			ficSortie	<< "</td>"<< endl;
			ficSortie	<< "</tr>"<< endl;
		}
	}

	cout << "fTxtVersHtml, nomFicEntree=" << nomFicEntree << " nomFicSortie=" << nomFicSortie << " : OK !!!!!!!!!" << endl;
	ficSortie	<< "</table>"<< endl;
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
