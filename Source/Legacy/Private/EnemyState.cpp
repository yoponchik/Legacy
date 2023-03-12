// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyState.h"

#include "Enemy.h"
#include "EnemyFSM.h"
#include "LegacyPlayer.h"
#include "AIController.h"
#include "EnemyAnim.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UEnemyState::UEnemyState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyState::BeginPlay()
{
	Super::BeginPlay();

	// Enemy 접근할 일이 많을테니 캐싱
	me = Cast<AEnemy>(GetOwner());
	// player 캐스팅
	player = Cast<ALegacyPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}


// Called every frame
void UEnemyState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bReadyToAir && bIsGrabbed)
	{
		me->enemyFSM->bIsInTheAir = true;
		bReadyToAir = false;
	}

	if (!bReadyToAir && !bIsGrabbed)
	{
		// bIsInTheAir 끄는건 바닥에 떨어졌을 때
		bReadyToAir = true;
	}
}

void UEnemyState::OnDamageProcess(int amount)
{
	// 데미지 빼고
	hp = hp - amount;
	// damage state (애님 재생 등)
	me->enemyFSM->SetState(EEnemyState::DAMAGE);
	// 잘 됨 (죽음 처리 필요)
	//me->PlayAnimMontage(me->enemyFSM->enemyAnim->montage_Paladin, 1, FName("Die"));
	me->PlayAnimMontage(me->enemyFSM->enemyAnim->montage_Paladin, 1, FName("Damage"));
}

void UEnemyState::Throw(FVector force, int Amount)
{
	// 데미지 계산
	OnDamageProcess(Amount);
	// 날려버리자
	me->GetCapsuleComponent()->AddForce(force * mass);

	// 랜덤하게 로테이션 변경
	int p = FMath::RandRange(0, 360);
	int y = FMath::RandRange(0, 360);
	int r = FMath::RandRange(0, 360);
	me->SetActorRotation(FRotator(p, y, r));

}

void UEnemyState::SetOriginalPhysicsState()
{
	me->enemyFSM->bIsInTheAir = false;
	me->GetCapsuleComponent()->SetSimulatePhysics(false);
	me->SetActorRotation(FRotator::ZeroRotator);
	me->enemyFSM->SetState(EEnemyState::IDLE);
}

