// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "LuzFocal.h"

ALuzFocal::ALuzFocal(){
	// Tipo de luz
	tipoDeLuz = "Focal";
	// Modelo luz
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cargadorModelo(TEXT("/Game/Modelos/Lightbulb"));
	if (cargadorModelo.Succeeded()){
		modeloLuz->SetStaticMesh(cargadorModelo.Object);
	}
	// Luz
	luz = CreateDefaultSubobject<USpotLightComponent>(TEXT("Luz"));
	luz->AttachTo(modeloLuz);
	flechaX->AttachTo(modeloLuz);
	flechaY->AttachTo(modeloLuz);
	flechaZ->AttachTo(modeloLuz);
}

void ALuzFocal::setAnguloConoInterior(float parAngulo){
	USpotLightComponent* spotLight = Cast<USpotLightComponent>(luz);
	spotLight->SetInnerConeAngle(parAngulo);
}

void ALuzFocal::setAnguloConoExterior(float parAngulo){
	USpotLightComponent* spotLight = Cast<USpotLightComponent>(luz);
	spotLight->SetOuterConeAngle(parAngulo);
}

