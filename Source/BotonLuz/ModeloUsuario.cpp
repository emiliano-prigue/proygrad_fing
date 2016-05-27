// Fill out your copyright notice in the Description page of Project Settings.


#include "BotonLuz.h"
#include "ModeloUsuario.h"


// Sets default values
AModeloUsuario::AModeloUsuario()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	errorCargaModelo = false;

	// Carga del material
	static ConstructorHelpers::FObjectFinder<UMaterial> MatObj(TEXT("Material'/Game/Materiales/MaterialEjemplo.MaterialEjemplo'"));
	if (MatObj.Succeeded()){
		BaseMat = MatObj.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MatVidrio(TEXT("Material'/Game/Materiales/M_Glass2.M_Glass2'"));
	if (MatVidrio.Succeeded()){
		MaterialVidrio = MatVidrio.Object;
	}

	FString replaceIn = "/Saved/Config/Windows/Game.ini";
	FString replaceOut = "/Config/Model/modelname";
	FString FilePath;
	FilePath = GGameIni.Replace(*replaceIn, *replaceOut);
	std::string fString(TCHAR_TO_UTF8(*FilePath));
	ifstream infile(fString);
	string s;
	if (!getline(infile, s)){
		return;
	}
	string ruta = "/Game/Modelos/" + s;
	const TCHAR* rutaConst = UTF8_TO_TCHAR(ruta.c_str());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cargadorModelo(rutaConst);

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
		modeloNuevo->Materials.Add(MaterialVidrio);
	}

	TArray<FText> BuildErrorsNuevo;
	modeloNuevo->Build(true, &BuildErrorsNuevo);
	modeloNuevo->MarkPackageDirty();

	// Asigno nuevo modelo
	modeloActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloActor"));
	modeloActor->SetStaticMesh(modeloNuevo);

	//string s = "Entra al constructor";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s.c_str());

}

void AModeloUsuario::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!errorCargaModelo && BaseMat){
		// Apertura de archivo de colores de los poligonos
		FString replaceIn = "/Saved/Config/Windows/Game.ini";
		FString replaceOut = "/coloresPoligonos.cvs";
		FString FilePath;
		FilePath = GGameIni.Replace(*replaceIn, *replaceOut);

		std::string fString(TCHAR_TO_UTF8(*FilePath));

		ifstream colores(fString);
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

//Recargo Materiales
void AModeloUsuario::RecargarMateriales()
{
	if (!errorCargaModelo && BaseMat){
		//ofstream archivoLuces;
		//double total = 0;
		//Abro el archivo
		//FString replaceInWrite = "/Saved/Config/Windows/Game.ini";
		//FString replaceOutWrite = "/archivoTiempoEjecucion.txt";
		//FString FilePathWrite;
		//FilePathWrite = GGameIni.Replace(*replaceInWrite, *replaceOutWrite);
		//std::string fStringWrite(TCHAR_TO_UTF8(*FilePathWrite));
		//archivoLuces.open(fStringWrite, std::ios_base::app);


		//Arranco el cálculo del tiempo de ejecución
		std::chrono::time_point<std::chrono::system_clock> startC, endC;
		startC = std::chrono::system_clock::now();
		//clock_t start = clock();
		//double duration;
		// Apertura de archivo de colores de los poligonos
		FString replaceIn = "/Saved/Config/Windows/Game.ini";
		FString replaceOut = "/coloresPoligonos.cvs";
		FString FilePath;
		FilePath = GGameIni.Replace(*replaceIn, *replaceOut);

		std::string fString(TCHAR_TO_UTF8(*FilePath));

		ifstream colores(fString);
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

		//Calculo el timpo de ejecución
		endC = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = endC - startC;
		std::time_t end_time = std::chrono::system_clock::to_time_t(endC);
		//double end = clock();
		//duration = (end - start);
		double cps = (double)CLOCKS_PER_SEC;
		//duration = duration/cps;

		//Escribo en archivo
		//archivoLuces.precision(10);
		//archivoLuces << elapsed_seconds.count() << "\n";

		//archivoLuces.close();
	}
}

// Called when the game starts or when spawned
void AModeloUsuario::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModeloUsuario::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

}

