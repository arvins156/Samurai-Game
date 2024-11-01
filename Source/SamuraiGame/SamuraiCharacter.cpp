// Fill out your copyright notice in the Description page of Project Settings.

#include "SamuraiCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Katana.h"

#include "Components/CapsuleComponent.h"
#include "SamuraiGameGameMode.h"

// Sets default values
ASamuraiCharacter::ASamuraiCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create the follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void ASamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Katana = GetWorld()->SpawnActor<AKatana>(KatanaClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Katana->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Katana->SetOwner(this);

}

bool ASamuraiCharacter::IsDead() const
{
	return Health <= 0;
}

float ASamuraiCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void ASamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check for the TargetLock Actor to change the Controller Control Rotation
	if (TargetLockActor) {
		UE_LOG(LogTemp, Warning, TEXT("TargetFound"));
		//Here we want to make sure that the camera is always pointed at the actor
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) {
			FVector TargetLocation = TargetLockActor->GetActorLocation();
			FVector PlayerForwardVector = this->GetActorLocation();
			FRotator LookAtTargetRow = UKismetMathLibrary::FindLookAtRotation(PlayerForwardVector, TargetLocation);
			PlayerController->SetControlRotation(LookAtTargetRow);
			UE_LOG(LogTemp, Warning, TEXT("Rotated"));
		}
	}
}

// Called to bind functionality to input
void ASamuraiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Call the parent version
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto EISubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	// Clear out existing mapping, add our mapping
	EISubSystem->ClearAllMappings();
	// Add the input mapping context
	EISubSystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PlayerEIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerEIComponent != nullptr) {

		// Bind the actions
		//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
		//ETriggerEvent is an enum, where Triggered means "button is held down"

		UE_LOG(LogTemp, Warning, TEXT("PEI WORKED."));
		PlayerEIComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ASamuraiCharacter::Move);
		PlayerEIComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ASamuraiCharacter::Look);
		PlayerEIComponent->BindAction(InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		PlayerEIComponent->BindAction(InputShoot, ETriggerEvent::Started, this, &ASamuraiCharacter::Attack);
		PlayerEIComponent->BindAction(InputTargetLock, ETriggerEvent::Started, this, &ASamuraiCharacter::TargetLock);
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PEI FAILED."));
	}
}

float ASamuraiCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead()) {

		ASamuraiGameGameMode* GameMode = GetWorld()->GetAuthGameMode<ASamuraiGameGameMode>();
		if (GameMode != nullptr) {

			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void ASamuraiCharacter::Move(const FInputActionValue& Value) {

	//UE_LOG(LogTemp, Warning, TEXT("Moved"));

	// Directional movement

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	// Previous movement implementation:

	// const FVector2D MovementVector = Value.Get<FVector2D>();
	// const FVector Forward = GetActorForwardVector();
	// const FVector Right = GetActorRightVector();

	// AddMovementInput(Forward, MovementVector.Y);
	// AddMovementInput(Right, MovementVector.X);
}

void ASamuraiCharacter::Look(const FInputActionValue& Value) {

	//UE_LOG(LogTemp, Warning, TEXT("Looked"));

	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASamuraiCharacter::Attack()
{
	Katana->PullTrigger();
}

void ASamuraiCharacter::TargetLock()
{
	UE_LOG(LogTemp, Warning, TEXT("TargetLockCalled"));
	if (TargetLockActor) {
		//Get rid of TargetLockActor
		TargetLockActor = nullptr;
	}
	else {
		APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
		if (PlayerController) {
			APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
			check(CameraManager);
			//Creates the startlocation as slightly above the character, and traces towards where the camera is facing
			USceneComponent* TransformComponent = CameraManager->GetTransformComponent();
			FVector StartLocation = TransformComponent->GetComponentLocation();
			StartLocation.Z += 70.0f;
			//Gets the location in front and 1500 units in front of player
			FVector ForwardVector = TransformComponent->GetForwardVector();
			ForwardVector *= 1500.0f;
			FVector EndLocation = ForwardVector + StartLocation;
			float SphereRadius = 200.0f;

			//Trace for Pawns
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
			ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
			//Ignore Owner in trace
			TArray<AActor*> IgnoreActors;
			IgnoreActors.Add(this);
			FHitResult OutHit;

			//Traces in a sphere shape ahead of character to and end point find actors, storing the first found actor in OutHit
			bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
				GetWorld(),
				StartLocation,
				EndLocation,
				SphereRadius,
				ObjectTypesArray,
				false,
				IgnoreActors,
				EDrawDebugTrace::ForDuration,
				OutHit,
				true
			);
			//When we hit something and it is a Actor, bind the TargetLockActor to it
			if (bHit && Cast<AActor>(OutHit.GetActor()))
			{
				TargetLockActor = OutHit.GetActor();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Hit"));
			}
		}
	}

}


