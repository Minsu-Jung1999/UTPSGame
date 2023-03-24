// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerFire.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UPlayerFire : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:

	UPlayerFire();
	virtual void BeginPlay() override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* tpsCamComp;

	// �� ���̷�Ż�޽�
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class USkeletalMeshComponent* gunMeshComp;

	// �������۰� ����ƽ�޽� �߰�
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class UStaticMeshComponent* sniperGunComp;


	// �Ѿ� ����
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
		TSubclassOf<class ABullet> bulletFactory;

	// �Ѿ� �߻� ó�� �Լ�
	void InputFire();

	// ��ź�� ��� ������ ����
	bool bUsingGrenadeGun = true;
	// ��ź������ ����
	void ChangeToGrenadeGun();
	// �������۰����� ����
	void ChangeToSniperGun();

	// �������� ����
	void SniperAim();

	// �������� ���� ������ ����
	bool bSniperAim = false;

	// �������� UI ���� ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget> sniperUIFactory;

	// �������� UI ���� �ν��Ͻ�
	class UUserWidget* _sniperUI;

	// ī�޶� ����ũ �������Ʈ�� ������ ����
	UPROPERTY(EditDefaultsOnly, Category = CameraMotion)
		TSubclassOf<class UCameraShakeBase> cameraShake;

	// �Ѿ� ���� ȿ�� ����
	UPROPERTY(EditAnywhere, Category = BulletEffect)
		class UParticleSystem* bulletEffectFactory;

	// �Ϲ� ���� ũ�ν���� UI ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget> crosshairUIFactory;

	// ũ�ν���� �ν��Ͻ�
	class UUserWidget* _crosshairUI;

	// �Ѿ� �߻� ����
	UPROPERTY(EditDefaultsonly, Category = Sound)
		class USoundBase* bulletSound;

	
};
