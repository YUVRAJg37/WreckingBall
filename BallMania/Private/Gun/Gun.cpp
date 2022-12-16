#include "Gun/Gun.h"

#include "BallPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	GunCollisionLeft = CreateDefaultSubobject<UBoxComponent>("Gun Collision Left");
	GunCollisionRight = CreateDefaultSubobject<UBoxComponent>("Gun Collision Right");
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	PickUpCollision = CreateDefaultSubobject<USphereComponent>("Pick Up Collision");

	SetRootComponent(Root);
	GunCollisionLeft->SetupAttachment(Root);
	GunCollisionRight->SetupAttachment(Root);
	GunMesh->SetupAttachment(Root);
	PickUpCollision->SetupAttachment(Root);
	
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	BallPlayerController = Cast<ABallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Root->SetAbsolute(false, true, false);
	GunCollisionLeft->SetAbsolute(false, true, false);
	GunCollisionRight->SetAbsolute(false, true, false);
	GunMesh->SetAbsolute(false, true, false);
	PickUpCollision->SetAbsolute(false, true, false);

}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(BallPlayerController)
	{}
		//Look();

}

void AGun::Look()
{
	FHitResult HitResult;
	BallPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if(HitResult.bBlockingHit)
	{
		const FRotator GunLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GunMesh->GetComponentLocation(), HitResult.ImpactPoint);
		const FRotator NewRotation = FRotator(GunMesh->GetComponentRotation().Pitch, GunLookAtRotation.Yaw, GunMesh->GetComponentRotation().Roll);
		GunMesh->SetWorldRotation(NewRotation);
	}
}
