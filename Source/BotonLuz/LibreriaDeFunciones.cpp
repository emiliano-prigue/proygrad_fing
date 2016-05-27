// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "LibreriaDeFunciones.h"

float ULibreriaDeFunciones::obtenerIntensidadLuz(ALight* luz){
	return luz->GetBrightness();
}

float ULibreriaDeFunciones::redondear(float aRedondear){
	return floorf(aRedondear * 100) / 100;
}

FRotator ULibreriaDeFunciones::obtenerRotacionDeComponente(ULightComponent* luz){
	return luz->GetComponentRotation();
}

void ULibreriaDeFunciones::grabarArchivoModelo(FString contenido){
	FString replaceIn = "/Saved/Config/Windows/Game.ini";
	FString replaceOut = "/Config/Model/modelname";
	FString FilePath;
	FilePath = GGameIni.Replace(*replaceIn, *replaceOut);

	std::string fString(TCHAR_TO_UTF8(*FilePath));

	ofstream archivoModelo;
	archivoModelo.open(fString);
	archivoModelo << TCHAR_TO_UTF8(*contenido);

	archivoModelo.close();
	}