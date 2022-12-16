#include "Ball.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABall::ABall() :
MoveForce(100.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	BallCollision = CreateDefaultSubobject<USphereComponent>("Ball Collision");
	BallMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Ball Mesh");
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");

	BallCollision->SetupAttachment(GetRootComponent());
	BallMesh->SetupAttachment(BallCollision);
	CameraBoom->SetupAttachment(BallCollision);
	Camera->SetupAttachment(CameraBoom);
	GunMesh->SetupAttachment(BallCollision);

	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bDoCollisionTest = false;

	BallCollision->SetSimulatePhysics(true);

}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	if(const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	BallPlayerController = Cast<ABallPlayerController>(Controller);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(BallPlayerController)
		Look();

}

void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABall::Move);
	}

}

void ABall::Move(const FInputActionValue& Value)
{
	const FVector2d Movement = Value.Get<FVector2d>();

	if(Controller)
	{
		BallCollision->AddForce(FVector(Movement.X, -Movement.Y, 0.0f)*MoveForce, NAME_None, true);
	}
}

void ABall::Look()
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
