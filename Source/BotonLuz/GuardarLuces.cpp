
#include "BotonLuz.h"
#include "GuardarLuces.h"

void UGuardarLuces::GuardarLucesArchivo(UObject* Context)
{
	FString replaceIn = "/Saved/Config/Windows/Game.ini";
	FString replaceOut = "/archivoLucesGuardadas.txt";
	FString FilePath;
	FilePath = GGameIni.Replace(*replaceIn, *replaceOut);
	
	std::string fString(TCHAR_TO_UTF8(*FilePath));
	
	ofstream archivoLuces;
	archivoLuces.open(fString);

	int tipoLuz = 1;
	for (TActorIterator<ALuz> ActorItr(GEngine->GetWorldFromContextObject(Context)); ActorItr; ++ActorItr)
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
		FRotator rotaci�nLuz = Luz->GetActorRotation();
		FLinearColor colorLuz = Luz->getColor();

		string caracteristicasFocal = "\n";
		
		if (tipoLuz == 3)
		{
			ALuzFocal* luzFocal = Cast<ALuzFocal>(Luz);
			
			float innerCone = luzFocal->getAnguloConoInterior();
			float outerCone = luzFocal->getAnguloConoExterior();
			
			archivoLuces << tipoLuz << ","
				<< posicionLuz.X << "," << posicionLuz.Y << "," << posicionLuz.Z << ","
				<< Luz->rotX << "," << Luz->rotY << "," << Luz->rotZ << ","
				<< colorLuz.R << "," << colorLuz.G << "," << colorLuz.B << ","
				<< Luz->getIntensidad() << ","
				<< innerCone << "," << outerCone << "\n";
		}
		else
		{
			archivoLuces << tipoLuz << ","
				<< posicionLuz.X << "," << posicionLuz.Y << "," << posicionLuz.Z << ","
				<< Luz->rotX << "," << Luz->rotY << "," << Luz->rotZ << ","
				<< colorLuz.R << "," << colorLuz.G << "," << colorLuz.B << ","
				<< Luz->getIntensidad() << "\n";
		}
	}

	archivoLuces.close();
}