// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "ModeloSponzaForEditMode.h"


// Sets default values
AModeloSponzaForEditMode::AModeloSponzaForEditMode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	errorCargaModelo = false;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MatVidrio(TEXT("Material'/Game/StarterContent/Materials/M_Glass.M_Glass'"));
	if (MatVidrio.Succeeded()){
		MaterialVidrio = MatVidrio.Object;
	}

	// Carga del material
	static ConstructorHelpers::FObjectFinder<UMaterial> MatObj(TEXT("Material'/Game/StarterContent/Materials/M_Concrete_Tiles.M_Concrete_Tiles'"));
	if (MatObj.Succeeded()){
		BaseMat = MatObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cargadorModelo(TEXT("/Game/Modelos/sponzaForRadiosity2"));
	UStaticMesh* modelo;
	if (cargadorModelo.Succeeded()){
		modelo = cargadorModelo.Object;
	}
	else {
		errorCargaModelo = true;
		return;
	}

	if (!modelo->IsValidLowLevel()){
		errorCargaModelo = true;
		return;
	}
	if (&modelo->SourceModels[0] == nullptr){
		errorCargaModelo = true;
		return;
	}

	FStaticMeshSourceModel* sourceModel = &modelo->SourceModels[0];
	FRawMesh rawMesh;
	sourceModel->RawMeshBulkData->LoadRawMesh(rawMesh);
	int32 cantTriangles = rawMesh.FaceMaterialIndices.Max();
	for (int32 i = 0; i < rawMesh.FaceMaterialIndices.Num(); i++){
		rawMesh.FaceMaterialIndices[i] = i;
	}

	// Creo nuevo modelo
	UStaticMesh* modeloNuevo = NewObject<UStaticMesh>();
	new(modeloNuevo->SourceModels) FStaticMeshSourceModel();
	modeloNuevo->SourceModels[0].RawMeshBulkData->SaveRawMesh(rawMesh);

	for (int32 i = 0; i < rawMesh.FaceMaterialIndices.Num(); i++){
		modeloNuevo->Materials.Add(BaseMat);
	}

	TArray<FText> BuildErrorsNuevo;
	modeloNuevo->Build(true, &BuildErrorsNuevo);
	modeloNuevo->MarkPackageDirty();

	// Asigno nuevo modelo
	modeloActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloActorForEditMode"));
	modeloActor->SetStaticMesh(modeloNuevo);

	//string s = "Entra al constructor";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s.c_str());*/
}

void AModeloSponzaForEditMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!errorCargaModelo){
		// Apertura de archivo de colores de los poligonos
		ifstream colores("D:\\Facultad\\Proyecto de grado\\RepoLimpio\\trunk\\coloresPoligonos-sponza.cvs");
		// Color auxiliar
		FLinearColor color;
		// Componentes del color
		float r;
		float g;
		float b;
		// Si las componentes del archivo son -1 entonces el material a asignar es vidrio
		float vidrio = -1;
		// Indice de recorrida del archivo
		int idPoligono = 0;
		// Lectura de arhivo de colores, creacion de materiales dinamicos y asignacion en el modelo
		while (colores)
		{
			string s;
			if (!getline(colores, s)) break;
			istringstream ss(s);
			vector <string> record;
			// Loop de datos de cada linea
			while (ss)
			{
				string s;
				if (!getline(ss, s, ',')) break;
				record.push_back(s);
			}
			// Cargo valores de las componentes a variables
			r = atof(record.at(0).c_str());
			g = atof(record.at(1).c_str());
			b = atof(record.at(2).c_str());
			if (r == vidrio){
				modeloActor->SetMaterial(idPoligono, MaterialVidrio);
			}

			idPoligono++;
		}
	}
}

//Recargo Materiales
void AModeloSponzaForEditMode::RecargarMateriales()
{
	if (!errorCargaModelo){
		// Apertura de archivo de colores de los poligonos
		ifstream colores("D:\\Facultad\\Proyecto de grado\\RepoLimpio\\trunk\\coloresPoligonos-sponza.cvs");
		// Color auxiliar
		FLinearColor color;
		// Componentes del color
		float r;
		float g;
		float b;
		// Si las componentes del archivo son -1 entonces el material a asignar es vidrio
		float vidrio = -1;
		// Indice de recorrida del archivo
		int idPoligono = 0;
		// Lectura de arhivo de colores, creacion de materiales dinamicos y asignacion en el modelo
		while (colores)
		{
			string s;
			if (!getline(colores, s)) break;
			istringstream ss(s);
			vector <string> record;
			// Loop de datos de cada linea
			while (ss)
			{
				string s;
				if (!getline(ss, s, ',')) break;
				record.push_back(s);
			}
			// Cargo valores de las componentes a variables
			r = atof(record.at(0).c_str());
			g = atof(record.at(1).c_str());
			b = atof(record.at(2).c_str());
			if (r != vidrio){
				// Creo y agrego material a la lista del modelo
				MaterialInst = UMaterialInstanceDynamic::Create(BaseMat, this);
				modeloActor->SetMaterial(idPoligono, MaterialInst);
				color = FLinearColor(r, g, b);
				MaterialInst->SetVectorParameterValue("baseColor", color);
				modeloActor->SetMaterial(idPoligono, MaterialInst);
			}
			else {
				// Agrego vidrio a la lista de materiales
				modeloActor->SetMaterial(idPoligono, MaterialVidrio);
			}

			idPoligono++;
		}
	}
}

// Called when the game starts or when spawned
void AModeloSponzaForEditMode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModeloSponzaForEditMode::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

