// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "CreadorLuces.h"

TArray <ALuz*> UCreadorLuces::ParsearArchivoLuces(UObject* Context)
{
	// Definiciones e inicializaciones
	vector <vector <string> > data;
	TArray<ALuz*> lucesCreadas;

	FString replaceIn = "/Saved/Config/Windows/Game.ini";
	FString replaceOut = "/archivoLuces.txt";
	FString FilePath;
	FilePath = GGameIni.Replace(*replaceIn, *replaceOut);

	std::string fString(TCHAR_TO_UTF8(*FilePath));

	ifstream infile(fString);
	UWorld* World = GEngine->GetWorldFromContextObject(Context);
	FVector ubicacionLuz;
	FRotator rotacionLuz;
	FTransform ActorTransform = FTransform(ubicacionLuz);
	FLinearColor color;
	ALuz* actorLuz = NULL;
	ALuzFocal* luzFocal;
	int tipoLuz;
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float colR;
	float colG;
	float colB;
	float intensidad;
	float anguloConoInterior;
	float anguloConoExterior;
	int luzProcesando = 1;
	bool errorLuz = false;

	// Loop de lineas del archivo
	while (infile)
	{
		errorLuz = false;
		string s;
		if (!getline(infile, s)) break;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s.c_str());
		istringstream ss(s);
		vector <string> record;

		// Loop de datos de cada linea
		while (ss)
		{
			string s;
			if (!getline(ss, s, ',')) break;
			record.push_back(s);
		}

		// Transformo atributos y creo luz
		tipoLuz = atoi(record.at(0).c_str());
		posX = atof(record.at(1).c_str());
		posY = atof(record.at(2).c_str());
		posZ = atof(record.at(3).c_str());
		rotX = atof(record.at(4).c_str());
		rotY = atof(record.at(5).c_str());
		rotZ = atof(record.at(6).c_str());
		colR = atof(record.at(7).c_str());
		colG = atof(record.at(8).c_str());
		colB = atof(record.at(9).c_str());
		intensidad = atof(record.at(10).c_str());

		ubicacionLuz = FVector(posX, posY, posZ);
		rotacionLuz = FRotator(rotX, rotY, rotZ);

		switch (tipoLuz){
			// Puntual
		case 1:
			actorLuz = Cast<ALuzPuntual>(World->SpawnActor<ALuzPuntual>(ALuzPuntual::StaticClass(), ubicacionLuz, FRotator(0, 0, 0)));
			break;
			// Direccional
		case 2:
			actorLuz = Cast<ALuzDireccional>(World->SpawnActor<ALuzDireccional>(ALuzDireccional::StaticClass(), ubicacionLuz, FRotator(0,0,0)));
			break;
			// Focal
		case 3:
			// Leo valores de angulos extra para este tipo de luz
			anguloConoInterior = atof(record.at(11).c_str());
			anguloConoExterior = atof(record.at(12).c_str());
			actorLuz = Cast<ALuzFocal>(World->SpawnActor<ALuzFocal>(ALuzFocal::StaticClass(), ubicacionLuz, FRotator(0, 0, 0)));
			luzFocal = Cast<ALuzFocal>(actorLuz);
			luzFocal->setAnguloConoInterior(anguloConoInterior);
			luzFocal->setAnguloConoExterior(anguloConoExterior);
			break;
		default:
			s = "Tipo de luz incorrecto: " + tipoLuz;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s.c_str());
			errorLuz = true;
		}
		if (!errorLuz){
			color = FLinearColor(colR, colG, colB);
			actorLuz->setColor(color);
			actorLuz->setIntensidad(intensidad);
			actorLuz->setRotacion(rotX,rotY,rotZ);
			lucesCreadas.Add(actorLuz);
		}
		luzProcesando++;
		// Agrego linea a registro de salida
		data.push_back(record);
	}
	if (!infile.eof())
	{
		cerr << "Fooey!\n";
	}
	return lucesCreadas;
}

