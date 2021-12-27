// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCameraActor.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "BasePawn.h"
#include "TimerManager.h"
#include "Math/Color.h"


ASpyCameraActor::ASpyCameraActor()
{
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetBoxExtent(FVector(500.0f));
	BoxComp->SetCollisionObjectType(ECC_WorldStatic);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetupAttachment(GetRootComponent());
}

void ASpyCameraActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASpyCameraActor::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ASpyCameraActor::BoxEndOverlap);
}

void ASpyCameraActor::ChangeColor()

{
	 Mesh = BasePawn->FindComponentByClass<UStaticMeshComponent>();
	 Material = Mesh->GetMaterial(0);
	 DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
	 Mesh->SetMaterial(0, DynamicMaterial);
	 DynamicMaterial->SetScalarParameterValue("ChangeColor", 1.0f);
}


void ASpyCameraActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FFromSweep, const FHitResult& SweepResult)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	PC->SetViewTarget(this, TransitionParams);

	if ((BasePawn = Cast<ABasePawn>(OtherActor)) != nullptr)
	{
		GetWorldTimerManager().SetTimer(ChangeColorTimer, this, &ASpyCameraActor::ChangeColor, 5.0f, false);
	}
}


void ASpyCameraActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)

{
	if (Cast<ABasePawn>(OtherActor))
	{
		BasePawn = nullptr;
		if (GetWorldTimerManager().IsTimerActive(ChangeColorTimer))
		{
			GetWorldTimerManager().ClearTimer(ChangeColorTimer);
		}
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	PC->SetViewTarget(PC->GetPawn(), TransitionParams);
}

