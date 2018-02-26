#include<iostream>
#include "SimpleMC8.h"
#include "Vanilla3.h"
#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include "AntiThetic.h"

#include "ParkMiller.h"
#include "BoxMuller.h"
#include "Fishman.h"

#include "BlackScholesFormulas.h"
#include "LEcuyer.h"

#include "LEcuyer.h"
#include "BoxMullerLE.h"
#include "FishmanLE.h"

#include <fstream>
using namespace std;

int main()
{

	double Expiry = 1;
	double Strike = 110; 
	double Spot = 100; 
	double Vol = 0.3; 
	double r = 0.05; 
	unsigned long NumberOfPaths = 10000;

	
	cout << "\nClosed-form option price = " << BlackScholesCall(Spot, Strike, r, 0, Vol, Expiry)<<"\n";


    PayOffCall thePayOff(Strike);
    VanillaOption theOption(thePayOff, Expiry);
    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

	// MC option price with LEcuyer uniform generator and inverse distribution normal generator

	StatisticsMean gathererL;
	ConvergenceTable gathererTwoL(gathererL);
	RandomLEcuyer generatorL(1);
	generatorL.Reset();
	AntiThetic GenTwoL(generatorL);

	SimpleMonteCarlo6(theOption,
		Spot,
		VolParam,
		rParam,
		NumberOfPaths,
		gathererTwoL,
		GenTwoL);

	vector<vector<double> > results0 = gathererTwoL.GetResultsSoFar();

	cout << "\nMC option price with LEcuyer uniform generator = " << results0[results0.size()-1][0] << "\n";

	// all generators below are driven by Park-Miller uniform generator

	// MC option price with inverse distribution normal generator

    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);
    RandomParkMiller generator(1);
	generator.Reset();
	AntiThetic GenTwo(generator);

	SimpleMonteCarlo6(theOption,
                                      Spot, 
                                      VolParam,
                                      rParam,
                                      NumberOfPaths,
                                      gathererTwo,
                                      GenTwo);

    vector<vector<double> > results1 =gathererTwo.GetResultsSoFar();

	cout << "\nMC option price with Park-Miller uniform uniform generator = " << results1[results1.size() - 1][0] << "\n";

	cout <<"\nFor the MC option price with inverse distribution normal generator are \n";

    for (unsigned long i=0; i < results1.size(); i++)
    {
        for (unsigned long j=0; j < results1[i].size(); j++)
            cout << results1[i][j] << " ";

        cout << "\n";
    }

	
	// MC option price with Box-Muller normal generator
	StatisticsMean gatherer2;
	ConvergenceTable gathererTwo2(gatherer2);

	RandomBoxMuller generator2(1);
	//generator2.Reset();
	AntiThetic GenTwo2(generator2);

	SimpleMonteCarlo6(theOption,
		Spot,
		VolParam,
		rParam,
		NumberOfPaths,
		gathererTwo2,
		generator2);

	vector<vector<double> > results2 = gathererTwo2.GetResultsSoFar();

	cout << "\nFor the MC option price with Box-Muller normal generator are \n";
	for (unsigned long i = 0; i < results2.size(); i++)
	{
		for (unsigned long j = 0; j < results2[i].size(); j++)
			cout << results2[i][j] << " ";

		cout << "\n";
	}
	

	// MC option price with Fishman normal generator 

	StatisticsMean gatherer3;
	ConvergenceTable gathererTwo3(gatherer3);

	RandomFishman generator3(1);
	//generator3.Reset();
	AntiThetic GenTwo3(generator3);

	SimpleMonteCarlo6(theOption,
		Spot,
		VolParam,
		rParam,
		NumberOfPaths,
		gathererTwo3,
		generator3);

	vector<vector<double> > results3 = gathererTwo3.GetResultsSoFar();

	cout << "\nFor the MC option price with Fishman normal generator are \n";
	for (unsigned long i = 0; i < results3.size(); i++)
	{
		for (unsigned long j = 0; j < results3[i].size(); j++)
			cout << results3[i][j] << " ";

		cout << "\n";
	}

	

	/*
	ofstream MyExcelFile;
	MyExcelFile.open("Data.csv");

	unsigned long NumberOfSample = 1000;

	MJArray IDPMdata(NumberOfSample);
	RandomParkMiller IDPMgenerator(NumberOfSample);
	IDPMgenerator.GetGaussians(IDPMdata);

	MJArray BMPMdata(NumberOfSample);
	RandomBoxMuller BMPMgenerator(NumberOfSample);
	BMPMgenerator.GetGaussians(BMPMdata);

	MJArray FPMdata(NumberOfSample);
	RandomFishman FPMgenerator(NumberOfSample);
	FPMgenerator.GetGaussians(FPMdata);

	MJArray IDLEdata(NumberOfSample);
	RandomLEcuyer IDLEgenerator(NumberOfSample);
	IDLEgenerator.GetGaussians(IDLEdata);

	MJArray BMLEdata(NumberOfSample);
	RandomBoxMullerLE BMLEgenerator(NumberOfSample);
	BMLEgenerator.GetGaussians(BMLEdata);

	MJArray FLEdata(NumberOfSample);
	RandomFishmanLE FLEgenerator(NumberOfSample);
	FLEgenerator.GetGaussians(FLEdata);

	MyExcelFile << "Inverse Distribution Normal with Park Miller" << ",";
	MyExcelFile << "Box Muller Normal with Park Miller" << ",";
	MyExcelFile << "Fishman Normal with Park Miller)" << ",";
	MyExcelFile << "Inverse distribution Normal with LEcuyer" << ",";
	MyExcelFile << "Box Muller Normal with LEcuyer" << ",";
	MyExcelFile << "Fishman Normal with LEcuyer";
	MyExcelFile << endl;

	for (unsigned long i = 0; i<NumberOfSample; i++) {
		MyExcelFile << IDPMdata[i] << ",";
		MyExcelFile << BMPMdata[i] << ",";
		MyExcelFile << FPMdata[i] << ",";
		MyExcelFile << IDLEdata[i] << ",";
		MyExcelFile << BMLEdata[i] << ",";
		MyExcelFile << FLEdata[i] << ",";
		MyExcelFile << endl;
	}

	MyExcelFile.close();
	*/

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

