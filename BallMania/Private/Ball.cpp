#include "Ball.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ABall::ABall() :
MoveForce(100.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	BallCollision = CreateDefaultSubobject<USphereComponent>("Ball Collision");
	BallMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Ball Mesh");
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	BallCollision->SetupAttachment(GetRootComponent());
	BallMesh->SetupAttachment(BallCollision);
	CameraBoom->SetupAttachment(BallCollision);
	Camera->SetupAttachment(CameraBoom);

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
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
