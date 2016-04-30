
#include "BotonLuz.h"
#include "GuardarLuces.h"


AGuardarLuces::AGuardarLuces()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGuardarLuces::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardarLuces::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGuardarLuces::GuardarLucesArchivo()
{
	FString replaceIn = "/Saved/Config/Windows/Game.ini";
	FString replaceOut = "/archivoLucesGuardadas.txt";
	FString FilePath;
	FilePath = GGameIni.Replace(*replaceIn, *replaceOut);
	
	std::string fString(TCHAR_TO_UTF8(*FilePath));
	
	ofstream archivoLuces;
	archivoLuces.open(fString);

	int tipoLuz;
	for (TActorIterator<ALuz> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ALuz* Luz = *ActorItr;
		if (Luz->IsA(ALuzPuntual::StaticClass()))
		{
			tipoLuz = 1;
		}
		else if (Luz->IsA(ALuzDireccional::StaticClass()))
		{
			tipoLuz = 2;
		}
		else if (Luz->IsA(ALuzFocal::StaticClass()))
		{
			tipoLuz = 3;
		}

		FVector posicionLuz = Luz->GetActorLocation();
		FRotator rotaciónLuz = Luz->GetActorRotation();
		FLinearColor colorLuz = Luz->getColor();

		string caracteristicasFocal = "\n";
		
		if (tipoLuz == 3)
		{
			ALuzFocal* luzFocal = Cast<ALuzFocal>(Luz);
			
			float innerCone = luzFocal->getAnguloConoInterior();
			float outerCone = luzFocal->getAnguloConoExterior();
			
			archivoLuces << tipoLuz << ","
				<< posicionLuz.X << "," << posicionLuz.Y << "," << posicionLuz.Z
				<< rotaciónLuz.Roll << "," << rotaciónLuz.Pitch << "," << rotaciónLuz.Yaw
				<< colorLuz.R << "," << colorLuz.G << "," << colorLuz.B
				<< Luz->getIntensidad() << ","
				<< innerCone << "," << outerCone << "\n";
		}
		else
		{
			archivoLuces << tipoLuz << ","
				<< posicionLuz.X << "," << posicionLuz.Y << "," << posicionLuz.Z
				<< rotaciónLuz.Roll << "," << rotaciónLuz.Pitch << "," << rotaciónLuz.Yaw
				<< colorLuz.R << "," << colorLuz.G << "," << colorLuz.B
				<< Luz->getIntensidad() << "\n";
		}
	}

	archivoLuces.close();
}