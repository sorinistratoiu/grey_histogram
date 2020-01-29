/**************************
~ PRELUCRAREA IMAGINILOR ~
***************************/
// App_Name : histogram_grey.cpp
// Student : Istratoiu Sorin

// Lib. Folosita : OpenCV
// Limbaj : C++

/*
Tema : 21
Elaborati in C / C++ si testati pe imaginile de test procedura 
histo de calcul a histogramei unei imagini cu niveluri multiple de gri.
Procedura trebuie sa genereze graficul histogramei si sa furnizeze date statistice precum:
valoarea medie,mediana,deviatia standard.
*/

#include "opencv2\opencv.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;



//Variabile globale
int niv_gri[255];//vector in care se retin nr de pixel pt fiecare nivel de gri
int highest = 0;//valoarea maxima din vectorul niv_gri
float histo[255];//vector in care se normalizeaza valorile din niv_gri
float variance[255];//vector pt calculul variantei
long rezolutie = 1;


double medie_aritmetica(int niv_gri[255]) {//functie pt calculul mediei aritmetice pt un vector de tip int
	long suma = 0;
	double medie;
	for (int i = 0; i <= 255; i++)
		suma = suma + niv_gri[i];
	medie = suma / 256.00;
	
	return medie;
}

double medie_aritmetica(float variance[255]) {//functie pt calculul mediei aritmetice pt un vector de tip float
	long suma = 0;
	double medie;
	for (int i = 0; i <= 255; i++)
		suma = suma + variance[i];
	medie = suma / 256.00;

	return medie;
}



int mediana(int niv_gri[255]) {//functie pt calculul medianei

	long suma = 0;//variabila care retine suma
	long suma2 = 0;//variabila care retine suma
	double medie;//variabila care retine jumatate din suma
	for (int i = 0; i <= 255; i++)
		suma = suma + niv_gri[i];
	medie = suma / 2.00;
	suma = 0;//reinitializare suma cu 0
	for (int i = 0; i <= 255; i++) {//se calculeaza suma de la primul termen pana cand
		suma2 = suma2 + niv_gri[i];//suma este egala cu medie
		if (suma2 >= medie)//iar termenul la care se opreste iteratia
			return i;//este mediana
		
	}
	
}

float deviatie_standard(double medie_a) {//functie care calculeaza deviatia standard
	float result;
	for (int i = 0; i <= 255; i++)
		variance[i] = medie_a;//se initializeaza vectorul variance cu media aritmetica a vectorului niv_gri
	for (int i = 0; i <= 255; i++)
		variance[i] = niv_gri[i] - variance[i];//se scade din vectorul niv_gri vectorul variance si se  mem in variance
	for (int i = 0; i <= 255; i++)
		variance[i] = variance[i] * variance[i];//se ridica la patrat fiecare valoare din variance
	result = medie_aritmetica(variance);//in result se memoreaza varianta adica media aritmetica a vectorului variance
	return sqrt(result);//deviatia standard este rad patrata din varianta

}

//main
int main() {

	for (int i = 0; i <= 255; i++)//initializare vector niv_gri cu 0
		niv_gri[i] = 0;

	Mat img = imread("img.jpg",CV_LOAD_IMAGE_GRAYSCALE);//incarcarea imaginii ca imagine alb-negru
	namedWindow("preview", WINDOW_NORMAL);//declarare fereastra preview pt afisarea imaginii incarcate
	imshow("preview", img);//afisarea imaginii incarcate
	//waitKey(0);

	rezolutie = img.cols * img.rows;

	//parcurgerea imaginii pixel cu pixel si incarcarea vectorului niv_gri cu nr de pixeli pt fiecare valoare de gri
	for (int r = 0; r < img.rows; r++) {
		for (int c = 0; c < img.cols; c++) {
			niv_gri[img.at<uint8_t>(r, c)]++;
		}
	}


	//stabilirea celui mai mare numar de pixeli pe un nivel;
	for (int i = 0; i <= 255; i++)
		if (niv_gri[i] > highest)
			highest = niv_gri[i];


	//normalizarea valorilor pt a avea un maxim de 100
	for (int i = 0; i <= 255; i++)
		histo[i] = niv_gri[i] * 10000 / rezolutie;
	
	//declararea unei imagini albe 150*256 pt afisarea graficului
	Mat HistPlot(150, 256, CV_8UC3, Scalar(0 , 0, 0));
	
	
	//trasarea liniilor pe noua imagine reprezentand valorile din vectorul histo
	for (int i = 0; i < 256; i++)
	{
		if (i == mediana(niv_gri)) {
			line(HistPlot, Point(i, 150), Point(i, 150 - histo[i]), Scalar( 66, 66, 244), 1, 8, 0);
			//mediana este afisata ca o linie rosie
		}
		else
		line(HistPlot, Point(i, 150), Point(i, 150 - histo[i]), Scalar(255, 255, 255), 1, 8, 0);
		
	}
	
	namedWindow("Histogram");//declararea unei ferestre pt afisarea graficului
	
	imshow("Histogram", HistPlot);//afisarea graficului
	
	imwrite("graph.jpg",HistPlot);

	cout << "Valoare medie: " << medie_aritmetica(niv_gri);//afisarea valorii medie
	
	cout << "\nMediana: " << mediana(niv_gri);//afisarea medianei
	
	cout << "\nDeviatia standard: " << deviatie_standard(medie_aritmetica(niv_gri));//afisarea deviatiei standard
	waitKey(0);

	
}//end main
