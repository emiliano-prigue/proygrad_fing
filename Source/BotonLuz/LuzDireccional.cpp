// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "LuzDireccional.h"

ALuzDireccional::ALuzDireccional(){
	// Modelo luz
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cargadorModelo(TEXT("/Game/Modelos/Lightbulb"));
	if (cargadorModelo.Succeeded()){
		modeloLuz->SetStaticMesh(cargadorModelo.Object);
	}
	// Luz
	luz = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Luz"));
	luz->AttachTo(modeloLuz);
	flechaX->AttachTo(modeloLuz);
	flechaY->AttachTo(modeloLuz);
	flechaZ->AttachTo(modeloLuz);
}


