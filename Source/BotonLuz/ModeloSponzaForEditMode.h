// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "GameFramework/Actor.h"
#include "UnrealEd.h"
#include "Developer/RawMesh/Public/RawMesh.h"
#include "Runtime/Engine/Public/StaticMeshResources.h"
#include "GameFramework/Actor.h"
#include "ModeloSponzaForEditMode.generated.h"

using namespace std;

UCLASS()
class BOTONLUZ_API AModeloSponzaForEditMode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AModeloSponzaForEditMode();

	//Recargo Materiales
	UFUNCTION(BlueprintCallable, Category = "Funciones Auxiliares")
	void RecargarMateriales();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(Category = StaticMeshActor, VisibleAnywhere, BlueprintReadOnly,
		Meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))
		UStaticMeshComponent * modeloActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterial* BaseMat;

	// Eliminar este atributo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterial* MaterialVidrio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterialInstanceDynamic* MaterialInst;

	bool errorCargaModelo;
	
};
